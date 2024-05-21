/**
 * DMA1 Generated Driver API Header File.
 * 
 * @file dma1.h
 * 
 * @defgroup  dma1 DMA1
 * 
 * @brief This file contains the API prototypes for the DMA1 driver.
 *
 * @version DMA1 Driver Version 2.11.0
 */

/*
� [2023] Microchip Technology Inc. and its subsidiaries.

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

#ifndef DMA1_H
#define DMA1_H

/**
  Section: Included Files
*/
#include <stdint.h>

/**
 * @var uint16_t Src
 * @brief Source address.
 */
uint16_t Src[1];
/**
 * @var uint16_t Dst
 * @brief Destination address.
 */
uint16_t Dst[1];

/**
 * @ingroup dma1
 * @brief Initializes the DMA1 module. This is called only once before calling other DMA1 APIs.
 * @param None.
 * @return None. 
 */
void DMA1_Initialize(void);

/**
 * @ingroup dma1
 * @brief Sets the source region.
 * @param [in] region - Desired source region.
 * @return None.
 */
void DMA1_SelectSourceRegion(uint8_t region);

/**
 * @ingroup dma1
 * @brief Sets the source address for the DMA packet.
 * @param [in] address - Desired source address.
 * @return None.
 */
void DMA1_SetSourceAddress(uint24_t address);

/**
 * @ingroup dma1
 * @brief Sets the destination address for the DMA packet.
 * @param [in] address - Desired destination address.
 * @return None.
 */
void DMA1_SetDestinationAddress(uint16_t address);

/**
 * @ingroup dma1
 * @brief Sets the size of the source array.
 * @param [in] size - Size of the source array in bytes.
 * @return None.
 */
void DMA1_SetSourceSize(uint16_t size);

/**
 * @ingroup dma1
 * @brief Sets the size of the destination array.
 * @param [in] size - Size of the destination array in bytes.
 * @return None.
 */
void DMA1_SetDestinationSize(uint16_t size);

/**
 * @ingroup dma1
 * @brief Returns the current location read by the DMA.
 * @param None.
 * @return Current address pointer to the source.
 */
uint24_t DMA1_GetSourcePointer(void);

/**
 * @ingroup dma1
 * @brief Returns the current location written by the DMA.
 * @param None.
 * @return Current address pointer to the destination.
 */
uint16_t DMA1_GetDestinationPointer(void);

/**
 * @ingroup dma1
 * @brief Sets the Start Trigger for the DMA. Note that this function does not start the transfer.
 * @param [in] sirq - Start trigger source.
 * @return None.
 */
void DMA1_SetStartTrigger(uint8_t sirq);

/**
 * @ingroup dma1
 * @brief Sets the Abort Trigger for the DMA. Note that this function does not start the transfer.
 * @param [in] airq - Abort trigger source.
 * @return None.
 */
void DMA1_SetAbortTrigger(uint8_t airq);

/**
 * @ingroup dma1
 * @brief Starts the DMA Transfer.
 * @param None.
 * @return None.
 */
void DMA1_StartTransfer(void);

/**
 * @ingroup dma1
 * @brief Starts the DMA transfer based on the requested interrupt source.
 * @param None.
 * @return None.
 */
void DMA1_StartTransferWithTrigger(void);	

/**
 * @ingroup dma1
 * @brief Stops the DMA transfer.
 * @param None.
 * @return None.
 */
void DMA1_StopTransfer(void);

/**
 * @ingroup dma1
 * @brief Sets the priority of the arbiter.
 * @param [in] priority - Priority of the DMA.
 * @return None.
 * NOTE: This function is dependent on the PR1WAY CONFIG bit.
 */
void DMA1_SetDMAPriority(uint8_t priority);

void DMA1_SetSCNTIInterruptHandler(void (* InterruptHandler)(void));


/**
 * @ingroup dma1
 * @brief Default interrupt handler for all interrupt events.
 * @param None.
 * @return None.
 */
void DMA1_DefaultInterruptHandler(void);
#endif //DMA1_H
