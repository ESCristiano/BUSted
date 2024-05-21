/**
 * DMA1 Generated Driver File.
 * 
 * @file dma1.c
 * 
 * @ingroup  dma1
 * 
 * @brief This file contains the API implementations for the DMA1 driver.
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

 /**
   Section: Included Files
 */

#include <xc.h>
#include "../dma1.h"
void (*DMA1_SCNTI_InterruptHandler)(void);

/**
  Section: DMA1 APIs
*/

void DMA1_Initialize(void)
{   
    
    //DMA Instance Selection : 0x0
    DMASELECT = 0x0;
    //Source Address : &Src
    DMAnSSA = &Src;
    //Destination Address : &Dst
    DMAnDSA= &Dst;
    //SSTP not cleared; SMODE unchanged; SMR GPR; DSTP not cleared; DMODE unchanged; 
    DMAnCON1 = 0x0;
    //Source Message Size : 1
    DMAnSSZ = 100;
    //Destination Message Size : 1
    DMAnDSZ = 100;
    //Start Trigger : SIRQ None; 
    DMAnSIRQ = 0x0;
    //Abort Trigger : AIRQ None; 
    DMAnAIRQ = 0x0;
	
    // Clear Destination Count Interrupt Flag bit
    PIR2bits.DMA1DCNTIF = 0; 
    // Clear Source Count Interrupt Flag bit
    PIR2bits.DMA1SCNTIF = 0; 
    // Clear Abort Interrupt Flag bit
    PIR2bits.DMA1AIF = 0; 
    // Clear Overrun Interrupt Flag bit
    PIR2bits.DMA1ORIF =0; 
    
    PIE2bits.DMA1DCNTIE = 0;
    PIE2bits.DMA1SCNTIE = 1; 
	DMA1_SetSCNTIInterruptHandler(DMA1_DefaultInterruptHandler);
    PIE2bits.DMA1AIE = 0;
    PIE2bits.DMA1ORIE = 0;
	
    //AIRQEN disabled; DGO not in progress; SIRQEN disabled; EN enabled; 
    DMAnCON0 = 0x80;
	 
}

void DMA1_SelectSourceRegion(uint8_t region)
{
    DMASELECT = 0x0;
	DMAnCON1bits.SMR  = region;
}

void DMA1_SetSourceAddress(uint24_t address)
{
    DMAnCON0 = 0x00;
    DMASELECT = 0x0;
	DMAnSSA = address;
    DMAnCON0 = 0x80;
}

void DMA1_SetDestinationAddress(uint16_t address)
{
    DMAnCON0 = 0x00;
    DMASELECT = 0x0;
	DMAnDSA = address;
    DMAnCON0 = 0x80;
}

void DMA1_SetSourceSize(uint16_t size)
{
    DMASELECT = 0x0;
	DMAnSSZ= size;
}

void DMA1_SetDestinationSize(uint16_t size)
{                     
    DMASELECT = 0x0;
	DMAnDSZ= size;
}

uint24_t DMA1_GetSourcePointer(void)
{
    DMASELECT = 0x0;
	return DMAnSPTR;
}

uint16_t DMA1_GetDestinationPointer(void)
{
    DMASELECT = 0x0;
	return DMAnDPTR;
}

void DMA1_SetStartTrigger(uint8_t sirq)
{
    DMASELECT = 0x0;
	DMAnSIRQ = sirq;
}

void DMA1_SetAbortTrigger(uint8_t airq)
{
    DMASELECT = 0x0;
	DMAnAIRQ = airq;
}

void DMA1_StartTransfer(void)
{
    DMASELECT = 0x0;
	DMAnCON0bits.DGO = 1;
}

void DMA1_StartTransferWithTrigger(void)
{
    DMASELECT = 0x0;
	DMAnCON0bits.SIRQEN = 1;
}

void DMA1_StopTransfer(void)
{
    DMASELECT = 0x0;
	DMAnCON0bits.SIRQEN = 0; 
	DMAnCON0bits.DGO = 0;
}

void DMA1_SetDMAPriority(uint8_t priority)
{
	PRLOCK = 0x55;
	PRLOCK = 0xAA;
	PRLOCKbits.PRLOCKED = 0;
	DMA1PR = priority;
	PRLOCK = 0x55;
	PRLOCK = 0xAA;
	PRLOCKbits.PRLOCKED = 1;
}

void __interrupt(irq(IRQ_DMA1SCNT),base(8)) DMA1_DMASCNTI_ISR()
{
    // Clear the source count interrupt flag
    PIR2bits.DMA1SCNTIF = 0;

    if (DMA1_SCNTI_InterruptHandler)
            DMA1_SCNTI_InterruptHandler();
}

void DMA1_SetSCNTIInterruptHandler(void (* InterruptHandler)(void))
{
	 DMA1_SCNTI_InterruptHandler = InterruptHandler;
}

void DMA1_DefaultInterruptHandler(void){
    // add your DMA1 interrupt custom code
    // or set custom function using DMA1_SetSCNTIInterruptHandler() /DMA1_SetDCNTIInterruptHandler() /DMA1_SetAIInterruptHandler() /DMA1_SetORIInterruptHandler()
}
/**
 End of File
*/
