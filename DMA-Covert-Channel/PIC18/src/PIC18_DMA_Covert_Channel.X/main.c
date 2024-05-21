 /*
 * MAIN Generated Driver File
 * 
 * @file main.c
 * 
 * @defgroup main MAIN
 * 
 * @brief This is the generated driver implementation file for the MAIN driver.
 *
 * @version MAIN Driver Version 1.0.0
*/

/*
� [2023] Microchip Technology Inc. and its subsidiaries.

    Subject to your compliance with these terms, you may use Microchip 
    software and any derivatives exclusively with Microchip products. 
    You are responsible for complying with 3rd party license terms  
    applicable to your use of 3rd party software (including open source  
    software) that may accompany Microchip software. SOFTWARE IS ?AS IS.? 
    NO WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS 
    SOFTWARE, INCLUDING ANY IMPLIED WARRANTIES OF NON-INFRINGEMENT,  
    MERCHANTABILITY, OR FITNESS FOR A PARTICULAR PURPOSE. IN NO EVENT 
    WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY 
    KIND WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF 
    MICROCHIP HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE 
    FORESEEABLE. TO THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP?S 
    TOTAL LIABILITY ON ALL CLAIMS RELATED TO THE SOFTWARE WILL NOT 
    EXCEED AMOUNT OF FEES, IF ANY, YOU PAID DIRECTLY TO MICROCHIP FOR 
    THIS SOFTWARE.
*/
#include <stdio.h>

#include "mcc_generated_files/system/system.h"

/*
    Main application
*/

//******************************************************************************
//DMA Covert-Channel
//******************************************************************************
//select the SRAM bank 6
#define SETUP_COLLISION_BANK_6()do { \
	asm("MOVLB 6"); \
	asm("MOVLW 0x54"); \
} while(0)

#define SETUP_CONTENTION()do { \
	SETUP_COLLISION_BANK_6(); \
} while(0)

//select the SRAM bank 7
#define SETUP_NO_CONTENTION()do { \
	asm("MOVLB 7"); \
	asm("MOVLW 0x98"); \
} while(0)

/* MOVWF 1 clock cycle */
#define TEN_MOV() do { \
	asm("MOVWF 0x0, 1");\  
	asm("MOVWF 0x0, 1");\
	asm("MOVWF 0x0, 1");\
	asm("MOVWF 0x0, 1");\
	asm("MOVWF 0x0, 1");\
	asm("MOVWF 0x0, 1");\
	asm("MOVWF 0x0, 1");\
	asm("MOVWF 0x0, 1");\
	asm("MOVWF 0x0, 1");\
	asm("MOVWF 0x0, 1");\
} while(0)

/* nop 1 clock cycle */
#define TEN_NOPS() do { \
	asm("nop");\
	asm("nop");\
	asm("nop");\
	asm("nop");\
	asm("nop");\
	asm("nop");\
	asm("nop");\
	asm("nop");\
	asm("nop");\
	asm("nop");\
} while(0)

#define MAX_SYMBOL 256
#define N_SAMPLES 100
#define TRASNFER_SIZE 2000 //max 4095

// #define TROJAN_SECURE
#define CONTENTION

void trojan(uint16_t input_symbol){
  // Trying to balance this code in terms of time as much as possible  
  for(uint16_t i=0;i < MAX_SYMBOL; i++){
    if(i < input_symbol){
      #ifdef CONTENTION
        TEN_MOV();       
      #else
        TEN_NOPS();
      #endif
    }
    // With else it would be unbalanced in terms of LDRs
    if(i >= input_symbol){
        TEN_NOPS();
    }
  }
}

uint16_t src;
uint16_t dst;

void config_DMA_M2M(uint16_t size){
// Make this vars global. The stack will be destroyed.
  // static int src, dst;
  DMAnCON0 = 0x00; // disable DMA
  DMASELECT = 0x0;
  DMAnSSA = 0x650; // src
  DMAnDSA = 0x651; // dst
  DMAnSSZ= size;
  DMAnDSZ= size;
  DMAnCON0 = 0x80; // enable DMA
  }

volatile int input_symbol = 0, sample = 0, sync = 0;


 uint16_t start, end, *ptr_cnt = 0x318;

// In PIC18 microcontrollers, interrupts cannot be preempted, so we need to 
//change the way we mount the covert channel
void DMA_ISR(){
  Timer0_Stop();
  sync = 1;
  return;
}

void covert_channel_logic(){
  static uint8_t first = 1;
  if(!first){ //ignore the first measurement, it is trash
    printf("(%d, %u)\r\n", input_symbol, *ptr_cnt);
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
  Timer0_Write(0);
  Timer0_Start();
  //start DMA transaction
  DMA1_StartTransfer();
  #ifdef TROJAN_SECURE
    trojan_s(input_symbol);
  #else
    trojan(input_symbol);
  #endif
}

void covert_channel(){
  DMA1_SetSCNTIInterruptHandler(DMA_ISR);
  // trigger chain of interrupts (DMA transfers)
  config_DMA_M2M(TRASNFER_SIZE);
  //trigegr DMA 
  DMA1_StartTransfer();
  while(1){
    if(sync){
      sync = 0;
      covert_channel_logic();
    }
  }
}

int main(void)
{
    SYSTEM_Initialize();
    INTERRUPT_GlobalInterruptHighEnable(); 
    printf("Helllo\n\r");
    covert_channel();
}