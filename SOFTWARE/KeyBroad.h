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
#define Keybroad_SEL    		P8SEL
#define Keybroad_DIR       	    P8DIR
#define Keybroad_REN       	    P8REN

#define Keybroad_OUT    		P8OUT
#define Keybroad_IN    			P8IN
/*引脚-------------------------------------------------------*/
#define OUTPIN1 BIT7
#define OUTPIN2 BIT6
#define OUTPIN3 BIT5
#define OUTPIN4 BIT4

#define INPIN1  BIT3
#define INPIN2  BIT2
#define INPIN3  BIT1
#define INPIN4  BIT0

#define INPIN_1  BIT_3
#define INPIN_2  BIT_2
#define INPIN_3  BIT_1
#define INPIN_4  BIT_0

/*输入组-------------------------------------------------------*/
#define ReadRow0 (Keybroad_IN&INPIN_1)
#define ReadRow1 (Keybroad_IN&INPIN_2)
#define ReadRow2 (Keybroad_IN&INPIN_3)
#define ReadRow3 (Keybroad_IN&INPIN_4)
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
