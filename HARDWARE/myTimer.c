#include "myTimer.h"     //"定时器" -驱动程序 -头文件(处理器内部资源)

//*****************************************************************************
//
// Init_Timer0_A
//
//*****************************************************************************
void Init_Timer0_A(void) //定时器A0初始化设置(用于系统每1ms自动中断一次)
{
	TA1CCR0 = 500000;
	TA1CTL = TASSEL_1 + MC_2 + TACLR;         // SMCLK, contmode, clear TAR
}

//*****************************************************************************
//
// Timer A0 interrupt service routine
//
//*****************************************************************************
#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector=TIMER1_A0_VECTOR
__interrupt void TIMER1_A0_ISR(void)
#elif defined(__GNUC__)
void __attribute__ ((interrupt(TIMER1_A0_VECTOR))) TIMER1_A0_ISR (void)
#else
#error Compiler not supported!
#endif
{
	TA1CCTL0 &= ~CCIE;
	P1OUT ^= 0x01;                            // Toggle P1.0
	TA1CCR0 += 50000;                         // Add Offset to CCR0
	__bic_SR_register_on_exit(SLEEPLIEVEL); // Exit LPM0
}

//*****************************************************************************
//
// Init_Timer0_B
//
//*****************************************************************************
void Init_Timer0_B(void)  //定时器B 初始化设置(用于系统每1ms自动中断一次)
{
	// 使能此定时器的中断, 增计数模式：定时器增计数到 TBCCR0,再从0重新计数
	TBCTL = TBSSEL_2 + MC_1 + TBCLR + TBIE + ID_3;  // 选SMCLK作为此定时器的时钟源, 清零 TBR

	//care	为"SMCLK=XT2=4 MHz"的情况下:  定时时间为1ms = 4000/4M(示波器实测1ms)
	TBCCR0 = 12000;

	//care	为"SMCLK=DCO=20 MHz"的情况下(实际DCO频率>20M):  定时时间为1ms = 20000/20M(示波器实测1ms,则TBCCR0要为20620)			   
	//TBCCR0 = 20620; 
}
