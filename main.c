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
extern const u8 lan[];
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
		//OLED_ShowStr(0, 0, text, FONTSIZE68);
		//__bis_SR_register(LPM0_bits + GIE);     // Enter LPM0 w/ interrupts

		OLED_All(0);
		delay_ms(1000);
		OLED_P16x16Ch(0, 0, 1);
		OLED_P16x16Ch(16, 2, 2);
		OLED_P16x16Ch(32, 4, 3);
		OLED_P16x16Ch(48, 6, 4);
		delay_ms(2000);
		Draw_BMP(lan);
		delay_ms(2000);
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
