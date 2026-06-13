
/*
 * Copyright (c) 2021, Arm Limited. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#include <stdint.h>
#include "psa/service.h"
#include "psa_manifest/appRoT.h"
//#include "tfm/tfm_spm_services.h"
#include "tfm_sp_log.h"
#include <assert.h>
#include "cmsis.h"

// #include "psa/crypto.h"
// #include "psa_manifest/sid.h"

// #ifdef AES_CACHE_PATTERN
// #include "tfm_memory_utils.h"
// #define BIT_SIZE_TEST_KEY (128)
// #define BIT_SIZE_TEST_LONG_KEY (256)
// #define BYTE_SIZE_TEST_KEY (BIT_SIZE_TEST_KEY/8)
// #define BYTE_SIZE_CHUNK (16)
// #define ENC_DEC_BUFFER_SIZE (32)
// #define ASSOCIATED_DATA_SIZE (24)
// #define TEST_MAX_KEY_LENGTH (64)
// #define TRUNCATED_AUTH_TAG_LEN (8)
// #define CIPHER_TEST_KEY_ID (0x1)
// uint8_t plain_text[BYTE_SIZE_CHUNK] = "Sixteen bytes!!";
// int probe_time_way_0[N_CACHE_SETS];


// void psa_cipher_test(const psa_key_type_t key_type,
//                      const psa_algorithm_t alg)
// {
//     psa_cipher_operation_t handle = psa_cipher_operation_init();
//     psa_cipher_operation_t handle_dec = psa_cipher_operation_init();
//     psa_status_t status = PSA_SUCCESS;
//     psa_key_handle_t key_handle;
//     const uint8_t data[] = "THIS IS MY KEY1";
//     const size_t iv_length = PSA_BLOCK_CIPHER_BLOCK_LENGTH(key_type);
//     const uint8_t iv[] = "012345678901234";
//     uint8_t decrypted_data[ENC_DEC_BUFFER_SIZE] = {0};
//     size_t output_length = 0, total_output_length = 0;
//     uint8_t encrypted_data[ENC_DEC_BUFFER_SIZE] = {0};
//     uint32_t comp_result;
//     psa_key_attributes_t key_attributes = psa_key_attributes_init();
//     psa_key_usage_t usage = (PSA_KEY_USAGE_ENCRYPT | PSA_KEY_USAGE_DECRYPT);
//     uint32_t i;

//     /* FIXME: Special override for the CC312 accelerator. Implemented because
//      * there is not yet a generic way to override tests.
//      */
// #ifdef CRYPTO_HW_ACCELERATOR_CC312
//     if (alg == PSA_ALG_CFB) {
//         TEST_LOG("%s %s", "The CC312 does not support CFB mode.",
//                  "The test execution was SKIPPED.\r\n");
//         return;
//     }
// #endif /* CRYPTO_HW_ACCELERATOR_CC312 */

//     /* Setup the key policy */
//     psa_set_key_usage_flags(&key_attributes, usage);
//     psa_set_key_algorithm(&key_attributes, alg);
//     psa_set_key_type(&key_attributes, key_type);
//     psa_set_key_id(&key_attributes, CIPHER_TEST_KEY_ID);

//     /* Import a key */
//     status = psa_import_key(&key_attributes, data, sizeof(data), &key_handle);
//     if (status != PSA_SUCCESS) {
//         LOG_INFFMT("Error importing a key\n");
//         goto destroy_key;
//     }

//     status = psa_get_key_attributes(key_handle, &key_attributes);
//     if (status != PSA_SUCCESS) {
//         LOG_INFFMT("Error getting key metadata\n");
//         goto destroy_key;
//     }

//     if (psa_get_key_bits(&key_attributes) != BIT_SIZE_TEST_KEY) {
//         LOG_INFFMT("The number of key bits is different from expected\n");
//         goto destroy_key;
//     }

//     if (psa_get_key_type(&key_attributes) != key_type) {
//         LOG_INFFMT("The type of the key is different from expected\n");
//         goto destroy_key;
//     }

//     psa_reset_key_attributes(&key_attributes);

//     /* Setup the encryption object */
//     status = psa_cipher_encrypt_setup(&handle, key_handle, alg);
//     if (status != PSA_SUCCESS) {
//         if (status == PSA_ERROR_NOT_SUPPORTED) {
//             LOG_INFFMT("Algorithm NOT SUPPORTED by the implementation\n");
//         } else {
//             LOG_INFFMT("Error setting up cipher operation object\n");
//         }
//         goto destroy_key;
//     }

//     /* Set the IV */
//     if (alg != PSA_ALG_ECB_NO_PADDING) {
//         status = psa_cipher_set_iv(&handle, iv, iv_length);
//         if (status != PSA_SUCCESS) {
//             LOG_INFFMT("Error setting the IV on the cypher operation object\n");
//             status = psa_cipher_abort(&handle);
//             if (status != PSA_SUCCESS) {
//                 LOG_INFFMT("Error aborting the operation\n");
//             }
//             goto destroy_key;
//         }
//     }

//     prime();

//     /* Encrypt one chunk of information */
//     status = psa_cipher_update(&handle, plain_text, BYTE_SIZE_CHUNK,
//                                encrypted_data, ENC_DEC_BUFFER_SIZE,
//                                &output_length);

//     //measure the time to access the N_CAHCE_SETS I-cache line buffer
//     for(int line = 0; line < N_CACHE_SETS; line++)
//         probe_time_way_0[line] = probe_line_s(line, 0);

//     for(int line = 0; line < N_CACHE_SETS; line++)
//         LOG_INFFMT("%d %d\n", line, probe_time_way_0[line]);

//     if (status != PSA_SUCCESS) {
//         LOG_INFFMT("Error encrypting one chunk of information\n");
//         status = psa_cipher_abort(&handle);
//         if (status != PSA_SUCCESS) {
//             LOG_INFFMT("Error aborting the operation\n");
//         }
//         goto destroy_key;
//     }

//     if (output_length != BYTE_SIZE_CHUNK) {
//         LOG_INFFMT("Expected encrypted data length is different from expected\n");
//         status = psa_cipher_abort(&handle);
//         if (status != PSA_SUCCESS) {
//             LOG_INFFMT("Error aborting the operation\n");
//         }
//         goto destroy_key;
//     }

//     /* Finalise the cipher operation */
//     status = psa_cipher_finish(&handle, &encrypted_data[output_length],
//                                ENC_DEC_BUFFER_SIZE - output_length,
//                                &output_length);

//     if (status != PSA_SUCCESS) {
//         LOG_INFFMT("Error finalising the cipher operation\n");
//         status = psa_cipher_abort(&handle);
//         if (status != PSA_SUCCESS) {
//             LOG_INFFMT("Error aborting the operation\n");
//         }
//         goto destroy_key;
//     }

//     if (output_length != 0) {
//         LOG_INFFMT("Unexpected output length after finalisation\n");
//         goto destroy_key;
//     }

//     /* Setup the decryption object */
//     if (alg == PSA_ALG_CFB) {
//         /* In CFB mode the object is always in encryption mode */
//         status = psa_cipher_encrypt_setup(&handle_dec, key_handle, alg);
//     } else {
//         status = psa_cipher_decrypt_setup(&handle_dec, key_handle, alg);
//     }

//     if (status != PSA_SUCCESS) {
//         LOG_INFFMT("Error setting up cipher operation object\n");
//         goto destroy_key;
//     }

//     /* Set the IV for decryption */
//     if (alg != PSA_ALG_ECB_NO_PADDING) {
//         status = psa_cipher_set_iv(&handle_dec, iv, iv_length);
//         if (status != PSA_SUCCESS) {
//             LOG_INFFMT("Error setting the IV for decryption\n");
//             status = psa_cipher_abort(&handle_dec);
//             if (status != PSA_SUCCESS) {
//                 LOG_INFFMT("Error aborting the operation\n");
//             }
//             goto destroy_key;
//         }
//     }

//     /* Decrypt */
//     for (i = 0; i < ENC_DEC_BUFFER_SIZE; i += BYTE_SIZE_CHUNK) {
//         status = psa_cipher_update(&handle_dec,
//                                    (encrypted_data + i), BYTE_SIZE_CHUNK,
//                                    (decrypted_data + total_output_length),
//                                    (ENC_DEC_BUFFER_SIZE - total_output_length),
//                                    &output_length);

//         if (status != PSA_SUCCESS) {
//             LOG_INFFMT("Error during decryption\n");
//             status = psa_cipher_abort(&handle_dec);
//             if (status != PSA_SUCCESS) {
//                 LOG_INFFMT("Error aborting the operation\n");
//             }
//             goto destroy_key;
//         }

//         total_output_length += output_length;
//     }

// #if DOMAIN_NS == 1U
//     /* Check that the plain text matches the decrypted data */
//     comp_result = memcmp(plain_text, decrypted_data, sizeof(plain_text));
// #else
//     comp_result = tfm_memcmp(plain_text, decrypted_data, sizeof(plain_text));
// #endif
//     if (comp_result != 0) {
//         LOG_INFFMT("Decrypted data doesn't match with plain text\n");
//         status = psa_cipher_abort(&handle_dec);
//         if (status != PSA_SUCCESS) {
//             LOG_INFFMT("Error aborting the operation\n");
//         }
//         goto destroy_key;
//     }

//     /* Finalise the cipher operation for decryption (destroys decrypted data) */
//     status = psa_cipher_finish(&handle_dec, decrypted_data, BYTE_SIZE_CHUNK,
//                                &output_length);

//     if (status != PSA_SUCCESS) {
//         LOG_INFFMT("Error finalising the cipher operation\n");
//         status = psa_cipher_abort(&handle_dec);
//         if (status != PSA_SUCCESS) {
//             LOG_INFFMT("Error aborting the operation\n");
//         }
//         goto destroy_key;
//     }

//     total_output_length += output_length;

//     /* Check that the decrypted length is equal to the original length */
//     if (total_output_length != ENC_DEC_BUFFER_SIZE) {
//         LOG_INFFMT("After finalising, unexpected decrypted length\n");
//         goto destroy_key;
//     }

// #if DOMAIN_NS == 1U
//     /* Clear intermediate buffers for additional single-shot API tests */
//     memset(encrypted_data, 0, sizeof(plain_text));
// #else
//     tfm_memset(decrypted_data, 0, sizeof(plain_text));
// #endif
//    // prime();
//     /* Replicate the encryption-decryption test above using single-shot APIs */
//     status = psa_cipher_encrypt(CIPHER_TEST_KEY_ID, alg, plain_text,
//                                 BYTE_SIZE_CHUNK,
//                                 encrypted_data, ENC_DEC_BUFFER_SIZE,
//                                 &output_length);
//     if (status != PSA_SUCCESS) {
//         LOG_INFFMT("Error encrypting with the single-shot API\n");
//         goto destroy_key;
//     }
// /*     //measure the time to access the N_CAHCE_SETS I-cache line buffer
//     for(int line = 0; line < N_CACHE_SETS; line++)
//         probe_time_way_0[line] = probe_line_s(line, 0);

//     for(int line = 0; line < N_CACHE_SETS; line++)
//         LOG_INFFMT("%d %d\n", line, probe_time_way_0[line]); */

//     status = psa_cipher_decrypt(CIPHER_TEST_KEY_ID, alg, encrypted_data,
//                                 ENC_DEC_BUFFER_SIZE,
//                                 decrypted_data, ENC_DEC_BUFFER_SIZE,
//                                 &output_length);
//     if (status != PSA_SUCCESS) {
//         LOG_INFFMT("Error decrypting with the single shot API\n");
//         goto destroy_key;
//     }

// #if DOMAIN_NS == 1U
//     /* Check that the plain text matches the decrypted data */
//     comp_result = memcmp(plain_text, decrypted_data, sizeof(plain_text));
// #else
//     comp_result = tfm_memcmp(plain_text, decrypted_data, sizeof(plain_text));
// #endif
//     if (comp_result != 0) {
//         LOG_INFFMT("Decrypted data doesn't match with plain text\n");
//     }

// destroy_key:
//     /* Destroy the key */
//     status = psa_destroy_key(key_handle);
//     if (status != PSA_SUCCESS) {
//         LOG_INFFMT("Error destroying a key\n");
//     }

// }
// #endif

// #ifdef HASH_CACHE_PATTERN
// /*
//  * \brief This is the list of algorithms supported by the current
//  *        configuration of the crypto engine used by the crypto
//  *        service. In case the crypto engine default capabilities
//  *        is changed, this list needs to be updated accordingly
//  */
// static const psa_algorithm_t hash_alg[] = {
//     PSA_ALG_SHA_224,
//     PSA_ALG_SHA_256,
//     PSA_ALG_SHA_384,
//     PSA_ALG_SHA_512,
// };

// static const uint8_t hash_val[][PSA_HASH_LENGTH(PSA_ALG_SHA_512)] = {
//     {0x00, 0xD2, 0x90, 0xE2, 0x0E, 0x4E, 0xC1, 0x7E, /*!< SHA-224 */
//      0x7A, 0x95, 0xF5, 0x10, 0x5C, 0x76, 0x74, 0x04,
//      0x6E, 0xB5, 0x56, 0x5E, 0xE5, 0xE7, 0xBA, 0x15,
//      0x6C, 0x23, 0x47, 0xF3},
//     {0x6B, 0x22, 0x09, 0x2A, 0x37, 0x1E, 0xF5, 0x14, /*!< SHA-256 */
//      0xF7, 0x39, 0x4D, 0xCF, 0xAD, 0x4D, 0x17, 0x46,
//      0x66, 0xCB, 0x33, 0xA0, 0x39, 0xD8, 0x41, 0x4E,
//      0xF1, 0x2A, 0xD3, 0x4D, 0x69, 0xC3, 0xB5, 0x3E},
//     {0x64, 0x79, 0x11, 0xBB, 0x47, 0x4E, 0x47, 0x59, /*!< SHA-384 */
//      0x3E, 0x4D, 0xBC, 0x60, 0xA5, 0xF9, 0xBF, 0x9C,
//      0xC0, 0xBA, 0x55, 0x0F, 0x93, 0xCA, 0x72, 0xDF,
//      0x57, 0x1E, 0x50, 0x56, 0xF9, 0x4A, 0x01, 0xD6,
//      0xA5, 0x6F, 0xF7, 0x62, 0x34, 0x4F, 0x48, 0xFD,
//      0x9D, 0x15, 0x07, 0x42, 0xB7, 0x72, 0x94, 0xB8},
//     {0xB4, 0x1C, 0xA3, 0x6C, 0xA9, 0x67, 0x1D, 0xAD, /*!< SHA-512 */
//      0x34, 0x1F, 0xBE, 0x1B, 0x83, 0xC4, 0x40, 0x2A,
//      0x47, 0x42, 0x79, 0xBB, 0x21, 0xCA, 0xF0, 0x60,
//      0xE4, 0xD2, 0x6E, 0x9B, 0x70, 0x12, 0x34, 0x3F,
//      0x55, 0x2C, 0x09, 0x31, 0x0A, 0x5B, 0x40, 0x21,
//      0x01, 0xA8, 0x3B, 0x58, 0xE7, 0x48, 0x13, 0x1A,
//      0x7E, 0xCD, 0xE1, 0xD2, 0x46, 0x10, 0x58, 0x34,
//      0x49, 0x14, 0x4B, 0xAA, 0x89, 0xA9, 0xF5, 0xB1},
// };

// //#define N_CACHE_SETS 256
// int probe_time_way_0[N_CACHE_SETS];
//     char *msg1 =
//         "This is my test message, please generate a hash for this.";
//     char *msg2 =
//         "Tais as ay tast massage, plaase ganarate a hash foa this.";

// void psa_hash_test(const psa_algorithm_t alg,char *msg )
// {
//     /* Length of each chunk in the multipart API */
//     const size_t msg_size[] = {25, 32};
//     const uint32_t msg_num = sizeof(msg_size)/sizeof(msg_size[0]);
//     uint32_t idx, start_idx = 0;
//     psa_status_t status;
//     psa_hash_operation_t handle = psa_hash_operation_init();

//     /* Setup the hash object for the desired hash*/
//     status = psa_hash_setup(&handle, alg);

//     if (status != PSA_SUCCESS) {
//         if (status == PSA_ERROR_NOT_SUPPORTED) {
//             LOG_INFFMT("Algorithm NOT SUPPORTED by the implementation \n");
//             return;
//         }

//         LOG_INFFMT("Error setting up hash operation object\n");
//         return;
//     }
//     prime();
//     /* Update object with all the chunks of message */
//     for (idx=0; idx<msg_num; idx++) {
//         status = psa_hash_update(&handle,
//                                  (const uint8_t *)&msg[start_idx],
//                                  msg_size[idx]);
//         if (status != PSA_SUCCESS) {
//             LOG_INFFMT("Error updating the hash operation object\n");
//             return;
//         }
//         start_idx += msg_size[idx];
//     }

//     //measure the time to access the N_CAHCE_SETS I-cache line buffer
//     for(int line = 0; line < N_CACHE_SETS; line++){
//         probe_time_way_0[line] = probe_line_s(line, 0);
//         //   probe_time_way_1[line] = probe_line(line, 1);
//     }
//     for(int line = 0; line < N_CACHE_SETS; line++)
//         LOG_INFFMT("%d %d\n", line, probe_time_way_0[line]);

//     /* Cycle until idx points to the correct index in the algorithm table */
//     for (idx=0; hash_alg[idx] != alg; idx++);

//     /* Finalise and verify that the hash is as expected */
//     status = psa_hash_verify(&handle, hash_val[idx], PSA_HASH_LENGTH(alg));
//     if (status != PSA_SUCCESS) {
//         LOG_INFFMT("Error verifying the hash operation object\n");
//         return;
//     }

//     /* Do the same as above with the single shot APIs */
//     status = psa_hash_compare(alg,
//                               (const uint8_t *)msg, strlen(msg),
//                               hash_val[idx], PSA_HASH_LENGTH(alg));
//     if (status != PSA_SUCCESS) {
//         LOG_INFFMT("Error using the single shot API\n");
//         return;
//     }

//    // ret->val = TEST_PASSED;
// }
// #endif

// static void tfm_crypto_test_1035()
// {
//     psa_status_t status;
//     psa_key_handle_t key_handle;
//     const uint8_t data[] = "THIS IS MY KEY1";
//     psa_key_attributes_t key_attributes = psa_key_attributes_init();

//     /* Set key sage and type */
//     psa_set_key_usage_flags(&key_attributes, PSA_KEY_USAGE_EXPORT);
//     psa_set_key_type(&key_attributes, PSA_KEY_TYPE_AES);

//     status = psa_import_key(&key_attributes, data, sizeof(data),
//                             &key_handle);
//     if (status != PSA_SUCCESS) {
//         LOG_INFFMT("Failed to import key");
//         return;
//     }

//     /* Destroy the key */
//     status = psa_destroy_key(key_handle);
//     if (status != PSA_SUCCESS) {
//         LOG_INFFMT("Error destroying a key");
//     }
// }

// int test(void)
// {
//     int miss_time, hit_time;
//     #ifdef HASH_CACHE_PATTERN
//     char *msg_changed[] = {"Tais as ay tast massage, ",
//                              "plaase ganarate a hash foa this."};
//     #endif
//     #ifdef AES_CACHE_PATTERN
//         uint8_t plain_text_changed[BYTE_SIZE_CHUNK] = "TTTTTTT bytes!!";
//     #endif

//     //measure hit and miss time
//     miss_time = probe_line_s(0, 0);
//     hit_time = probe_line_s(0, 0);
//     LOG_INFFMT("cache_sets %d\n", N_CACHE_SETS);
//     LOG_INFFMT("miss_time %d\n", miss_time);
//     LOG_INFFMT("hit_time %d\n", hit_time);

//     #ifdef HASH_CACHE_PATTERN
//         LOG_INFFMT("HASH_CACHE_PATTERN\r\n");
//         psa_hash_test(PSA_ALG_SHA_224, msg1);
//         LOG_INFFMT("Second_test\n");
//         psa_hash_test(PSA_ALG_SHA_224, msg2);
//     #endif
//     #ifdef AES_CACHE_PATTERN
//         LOG_INFFMT("AES_CACHE_PATTERN\r\n");
//         psa_cipher_test(PSA_KEY_TYPE_AES, PSA_ALG_CTR);
//         for (int i = 0; i < BYTE_SIZE_CHUNK; i++)
//             plain_text[i] = plain_text_changed[i];
//         LOG_INFFMT("Second_test\n");
//         psa_cipher_test(PSA_KEY_TYPE_AES, PSA_ALG_CTR);
//     #endif
// }

int dummy(int x)
{
    if(!x){
        LOG_INFFMT("Dummy Thing\n");
    }else{
        LOG_INFFMT(" Extreme Dummy THING \n");
    }
}

static void tfm_appRoT_service1(void)
{
 psa_status_t status;
    uint32_t arg;
    psa_msg_t msg;
    size_t num;
    uint8_t x; //needs to be a buffer (or tf-m will fail)
    int miss_time =0, hit_time = 0, i;
    /* Retrieve the message corresponding to the example service signal */
    status = psa_get(TFM_APPROT_SERVICE1_SIGNAL, &msg);
    if (status != PSA_SUCCESS) {
        return;
    }

    /* Decode the message */
    switch (msg.type) {
    case PSA_IPC_CALL:
        if (msg.in_size[i] != 0) {
                psa_read(msg.handle, 0, &x, 1);
            } 
        dummy(x);        
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
void appRoT_main(void)
{
    psa_signal_t signals;

    while (1) {
        signals = psa_wait(PSA_WAIT_ANY, PSA_BLOCK);
        if (signals & TFM_APPROT_SERVICE1_SIGNAL) {
            tfm_appRoT_service1();   
        }else{
            /* Should not come here */
            psa_panic();
        }
    }
}
