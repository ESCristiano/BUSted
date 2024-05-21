/*
 * Copyright 2018 NXP
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#include <stdio.h>

#include "fsl_device_registers.h"
#include "fsl_debug_console.h"
#include "veneer_table.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "board.h"
#include "fsl_power.h"
#include "fsl_dma.h"
#include "peripherals.h"
/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define PRINTF_NSE 		DbgConsole_Printf_NSE
#define OPTZ0 __attribute__((optimize(0)))

/*! @brief DMA channel transfer configurations macro
 * @param reload true is reload link descriptor after current exhaust, false is not
 * @param clrTrig true is clear trigger status, wait software trigger, false is not
 * @param intA enable interruptA
 * @param intB enable interruptB
 * @param width transfer width
 * @param srcInc source address interleave size
 * @param dstInc destination address interleave size
 * @param bytes transfer bytes
 */
//#define DMA_CHANNEL_XFER(reload, clrTrig, intA, intB, width, srcInc, dstInc, bytes)

uint32_t src;
uint32_t dst;

int input_symbol = 0;
int sample = 0;
char buff[64];

dma_handle_t g_DMA_Handle;
dma_channel_config_t transferConfig;
dma_channel_trigger_t triggerChnl;
/*******************************************************************************
 * Prototypes
 ******************************************************************************/
void config_DMA_M2M(int size);
OPTZ0 void covert_channel();
/*******************************************************************************
 * Code
 ******************************************************************************/
//******************************************************************************
//DMA Covert-Channel
//******************************************************************************
#define SETUP_COLLISION_SRAM1()do { \
	__asm("ldr r0, =0x20020000"); \
} while(0)

#define SETUP_CONTENTION()do { \
	SETUP_COLLISION_SRAM1(); \
} while(0)

#define SETUP_NO_CONTENTION()do { \
	__asm("ldr r0, =0x20010000"); \
} while(0)


#define TEN_LDRS() do { \
	__asm volatile("ldr r1, [r0]");\
	__asm volatile("ldr r1, [r0]");\
	__asm volatile("ldr r1, [r0]");\
	__asm volatile("ldr r1, [r0]");\
	__asm volatile("ldr r1, [r0]");\
	__asm volatile("ldr r1, [r0]");\
	__asm volatile("ldr r1, [r0]");\
	__asm volatile("ldr r1, [r0]");\
	__asm volatile("ldr r1, [r0]");\
	__asm volatile("ldr r1, [r0]");\
} while(0)

#define HUND_LDRS()do {\
		TEN_LDRS();\
		TEN_LDRS();\
		TEN_LDRS();\
		TEN_LDRS();\
		TEN_LDRS();\
		TEN_LDRS();\
		TEN_LDRS();\
		TEN_LDRS();\
		TEN_LDRS();\
		TEN_LDRS();\
	} while(0)

#define MAX_SYMBOL 256
#define N_SAMPLES 100
#define TRANSFER_SIZE 4096 // Max

//#define TROJAN_SECURE
#define CONTENTION

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

/* User callback function for DMA transfer. */
OPTZ0 void DMA_Callback(dma_handle_t *handle, void *param, bool transferDone, uint32_t tcds)
{
	if (transferDone)
	{
		int *ptr_cnt = &SysTick->VAL; 	// (24 bits)
		int *ptr_ctr = &SysTick->CTRL; 	// (24 bits)
		static int first = 1;

		//clean IRQ on DMA periph
		//HAL_DMA_IRQHandler(&hdma_memtomem_dma1_channel1);

		if(!first){ //ignore the first measurement, it is trash
			sprintf(buff,"(%d, %d)\r\n", input_symbol, ((0xFFFFFF - 1) - *ptr_cnt));
			PRINTF_NSE(buff);
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
				PRINTF_NSE("END\r\n");
				return;
			}
		}

		DMA_Deinit(DMA0);
		config_DMA_M2M(TRANSFER_SIZE);

		*ptr_cnt = 0; 		// reset the val  counter
		*ptr_ctr = 0x05; 	// starts the systick

		//start DMA transaction
		//need to comment this line in function HAL_DMA_Start()
		DMA_StartTransfer(&g_DMA_Handle);

#ifdef TROJAN_SECURE
		trojan_s(input_symbol);
#else
		trojan(input_symbol);
#endif
	}
	return;
}

__attribute__ ((aligned (16))) dma_descriptor_t nextDesc[3];

void config_DMA_M2M(int size)
{
	SysTick->CTRL = 0x0; 						//Clean SysTick Default Configs
	SysTick->LOAD = (uint32_t)(0xFFFFFF - 1); 	//max counter value

	DMA_Init(DMA0);
	// Linked List/descriptors
    DMA_CreateHandle(&g_DMA_Handle, DMA0, 0);
	DMA_EnableChannel(DMA0, 0);
    DMA_PrepareChannelTransfer(&transferConfig,0x20020000,0x20020010,
					DMA_CHANNEL_XFER(true, false, false, false, 4, 0, 0, size),
					kDMA_MemoryToMemory,&triggerChnl,&nextDesc[0]);
    DMA_SetupDescriptor(&nextDesc[0],  
					DMA_CHANNEL_XFER(true, false, false,  false, 4, 0, 0, size),
					0x20020000, 0x20020010, &nextDesc[1]);
    DMA_SetupDescriptor(&nextDesc[1],  
					DMA_CHANNEL_XFER(true, false, false,  false, 4, 0, 0, size),
					0x20020000, 0x20020010, &nextDesc[2]);
    DMA_SetupDescriptor(&nextDesc[2],  
					DMA_CHANNEL_XFER(false, false, true,  false, 4, 0, 0, size),
					0x20020000, 0x20020010, NULL);
	DMA_SetCallback(&g_DMA_Handle, DMA_Callback, NULL);
    DMA_SubmitChannelTransfer(&g_DMA_Handle, &transferConfig);
}

OPTZ0 void covert_channel(){
	int *ptr_cnt = &SysTick->VAL; 		// (24 bits)
	int *ptr_ctr = &SysTick->CTRL; 		// (24 bits)

	// trigger chain of interrupts (DMA transfers)
	config_DMA_M2M(TRANSFER_SIZE);
	*ptr_cnt = 0; // reset the val  counter
	*ptr_ctr = 0x05; // starts the systick

	//start DMA transaction
	//need to comment this line in function HAL_DMA_Start()
	DMA_StartTransfer(&g_DMA_Handle);

#ifdef TROJAN_SECURE
	trojan_s(input_symbol);
#else
	trojan(input_symbol);
#endif
	while(1);
}



void SystemInit(void)
{
}
/*!
 * @brief Main function
 */
int main(void)
{
	int result;

	/* set BOD VBAT level to 1.65V */
	POWER_SetBodVbatLevel(kPOWER_BodVbatLevel1650mv, kPOWER_BodHystLevel50mv, false);

	PRINTF_NSE("Starting covert channel from NS ("__TIME__")...\r\n");

	triggerChnl.burst = kDMA_BurstSize1;
	triggerChnl.type = kDMA_SingleTransfer;
	triggerChnl.wrap = kDMA_NoWrap;

	covert_channel();

	while (1)
	{
	}
}
