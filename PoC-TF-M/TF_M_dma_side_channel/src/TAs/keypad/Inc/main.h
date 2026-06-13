/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32l5xx_hal.h"
#include <stdint.h>
#include "psa/service.h"
#include "psa_manifest/keypad.h"
//#include "tfm/tfm_spm_services.h"
#include "tfm_sp_log.h"
#include <assert.h>
#include "cmsis.h"
#include "keypad.h"
#include "gpio.h"

/* Private defines -----------------------------------------------------------*/
#define R1_Pin GPIO_PIN_3
#define R1_GPIO_Port GPIOA
#define R2_Pin GPIO_PIN_2
#define R2_GPIO_Port GPIOA
#define R3_Pin GPIO_PIN_10
#define R3_GPIO_Port GPIOA
#define R4_Pin GPIO_PIN_3
#define R4_GPIO_Port GPIOB

#define C1_Pin GPIO_PIN_5
#define C1_GPIO_Port GPIOB
#define C2_Pin GPIO_PIN_4
#define C2_GPIO_Port GPIOB
#define C3_Pin GPIO_PIN_10
#define C3_GPIO_Port GPIOB
#define C4_Pin GPIO_PIN_8
#define C4_GPIO_Port GPIOA
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
