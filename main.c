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
unsigned char FreqStr[] = "Freq:";
unsigned char ProxStr[] = "Prox:";
struct LDC1000DATA_Struct LDC1000 = { 0, 0, 0, 0, 0, 0 };
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

	//��ʼ����ʱ��
	Init_Timer0_A(); //��ʱ��A0��ʼ������(����ϵͳÿ1ms�Զ��ж�һ��)

	//��ʼ���������
	KeyBroadInit();

	//��ʼ��OLED��ʾģ��
	I2C_OLED_Init();

	//��ʼ������īˮ��
	IncS_Init();

	//DMA��ʽ��ʼ��ADC
	ADC_Init(DMACLOSE);

	//��ʼ����ʱ��A
	Init_Timer0_A();

	//UART��ʼ��
	UART_Init();

	//LDC1000��ʼ��
	//while (LDC1000.freq == 0 || LDC1000.prox == 0) {
	//	LDC1000_INIT();
	//	LDC1000_ValueGet(&LDC1000);
	//}
	DIS_IMG(PIC_WHITE);
	//��Ҫ��Ϣ��ʾ
	IncS_P24x32Str(15, 0, FreqStr);
	IncS_P24x32Str(7, 0, ProxStr);
	//������Ļ
	IncS_Updata();
	IncS_P24x32Str(15, 0, FreqStr);
	IncS_P24x32Str(7, 0, ProxStr);
	//������Ļ
	IncS_Updata();
	/*-------------------------------------------------------*/
	while (1) {

		ADCSingleConv = ADCs_Get();
//
//		g_KeyValue=KeyBroadScan();
//
		OLED_Num2StrShow_Int(ADCSingleConv, 5, 0);

		//LDC1000_ValueGet(&LDC1000);

		//��ʾƵ�ʺ�prox
		IncS_Num2StrShow_Double(LDC1000.freq, 11, 0);	//COUNTOF(FreqStr)
		IncS_Num2StrShow_Double(LDC1000.prox, 3, 0);	//COUNTOF(ProxStr)

		//������Ļ
		IncS_Updata();

//		TA1CCTL0 = CCIE; //��ʼ��ʱ
//		__bis_SR_register(SLEEPLIEVEL + GIE);   // Enter LPM0, enable interrupts
//		__no_operation();                       // Remain in LPM0 until all data

		//SPI_SendByte('A');

		//UART_SendByte('A');
	}
}

