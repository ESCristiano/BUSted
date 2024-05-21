/**
 * TMR0 Generated Driver API Header File
 * 
 * @file tmr0.h
 * 
 * @defgroup tmr0 TMR0
 * 
 * @brief This file contains the API prototypes and other data types for the TMR0 driver.
 *
 * @version TMR0 Driver Version 2.1.0
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

#ifndef TMR0_H
#define TMR0_H

#include <stdint.h>
#include <stdbool.h>
#include "timer_interface.h"


/**
 @ingroup tmr0
 @struct TMR_INTERFACE
 @brief Declares an instance of TMR_INTERFACE for the Timer0 module
 */
extern const struct TMR_INTERFACE Timer0;

/**
 * @ingroup tmr0
 * @brief Initializes the Timer0 module.
 *        This routine must be called before any other Timer0 routines.
 * @param None.
 * @return None.
 */
void Timer0_Initialize(void);

/**
 * @ingroup tmr0
 * @brief Starts Timer0.
 * @pre Timer0 should be initialized with Timer0_Initialize() before calling this API.
 * @param None.
 * @return None.
 */
void Timer0_Start(void);

/**
 * @ingroup tmr0
 * @brief Stops Timer0.
 * @pre Timer0 should be initialized with Timer0_Initialize() before calling this API.
 * @param None.
 * @return None.
 */
void Timer0_Stop(void);

/**
 * @ingroup tmr0
 * @brief Reads the 16-bit from the TMR0 register.
 * @pre Timer0 should be initialized with Timer0_Initialize() before calling this API.
 * @param None.
 * @return 16-bit data from the TMR0 register.
 */
uint16_t Timer0_Read(void);

/**
 * @ingroup tmr0
 * @brief Writes the 16-bit value to the TMR0 register.
 * @pre Timer0 should be initialized with Timer0_Initialize() before calling this API.
 * @param timerVal - 16-bit value to be written to the TMR0 register.
 * @return None.
 */
void Timer0_Write(size_t timerVal);

/**
 * @ingroup tmr0
 * @brief Loads the 16-bit value to the TMR0 register.
 * @pre Timer0 should be initialized with Timer0_Initialize() before calling this API.
 * @param None.
 * @return None.
 */
void Timer0_Reload(void);

/**
 * @ingroup tmr0
 * @brief Sets the 16-bit period value to global variable timerTMR0ReloadVal16bit.
 * @pre Timer0 should be initialized with Timer0_Initialize() before calling this API.
 * @param  periodVal - 16-bit period value.
 * @return None.
 */
void Timer0_PeriodCountSet(size_t periodVal);


/**
 * @ingroup tmr0
 * @brief Setter function for Timer0 overflow callback.
 * @param CallbackHandler - Pointer to the custom callback.
 * @return None.
 */
 void Timer0_OverflowCallbackRegister(void (* CallbackHandler)(void));

/**
 * @ingroup tmr0
 * @brief Performs tasks to be executed on timer overflow event
 * @param None.
 * @return None.
 */
void Timer0_Tasks(void);

/**
 * @}
 */
#endif //TMR0_H
