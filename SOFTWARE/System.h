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
#define mClose_WDT      (WDTCTL = WDTPW + WDTHOLD)  // 关闭看门狗
#define mClr_WDTCNT     (WDTCTL = WDTPW + WDTCNTCL) // 清看门狗(对于MSP430单片机)
#define	mNop	        (__no_operation())    //空操作指令(用于"短延时"或"调试")

#define	mEnable_GIE     (_EINT())  // 开启总中断GIE
#define	mDisable_GIE    (_DINT())  // 关闭总中断GIE

#define	mReset_Soft    (PMMCTL0 |= PMMSWPOR) //"软件复位" (MSP430单片机)

//*****************************************************************************
//
// declartion
//
//*****************************************************************************
extern void System_GetLoopClockTick(void); //每次"死等"延时10ms后，系统"循环"执行一次程序
void System_Initial_OSC(void);          //   系统初使化 :单片机内部资源+外部基本资源的初使化 
void Osccon_Initial(void);  //晶振初始化函数:定义相关晶振参数
void delayms(int count);
void delayns(int count);


