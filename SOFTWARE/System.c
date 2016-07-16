#include "System.h"
//*****************************************************************************
//
// ϵͳ��ʼ��
//
//*****************************************************************************
void System_Initial_OSC(void) {
	P4DIR &= ~BIT0;  //care �ϵ��һ��Ҫ��Ϊ����,��Ȼ���п��ܻ��Դ��·
	WDTCTL = WDTPW + WDTHOLD;                 // Stop watchdog timer
	Osccon_Initial(); //�����ʼ������:������ؾ������
	/*-------------------------------------------------------*/
	KeyBroadInit(); //��ʼ���������
	I2C_OLED_Init(); //��ʼ��OLED��ʾģ��
	ADC_Init(DMAOPEN); //DMA��ʽ��ʼ��ADC
	SPI0MasterInit(DMAOPEN); //DMA��ʽ��ʼ��SPI
	/*-------------------------------------------------------*/
	//	Init_Timer0_A(); //��ʱ��A0��ʼ������(����ϵͳÿ1ms�Զ��ж�һ��)
	//  Init_Timer0_B();
}
//*****************************************************************************
//
// ʱ�ӳ�ʼ��
//
//*****************************************************************************
void Osccon_Initial(void) {
	SetVCore(PMMCOREV_3);// Set Vcore to accomodate for max. allowed system speed

	UCSCTL3 |= SELREF_2;					  // Set DCO FLL reference = REFO

	__bis_SR_register(SCG0);				  // Disable the FLL control loop
	UCSCTL0 = 0x0000;						  // Set lowest possible DCOx, MODx
	UCSCTL1 = DCORSEL_5;					 // Select DCO range 24MHz operation
	UCSCTL2 = FLLD_1 + 374; 				  // Set DCO Multiplier for 12MHz
	__bic_SR_register(SCG0);				  // Enable the FLL control loop
	P5SEL |= BIT2 + BIT3;					   // Port select XT2

	UCSCTL6 &= ~XT2OFF;					   // Enable XT2

	UCSCTL6 &= ~(XT1OFF);					   // XT1 On
	UCSCTL6 |= XCAP_3; 					   // Internal load cap

	UCSCTL4 &= ~SELS_5;
	UCSCTL4 |= SELS_4;	 //SMCLKѡ��DCOCLKDIV (��Ƶ���Ƶ��)

	UCSCTL7 &= ~(XT2OFFG + XT1LFOFFG + XT1HFOFFG + DCOFFG);
	// Clear XT2,XT1,DCO fault flags
	SFRIFG1 &= ~OFIFG;					  // Clear fault flags

	delayms(800);
	UCSCTL6 &= ~XT2DRIVE0;// Decrease XT2 Drive according to  expected frequency

}
//*****************************************************************************
//
// delayms
//
//*****************************************************************************
void delayms(int count)  // /* X1ms */
{
	int i, j;
	for (i = 0; i < count; i++)
		for (j = 0; j < 2000; j++)
			;
}
//*****************************************************************************
//
// delayns
//
//*****************************************************************************
void delayns(int count)  // /* X1ms */
{
	int i;
	for (i = 0; i < count; i++)
		;
}
