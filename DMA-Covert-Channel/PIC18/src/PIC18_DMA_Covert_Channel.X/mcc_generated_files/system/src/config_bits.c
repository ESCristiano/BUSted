/**
 * CONFIGURATION BITS Generated Driver Source File.
 * 
 * @file config_bits.c
 * 
 * @ingroup config_bitsdriver
 * 
 * @brief This file contains the API Implementation for the Device Configuration Bits driver.
 *
 * @version Driver Version 2.0.1
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

// Configuration bits: selected in the GUI

//CONFIG1
#pragma config FEXTOSC = OFF     // External Oscillator Mode Selection->Oscillator not enabled
#pragma config RSTOSC = HFINTOSC_1MHZ     // Power-up Default Value for COSC->HFINTOSC with HFFRQ = 4 MHz and CDIV = 4:1

//CONFIG2
#pragma config FCMENP = ON     // Fail-Safe Clock Monitor Enable - Primary XTAL Enable->Fail-Safe Clock Monitor enabled; timer will flag FSCMP bit and OSFIF interrupt on EXTOSC failure.
#pragma config CLKOUTEN = OFF     // Clock Out Enable->CLKOUT function is disabled
#pragma config FCMEN = ON     // Fail-Safe Clock Monitor Enable->Fail-Safe Clock Monitor enabled
#pragma config CSWEN = ON     // Clock Switch Enable->Writing to NOSC and NDIV is allowed
#pragma config FCMENS = ON     // Fail-Safe Clock Monitor Enable - Secondary XTAL Enable->Fail-Safe Clock Monitor enabled; timer will flag FSCMP bit and OSFIF interrupt on SOSC failure.
#pragma config PR1WAY = ON     // PRLOCKED One-Way Set Enable->PRLOCKED bit can be cleared and set only once

//CONFIG3
#pragma config MVECEN = ON     // Multivector Enable->Multi-vector enabled, Vector table used for interrupts
#pragma config MCLRE = EXTMCLR     // Master Clear (MCLR) Enable->If LVP = 0, MCLR pin is MCLR; If LVP = 1, RE3 pin function is MCLR 
#pragma config BOREN = SBORDIS     // Brown-out Reset Enable->Brown-out Reset enabled , SBOREN bit is ignored
#pragma config PWRTS = PWRT_OFF     // Power-up Timer Selection->PWRT is disabled
#pragma config IVT1WAY = ON     // IVTLOCK One-Way Set Enable->IVTLOCKED bit can be cleared and set only once
#pragma config LPBOREN = OFF     // Low-Power BOR Enable->Low-Power BOR disabled

//CONFIG4
#pragma config XINST = OFF     // Extended Instruction Set Enable->Extended Instruction Set and Indexed Addressing Mode disabled
#pragma config LVP = ON     // Low-Voltage Programming Enable->Low voltage programming enabled. MCLR/VPP pin function is MCLR. MCLRE configuration bit is ignored
#pragma config ZCD = OFF     // ZCD Disable->ZCD module is disabled. ZCD can be enabled by setting the ZCDSEN bit of ZCDCON
#pragma config STVREN = ON     // Stack Overflow/Underflow Reset Enable->Stack full/underflow will cause Reset
#pragma config BORV = VBOR_1P9     // Brown-out Reset Voltage Selection->Brown-out Reset Voltage (VBOR) set to 1.9V
#pragma config PPS1WAY = ON     // PPSLOCKED One-Way Set Enable->PPSLOCKED bit can be cleared and set only once; PPS registers remain locked after one clear/set cycle

//CONFIG5
#pragma config WDTCPS = WDTCPS_31     // WDT Period Select->Divider ratio 1:65536; software control of WDTPS
#pragma config WDTE = OFF     // WDT Operating Mode->WDT Disabled; SWDTEN is ignored

//CONFIG6
#pragma config WDTCWS = WDTCWS_7     // WDT Window Select->window always open (100%); software control; keyed access not required
#pragma config WDTCCS = SC     // WDT Input Clock Selector->Software Control

//CONFIG7
#pragma config SAFEN = OFF     // Storage Area Flash (SAF) Enable->SAF disabled
#pragma config BBEN = OFF     // Boot Block Enable->Boot block disabled
#pragma config BBSIZE = BBSIZE_512     // Boot Block Size Selection->Boot Block size is 512 words
#pragma config DEBUG = OFF     // Debugger Enable->Background Debugger disabled

//CONFIG8
#pragma config WRTB = OFF     // Boot Block Write Protection->Boot Block not Write protected
#pragma config WRTC = OFF     // Configuration Register Write Protection->Configuration registers not Write protected
#pragma config WRTD = OFF     // Data EEPROM Write Protection->Data EEPROM not Write protected
#pragma config WRTAPP = OFF     // Application Block Write Protection->Application Block not write protected
#pragma config WRTSAF = OFF     // Storage Area Flash (SAF) Write Protection->SAF not Write Protected

//CONFIG9
#pragma config CP = OFF     // User Program Flash Memory and Data EEPROM Code Protection->PFM and Data EEPROM code protection disabled


/**
 End of File
*/