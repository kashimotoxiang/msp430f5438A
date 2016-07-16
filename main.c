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
	double ADCSingleConv = 0;
	char ADCSingleConvStr[10] = { 0 };
	P1DIR |= 0x01;                            // P1.0 output
	System_Init();
	/*-------------------------------------------------------*/
	KeyBroadInit(); //初始化矩阵键盘
	I2C_OLED_Init(); //初始化OLED显示模块
//	ADC_Init(DMACLOSE); //DMA方式初始化ADC

	Init_Timer0_A();
	SPI0SlaveDMAInit(); //DMA方式初始化SPI
	/*-------------------------------------------------------*/
	while (1) {
		//	ADCSingleConv = ADCs_Get();
		OLED_P8x16Str(0, 0, text);
		Num_Show(ADCSingleConv, "%d", 5, 0);
		TA1CCTL0 = CCIE; //开始计时
		__bis_SR_register(SLEEPLIEVEL + GIE);   // Enter LPM0, enable interrupts
		__no_operation();                       // Remain in LPM0 until all data
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
