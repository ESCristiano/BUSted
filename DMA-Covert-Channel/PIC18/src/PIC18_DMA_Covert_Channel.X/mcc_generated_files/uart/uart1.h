/**
 * UART1 Generated Driver API Header File
 * 
 * @file uart1.h
 * 
 * @defgroup uart1 UART1
 * 
 * @brief This file contains API prototypes and other datatypes for UART1 module.
 *
 * @version UART1 Driver Version 3.0.4
*/
/*
© [2023] Microchip Technology Inc. and its subsidiaries.

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

#ifndef UART1_H
#define UART1_H

/**
  Section: Included Files
 */

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include "../system/system.h"
#include "uart_drv_interface.h"

#ifdef __cplusplus  // Provide C++ Compatibility

    extern "C" {

#endif

#define UART1_interface UART1


#define UART1_Initialize     UART1_Initialize
#define UART1_Deinitialize   UART1_Deinitialize
#define UART1_Write          UART1_Write
#define UART1_Read           UART1_Read
#define UART1__IsRxReady     UART1_IsRxReady
#define UART1_IsTxReady      UART1_IsTxReady
#define UART1_IsTxDone       UART1_IsTxDone

#define UART1_TransmitEnable       UART1_TransmitEnable
#define UART1_TransmitDisable      UART1_TransmitDisable
#define UART1_AutoBaudSet          UART1_AutoBaudSet
#define UART1_AutoBaudQuery        UART1_AutoBaudQuery
#define UART1_BRGCountSet               (NULL)
#define UART1_BRGCountGet               (NULL)
#define UART1_BaudRateSet               (NULL)
#define UART1_BaudRateGet               (NULL)
#define UART1__AutoBaudEventEnableGet   (NULL)
#define UART1_ErrorGet             UART1_ErrorGet

#define UART1_TxCompleteCallbackRegister     (NULL)
#define UART1_RxCompleteCallbackRegister      (NULL)
#define UART1_TxCollisionCallbackRegister  (NULL)
#define UART1_FramingErrorCallbackRegister UART1_FramingErrorCallbackRegister
#define UART1_OverrunErrorCallbackRegister UART1_OverrunErrorCallbackRegister
#define UART1_ParityErrorCallbackRegister  UART1_ParityErrorCallbackRegister
#define UART1_EventCallbackRegister        (NULL)

/**
 @ingroup uart1
 @struct uart1_status_t
 @breif This is an instance of UART1_STATUS for UART1 module
 */
typedef union {
    struct {
        uint8_t perr : 1;     /**<This is a bit field for Parity Error status*/
        uint8_t ferr : 1;     /**<This is a bit field for Framing Error status*/
        uint8_t oerr : 1;     /**<This is a bit field for Overfrun Error status*/
        uint8_t reserved : 5; /**<Reserved*/
    };
    size_t status;            /**<Group byte for status errors*/
}uart1_status_t;

/**
 Section: Data Type Definitions
 */

/**
 * @ingroup uart1
 * @brief External object for uart_drv_interface.
 */
extern const uart_drv_interface_t UART1;

/**
 * @ingroup uart1
 * @brief This API initializes the UART1 driver.
 *        This routine initializes the UART1 module.
 *        This routine must be called before any other UART1 routine is called.
 *        This routine should only be called once during system initialization.
 * @param None.
 * @return None.
 */
void UART1_Initialize(void);

/**
 * @ingroup uart1
 * @brief This API Deinitializes the UART1 driver.
 *        This routine disables the UART1 module.
 * @param None.
 * @return None.
 */
void UART1_Deinitialize(void);

/**
 * @ingroup uart1
 * @brief This API enables the UART1 module.     
 * @param None.
 * @return None.
 */
inline void UART1_Enable(void);

/**
 * @ingroup uart1
 * @brief This API disables the UART1 module.
 * @param None.
 * @return None.
 */
inline void UART1_Disable(void);

/**
 * @ingroup uart1
 * @brief This API enables the UART1 transmitter.
 *        UART1 should also be enable to send bytes over TX pin.
 * @param None.
 * @return None.
 */
inline void UART1_TransmitEnable(void);

/**
 * @ingroup uart1
 * @brief This API disables the UART1 transmitter.
 * @param None.
 * @return None.
 */
inline void UART1_TransmitDisable(void);

/**
 * @ingroup uart1
 * @brief This API enables the UART1 Receiver.
 *        UART1 should also be enable to receive bytes over RX pin.
 * @param None.
 * @return None.
 */
inline void UART1_ReceiveEnable(void);

/**
 * @ingroup uart1
 * @brief This API disables the UART1 Receiver.
 * @param None.
 * @return None.
 */
inline void UART1_ReceiveDisable(void);

/**
 * @ingroup uart1
 * @brief This API enables the UART1 send break control.
 * @param None.
 * @return None.
 */
inline void UART1_SendBreakControlEnable(void);

/**
 * @ingroup uart1
 * @brief This API disables the UART1 send break control.
 * @param None.
 * @return None.
 */
inline void UART1_SendBreakControlDisable(void);

/**
 * @ingroup uart1
 * @brief This API enables the UART1 AutoBaud Detection.
 * @param bool enable.
 * @return None.
 */
inline void UART1_AutoBaudSet(bool enable);


/**
 * @ingroup uart1
 * @brief This API reads the UART1 AutoBaud Detection Complete bit.
 * @param None.
 * @return None.
 */
inline bool UART1_AutoBaudQuery(void);

/**
 * @ingroup uart1
 * @brief This API Reset the UART1 AutoBaud Detection Complete bit.
 * @param None.
 * @return None.
 */
inline void UART1_AutoBaudDetectCompleteReset(void);

/**
 * @ingroup uart1
 * @brief This API reads the UART1 AutoBaud Detection overflow bit.
 * @param None.
 * @return None.
 */
inline bool UART1_IsAutoBaudDetectOverflow(void);

/**
 * @ingroup uart1
 * @brief This API Reset the UART1 AutoBaud Detection Overflow bit.
 * @param None.
 * @return None.
 */
inline void UART1_AutoBaudDetectOverflowReset(void);

/**
 * @ingroup uart1
 * @brief This API checks if UART1 receiver has received data and ready to be read.
 * @param None.
 * @retval true if UART1 receiver FIFO has a data
 * @retval false UART1 receiver FIFO is empty
 */
bool UART1_IsRxReady(void);

/**
 * @ingroup uart1
 * @brief This function checks if UART1 transmitter is ready to accept a data byte.
 * @param None.
 * @retval true if UART1 transmitter FIFO has atleast 1 byte space
 * @retval false if UART1 transmitter FIFO is full
 */
bool UART1_IsTxReady(void);

/**
 * @ingroup uart1
 * @brief This function return the status of transmit shift register (TSR).
 * @param None.
 * @retval true if Data completely shifted out from the TSR
 * @retval false if Data is present in Transmit FIFO and/or in TSR
 */
bool UART1_IsTxDone(void);

/**
 * @ingroup uart1
 * @brief This function gets the error status of the last read byte.
 *        This function should be called before UART1_Read().
 * @pre RX should be enable by calling UART1_RxEnable() before calling this API.
 * @param None.
 * @return Status of the last read byte. See uart1_status_t struct for more details.
 */
size_t UART1_ErrorGet(void);

/**
 * @ingroup uart1
 * @brief This function reads the 8 bits from receiver FIFO register.
 * @pre The transfer status should be checked to see if the receiver is not empty
 *      before calling this function. UART1_IsRxReady() should be checked in if () before calling this API.
 * @param None.
 * @return 8-bit data from RX FIFO register.
 */
uint8_t UART1_Read(void);

/**
 * @ingroup uart1
 * @brief This function writes a byte of data to the transmitter FIFO register.
 * @pre The transfer status should be checked to see if the transmitter is ready to accept a byte
 *      before calling this function. UART1_IsTxReady() should be checked in if() before calling this API.
 * @param txData  - Data byte to write to the TX FIFO.
 * @return None.
 */
void UART1_Write(uint8_t txData);

/**
 * @ingroup uart1
 * @brief This API registers the function to be called upon UART1 framing error.
 * @param callbackHandler - a function pointer which will be called upon framing error condition.
 * @return None.
 */
void UART1_FramingErrorCallbackRegister(void (* callbackHandler)(void));

/**
 * @ingroup uart1
 * @brief This API registers the function to be called upon UART1 overrun error.
 * @param callbackHandler - a function pointer which will be called upon overrun error condition.
 * @return None.
 */
void UART1_OverrunErrorCallbackRegister(void (* callbackHandler)(void));

/**
 * @ingroup uart1
 * @brief This API registers the function to be called upon UART1 Parity error.
 * @param callbackHandler - a function pointer which will be called upon Parity error condition.
 * @return None.
 */
void UART1_ParityErrorCallbackRegister(void (* callbackHandler)(void));

#ifdef __cplusplus  // Provide C++ Compatibility


    }

#endif

#endif  // UART1_H
