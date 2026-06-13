/*
 * Copyright (c) 2018-2021, Arm Limited. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#ifndef __TFM_PERIPHERALS_DEF_H__
#define __TFM_PERIPHERALS_DEF_H__

//------added by cris------------------------
#include "platform_irq.h"
//--------------------------------------------

struct platform_data_t;

//------added by cris------------------------
#define TFM_TIMER_IRQ           (TIM7_IRQn) // TIM7 global interrupt | "platform_irq.h" -> stm32l5xx.h -> "stm32l552xx.h"
//--------------------------------------------
#define TFM_PERIPHERAL_STD_UART     (0)
#define TFM_PERIPHERAL_TIMER0       (0)

//------added by cris------------------------
    extern struct platform_data_t gpioA;
    extern struct platform_data_t gpioB;
    extern struct platform_data_t gpioC;
    extern struct platform_data_t gpioD;
    extern struct platform_data_t gpioG;
    extern struct platform_data_t pwr;
    extern struct platform_data_t rcc;

    #define TFM_PERIPHERAL_GPIOA    &gpioA
    #define TFM_PERIPHERAL_GPIOB    &gpioB
    #define TFM_PERIPHERAL_GPIOC    &gpioC
    #define TFM_PERIPHERAL_GPIOD    &gpioD
    #define TFM_PERIPHERAL_GPIOG    &gpioG
    #define TFM_PERIPHERAL_PWR      &pwr
    #define TFM_PERIPHERAL_RCC      &rcc
//--------------------------------------------

#endif /* __TFM_PERIPHERALS_DEF_H__ */
