#pragma once

//*****************************************************************************
//
// include
//
//*****************************************************************************
#include "main.h"

//*****************************************************************************
//
// define
//
//*****************************************************************************
#define mClose_WDT      (WDTCTL = WDTPW + WDTHOLD)  // �رտ��Ź�
#define mClr_WDTCNT     (WDTCTL = WDTPW + WDTCNTCL) // �忴�Ź�(����MSP430��Ƭ��)
#define	mNop	        (__no_operation())    //�ղ���ָ��(����"����ʱ"��"����")

#define	mEnable_GIE     (_EINT())  // �������ж�GIE
#define	mDisable_GIE    (_DINT())  // �ر����ж�GIE

#define	mReset_Soft    (PMMCTL0 |= PMMSWPOR) //"�����λ" (MSP430��Ƭ��)

#define	delayms(x) __delay_cycles(24000*x);
#define	delayus(x) __delay_cycles(24*x);
#define	delay42ns(x) __delay_cycles(x);
//*****************************************************************************
//
// declartion
//
//*****************************************************************************
extern void System_GetLoopClockTick(void); //ÿ��"����"��ʱ10ms��ϵͳ"ѭ��"ִ��һ�γ���
void System_Init(void);          //   ϵͳ��ʹ�� :��Ƭ���ڲ���Դ+�ⲿ������Դ�ĳ�ʹ�� 
void Osccon_Initial(void);  //�����ʼ������:������ؾ������



