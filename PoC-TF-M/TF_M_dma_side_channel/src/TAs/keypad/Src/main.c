
/*
 * Copyright (c) 2021, Arm Limited. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */
#include "main.h"

const char keymap[] = {
    '1', '4', '7', '*',
    '2', '5', '8', '0',
    '3', '6', '9', '#',
    'A', 'B', 'C', 'D', 
}; 

static void tfm_keypad_service1(void)
{
 psa_status_t status;
    uint32_t arg;
    psa_msg_t msg;
    size_t num;
    uint8_t x; //needs to be a buffer (or tf-m will fail)
    int miss_time =0, hit_time = 0, i;
    /* Retrieve the message corresponding to the example service signal */
    status = psa_get(TFM_KEYPAD_SERVICE1_SIGNAL, &msg);
    if (status != PSA_SUCCESS) {
        return;
    }
    /* Decode the message */
    switch (msg.type) {
    case PSA_IPC_CALL:
        // LOG_INFFMT("***********************************\n");
        // LOG_INFFMT("Entering Read Keypad Secure Service\n");
        // LOG_INFFMT("4-digit Secure PIN = ");
         read_pin();
       // read_pin_get_trace();
        LOG_INFFMT(" %c %c %c %c\n" ,keymap[pin[0]]
                                    ,keymap[pin[1]]
                                    ,keymap[pin[2]]
                                    ,keymap[pin[3]]);
        // LOG_INFFMT("Leaving Read Keypad Secure Service\n");
        // LOG_INFFMT("***********************************\n");
        status = PSA_SUCCESS;
        break;
    default:
        /* Invalid message type */
        status = PSA_ERROR_PROGRAMMER_ERROR;
        break;
    }
    /* Reply with the message result status to unblock the client */
    psa_reply(msg.handle, status);
}

/**
 * \brief The example FFM-1.1 partition's entry function.
 */
void keypad_main(void)
{
    psa_signal_t signals;
    MX_GPIO_Init();
    while (1) {
        signals = psa_wait(PSA_WAIT_ANY, PSA_BLOCK);
        if (signals & TFM_KEYPAD_SERVICE1_SIGNAL) {
            tfm_keypad_service1();   
        }else{
            /* Should not come here */
            psa_panic();
        }
    }
}
