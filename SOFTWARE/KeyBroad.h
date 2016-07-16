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
/*键盘参数-------------------------------------------------------*/
#define ROWNUM 4
#define COLNUM 4
/*控制组-------------------------------------------------------*/
#define Keybroad_SEL    		P9SEL
#define Keybroad_DIR       	    P9DIR
#define Keybroad_REN       	    P9REN

#define Keybroad_OUT    		P9OUT
#define Keybroad_IN    			P9IN
/*引脚-------------------------------------------------------*/
#define OUTPIN1 BIT0
#define OUTPIN2 BIT1
#define OUTPIN3 BIT2
#define OUTPIN4 BIT3
#define INPIN1  BIT4
#define INPIN2  BIT5
#define INPIN3  BIT6
#define INPIN4  BIT7
/*输入组-------------------------------------------------------*/
#define ReadRow0 (Keybroad_IN&BIT_4)
#define ReadRow1 (Keybroad_IN&BIT_5)
#define ReadRow2 (Keybroad_IN&BIT_6)
#define ReadRow3 (Keybroad_IN&BIT_7)
/*按键状态-------------------------------------------------------*/
#define e_KeyDown  		1
#define e_KeyUp  		0
#define e_KeyScanExit 		-1
#define e_KeyScanFail 		-2
#define e_KeyScanConti 		0
//*****************************************************************************
//
// define
//
//*****************************************************************************
struct KeyBroadStatus {
	int Status;
	int Cache;
	int Result;
};
//*****************************************************************************
//
// declartion
//
//*****************************************************************************
void KeyBroadInit(void);
int KeyBroadScan(void);
