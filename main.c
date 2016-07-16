//*****************************************************************************
//
// include
//
//*****************************************************************************
#include "main.h"
//*****************************************************************************
//
// variable
//
//*****************************************************************************
SPIDataType g_SPIRxBuf[SPI_RXBUF_SIZE];
ADCDataType g_ADCConvBuf[ADC_CONVBUF_SIZE];
int g_KeyValue;
unsigned char text[] = "ADC:";
//*****************************************************************************
//
// main
//
//*****************************************************************************
int main(void) {
	System_Initial_OSC();
	while (1) {
		g_KeyValue = KeyBroadScan();
		OLED_ShowStr(0, 0, text, COUNTOF(text));
		//__bis_SR_register(LPM0_bits + GIE);     // Enter LPM0 w/ interrupts
	}
}
//*****************************************************************************
//
// interrupt
//
//*****************************************************************************
#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector=USCI_A0_VECTOR
__interrupt void USCI_A0_ISR(void)
#elif defined(__GNUC__)
void __attribute__ ((interrupt(USCI_A0_VECTOR))) USCI_A0_ISR (void)
#else
#error Compiler not supported!
#endif
{
	switch (__even_in_range(UCA0IV, 4)) {
	case 0:
		break;                          // Vector 0 - no interrupt
	case 2:                                 // Vector 2 - RXIFG
		while (!(UCA0IFG & UCTXIFG))
			;           // USCI_A0 TX buffer ready?

		break;
	case 4:
		break;                          // Vector 4 - TXIFG
	default:
		break;
	}
}
