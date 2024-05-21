import matplotlib.pyplot as plt
import numpy as np
import sys

rT = np.loadtxt("data.txt", delimiter="|")
TRACE_SIZE = rT[0].size
N_ACTIONS = 9
THRESHOLD = 22
ONLY_CONTENTION = 1
CONTENTION = 0  

# Transform latency in "Yes or No" contention
def transf_cont(T):
    T = rT
    for i in range(0,N_ACTIONS):
        for j in range(TRACE_SIZE):
            #skip this step if the file is already configured in binary format
            if(rT[i][j] > 1): 
                T[i][j] = 1 if (rT[i][j] > THRESHOLD) else 0
    return T

def detect_contention(rT, only_contention):
    pT_aux = np.zeros(( N_ACTIONS*2,TRACE_SIZE))
    T = transf_cont(rT)
    i = 0
    for action in range(1,N_ACTIONS):
        i = 0
        for clk in range(TRACE_SIZE):
            if (T[0][clk]!=T[action][clk]):
                if only_contention == 1:
                    #only contention clock cycles
                    if T[action][clk] != 0: 
                        if (i < TRACE_SIZE): 
                            pT_aux[action*2][i] = clk
                            pT_aux[action*2+1][i] = T[action][clk]
                        else: 
                            print("(Prune) Out of bounds")
                            break    
                        i = i + 1   
                else:
                    #all clock cycles stay, with contention or not
                    if (i < TRACE_SIZE): 
                        pT_aux[action*2][i] = clk
                        pT_aux[action*2+1][i] = T[action][clk]
                    else: 
                        print("(Prune) Out of bounds")
                        break      
                    i = i + 1  
    return pT_aux

def prune_contention(T):
    pT_aux = np.zeros((N_ACTIONS,TRACE_SIZE))
    index = 0
    for action in range(2,N_ACTIONS*2,2):
        if (index < N_ACTIONS-1): 
            pT_aux[index] = T[action]
        index += 1
    return pT_aux

def pad(A, length):
    arr = np.zeros(length)
    arr[:len(A)] = A
    return arr

def prune_clocks(T):
    pT_aux = np.zeros((N_ACTIONS-1,TRACE_SIZE))
    for action in range(N_ACTIONS-2):
        pT_aux[action] = pad(np.setdiff1d(T[action], T[action+1]),TRACE_SIZE)
    #remove the elements in last action that are present in action - 1 
    pT_aux[N_ACTIONS-2] = pad(np.setdiff1d(T[N_ACTIONS-2], T[N_ACTIONS-3]),TRACE_SIZE)
    return pT_aux

def prune_overlapping(pT, pT_aux):
    for action in range(N_ACTIONS-2):
        for clk in range(TRACE_SIZE):
            if pT[action][clk] >= pT[action+1][0]:
                pT[action][clk] = 0 
            if action == N_ACTIONS-3:
                # The difference should be bigger, this check is to correct the
                # last it in pT
                if pT[action+1][0] - pT[action][0] < 100: 
                    pT[action+1] = pad(pT[action+1][1:],TRACE_SIZE)
                # The last actions needs different handling to include all the 
                # clocks excluded from (last action - 1) and (last action)
                i = np.where(pT_aux[action+1] == pT[action+1][0])[0][0]
                pT[action+1] =  pad(pT_aux[action+1][i:],TRACE_SIZE)
    return pT

# clk A1    clk A2    clk A3    clk  A4
# xx  1      xx  0     xx  0    xx    1
# xx  0      xx  1     xx  1    xx    0
# xx  1      xx  0     xx  1    xx    0
# xx  0      xx  1     xx  0    xx    1
#
# This function needs a base action to serve as control
# 1 - All the Actions are compared against the base control action 
# 2 - For each actions, it is saved the clocks that are different compared to the 
# the base action
# 3 - All actions are pruned to hold just the clocks with contention (No 
# contention also gives us information, but we are interested only in the 
# clocks with contention )
# 4 - Last setp, the duplicated clocks between action traces are deleted. 
#  
# This function returns only the clocks with contention 
def prune_all_actions_with_contention():
    pT_aux_1 = np.zeros(( N_ACTIONS*2,TRACE_SIZE))
    
    pT_aux_1 = detect_contention(rT, ONLY_CONTENTION)
    
    # Stay only with the clocks, remove the column identifying the contention
    pT_aux_2 = np.zeros((N_ACTIONS,TRACE_SIZE))
    pT_aux_2 = prune_contention(pT_aux_1)

    # return pT_aux_1
    
    # remove duplicate clocks between actions
    pT = np.zeros((N_ACTIONS-1,TRACE_SIZE))
    pT = prune_clocks(pT_aux_2)

    # prune overlapping clocks 
    # this give us uniques contention points per action where we can unequivocally 
    # identify the action
    pT = prune_overlapping(pT, pT_aux_2)
    return pT


def add_contention_column(pT, pT_aux_1):
    # remove pt_aux_1[0] and pt_aux_1[1] 
    pT_aux_1 = np.delete(pT_aux_1, (0,1), axis=0)

    # compare matrix pt_aux_1 with pT and store the clocks that are equal
    pT_aux_2 = np.zeros(( N_ACTIONS*2,TRACE_SIZE))
    for action in range(N_ACTIONS-1):
        index = 0
        for clk in range(TRACE_SIZE):
            if pT[action][clk] != 0:
                for i in range(TRACE_SIZE):
                    if pT[action][clk] == pT_aux_1[2*action][i]:
                        pT_aux_2[2*action][index] = pT_aux_1[2*action][i]
                        pT_aux_2[2*action+1][index] = pT_aux_1[2*action+1][i]
                        index = index + 1
    
    # Calculate the size of all pT columns and store in a vector
    size = np.zeros((N_ACTIONS-1))
    for action in range(N_ACTIONS-1):
        size[action] = np.count_nonzero(pT[action])
    
    # Calculate the size of the smallest column
    min_size = min(size)
    
    # remove rows clk > min_size
    # copy pT_aux_2[N_ACTIONS][clk] to pT_aux_3[N_ACTIONS][min_size]  
    pT_aux_3 = np.zeros(((N_ACTIONS-1)*2,min_size.astype(int)))
    for action in range((N_ACTIONS-1)*2):
        for clk in range(min_size.astype(int)):
            pT_aux_3[action][clk] = pT_aux_2[action][clk]
            
    return pT_aux_3

# This function is similar with  prune_all_actions_with_contention, but returns
# all unique clocks for each action, with and without contention 
def prune_all_actions():
    #pT_aux_1[N_ACTIONS*2][TRACE_SIZE] 
    pT_aux_1 = detect_contention(rT, CONTENTION)
    
    # Stay only with the clocks, remove the column identifying the contention
    #pT_aux_1[N_ACTIONS][TRACE_SIZE] 
    pT_aux_2 = prune_contention(pT_aux_1)
    
    # remove duplicate clocks between actions
    #pT_aux_1[N_ACTIONS-1][TRACE_SIZE] 
    pT_aux_3 = prune_clocks(pT_aux_2)

    # prune overlapping clocks 
    # this give us uniques contention points per action where we can unequivocally 
    # identify the action
    pT_aux_3 = prune_overlapping(pT_aux_3, pT_aux_2)
    
    # Add contention column to the matrix
    pT = add_contention_column(pT_aux_3, pT_aux_1)
    
    return pT

def diff_matrix(T):
    dT = np.zeros((N_ACTIONS-2,TRACE_SIZE))
    for action in range(N_ACTIONS-2):
        dT[action] = pad(np.subtract(T[action+1], T[action]),TRACE_SIZE)
    return dT

def profiling():
    pT = prune_all_actions_with_contention() #gives unique points of contention for each action
    dT = diff_matrix(pT)
    nonzero = np.count_nonzero(dT[0])    
    T = np.zeros(((N_ACTIONS-1)*2,nonzero))
    for i in range(N_ACTIONS-2):
        T[i*2] = pT[i][:nonzero]
        T[i*2+1] = dT[i][:nonzero]
    T[(N_ACTIONS-2)*2] = pT[N_ACTIONS-2][:nonzero]
    #Print to file the matrix with contention clocks + differences in between actions
    np.savetxt("data_out.txt", np.transpose(pT), delimiter=" ", fmt = '%5i',
                header="A0          A1          A2          A3          A4          A5          A6          A7")

def profiling_all():
    pT = prune_all_actions() #gives unique points of contention for each action
    #Print to file the matrix with contention clocks + differences in between actions
    np.savetxt("data_out.txt", pT, delimiter=" ", fmt = '%5i')
    # np.savetxt("data_out.txt", np.transpose(pT), delimiter=" ", fmt = '%5i')
#------------------------------------------------------------------------------

def build_trace(rT):
    pT_aux = np.zeros(( N_ACTIONS*2,TRACE_SIZE))
    T = transf_cont(rT)
    for action in range(0,N_ACTIONS):
        for clk in range(TRACE_SIZE):
                pT_aux[action*2][clk] = clk
                pT_aux[action*2+1][clk] = T[action][clk]
    return pT_aux

def trace():
    T = np.zeros(( N_ACTIONS*2,TRACE_SIZE))
    T = build_trace(rT)
    np.savetxt("data_out.txt", T, delimiter=" ", fmt = '%5i')

if len(sys.argv) < 3:
    print("Usage: python profile.py [option] [N_ACTIONS]")
    print("Options:")
    print("  - prof_only_contention: Return unique clocks for each action (only considering contention)")
    print("  - prof_all: Return unique clocks for each action (with and without contention)")
    print("  - trace: Generate trace with unique clocks for each action")
else:
    # Return unique clocks for each action (only considering contention)
    # one column per action with the unique clocks plus diff in time between actions
    if sys.argv[1] == "prof_only_contention":
        N_ACTIONS = int(sys.argv[2])
        profiling()

    # Return unique clocks for each action (with and without contention)
    # one column per action with the unique clocks and 0 or 1 indicating contention
    if sys.argv[1] == "prof_all":
        N_ACTIONS = int(sys.argv[2])
        profiling_all()

    if sys.argv[1] == "trace":
        N_ACTIONS = int(sys.argv[2])
        trace()
