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
long SystemTimeCounter = 0; //ϵͳ��ʱ��ʹר��
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
	//ϵͳ��ʼ��
	System_Init();

	//��ʼ���������
	KeyBroadInit();

	//��ʼ��OLED��ʾģ��
	I2C_OLED_Init();

	//��ʼ������īˮ��
	//IncS_Init();

	//DMA��ʽ��ʼ��ADC
	ADC_Init(DMACLOSE);

	//��ʼ����ʱ��A
	Init_Timer0_A();

	//UART��ʼ��
	UART_Init();

	//DMA��ʽ��ʼ��SPI
	SPI0SlaveDMAInit();

	/*-------------------------------------------------------*/
	while (1) {

		ADCSingleConv = ADCs_Get();

		g_KeyValue=KeyBroadScan();

		OLED_Num2StrShow(ADCSingleConv, "%d", 5, 0);

//		IncS_Num2StrShow(ADCSingleConv, "%d", 5, 0);
//		IncS_P8x16Str(0x04, 0X00, text);
//		IncS_Updata();

		//TA1CCTL0 = CCIE; //��ʼ��ʱ

		//__bis_SR_register(SLEEPLIEVEL + GIE);   // Enter LPM0, enable interrupts
		//__no_operation();                       // Remain in LPM0 until all data

		SPI_SendByte('A');

		//UART_SendByte('A');
	}
}

