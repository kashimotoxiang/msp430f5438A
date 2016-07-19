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
	SetVCoreUp(1);
	SetVCoreUp(2);
	SetVCoreUp(3);

	//	//UCS SETTING
	UCSCTL3 |= SELREF__REFOCLK;

	__bis_SR_register(SCG0);                  // Disable the FLL control loop
	UCSCTL0 = 0x0000;                         // Set lowest possible DCOx, MODx
	UCSCTL1 = DCORSEL_6;                     // Select DCO range 24MHz operation
	UCSCTL2 = FLLD_0 + 731;                   // Set DCO Multiplier for 24MHz
											  // (N + 1) * FLLRef = Fdco
											  // (731 + 1) * 32768 = 24MHz
											  // Set FLL Div = fDCOCLK/2
	__bic_SR_register(SCG0);                  // Enable the FLL control loop
	UCSCTL4 |= SELA__DCOCLK + SELS__XT1CLK + SELM__DCOCLK; //ACLK,SMCLK,MCLK Source select
	UCSCTL5 |= DIVPA_2;                                   //ACLK output divide
	UCSCTL6 |= XT1DRIVE_3 + XCAP_0;                       //XT1 cap

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
