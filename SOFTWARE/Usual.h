#pragma once
/*  Usual Macro---------------------------------------------------------*/
#define COUNTOF(__BUFFER__)   (sizeof(__BUFFER__) / sizeof(*(__BUFFER__)))//编译时进行，必须是已知常量
#define  MAX( x_cur, y_cur )		( ((x_cur) > (y_cur))  (x_cur) : (y_cur) )//大值
#define  MIN( x_cur, y_cur )		( ((x_cur) < (y_cur))  (x_cur) : (y_cur) )//小值
#define  UPCASE( c )		( ((c) >= 'a' && (c) <= 'z')  ((c) - 0x20) : (c) )//转换为大写
#define  ARR_SIZE( a )		( sizeof( (a) ) / sizeof( (a[0]) ) )//数组长度获取
#define  INC_SAT( val )		(val = ((val)+1 > (val)) ? (val)+1 : (val))//防止溢出
#define  ABS(x_cur)				( (x_cur)>0(x_cur):-(x_cur) ) //求整型绝对值
#define  uDiffABS(x_cur,y_cur)			( (x_cur>y_cur)?(x_cur-y_cur):(y_cur-x_cur) ) //求无符号型的差的绝对值
#define  Safe_Return(Current, Begin, End) (((Current)>(End)?(Begin):((Current)<(Begin)?(End):(Current))))//安全返回，防止上下溢出
#define  isBound(x,MIN,MAX)       ((x)>(MIN)&&(x)<(MAX))
/*-------------------------------------------------------*/
#include "main.h"
/*  ---------------------------------------------------------*/
void Bubble_Sort(uint8_t volatile* num, int n);
//---------------------------------------------------------------------//
extern char TemptString[20];

/*数字显示-------------------------------------------------------*/
inline void Num_Show(long int data, char* com, u16 x, u16 y) {
	sprintf(TemptString, com, data);
	OLED_P8x16Str(x * 8, y * 16, TemptString);
}

/*插入排序---------------------------------------------------------*/
inline void InsertSort(int ai[], int low, int high) {
	int i, j, key;
	for (i = low + 1; i <= high; i++) //控制需要插入的元素
			{
		key = ai[i]; //key为要插入的元素
		for (j = i; j > low && ai[j - 1] > key; j--) //查找要插入的位置,循环结束,则找到插入位置
				{
			ai[j] = ai[j - 1]; //移动元素的位置.供要插入元素使用
		}
		ai[j] = key; //插入需要插入的元素
	}
}

/*交换---------------------------------------------------------*/
inline void Swap(int ai[], int x_cur, int y_cur) {
	int temp = ai[x_cur];
	ai[x_cur] = ai[y_cur];
	ai[y_cur] = temp;
	return;
}

//*****************************************************************************
//
// OLED数字显示
//
//*****************************************************************************
inline void OLED_Num2StrShow_Int(int data, u16 x, u16 y) {
	sprintf(TemptString, "%d", data);
	OLED_P8x16Str(x * 8, y * 16, TemptString);
}

inline void OLED_Num2StrShow_Double(double data, u16 x, u16 y) {
	sprintf(TemptString, "%f", data);
	TemptString[9]='\0';
	OLED_P8x16Str(x * 8, y * 16, TemptString);
}
//*****************************************************************************
//
// 电子墨水屏数字显示
//
//*****************************************************************************
inline void IncS_Num2StrShow_Int(int data, u16 x, u16 y) {
	sprintf(TemptString, "%d", data);
	IncS_P8x16Str(x, y * 24, TemptString);
}

inline void IncS_Num2StrShow_Double(double data, u16 x, u16 y) {
	//F2S(data, TemptString);
	sprintf(TemptString, "%f", data);
	TemptString[9]='\0';
	IncS_P24x32Str(x, y * 24, TemptString);

}

//*****************************************************************************
//
// declartion
//
//*****************************************************************************
void F2S(double d, char* str) ;
