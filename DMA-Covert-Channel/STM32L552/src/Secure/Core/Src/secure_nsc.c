/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    Secure/Src/secure_nsc.c
  * @author  MCD Application Team
  * @brief   This file contains the non-secure callable APIs (secure world)
  ******************************************************************************
    * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* USER CODE BEGIN Non_Secure_CallLib */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "secure_nsc.h"
/** @addtogroup STM32L5xx_HAL_Examples
  * @{
  */

/** @addtogroup Templates
  * @{
  */

/* Global variables ----------------------------------------------------------*/
void *pSecureFaultCallback = NULL;   /* Pointer to secure fault callback in Non-secure */
void *pSecureErrorCallback = NULL;   /* Pointer to secure error callback in Non-secure */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Secure registration of non-secure callback.
  * @param  CallbackId  callback identifier
  * @param  func        pointer to non-secure function
  * @retval None
  */
CMSE_NS_ENTRY void SECURE_RegisterCallback(SECURE_CallbackIDTypeDef CallbackId, void *func)
{
  if(func != NULL)
  {
    switch(CallbackId)
    {
      case SECURE_FAULT_CB_ID:           /* SecureFault Interrupt occurred */
        pSecureFaultCallback = func;
        break;
      case GTZC_ERROR_CB_ID:             /* GTZC Interrupt occurred */
        pSecureErrorCallback = func;
        break;
      default:
        /* unknown */
        break;
    }
  }
}

//******************************************************************************
//DMA Covert-Channel
//******************************************************************************
#define SETUP_COLLISION_SRAM1()do { \
	__asm("ldr r0, =0x30030000"); \
} while(0)

#define SETUP_CONTENTION()do { \
	SETUP_COLLISION_SRAM1(); \
} while(0)

#define SETUP_NO_CONTENTION()do { \
	__asm("ldr r0, =0x30018000"); \
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
#define CONTENTION

__attribute__((optimize(0))) CMSE_NS_ENTRY void trojan_s(int input_symbol){
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

//******************************************************************************

/**
  * @}
  */

/**
  * @}
  */
/* USER CODE END Non_Secure_CallLib */

