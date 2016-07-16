#include "myTimer.h"     //"��ʱ��" -�������� -ͷ�ļ�(�������ڲ���Դ)

//*****************************************************************************
//
// Init_Timer0_A
//
//*****************************************************************************
void Init_Timer0_A(void) //��ʱ��A0��ʼ������(����ϵͳÿ1ms�Զ��ж�һ��)
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
void Init_Timer0_B(void)  //��ʱ��B ��ʼ������(����ϵͳÿ1ms�Զ��ж�һ��)
{
	// ʹ�ܴ˶�ʱ�����ж�, ������ģʽ����ʱ���������� TBCCR0,�ٴ�0���¼���
	TBCTL = TBSSEL_2 + MC_1 + TBCLR + TBIE + ID_3;  // ѡSMCLK��Ϊ�˶�ʱ����ʱ��Դ, ���� TBR

	//care	Ϊ"SMCLK=XT2=4 MHz"�������:  ��ʱʱ��Ϊ1ms = 4000/4M(ʾ����ʵ��1ms)
	TBCCR0 = 12000;

	//care	Ϊ"SMCLK=DCO=20 MHz"�������(ʵ��DCOƵ��>20M):  ��ʱʱ��Ϊ1ms = 20000/20M(ʾ����ʵ��1ms,��TBCCR0ҪΪ20620)			   
	//TBCCR0 = 20620; 
}
