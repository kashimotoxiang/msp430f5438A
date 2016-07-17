//******************************************************************************
//   MSP430F543xA Demo - USCI_A1, 115200 UART Echo ISR, DCO SMCLK
//
//   Description: Echo a received character, RX ISR used. Normal mode is LPM0.
//   USCI_A1 RX interrupt triggers TX Echo.
//   Baud rate divider with 1048576hz = 1048576/115200 = ~9.1 (009h|01h)
//   ACLK = REFO = ~32768Hz, MCLK = SMCLK = default DCO = 32 x ACLK = 1048576Hz
//   See User Guide for baud rate divider table
//
//                 MSP430F5438A
//             -----------------
//         /|\|                 |
//          | |                 |
//          --|RST              |
//            |                 |
//            |     P3.4/UCA1TXD|------------>
//            |                 | 115200 - 8N1
//            |     P3.5/UCA1RXD|<------------
//
//   M. Morales
//   Texas Instruments Inc.
//   June 2009
//   Built with CCE Version: 3.2.2 and IAR Embedded Workbench Version: 4.11B
//******************************************************************************
//*****************************************************************************
//
// include
//
//*****************************************************************************
#include "main.h"

//*****************************************************************************
//
//  UART_Init
//  while (!(UCA1IFG&UCTXIFG));             // USCI_A1 TX buffer ready?
//	UCA1TXBUF = UCA1RXBUF;                  // TX -> RXed character
//
//*****************************************************************************
void UART_Init(void) {
	P5SEL = BIT6 + BIT7;                             // P3.4,5 = USCI_A1 TXD/RXD
	UCA1CTL1 |= UCSWRST;                      // **Put state machine in reset**
	UCA1CTL1 |= UCSSEL_2;                     // SMCLK
	UCA1BR0 = 9;                              // 1MHz 115200 (see User's Guide)
	UCA1BR1 = 0;                              // 1MHz 115200
	UCA1MCTL |= UCBRS_1 + UCBRF_0;            // Modulation UCBRSx=1, UCBRFx=0
	UCA1CTL1 &= ~UCSWRST;                   // **Initialize USCI state machine**
	//UCA1IE |= UCRXIE;                         // Enable USCI_A1 RX interrupt
}

//*****************************************************************************
//
// UART中断服务函数
//
//*****************************************************************************
// Echo back RXed character, confirm TX buffer is ready first
#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector=USCI_A1_VECTOR
__interrupt void USCI_A1_ISR(void)
#elif defined(__GNUC__)
void __attribute__ ((interrupt(USCI_A1_VECTOR))) USCI_A1_ISR (void)
#else
#error Compiler not supported!
#endif
{
	switch (__even_in_range(UCA1IV, 4)) {
	case 0:
		break;                             // Vector 0 - no interrupt
	case 2:                                   // Vector 2 - RXIFG
		break;
	case 4:
		break;                             // Vector 4 - TXIFG
	default:
		break;
	}
}

//*****************************************************************************
//
// UART发送
//
//*****************************************************************************
inline void UART_SendByte(uint8_t TXData) {
	while (!(UCA1IFG & UCTXIFG))
		;             // USCI_A1 TX buffer ready?
	UCA1TXBUF = TXData;
}
