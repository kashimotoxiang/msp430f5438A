#include "System.h"
//*****************************************************************************
//
// 系统初始化
//
//*****************************************************************************
void System_Initial_OSC(void) {
	P4DIR &= ~BIT0;  //care 上电后，一定要设为输入,不然，有可能会电源短路
	WDTCTL = WDTPW + WDTHOLD;                 // Stop watchdog timer
	Osccon_Initial(); //晶振初始化函数:定义相关晶振参数
	/*-------------------------------------------------------*/
	KeyBroadInit(); //初始化矩阵键盘
	I2C_OLED_Init(); //初始化OLED显示模块
	ADC_Init(DMAOPEN); //DMA方式初始化ADC
	SPI0MasterInit(DMAOPEN); //DMA方式初始化SPI
	/*-------------------------------------------------------*/
	//	Init_Timer0_A(); //定时器A0初始化设置(用于系统每1ms自动中断一次)
	//  Init_Timer0_B();
}
//*****************************************************************************
//
// 时钟初始化
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
	UCSCTL4 |= SELS_4;	 //SMCLK选择DCOCLKDIV (倍频后的频率)

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
