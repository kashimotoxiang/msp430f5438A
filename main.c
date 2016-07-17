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
long SystemTimeCounter=0;//系统延时即使专用
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
	IncS_Init();//初始化电子墨水屏
	ADC_Init(DMACLOSE); //DMA方式初始化ADC

	Init_Timer0_A();
	SPI0SlaveDMAInit(); //DMA方式初始化SPI
	/*-------------------------------------------------------*/
	//DIS_IMG(PIC_Orientation);
//	DIS_IMG(PIC_WHITE);
//	DIS_IMG(PIC_WHITE);
	/*-------------------------------------------------------*/
	while (1) {
		ADCSingleConv = ADCs_Get();
		IncS_P8x16Str(0x04, 0X00, text);
		UpDataIncScreen();
		Num_Show(ADCSingleConv, "%d", 5, 0);
		TA1CCTL0 = CCIE; //开始计时
		__bis_SR_register(SLEEPLIEVEL + GIE);   // Enter LPM0, enable interrupts
		__no_operation();                       // Remain in LPM0 until all data
		while (!(UCA2IFG & UCTXIFG))
			;               // USCI_A2 TX buffer ready?
		UCA2TXBUF = 'A';
	}
}

