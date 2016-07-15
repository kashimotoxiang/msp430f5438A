#include "myTimer.h"     //"定时器" -驱动程序 -头文件(处理器内部资源)

void Init_Timer0_A(void) //定时器A0初始化设置(用于系统每1ms自动中断一次)
{
	// 使能Timer0中断, 增计数模式：定时器增计数到 TAxCCR0,再从0重新计数
	TA0CTL = TASSEL_2 + MC_1 + TACLR + TAIE;  // 选SMCLK作为Timer2的时钟源, 清零 TAR

	//care	为"SMCLK=XT2=4 MHz"的情况下:  定时时间为1ms = 4000/4M(示波器实测1ms)
	//	TA0CCR0 = 4000;
	TA0CCR0 = 12000;

	//care	为"SMCLK=DCO=20 MHz"的情况下(实际DCO频率>20M):  定时时间为1ms = 20000/20M(示波器实测1ms,则TA2CCR0要为20620)			   
	//TA2CCR0 = 20620; 
}

void Init_Timer0_B(void)  //定时器B 初始化设置(用于系统每1ms自动中断一次)
{
	// 使能此定时器的中断, 增计数模式：定时器增计数到 TBCCR0,再从0重新计数
	TBCTL = TBSSEL_2 + MC_1 + TBCLR + TBIE + ID_3;  // 选SMCLK作为此定时器的时钟源, 清零 TBR

	//care	为"SMCLK=XT2=4 MHz"的情况下:  定时时间为1ms = 4000/4M(示波器实测1ms)
	TBCCR0 = 12000;

	//care	为"SMCLK=DCO=20 MHz"的情况下(实际DCO频率>20M):  定时时间为1ms = 20000/20M(示波器实测1ms,则TBCCR0要为20620)			   
	//TBCCR0 = 20620; 
}
