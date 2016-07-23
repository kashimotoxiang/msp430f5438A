#include "System.h"

//*****************************************************************************
//
// declartion
//
//*****************************************************************************
static void SetVCoreUp(unsigned int level);
//*****************************************************************************
//
// 系统初始化
//
//*****************************************************************************
void System_Init(void) {
	P4DIR &= ~BIT0;  //care 上电后，一定要设为输入,不然，有可能会电源短路
	WDTCTL = WDTPW + WDTHOLD;                 // Stop watchdog timer
	Osccon_Initial(); //晶振初始化函数:定义相关晶振参数

	//  Init_Timer0_B();
}
//*****************************************************************************
//
// 时钟初始化
//
//*****************************************************************************
void Osccon_Initial(void) {
	SetVCoreUp(PMMCOREV_3); // Set Vcore to accomodate for max. allowed system speed

	UCSCTL3 |= SELREF_2;					  // Set DCO FLL reference = REFO

	__bis_SR_register(SCG0);				  // Disable the FLL control loop
	UCSCTL0 = 0x0000;						  // Set lowest possible DCOx, MODx
	UCSCTL1 = DCORSEL_7;					 // Select DCO range 24MHz operation
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

void SetVCoreUp(unsigned int level) {
	// Open PMM registers for write access
	PMMCTL0_H = 0xA5;
	// Make sure no flags are set for iterative sequences
//		while ((PMMIFG & SVSMHDLYIFG) == 0);
//		while ((PMMIFG & SVSMLDLYIFG) == 0);
	// Set SVS/SVM high side new level
	SVSMHCTL = SVSHE + SVSHRVL0 * level + SVMHE + SVSMHRRL0 * level;
	// Set SVM low side to new level
	SVSMLCTL = SVSLE + SVMLE + SVSMLRRL0 * level;
	// Wait till SVM is settled
	while ((PMMIFG & SVSMLDLYIFG) == 0)
		;
	// Clear already set flags
	PMMIFG &= ~(SVMLVLRIFG + SVMLIFG);
	// Set VCore to new level
	PMMCTL0_L = PMMCOREV0 * level;
	// Wait till new level reached
	if ((PMMIFG & SVMLIFG))
		while ((PMMIFG & SVMLVLRIFG) == 0)
			;
	// Set SVS/SVM low side to new level
	SVSMLCTL = SVSLE + SVSLRVL0 * level + SVMLE + SVSMLRRL0 * level;
	// Lock PMM registers for write access
	PMMCTL0_H = 0x00;
}
