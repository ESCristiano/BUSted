
/*
 * Copyright (c) 2021, Arm Limited. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#include <stdint.h>
#include "psa/service.h"
#include "psa_manifest/covert.h"
#include "psa_manifest/sid.h"
//#include "tfm/tfm_spm_services.h"
#include "tfm_sp_log.h"
#include <assert.h>
#include "cmsis.h"
//#include "covert_src/covert.h"
#include "uArchChannel_lib.h"


//#include "cy_tcpwm_counter.h"

// cy_stc_tcpwm_counter_config_t tcpwm_v2_counter_config =
//     {
//         /* .period            = */ 65000UL, /* Period of 100 (0-99). Terminal count event when rolls over back to 0. */
//         /* .clockPrescaler    = */ CY_TCPWM_COUNTER_PRESCALER_DIVBY_1, /* Clk_counter = Clk_input / 4 */
//         /* .runMode           = */ CY_TCPWM_COUNTER_CONTINUOUS, /* Wrap around at terminal count. */
//         /* .countDirection    = */ CY_TCPWM_COUNTER_COUNT_UP, /* Up counter, counting from 0 to period value. */
//         /* .compareOrCapture  = */ CY_TCPWM_COUNTER_MODE_COMPARE, /* Trigger interrupt/event signal when Counter value is equal to Compare 0 */
//         /* .compare0          = */ 65000UL,
//         /* .compare1          = */ 0UL,
//         /* .enableCompareSwap = */ false, /* Upon a compare event, swap the Compare 0 and Compare 1 values. */
//         /* .interruptSources  = */ CY_TCPWM_INT_NONE,
//         /* .captureInputMode  = */ CY_TCPWM_INPUT_RISINGEDGE, /* This input is NOT used, leave it in default state (CY_TCPWM_INPUT_RISINGEDGE = 0UL) */
//         /* .captureInput      = */ CY_TCPWM_INPUT_0,
//         /* .reloadInputMode   = */ CY_TCPWM_INPUT_RISINGEDGE, /* This input is NOT used, leave it in default state (CY_TCPWM_INPUT_RISINGEDGE = 0UL) */
//         /* .reloadInput       = */ CY_TCPWM_INPUT_0,
//         /* .startInputMode    = */ CY_TCPWM_INPUT_RISINGEDGE, /* This input is NOT used, leave it in default state (CY_TCPWM_INPUT_RISINGEDGE = 0UL) */
//         /* .startInput        = */ CY_TCPWM_INPUT_0,
//         /* .stopInputMode     = */ CY_TCPWM_INPUT_RISINGEDGE, /* This input is NOT used, leave it in default state (CY_TCPWM_INPUT_RISINGEDGE = 0UL) */
//         /* .stopInput         = */ CY_TCPWM_INPUT_0,
//         /* .countInputMode    = */ CY_TCPWM_INPUT_LEVEL, /* Set this input to LEVEL and 1 (high logic level) */
//         /* .countInput        = */ CY_TCPWM_INPUT_1, /* So the counter will count input clock periods (Clk_counter, taking into account the clock prescaler) */
//         /* .capture1InputMode = */ CY_TCPWM_INPUT_RISINGEDGE, /* This input is NOT used, leave it in default state (CY_TCPWM_INPUT_RISINGEDGE = 0UL) */
//         /* .capture1Input     = */ CY_TCPWM_INPUT_0,
//         /* .enableCompare1Swap= */ false, /* Disable CC1 */
//         /* .compare2          = */ 0,
//         /* .compare3          = */ 0,
//         /* .trigger0Event     = */ CY_TCPWM_CNT_TRIGGER_ON_DISABLED, /* Disable output trigger0 event generation*/
//         /* .trigger1Event     = */ CY_TCPWM_CNT_TRIGGER_ON_DISABLED, /* Disable output trigger1 event generation*/
//     };

// cy_stc_tcpwm_counter_config_t tcpwm_counter_config =
// {
//     /* .period            = */ 65000UL, /* Period of 100 (0-99). Terminal count event when rolls over back to 0. */
//     /* .clockPrescaler    = */ CY_TCPWM_COUNTER_PRESCALER_DIVBY_1, /* Clk_counter = Clk_input / 4 */
//     /* .runMode           = */ CY_TCPWM_COUNTER_CONTINUOUS, /* Wrap around at terminal count. */
//     /* .countDirection    = */ CY_TCPWM_COUNTER_COUNT_UP, /* Up counter, counting from 0 to period value. */
//     /* .compareOrCapture  = */ CY_TCPWM_COUNTER_MODE_COMPARE, /* Trigger interrupt/event signal when Counter value is equal to Compare0 */
//     /* .compare0          = */ 0UL,
//     /* .compare1          = */ 0UL,
//     /* .enableCompareSwap = */ false, /* Upon a compare event, swap the Compare0 and Compare1 values. */
//     /* .interruptSources  = */ CY_TCPWM_INT_NONE,
//     /* .captureInputMode  = */ CY_TCPWM_INPUT_RISINGEDGE, /* This input is NOT used, leave it in default state (CY_TCPWM_INPUT_RISINGEDGE = 0UL) */
//     /* .captureInput      = */ CY_TCPWM_INPUT_0,
//     /* .reloadInputMode   = */ CY_TCPWM_INPUT_RISINGEDGE, /* This input is NOT used, leave it in default state (CY_TCPWM_INPUT_RISINGEDGE = 0UL) */
//     /* .reloadInput       = */ CY_TCPWM_INPUT_0,
//     /* .startInputMode    = */ CY_TCPWM_INPUT_RISINGEDGE, /* This input is NOT used, leave it in default state (CY_TCPWM_INPUT_RISINGEDGE = 0UL) */
//     /* .startInput        = */ CY_TCPWM_INPUT_0,
//     /* .stopInputMode     = */ CY_TCPWM_INPUT_RISINGEDGE, /* This input is NOT used, leave it in default state (CY_TCPWM_INPUT_RISINGEDGE = 0UL) */
//     /* .stopInput         = */ CY_TCPWM_INPUT_0,
//     /* .countInputMode    = */ CY_TCPWM_INPUT_LEVEL, /* Set this input to LEVEL and 1 (high logic level) */
//     /* .countInput        = */ CY_TCPWM_INPUT_1 /* So the counter will count input clock periods (Clk_counter, taking into account the clock prescaler) */
// };

//#define COUNTER_NUMBER 0

volatile time[128];


__attribute__((optimize(0))) __attribute__ ((noinline)) void native_channel(){
    int probe_time, time1, time2, time3, time4;
    for (int touch_n_lines = 0; touch_n_lines < I_N_CACHE_SETS; touch_n_lines++)
    {
    // for(int sample = 0; sample < 1000; sample++)
        {

            prime();
            touch_ns(touch_n_lines);
            time[touch_n_lines] = probe_all_s();
        }
    }
    for (int i = 0; i < 128; i++)
    {
        LOG_INFFMT("%d %d\n", i, time[i]);
    }
    
}

//int probe_time_way_0[I_CACHE_LINE_SIZE];

// int test(void)
// {
//     char x;
//     struct psa_invec invecs[1] = {{&x, sizeof(x)}};
//     prime();
//     x = 0;
//     psa_call(TFM_APPROT_SERVICE1_HANDLE, PSA_IPC_CALL, invecs, 1, NULL, 0);

//     //measure the time to access the N_CAHCE_SETS I-cache line buffer
//     for(int line = 0; line < N_CACHE_SETS; line++)
//         probe_time_way_0[line] = probe_line_s(line, 0);

//     for(int line = 0; line < N_CACHE_SETS; line++)
//         LOG_INFFMT("%d %d\n", line, probe_time_way_0[line]);

//     LOG_INFFMT("Second_test\n");

//     prime();
//     x = 1;
//     psa_call(TFM_APPROT_SERVICE1_HANDLE, PSA_IPC_CALL, invecs, 1, NULL, 0);

//     //measure the time to access the N_CAHCE_SETS I-cache line buffer
//     for(int line = 0; line < N_CACHE_SETS; line++)
//         probe_time_way_0[line] = probe_line_s(line, 0);

//     for(int line = 0; line < N_CACHE_SETS; line++)
//         LOG_INFFMT("%d %d\n", line, probe_time_way_0[line]);


// }


// static void tfm_covert_service1(void)
// {
//  psa_status_t status;
//     uint32_t arg;
//     psa_msg_t msg;
//     size_t num;
//     int miss_time =0, hit_time = 0;
//     /* Retrieve the message corresponding to the example service signal */
//     status = psa_get(TFM_COVERT_SERVICE1_SIGNAL, &msg);
//     if (status != PSA_SUCCESS) {
//         return;
//     }

//     /* Decode the message */
//     switch (msg.type) {
//     case PSA_IPC_CALL:
//        // test();
//        LOG_INFFMT("Covert Teeeest\n");        
//        //prime();
//       // LOG_INFFMT("Covert Primed\n");        
//         status = PSA_SUCCESS;
//         break;
//     default:
//         /* Invalid message type */
//         LOG_INFFMT("Covert %d\n", msg.type); 
//         status = PSA_ERROR_PROGRAMMER_ERROR;
//         break;
//     }
//     /* Reply with the message result status to unblock the client */
//     psa_reply(msg.handle, status);
// }

    // #define UP_COUNTER
    // int *ptr_ctr_set = &TCPWM0->CTRL_SET, *ptr_ctr_clr = &TCPWM0->CTRL_CLR, 
    //     *ptr_start = &TCPWM0->CMD_START, *ptr_stop = &TCPWM0->CMD_STOP,
    //     *ptr_cnt = &TCPWM0_CNT0->COUNTER;

    // #define config_timer() Cy_TCPWM_Counter_Init(TCPWM0, COUNTER_NUMBER, &tcpwm_counter_config)

    // #define enable_timer() do {\
    //     *ptr_ctr_set = *ptr_ctr_set|1<<COUNTER_NUMBER; \
    //     *ptr_start = (*ptr_start)|1<<COUNTER_NUMBER;\
    //     } while(0)

    // #define disable_timer() do {\
    //     *ptr_stop = (*ptr_stop)|1<<COUNTER_NUMBER;\
    //     *ptr_ctr_clr = *ptr_ctr_clr|1<<COUNTER_NUMBER; \
    //     } while(0)
    #include "cycfg.h"
__attribute__((optimize(0))) __attribute__ ((noinline)) volatile int count(){
  volatile int counter1 = 0, counter2 = 0;
  
  config_timer();
        enable_timer();
        counter1 = *ptr_cnt;
        //prime();
        __asm("nop");
        __asm("nop");
        __asm("nop");
        __asm("nop");
        __asm("nop");
        __asm("nop");
        __asm("nop");
        __asm("nop");
        __asm("nop");
        __asm("nop");
        
        __asm("nop");
        __asm("nop");
        __asm("nop");
        __asm("nop");
        __asm("nop");
        __asm("nop");
        __asm("nop");
        __asm("nop");
        __asm("nop");
        __asm("nop");

        __asm("nop");
        __asm("nop");
        __asm("nop");
        __asm("nop");
        __asm("nop");
        __asm("nop");
        __asm("nop");
        __asm("nop");
        __asm("nop");
        __asm("nop");

        // __asm("nop");
        // __asm("nop");
        // __asm("nop");
        // __asm("nop");
        // __asm("nop");
        // __asm("nop");
        // __asm("nop");
        // __asm("nop");
        // __asm("nop");
        // __asm("nop");
        counter2 = *ptr_cnt;
        LOG_INFFMT("Something to be counted\n");    
        disable_timer();
        LOG_INFFMT("Time %d\n", counter2-counter1);           
}


/**
 * \brief An example service implementation that prints out a message.
 */
static void tfm_covert_service1(void)
{
   const int BUFFER_LEN = 32;
    int counter1 = 0, counter2 = 0;
    psa_msg_t msg;
    psa_status_t r;
    int i;
    uint8_t lines; //needs to be a buffer (or tf-m will fail)
    uint8_t rec_buf[BUFFER_LEN];
    uint8_t send_buf[32] = "Hello World";

    //LOG_INFFMT("Hello from  covert service\n");


    

    psa_get(TFM_COVERT_SERVICE1_SIGNAL, &msg);
    switch (msg.type) {
    case PSA_IPC_CONNECT:
/*        if (service_in_use & TFM_COVERT_SERVICE1_SIGNAL) {
            r = PSA_ERROR_CONNECTION_REFUSED;
        } else {
            service_in_use |= TFM_COVERT_SERVICE1_SIGNAL;
            r = PSA_SUCCESS;
        }*/

        psa_reply(msg.handle, PSA_SUCCESS);
        break;
    case PSA_IPC_CALL:
        //count();
        native_channel();
        //native_channel_2();
        //status = PSA_SUCCESS;
        psa_reply(msg.handle, PSA_SUCCESS);
        break;
    case PSA_IPC_DISCONNECT:
/*        assert((service_in_use & TFM_COVERT_SERVICE1_SIGNAL) != 0);
        service_in_use &= ~TFM_COVERT_SERVICE1_SIGNAL;*/
        psa_reply(msg.handle, PSA_SUCCESS);
        break;
    default:
        /* cannot get here [broken SPM] */
        psa_panic();
        break;
    }
}

/**
 * \brief The example FFM-1.1 partition's entry function.
 */
void covert_main(void)
{
    psa_signal_t signals;

    while (1) {
        signals = psa_wait(PSA_WAIT_ANY, PSA_BLOCK); 
        if (signals & TFM_COVERT_SERVICE1_SIGNAL) {
            tfm_covert_service1();   
        }else{
            /* Should not come here */
            psa_panic();
        }
    }
}
