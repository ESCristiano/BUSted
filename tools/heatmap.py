import sys
import numpy as np
import seaborn as sns
import matplotlib.pyplot as plt 
from   matplotlib.colors import LinearSegmentedColormap
from   matplotlib.ticker import (MultipleLocator, AutoMinorLocator)

def image_size(x, y):
    x_size_inchs = x
    y_size_inchs = y
    f, ax = plt.subplots(figsize=(x_size_inchs, y_size_inchs))
    sns.set(font_scale=1.5)
    return f, ax

def define_pallette(color1, color2):
    low_color = color1
    high_color = color2
    colors = [low_color, high_color] 
    colors_r = [high_color, low_color] 
    my_cmap = LinearSegmentedColormap.from_list('Custom', colors, len(colors))
    my_cmap_r = LinearSegmentedColormap.from_list('Custom', colors_r, len(colors))
    return my_cmap, my_cmap_r

def trace():
    # Create a matrix initialized with zeros
    PATHS=16
    Size = 1500
    T = np.zeros((PATHS, Size))
    rT = np.loadtxt("data.txt", delimiter="|")
    # f, ax = image_size(6, 6)
    
    Start = 0
    End = Size
    #copy rT to T
    for i in range(PATHS):
        for j in range(Start,End):
            T[i][j-Start] = rT[i][j]

    my_cmap, my_cmap_r = define_pallette("white", "black")
    
    fig = plt.figure(constrained_layout=True)
    fig.set_size_inches(12, 6)
    axs = fig.subplots(ncols=2)
    
    sns.heatmap(
                np.transpose(T), 
                cbar=False,
                yticklabels=100,
                vmin=0,
                vmax=1,
                ax=axs[0],
                cbar_kws={"shrink": .5},
                cmap=my_cmap) 

    sns.heatmap(
                np.transpose(T), 
                cbar=False,
                yticklabels=100,
                vmin=0,
                vmax=1,
                ax=axs[1],
                cbar_kws={"shrink": .5},
                cmap=my_cmap_r) 

    # plt.ylabel('Clock Cycle',fontsize=18)
    # plt.xlabel('Key',fontsize=18)

    # Set the colorbar labels
    # colorbar = ax.collections[0].colorbar
    # colorbar.set_ticks([0.25,0.75]) # Put at the middle of the two colors
    # colorbar.set_ticklabels(['0', '1'])

    plt.savefig('SAM_trace.pdf')  
    plt.show()
    
def pruned_matrix():
    data = np.loadtxt("data_out.txt")
    # count the number of elements of data[0]
    Size = int(len(data[0]))
    # Size = int(len(data[0])/2) # half pruned matrix for visualization
    PATHS = int(len(data))
    
    f, ax = image_size(4,  14)
    my_cmap, my_cmap_r = define_pallette("#E2DEDE", "#FFC6C0") #
    
    # copy even rows of data to rT
    rT = np.zeros((int(PATHS/2), Size))
    for i in range(int(PATHS/2)):
        for j in range(Size):
            rT[i][j] = data[i*2+1][j]
    
    cont = np.zeros((int(PATHS/2), Size))
    for i in range(int(PATHS/2)):
        for j in range(Size):
            cont[i][j] = data[i*2][j]
    
    test = np.zeros((1,Size))
    test = cont
    test = test.astype(int)
    sns.heatmap(
                np.transpose(rT), 
                cbar=False,
                yticklabels=False, 
                xticklabels=1,
                # square=True,
                annot=np.transpose(test),
                annot_kws={"size": 8},
                fmt="d",
                vmin=0,
                vmax=1,
                linewidth=0.3, linecolor="white",
                cbar_kws={"shrink": .5},
                cmap=my_cmap) 
    
    plt.xlabel('Key',fontsize=12)
    plt.ylabel('Clock Cycle',fontsize=12)
    plt.show()

def pruned_matrix_isolate_paths():
    data = np.loadtxt("data_out.txt")
    # count the number of elements of data[0]
    Size = int(len(data[0]))
    # Size = int(len(data[0])/2) # half pruned matrix for visualization
    PATHS = int(len(data))
    
    # fig = image_size(6, 12)
    my_cmap, my_cmap_r = define_pallette("#595555", "#E2DEDE") #
    
    # copy even rows of data to rT
    rT = np.zeros((int(PATHS/2), Size))
    for i in range(int(PATHS/2)):
        for j in range(Size):
            rT[i][j] = data[i*2+1][j]
            
    cont = np.zeros((int(PATHS/2), Size))
    for i in range(int(PATHS/2)):
        for j in range(Size):
            cont[i][j] = data[i*2][j]
            
    # convert cont to int
    cont = cont.astype(int)
    
    fig = plt.figure(constrained_layout=True)
    fig.set_size_inches(6, 10)
    axs = fig.subplots(ncols=int(PATHS/2))
    
    keys = np.zeros((int(PATHS/2), 1))
    for i in range(int(PATHS/2)):
        keys[i][0] = i
        
     # convert keys to int
    keys = keys.astype(int)
    
    T = np.zeros((1,Size))
    test = np.zeros((1,Size))
    test[0] = cont[0]
    test = test.astype(int)
    for i in range(int(PATHS/2)):
        T[0] = rT[i]
        sns.heatmap(
                    np.transpose(T), 
                    cbar=False,
                    yticklabels=cont[i], 
                    xticklabels=keys[i],
                    square=True,
                    annot=np.transpose(test),
                    annot_kws={"size": 8},
                    fmt="d",
                    vmin=0,
                    vmax=1,
                    linewidth=0.01, linecolor="black",
                    cbar_kws={"shrink": .5},
                    ax=axs[i],
                    cmap=my_cmap_r)
    
    plt.show()
    
def ch_matrix(board):
    path_in = f"./results_ch_matrix/{board}_ch_matrix.txt"
    path_out = f"./results_ch_matrix/{board}_ch_matrix.png"
    data = np.loadtxt(path_in, delimiter="|")
    size = int(len(data[0]))
    
    my_cmap, my_cmap_r = define_pallette("black", "#E2DEDE")

    yAxis = np.zeros(size)
    # delete 10 in 10 elements in yAxis
    step = 40
    for i in range(1, size, step):
        yAxis[i] = data[0][i]
    
    yAxis = yAxis[yAxis != 0]
    yAxis = yAxis.astype(int)
        
    # delete first row
    data = np.delete(data, 0, 0) # delete axis = x, row = 0
    # delete first column
    data = np.delete(data, 0, 1) # delete axis = y, column = 0
    
    fig = plt.figure(constrained_layout=True)
    fig.set_size_inches(12, 8)
    ax = sns.heatmap( 
        np.transpose(data), 
        cbar=True,
        xticklabels=20,
        vmin=0,
        vmax=1,
        cmap="rocket") 
    ax.yaxis.set_major_locator(MultipleLocator(step))
    ax.set_yticklabels(yAxis)
    ax.invert_yaxis()
    ax.set_title(board, fontsize=18)

    plt.savefig(path_out, dpi=500)
    plt.show()
    
def ch_matrix_4_ST():
    
    data1 = np.loadtxt("./results_ch_matrix/STM32L552_ch_matrix.txt", delimiter="|")
    data2 = np.loadtxt("./results_ch_matrix/STM32L073_ch_matrix.txt", delimiter="|")
    data3 = np.loadtxt("./results_ch_matrix/STM32L412_ch_matrix.txt", delimiter="|")
    data4 = np.loadtxt("./results_ch_matrix/STM32F767_ch_matrix.txt", delimiter="|")
    size1 = int(len(data1[0]))
    size2 = int(len(data2[0]))
    size3 = int(len(data3[0]))
    size4 = int(len(data4[0]))
    
    my_cmap, my_cmap_r = define_pallette("black", "#E2DEDE")

    y1 = np.zeros(size1)
    y2 = np.zeros(size2)
    y3 = np.zeros(size3)
    y4 = np.zeros(size4)
    # delete 10 in 10 elements in y
    step = 40
    for i in range(1, size1, step):
        y1[i] = data1[0][i]
    
    for i in range(1, size2, int(step)):
        y2[i] = data2[0][i]
        
    for i in range(1, size3, int(step)):
        y3[i] = data3[0][i]
    
    for i in range(1, size4, int(step)):
        y4[i] = data4[0][i]
        
    
    y1 = y1[y1 != 0]
    y1 = y1.astype(int)
    # insert dummy value, because heatmeap ignores first value
    y1 = np.insert(y1, 0, 0)
    
    y2 = y2[y2 != 0]
    y2 = y2.astype(int)
    # insert dummy value, because heatmeap ignores first value
    y2 = np.insert(y2, 0, 0)
    
    y3 = y3[y3 != 0]
    y3 = y3.astype(int)
    # insert dummy value, because heatmeap ignores first value
    y3 = np.insert(y3, 0, 0)
    
    y4 = y4[y4 != 0 ]
    y4 = y4.astype(int)
    # insert dummy value, because heatmeap ignores first value
    y4 = np.insert(y4, 0, 0)
    
    # delete first row
    data1 = np.delete(data1, 0, 0) # delete axis = x, row = 0
     # delete first column
    data1 = np.delete(data1, 0, 1) # delete axis = y, column = 0
    
    # delete first row
    data2 = np.delete(data2, 0, 0) # delete axis = x, row = 0
     # delete first column
    data2 = np.delete(data2, 0, 1) # delete axis = y, column = 0
    
    # delete first row
    data3 = np.delete(data3, 0, 0) # delete axis = x, row = 0
     # delete first column
    data3 = np.delete(data3, 0, 1) # delete axis = y, column = 0
    
    # delete first row
    data4 = np.delete(data4, 0, 0) # delete axis = x, row = 0
     # delete first column
    data4 = np.delete(data4, 0, 1) # delete axis = y, column = 0
    
    
    fig = plt.figure(constrained_layout=True)
    fig.set_size_inches(12, 8)
    axs = fig.subplots(nrows=2, ncols=2)
    
    ax =  sns.heatmap( 
                np.transpose(data1), 
                cbar=True,
                xticklabels=20,
                vmin=0,
                vmax=1,
                ax=axs[0][0],
                cmap="rocket") 
    ax.yaxis.set_major_locator(MultipleLocator(step))
    ax.set_yticklabels(y1)
    ax.invert_yaxis()
    ax.set_title("STM32L552", fontsize=18)
    # ax.set_title("Board " + str(0*2+0+1), fontsize=18)

    ax =  sns.heatmap( 
                np.transpose(data2), 
                cbar=True,
                xticklabels=20,
                vmin=0,
                vmax=1,
                ax=axs[0][1],
                cmap="rocket") 
    ax.yaxis.set_major_locator(MultipleLocator(step))
    ax.set_yticklabels(y2)
    ax.invert_yaxis()
    ax.set_title("STM32L073", fontsize=18)
    # ax.set_title("Board " + str(0*2+1+1), fontsize=18)
    
    ax =  sns.heatmap( 
                np.transpose(data3), 
                cbar=True,
                xticklabels=20,
                vmin=0,
                vmax=1,
                ax=axs[1][0],
                cmap="rocket") 
    ax.yaxis.set_major_locator(MultipleLocator(step))
    ax.set_yticklabels(y3)
    ax.invert_yaxis()
    ax.set_title("STM32L412", fontsize=18)
    # ax.set_title("Board " + str(1*2+0+1), fontsize=18)
    
    ax =  sns.heatmap( 
                np.transpose(data4), 
                cbar=True,
                xticklabels=20,
                vmin=0,
                vmax=1,
                ax=axs[1][1],
                cmap="rocket") 
    ax.yaxis.set_major_locator(MultipleLocator(step))
    ax.set_yticklabels(y4)
    ax.invert_yaxis()
    ax.set_title("STM32F767", fontsize=18)
    # ax.set_title("Board " + str(1*2+1+1), fontsize=18)

    plt.savefig('./results_ch_matrix/ST_ch_matrix.png', dpi=500)
    plt.show()

def ch_matrix_4_MC():
    
    data1 = np.loadtxt("./results_ch_matrix/PIC18_ch_matrix.txt", delimiter="|")
    data2 = np.loadtxt("./results_ch_matrix/SAMD21_ch_matrix.txt", delimiter="|")
    data3 = np.loadtxt("./results_ch_matrix/SAML11_ch_matrix.txt", delimiter="|")
    data4 = np.loadtxt("./results_ch_matrix/SAME54_ch_matrix.txt", delimiter="|")
    size1 = int(len(data1[0]))
    size2 = int(len(data2[0]))
    size3 = int(len(data3[0]))
    size4 = int(len(data4[0]))
    
    my_cmap, my_cmap_r = define_pallette("black", "#E2DEDE")

    y1 = np.zeros(size1)
    y2 = np.zeros(size2)
    y3 = np.zeros(size3)
    y4 = np.zeros(size4)
    # delete 10 in 10 elements in y
    step = 40
    for i in range(1, size1, step):
        y1[i] = data1[0][i]
    
    for i in range(1, size2, int(step)):
        y2[i] = data2[0][i]
        
    for i in range(1, size3, int(step)):
        y3[i] = data3[0][i]
    
    for i in range(1, size4, int(step)):
        y4[i] = data4[0][i]
        
    
    y1 = y1[y1 != 0]
    y1 = y1.astype(int)
    # insert dummy value, because heatmeap ignores first value
    y1 = np.insert(y1, 0, 0)
    
    y2 = y2[y2 != 0]
    y2 = y2.astype(int)
    # insert dummy value, because heatmeap ignores first value
    y2 = np.insert(y2, 0, 0)
    
    y3 = y3[y3 != 0]
    y3 = y3.astype(int)
    # insert dummy value, because heatmeap ignores first value
    y3 = np.insert(y3, 0, 0)
    
    y4 = y4[y4 != 0 ]
    y4 = y4.astype(int)
    # insert dummy value, because heatmeap ignores first value
    y4 = np.insert(y4, 0, 0)
    
    # delete first row
    data1 = np.delete(data1, 0, 0) # delete axis = x, row = 0
     # delete first column
    data1 = np.delete(data1, 0, 1) # delete axis = y, column = 0
    
    # delete first row
    data2 = np.delete(data2, 0, 0) # delete axis = x, row = 0
     # delete first column
    data2 = np.delete(data2, 0, 1) # delete axis = y, column = 0
    
    # delete first row
    data3 = np.delete(data3, 0, 0) # delete axis = x, row = 0
     # delete first column
    data3 = np.delete(data3, 0, 1) # delete axis = y, column = 0
    
    # delete first row
    data4 = np.delete(data4, 0, 0) # delete axis = x, row = 0
     # delete first column
    data4 = np.delete(data4, 0, 1) # delete axis = y, column = 0
    
    
    fig = plt.figure(constrained_layout=True)
    fig.set_size_inches(12, 8)
    axs = fig.subplots(nrows=2, ncols=2)
    
    ax =  sns.heatmap( 
                np.transpose(data1), 
                cbar=True,
                xticklabels=20,
                vmin=0,
                vmax=1,
                ax=axs[0][0],
                cmap="rocket") 
    ax.yaxis.set_major_locator(MultipleLocator(step))
    ax.set_yticklabels(y1)
    ax.invert_yaxis()
    ax.set_title("PIC18", fontsize=18)
    # ax.set_title("Board " + str(0*2+0+1), fontsize=18)

    ax =  sns.heatmap( 
                np.transpose(data2), 
                cbar=True,
                xticklabels=20,
                vmin=0,
                vmax=1,
                ax=axs[0][1],
                cmap="rocket") 
    ax.yaxis.set_major_locator(MultipleLocator(step))
    ax.set_yticklabels(y2)
    ax.invert_yaxis()
    ax.set_title("SAMD21", fontsize=18)
    # ax.set_title("Board " + str(0*2+1+1), fontsize=18)
    
    ax =  sns.heatmap( 
                np.transpose(data3), 
                cbar=True,
                xticklabels=20,
                vmin=0,
                vmax=1,
                ax=axs[1][0],
                cmap="rocket") 
    ax.yaxis.set_major_locator(MultipleLocator(step))
    ax.set_yticklabels(y3)
    ax.invert_yaxis()
    ax.set_title("SAML11", fontsize=18)
    # ax.set_title("Board " + str(1*2+0+1), fontsize=18)
    
    ax =  sns.heatmap( 
                np.transpose(data4), 
                cbar=True,
                xticklabels=20,
                vmin=0,
                vmax=1,
                ax=axs[1][1],
                cmap="rocket") 
    ax.yaxis.set_major_locator(MultipleLocator(step))
    ax.set_yticklabels(y4)
    ax.invert_yaxis()
    ax.set_title("SAME54", fontsize=18)
    # ax.set_title("Board " + str(1*2+1+1), fontsize=18)

    plt.savefig('./results_ch_matrix/MC_ch_matrix.png', dpi=500)
    plt.show()
    
if len(sys.argv) < 2:
    print("Insufficient command-line arguments!")
    print("Usage: python heatmap.py [trace | pruned_matrix | pruned_matrix_paths | ch_matrix]")
else:
    if sys.argv[1] == "trace":
        trace()
        # N_ACTIONS = int(sys.argv[2])
        
    if sys.argv[1] == "pruned_matrix":
        pruned_matrix()
    
    if sys.argv[1] == "pruned_matrix_paths":
        pruned_matrix_isolate_paths()
        
    if sys.argv[1] == "ch_matrix":
        if len(sys.argv) < 3:
            print("Insufficient command-line arguments!")
            print("heatmap ch_matrix [vendor]")
            print("vendor = ST || MC || SL || NXP || GD")
        else:
            if sys.argv[1] == "ch_matrix":
                # ch_matrix()
                if sys.argv[2] == "ST":
                    ch_matrix_4_ST()
                elif sys.argv[2] == "MC": 
                    ch_matrix_4_MC() 
                elif sys.argv[2] == "GD":
                    ch_matrix("GD32VF103") 
                elif sys.argv[2] == "NXP":
                    ch_matrix("LPC55S69") 
                elif sys.argv[2] == "SL":
                    ch_matrix("EFM32GG") 
                else:
                    print("Vendor not supported!")
