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
/*�������-------------------------------------------------------*/
static uint32_t WriteCol[COLNUM] = { OUTPIN1, OUTPIN2, OUTPIN3, OUTPIN4 };
/*��������-------------------------------------------------------*/
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
// ���̳�ʼ��
//
//*****************************************************************************
void KeyBroadInit(void) {
	Keybroad_DIR |= OUTPIN1 | OUTPIN2 | OUTPIN3 | OUTPIN4; // Set output direction
}

//*****************************************************************************
//
// ����ɨ�����
//
//*****************************************************************************
uint32_t KeyBroadScan(void) {
	/*��������-------------------------------------------------------*/
	int result = e_ERROR;
	int i = 0;
	for (i = 0; i < COLNUM; i++) {
		Keybroad_OUT = WriteCol[i];
		result = Row_KeyBroadScan(i);
		if (result != e_ERROR)
			return result;
	}
	return result; //��ôҲ�÷�����
}
//*****************************************************************************
//
// ������ɨ�����
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
