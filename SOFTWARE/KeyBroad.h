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
#define Keybroad_SEL    		P6SEL
#define Keybroad_DIR       	    P6DIR

#define Keybroad_OUT    		P6OUT
#define Keybroad_IN    			P6IN
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
#define ReadRow0 (Keybroad_IN&INPIN1)
#define ReadRow1 (Keybroad_IN&INPIN2)
#define ReadRow2 (Keybroad_IN&INPIN3)
#define ReadRow3 (Keybroad_IN&INPIN4)
/*按键状态-------------------------------------------------------*/
#define e_KeyTrue 		0
#define e_KeyFalse 		!e_KeyTrue

//*****************************************************************************
//
// declartion
//
//*****************************************************************************
void KeyBroadInit(void);
uint32_t KeyBroadScan(void);
