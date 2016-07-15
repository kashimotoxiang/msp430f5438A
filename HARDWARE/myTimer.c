#include "myTimer.h"     //"��ʱ��" -�������� -ͷ�ļ�(�������ڲ���Դ)

void Init_Timer0_A(void) //��ʱ��A0��ʼ������(����ϵͳÿ1ms�Զ��ж�һ��)
{
	// ʹ��Timer0�ж�, ������ģʽ����ʱ���������� TAxCCR0,�ٴ�0���¼���
	TA0CTL = TASSEL_2 + MC_1 + TACLR + TAIE;  // ѡSMCLK��ΪTimer2��ʱ��Դ, ���� TAR

	//care	Ϊ"SMCLK=XT2=4 MHz"�������:  ��ʱʱ��Ϊ1ms = 4000/4M(ʾ����ʵ��1ms)
	//	TA0CCR0 = 4000;
	TA0CCR0 = 12000;

	//care	Ϊ"SMCLK=DCO=20 MHz"�������(ʵ��DCOƵ��>20M):  ��ʱʱ��Ϊ1ms = 20000/20M(ʾ����ʵ��1ms,��TA2CCR0ҪΪ20620)			   
	//TA2CCR0 = 20620; 
}

void Init_Timer0_B(void)  //��ʱ��B ��ʼ������(����ϵͳÿ1ms�Զ��ж�һ��)
{
	// ʹ�ܴ˶�ʱ�����ж�, ������ģʽ����ʱ���������� TBCCR0,�ٴ�0���¼���
	TBCTL = TBSSEL_2 + MC_1 + TBCLR + TBIE + ID_3;  // ѡSMCLK��Ϊ�˶�ʱ����ʱ��Դ, ���� TBR

	//care	Ϊ"SMCLK=XT2=4 MHz"�������:  ��ʱʱ��Ϊ1ms = 4000/4M(ʾ����ʵ��1ms)
	TBCCR0 = 12000;

	//care	Ϊ"SMCLK=DCO=20 MHz"�������(ʵ��DCOƵ��>20M):  ��ʱʱ��Ϊ1ms = 20000/20M(ʾ����ʵ��1ms,��TBCCR0ҪΪ20620)			   
	//TBCCR0 = 20620; 
}
