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

#include <xc.h>
#include "../uart2.h"

// Set the UART2 module to the options selected in the user interface.
void UART2_Initialize(void) {
    // TXB disabled; 
    U2TXB = 0x0;
    // P1L 0x0; 
    U2P1L = 0x0;
    // P2L 0x0; 
    U2P2L = 0x0;
    // P3L 0x0; 
    U2P3L = 0x0;
    // BRGS normal speed; ABDEN disabled; TXEN disabled; RXEN disabled; MODE Asynchronous 8-bit mode; 
    U2CON0 = 0x0;
    // ON disabled; WUE disabled; RXBIMD Set RXBKIF on rising RX input; BRKOVR disabled; SENDB disabled; 
    U2CON1 = 0x0;
    // RUNOVF RX input shifter stops all activity; RXPOL not inverted; STP Transmit 1Stop bit, receiver verifies first Stop bit; TXPOL not inverted; FLO off; 
    U2CON2 = 0x0;
    // BRGL 0x0; 
    U2BRGL = 0x0;
    // BRGH 0x0; 
    U2BRGH = 0x0;
    // TXWRE No error; STPMD in middle of first Stop bit; TXBE empty; 
    U2FIFO = 0x20;
    // WUIF WUE not enabled by software; ABDIF Auto-baud not enabled or not complete; ABDIE disabled; 
    U2UIR = 0x0;
    // TXMTIF empty; PERIF Byte not at top; ABDOVF Not overflowed; CERIF No Checksum error; FERIF no error; RXBKIF No Break detected; RXFOIF not overflowed; TXCIF equal; 
    U2ERRIR = 0x80;
    // TXMTIE disabled; PERIE disabled; ABDOVE disabled; CERIE disabled; FERIE disabled; RXBKIE disabled; RXFOIE disabled; TXCIE disabled; 
    U2ERRIE = 0x0;
}
