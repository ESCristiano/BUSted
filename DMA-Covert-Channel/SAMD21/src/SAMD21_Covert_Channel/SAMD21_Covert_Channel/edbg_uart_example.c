/**
 * \file
 *
 * \brief Application implement
 *
 * Copyright (c) 2015-2018 Microchip Technology Inc. and its subsidiaries.
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
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */

#include "atmel_start.h"
#include <stdio.h>

int __io_putchar(int ch)
{
	uint8_t c[1];
	c[0] = ch & 0x00FF;
	io_write(&EDBG_COM.io, &*c, 1);
	return ch;
}

int _read(int file,char *ptr, int len)
{
}

int _write(int file,char *ptr, int len)
{
	int DataIdx;
	for(DataIdx= 0; DataIdx< len; DataIdx++)
	{
		__io_putchar(*ptr++);
	}
	return len;
}

#define SETUP_COLLISION_SRAM1()do { \
    __asm volatile("ldr r0, =0x20000004"); \
} while(0)

#define SETUP_NO_COLLISION_APBB()do { \
    __asm volatile("ldr r0, =0x60000000"); \
} while(0)

#define SETUP_CONTENTION()do { \
	SETUP_COLLISION_SRAM1(); \
} while(0)

#define SETUP_NO_CONTENTION()do { \
	SETUP_NO_COLLISION_APBB(); \
} while(0)

// "nop" instruction cannot used, because it is not reliable! Sometimes it
// last 1 clock other times 0 clocks. Even with -o0 and the actual nop being
// present in the asm code. I think the processor sometimes does not execute the
// nop instructions
#define MY_NOP()  __asm volatile("mov r8,r8")

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


//******************************************************************************
// DMA Covert-Channel 
//******************************************************************************
#define MAX_SYMBOL 256
#define N_SAMPLES 100
#define TRASNFER_SIZE 2000

// #define TROJAN_SECURE
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
    HUND_LDRS();
  }
}

void config_DMA_M2M(int size){
	// Make this vars global. The stack will be destroyed.
	static int cont;
	_dma_srcinc_enable(0, false);
	_dma_dstinc_enable(0, false);
	_dma_set_source_address(0, &cont);
	_dma_set_destination_address(0, &cont);
	_dma_set_data_amount(0, size);
	_dma_enable_transaction(0, false); // enable but not trigger
	_dma_set_irq_state(0, 0, true);
}

int input_symbol = 0, sample = 0;

__attribute__((optimize(0))) void DMAC_Handler(void)
{
	int *ptr_ctr = 0x42003000; 
	int *ptr_cnt = 0x42003000+0x10; // (32 bits)
	int *ptr_DMA_trigger = 0x41004800 + 0x10;
	int cnt = *ptr_cnt;
 	static int first = 1;
	*ptr_ctr &= ~(1<<1); // this cleans the counter 	
	hri_dmac_clear_CHINTFLAG_TCMPL_bit(DMAC);
	if(!first){ //ignore the first measurement, it is trash
		printf("(%d, %d)\r\n", input_symbol, cnt );
	}
	first = 0;
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
	int *ptr_ctr = 0x42003000; 
	int *ptr_cnt = 0x42003000+0x10; // (32 bits)
	int *ptr_DMA_trigger = 0x41004800 + 0x10;
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

__attribute__((optimize(0)))int main(void)
{	
	atmel_start_init();
	usart_sync_enable(&EDBG_COM);
	printf("\r\n");
	printf("\r\n");
	covert_channel();
	while (1) {
	}
}
