/**
 * System Driver Source File.
 * 
 * @file system.c
 * 
 * @ingroup systemdriver
 * 
 * @brief This file contains the API implementation for the System Driver.
 *
 * @version Driver Version 2.0.2
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

#include "../system.h"

/** 
* @ingroup systemdriver
* @brief Initializes the CPU module.
* @param None.
* @return None.
*/
void CPU_Initialize(void);
void SystemArbiter_Initialize();

void SYSTEM_Initialize(void)
{
    CLOCK_Initialize();
    PIN_MANAGER_Initialize();
    CPU_Initialize();
    DMA1_Initialize();
    Timer0_Initialize();
    UART1_Initialize();
    UART2_Initialize();
    INTERRUPT_Initialize();
    SystemArbiter_Initialize();
}

void CPU_Initialize(void)
{
    //PRLOCKED unlocked; 
    PRLOCK = 0x0;
    //PR priority level 7; 
    SCANPR = 0x7;
    //PR priority level 7; 
    DMA1PR = 0x7;
    //PR priority level 7; 
    DMA2PR = 0x7;
    //PR priority level 7; 
    DMA3PR = 0x7;
    //PR priority level 7; 
    DMA4PR = 0x7;
    //PR priority level 7; 
    MAINPR = 0x7;
    //PR priority level 7; 
    ISRPR = 0x7;
    //PRODH undefined; 
    PRODH = 0x0;
    //PRODL undefined; 
    PRODL = 0x0;
}


void SystemArbiter_Initialize(void)
{
    // This function is dependant on the PR1WAY CONFIG bit
    PRLOCK = 0x55;
    PRLOCK = 0xAA;
    PRLOCKbits.PRLOCKED = 1;
}
