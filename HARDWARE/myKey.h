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
#define Key_DIR    (P5DIR)  
#define Key_IN     (P5IN)
#define Key_1_IO   (BIT4)
#define Key_2_IO   (BIT5)
/*-------------------------------------------------------*/
#define mSetIn_Key_1_IO   (Key_DIR &= (~Key_1_IO)) //��������Ϊ"����"
#define mSetIn_Key_2_IO   (Key_DIR &= (~Key_2_IO)) //��������Ϊ"����"

//*****************************************************************************
//
// declartion
//
//*****************************************************************************
void KeyInit(void);
void KeyDeal(void);
