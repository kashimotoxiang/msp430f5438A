//*****************************************************************************
//
// include
//
//*****************************************************************************
#include "Keybroad.h"
//*****************************************************************************
//
// define
//
//*****************************************************************************
#define DELAYMS 1
//*****************************************************************************
//
//variable
//
//*****************************************************************************
/*输出序列-------------------------------------------------------*/
static uint32_t WriteCol[COLNUM] = { OUTPIN1, OUTPIN2, OUTPIN3, OUTPIN4 };
/*键盘数组-------------------------------------------------------*/
static uint8_t KeyBroad_Array[ROWNUM][COLNUM] = { 1, 2, 3, 0, 4, 5, 6, 0, 7, 8,
		9, 0, 0, 0, 0, 0 };
/*键盘当前状态-------------------------------------------------------*/
static struct KeyBroadStatus AKB;
//*****************************************************************************
//
// declartion
//
//*****************************************************************************
static inline int Row_KeyBroadScan(uint8_t row);

//*****************************************************************************
//
// 键盘初始化
//
//*****************************************************************************
void KeyBroadInit(void) {
	Keybroad_DIR |= OUTPIN1 | OUTPIN2 | OUTPIN3 | OUTPIN4; // Set output direction
	Keybroad_REN |= INPIN1 | INPIN2 | INPIN3 | INPIN4;
}

//*****************************************************************************
//
// 键盘扫描程序
//
//*****************************************************************************
int KeyBroadScan(void) {
	int i = 0;
	for (i = 0; i < COLNUM; i++) {
		Keybroad_OUT = WriteCol[i];
		AKB.Status = Row_KeyBroadScan(i);
		if (AKB.Status == e_KeyScanExit) //有按键按下强制退出
			return e_KeyScanFail;
	}
	/*无按键按下-------------------------------------------------------*/
	AKB.Result = AKB.Cache;
	AKB.Cache = e_KeyScanFail;
	return AKB.Result; //返回最后一个按下的 或者 e_KeyScanFail
}
//*****************************************************************************
//
// 键盘行扫描程序
//
//*****************************************************************************
static inline int Row_KeyBroadScan(uint8_t row) {
	if (ReadRow0) {
		delayms(DELAYMS);
		if (ReadRow0) {
			AKB.Cache = KeyBroad_Array[row][0];
			return e_KeyScanExit;
		}
	}

	if (ReadRow1) {
		delayms(DELAYMS);
		if (ReadRow1) {
			AKB.Cache = KeyBroad_Array[row][1];
			return e_KeyScanExit;
		}
	}

	if (ReadRow2) {
		delayms(DELAYMS);
		if (ReadRow2) {
			AKB.Cache = KeyBroad_Array[row][2];
			return e_KeyScanExit;
		}
	}

	if (ReadRow3) {
		delayms(DELAYMS);
		if (ReadRow3) {
			AKB.Cache = KeyBroad_Array[row][3];
			return e_KeyScanExit;
		}
	}
	return e_KeyScanConti;
}
