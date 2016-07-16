//******************************************************************************
//  MSP430F543xA Demo - USCI_B0 I2C Master TX single bytes to MSP430 Slave
//
//  Description: This demo connects two MSP430's via the I2C bus. The master
//  transmits to the slave. This is the master code. It continuously
//  transmits 00h, 01h, ..., 0ffh and demonstrates how to implement an I2C
//  master transmitter sending a single byte using the USCI_B0 TX interrupt.
//  ACLK = n/a, MCLK = SMCLK = BRCLK = default DCO = ~1.045MHz
//
//      ***to be used with msp430x54xA_uscib0_i2c_07.c***
//
//                                /|\  /|\
//                MSP430F5438A     10k  10k     MSP430F5438A
//                   slave         |    |         master
//             -----------------   |    |   -----------------
//           -|XIN  P3.1/UCB0SDA|<-|----+->|P3.1/UCB0SDA  XIN|-
//            |                 |  |       |                 |
//           -|XOUT             |  |       |             XOUT|-
//            |     P3.2/UCB0SCL|<-+------>|P3.2/UCB0SCL     |
//            |                 |          |                 |
//
//   F. Chen
//   Texas Instruments Inc.
//   Dec. 2012
//   Built with CCS Version: 5.2.1 and IAR Embedded Workbench Version: 5.51.1
//******************************************************************************
//*****************************************************************************
//
// #include
//
//*****************************************************************************
#include "myIIC.h"
//*****************************************************************************
//
// IIC≥ı ºªØ
//
//*****************************************************************************
void IIC_Init(void) {
	P3SEL |= 0x06;                            // Assign I2C pins to USCI_B0
	UCB0CTL1 |= UCSWRST;                      // Enable SW reset
	UCB0CTL0 = UCMST + UCMODE_3 + UCSYNC;     // I2C Master, synchronous mode
	UCB0CTL1 = UCSSEL_2 + UCSWRST;            // Use SMCLK, keep SW reset
	UCB0BR0 = 12;                             // fSCL = SMCLK/12 = ~100kHz
	UCB0BR1 = 0;
	UCB0I2CSA = OLED_ADDRESS;                         // Slave Address is 048h
	UCB0CTL1 &= ~UCSWRST;                    // Clear SW reset, resume operation
	UCB0IE |= UCTXIE;                         // Enable TX interrupt
}
//*****************************************************************************
//
//°°IIC°°Send a Byte
//
//*****************************************************************************
inline void IICSendByte(uint8_t Addr, uint8_t TXData) {
	UCB0TXBUF = Addr;
	while (UCB0CTL1 & UCTXSTP)
		;             // Ensure stop condition got sent
	UCB0CTL1 |= UCTR + UCTXSTT;             // I2C TX, start condition
	/*-------------------------------------------------------*/
	UCB0TXBUF = TXData;
	while (UCB0CTL1 & UCTXSTP)
		;             // Ensure stop condition got sent
	UCB0CTL1 |= UCTR + UCTXSTT;             // I2C TX, start condition
}
//*****************************************************************************
//
// IIC÷–∂œ
//
//*****************************************************************************
#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector = USCI_B0_VECTOR
__interrupt void USCI_B0_ISR(void)
#elif defined(__GNUC__)
void __attribute__ ((interrupt(USCI_B0_VECTOR))) USCI_B0_ISR (void)
#else
#error Compiler not supported!
#endif
{
	switch (__even_in_range(UCB0IV, 12)) {
	case 0:
		break;                           // Vector  0: No interrupts
	case 2:
		break;                           // Vector  2: ALIFG
	case 4:
		break;                           // Vector  4: NACKIFG
	case 6:
		break;                           // Vector  6: STTIFG
	case 8:
		break;                           // Vector  8: STPIFG
	case 10:
		break;                           // Vector 10: RXIFG
	case 12:                                  // Vector 12: TXIFG
//		if (TXByteCtr)                          // Check TX byte counter
//		{
//			UCB0TXBUF = TXData;                   // Load TX buffer
//			TXByteCtr--;                          // Decrement TX byte counter
//		} else {
//			UCB0CTL1 |= UCTXSTP;                  // I2C stop condition
//			UCB0IFG &= ~UCTXIFG;                  // Clear USCI_B0 TX int flag
//			__bic_SR_register_on_exit(LPM0_bits); // Exit LPM0
//		}
		break;
	default:
		break;
	}
}
