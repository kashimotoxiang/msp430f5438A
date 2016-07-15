//*****************************************************************************
//
// include
//
//*****************************************************************************
#include "Keybroad.h"

//*****************************************************************************
//
//variable
//
//*****************************************************************************
/*输出序列-------------------------------------------------------*/
static uint32_t WriteCol[COLNUM] = { OUTPIN1, OUTPIN2, OUTPIN3, OUTPIN4 };
/*键盘数组-------------------------------------------------------*/
static uint8_t KeyBroad_Array[ROWNUM][COLNUM] = { 1, 2, 3, 0, 4, 5, 6, 0, 7, 8, 9, 0,
		0, 0, 0, 0 };

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
}

//*****************************************************************************
//
// 键盘扫描程序
//
//*****************************************************************************
uint32_t KeyBroadScan(void) {
	/*变量定义-------------------------------------------------------*/
	int result = e_ERROR;
	int i = 0;
	for (i = 0; i < COLNUM; i++) {
		Keybroad_OUT = WriteCol[i];
		result = Row_KeyBroadScan(i);
		if (result != e_ERROR)
			return result;
	}
	return result; //怎么也得返回了
}
//*****************************************************************************
//
// 键盘行扫描程序
//
//*****************************************************************************
static inline int Row_KeyBroadScan(uint8_t row) {
	if (ReadRow0 != e_KeyTrue) {
		while (ReadRow0 != e_KeyTrue)
			;
		return KeyBroad_Array[row][0];
	}
	if (ReadRow1 != e_KeyTrue) {
		while (ReadRow1 != e_KeyTrue)
			;
		return KeyBroad_Array[row][1];
	}
	if (ReadRow2 != e_KeyTrue) {
		while (ReadRow2 != e_KeyTrue)
			;
		return KeyBroad_Array[row][2];
	}
	if (ReadRow3 != e_KeyTrue) {
		while (ReadRow3 != e_KeyTrue)
			;
		return KeyBroad_Array[row][3];
	}
	return e_ERROR;
}
