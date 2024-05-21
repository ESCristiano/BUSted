// See LICENSE for license details.
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "nuclei_sdk_soc.h"

extern void DMA0_Channel0_IRQHandler(void);

//******************************************************************************
//DMA Covert-Channel
//******************************************************************************
#define SETUP_COLLISION_SRAM1()do { \
	__asm("la x10, 0x20000000"); \
} while(0)

#define SETUP_CONTENTION()do { \
	SETUP_COLLISION_SRAM1(); \
} while(0)

#define SETUP_NO_CONTENTION()do { \
	__asm("la x10, 0x40022000"); \
} while(0)

#define TEN_LDRS() do { \
	__asm volatile("lw x11, 0(x10)");\
	__asm volatile("lw x11, 0(x10)");\
	__asm volatile("lw x11, 0(x10)");\
	__asm volatile("lw x11, 0(x10)");\
	__asm volatile("lw x11, 0(x10)");\
	__asm volatile("lw x11, 0(x10)");\
	__asm volatile("lw x11, 0(x10)");\
	__asm volatile("lw x11, 0(x10)");\
	__asm volatile("lw x11, 0(x10)");\
	__asm volatile("lw x11, 0(x10)");\
} while(0)

#define MAX_SYMBOL 256
#define N_SAMPLES 100
#define TRASNFER_SIZE 4000

//#define TROJAN_SECURE
// #define CONTENTION

__attribute__((optimize(0))) void trojan(int input_symbol){
  // Trying to balance this code in terms of time as much as possible  
  for(int i=0;i < MAX_SYMBOL; i++){
    if(i < input_symbol){
      #ifdef CONTENTION
        SETUP_CONTENTION();
      #else
        SETUP_NO_CONTENTION();
      #endif
    }
    // With else it would be unbalanced in terms of LDRs
    if(i >= input_symbol){
    	SETUP_NO_CONTENTION();
    }
    TEN_LDRS();
  }
}

void config_wall_clock(){
    timer_parameter_struct timerInit;
    timer_struct_para_init(&timerInit);
    timerInit.prescaler         = 0;
    timerInit.counterdirection  = TIMER_COUNTER_UP;
    timerInit.period            = 0xFFFF;
    timerInit.clockdivision     = TIMER_CKDIV_DIV1;
    timer_deinit(TIMER5);
    timer_init(TIMER5, &timerInit);
    timer_enable(TIMER5);
}

uint32_t src;
uint32_t dst;

void config_DMA_M2M(int size){
// Make this vars global. The stack will be destroyed.
    // static int src, dst;
    // SysTick->CTRL = 0x0; //Clean SysTick Default Configs
    // SysTick->LOAD = (uint32_t)(0xFFFFFF - 1); //max counter value
    dma_parameter_struct dmaInit ;
    dma_struct_para_init(&dmaInit) ;
    dmaInit.direction = DMA_MEMORY_TO_PERIPHERAL;
    dmaInit.memory_addr = (uint32_t)&src;
    dmaInit.memory_inc = DMA_PERIPH_INCREASE_DISABLE;
    dmaInit.memory_width = DMA_MEMORY_WIDTH_32BIT;
    dmaInit.number = size;
    dmaInit.periph_addr = (uint32_t)&dst;
    dmaInit.periph_inc = DMA_PERIPH_INCREASE_DISABLE;
    dmaInit.periph_width = DMA_PERIPHERAL_WIDTH_32BIT;
    dmaInit.priority = DMA_PRIORITY_MEDIUM;
    dma_deinit(DMA0, DMA_CH0) ;
    dma_init(DMA0, DMA_CH0, &dmaInit);
    /* configure DMA mode */
    dma_circulation_disable(DMA0, DMA_CH0);
    dma_memory_to_memory_enable(DMA0, DMA_CH0);
    dma_interrupt_enable(DMA0, DMA_CH0, DMA_INT_FTF);
    // initialize software interrupt as vector interrupt
    ECLIC_Register_IRQ(DMA0_Channel0_IRQn, ECLIC_VECTOR_INTERRUPT,
                        ECLIC_LEVEL_TRIGGER, 2, 0, DMA0_Channel0_IRQHandler);

}

int input_symbol = 0, sample = 0;

__attribute__((optimize(0))) void covert_channel(){
    config_wall_clock();
    config_DMA_M2M(TRASNFER_SIZE);
    timer_enable(TIMER5);
    dma_channel_enable(DMA0, DMA_CH0);
    #ifdef TROJAN_SECURE
        trojan_s(input_symbol);
    #else
        trojan(input_symbol);
    #endif
    while(1);
}

/* 
* The channel is measured in the DMA ISR to avoid accessing the SRAM,which would 
* introduce a lot of noise in the covert-channel. (Remove the need of a flag
* shared between ISR and code, that would generate a lot of SRAM accesses)
*/
volatile int *ptr_cnt = TIMER5 + 0x24;  
__INTERRUPT __attribute__((optimize(0))) void DMA0_Channel0_IRQHandler(){
    static int first = 1;
    timer_disable(TIMER5);
    dma_interrupt_flag_clear(DMA0, DMA_CH0, DMA_INT_FLAG_FTF);
    if(!first){ //ignore the first measurement, it is trash
        printf("(%d, %d)\r\n", input_symbol, (*ptr_cnt)&0xFFFF);
        sample++;
    }
    first = 0;
    // N_SAMPLES per input symbol
    if(sample >= N_SAMPLES){
        if(input_symbol < MAX_SYMBOL-1){
        input_symbol++;
        sample = 0;
        }
        else {
        input_symbol = 0;
        // printf("END\r\n");
        return;
        }
    }
    config_DMA_M2M(TRASNFER_SIZE);
    *ptr_cnt = 0; // reset the val  counter
    timer_enable(TIMER5);
    dma_channel_enable(DMA0, DMA_CH0);
    #ifdef TROJAN_SECURE
        trojan_s(input_symbol);
    #else
        trojan(input_symbol);
    #endif
    return;
}

int main(void)
{   
    printf("Hello World\n");
    rcu_periph_clock_enable(RCU_DMA0);
    rcu_periph_clock_enable(RCU_TIMER5);
    __enable_irq();
    covert_channel();
}

