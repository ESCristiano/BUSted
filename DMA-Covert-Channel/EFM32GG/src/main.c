/***************************************************************************//**
 * @file main.c
 * @brief main() function.
 *******************************************************************************
 * # License
 * <b>Copyright 2020 Silicon Laboratories Inc. www.silabs.com</b>
 *******************************************************************************
 *
 * The licensor of this software is Silicon Laboratories Inc. Your use of this
 * software is governed by the terms of Silicon Labs Master Software License
 * Agreement (MSLA) available at
 * www.silabs.com/about-us/legal/master-software-license-agreement. This
 * software is distributed to you in Source Code format and is governed by the
 * sections of the MSLA applicable to Source Code.
 *
 ******************************************************************************/
#include "sl_component_catalog.h"
#include "sl_system_init.h"
#include "app.h"
#if defined(SL_CATALOG_POWER_MANAGER_PRESENT)
#include "sl_power_manager.h"
#endif
#if defined(SL_CATALOG_KERNEL_PRESENT)
#include "sl_system_kernel.h"
#else // SL_CATALOG_KERNEL_PRESENT
#include "sl_system_process_action.h"
#endif // SL_CATALOG_KERNEL_PRESENT

#include "em_chip.h"
#include "em_device.h"
#include "em_cmu.h"
#include "em_emu.h"
#include "em_dma.h"

#include "dmactrl.h"

/* DMA channel used for the examples */
#define DMA_CHANNEL     0
#define DMA_CH_MASK     (1 << DMA_CHANNEL)

/* Memory to memory transfer buffer size and constant for GPIO PRS */
#define BUFFER_SIZE     128
#define ARB_SIZE        dmaArbitrate1024

#define DATA_SIZE       dmaDataSize4

/* Buffer for memory to memory transfer */
uint16_t srcBuffer[BUFFER_SIZE];
uint16_t dstBuffer[BUFFER_SIZE];

DMA_CB_TypeDef dmacb;

///**************************************************************************//**
// * @brief DMA Callback function
// *****************************************************************************/
void dmaCallback(unsigned int channel, bool primary, void *user);

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
  __asm("ldr r0, =0x20000000"); \
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
#define TRASNFER_SIZE 2000
/***************************************************************************//**
 * @brief
 *   Initialize the DMA controller for single direct register transfer
 ******************************************************************************/
void initDma(int size)
{
  uint32_t i;

  /* Initialize buffers for memory transfer */
  for (i = 0; i < BUFFER_SIZE; i++){
    srcBuffer[i] = 0xff+i;
    dstBuffer[i] = 0;
  }

  // Enable CMU clock
  CMU_ClockEnable(cmuClock_DMA, true);

  // Basic DMA configuration
  DMA_Init_TypeDef       dmaInit;
  DMA_CfgDescr_TypeDef   descrCfg;
  DMA_CfgChannel_TypeDef chnlCfg;

  bool isPrimary = true;

  // Configure general DMA issues
  dmaInit.hprot        = 0;
  dmaInit.controlBlock = dmaControlBlock;

  DMA_Init(&dmaInit);

  // Setup callback function
  dmacb.cbFunc  = dmaCallback;
  dmacb.userPtr = NULL;

  // Configure DMA channel used
  chnlCfg.highPri   = false;
  chnlCfg.enableInt = true;
  chnlCfg.select    = 0;      // software triggered
  chnlCfg.cb        = &dmacb;
  DMA_CfgChannel(DMA_CHANNEL, &chnlCfg);

  descrCfg.dstInc  = 3;// No inc
  descrCfg.srcInc  = 3;// No inc
  descrCfg.size    = DATA_SIZE;
  descrCfg.arbRate = ARB_SIZE;
  descrCfg.hprot   = 0;
  DMA_CfgDescr(DMA_CHANNEL, isPrimary, &descrCfg);

  // Start DMA
  DMA_ActivateBasic(
      DMA_CHANNEL,      // Channel
      isPrimary,
      false,
      0x20020000,        // Destination
      0x20020004,        // Source
      1024-1);   // Transfer size

  // Request via software
  //DMA->CHSWREQ |= DMA_CH_MASK;

}



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
    HUND_LDRS();
  }
}

uint32_t src;
uint32_t dst;

void config_DMA_M2M(int size){
// Make this vars global. The stack will be destroyed.
  // static int src, dst;
  SysTick->CTRL = 0x0; //Clean SysTick Default Configs
  SysTick->LOAD = (uint32_t)(0xFFFFFF - 1); //max counter value
  initDma(size);
}

int input_symbol = 0, sample = 0;

__attribute__((optimize(0))) void covert_channel(){
  int *ptr_cnt = &SysTick->VAL; // (24 bits)
  int *ptr_ctr = &SysTick->CTRL; // (24 bits)
  // trigger chain of interrupts (DMA transfers)
  config_DMA_M2M(TRASNFER_SIZE);
  *ptr_cnt = 0; // reset the val  counter
  *ptr_ctr = 0x05; // starts the systick
  //start DMA transaction
  DMA->CHSWREQ |= DMA_CH_MASK;
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
__attribute__((optimize(0))) void dmaCallback(unsigned int channel, bool primary, void *user){
  int *ptr_cnt = &SysTick->VAL; // (24 bits)
  int *ptr_ctr = &SysTick->CTRL; // (24 bits)
  static int first = 1;
  SysTick->CTRL = 0x0; // Stops Systickpwd
  if(!first){ //ignore the first measurement, it is trash
    printf("(%d, %d)\r\n", input_symbol, (0xFFFFFF - 1) - *ptr_cnt);
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
//  config_DMA_M2M(TRASNFER_SIZE);
  initDma(TRASNFER_SIZE);
  *ptr_cnt = 0; // reset the val  counter
  *ptr_ctr = 0x05; // starts the systick
  //start DMA transaction
  DMA->CHSWREQ |= DMA_CH_MASK;
  #ifdef TROJAN_SECURE
    trojan_s(input_symbol);
  #else
    trojan(input_symbol);
  #endif
  return;

}

int main(void)
{
  // Initialize Silicon Labs device, system, service(s) and protocol stack(s).
  // Note that if the kernel is present, processing task(s) will be created by
  // this call.
  sl_system_init();
  printf("\e[1;1H\e[2J"); // clear terminal
  printf("\r\n"); // clear terminal
  covert_channel();
  while(1);
}
