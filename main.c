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
long SystemTimeCounter = 0; //系统延时即使专用
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
	/*-------------------------------------------------------*/
	//系统初始化
	System_Init();

	//初始化矩阵键盘
	KeyBroadInit();

	//初始化OLED显示模块
	I2C_OLED_Init();

	//初始化电子墨水屏
	//IncS_Init();

	//DMA方式初始化ADC
	ADC_Init(DMACLOSE);

	//初始化定时器A
	Init_Timer0_A();

	//UART初始化
	UART_Init();

	//DMA方式初始化SPI
	SPI0SlaveDMAInit();

	//LDC1000初始化
	/*LDC CLK for Freq counter (set to output selected clock)-------------------------------------------------------*/
	LCD1000_CLK_DIR |= LCD1000_CLK_PIN;
	LCD1000_CLK_SEL |= LCD1000_CLK_PIN;
	/*CS-------------------------------------------------------*/
	LCD1000_CS_DIR |= LCD1000_CS_PIN;  // Output
	LCD1000_CS_SEL &= ~LCD1000_CS_PIN;

	LDC1000_INIT();
	/*-------------------------------------------------------*/
	while (1) {

//		ADCSingleConv = ADCs_Get();
//
//		g_KeyValue=KeyBroadScan();
//
//		OLED_Num2StrShow(ADCSingleConv, "%d", 5, 0);

		LDC1000_INIT();
		LDC1000_READ();
//		IncS_Num2StrShow(ADCSingleConv, "%d", 5, 0);
//		IncS_P8x16Str(0x04, 0X00, text);
//		IncS_Updata();

		//TA1CCTL0 = CCIE; //开始计时

		//__bis_SR_register(SLEEPLIEVEL + GIE);   // Enter LPM0, enable interrupts
		//__no_operation();                       // Remain in LPM0 until all data

		//SPI_SendByte('A');

		//UART_SendByte('A');
	}
}

