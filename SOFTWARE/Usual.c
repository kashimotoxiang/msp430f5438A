#include "Usual.h"
#include <cstdarg>
#include <stdarg.h>
/*-------------------------------------------------------*/
char TemptString[20] = { 0 }; //数字字符串转换数组
//---------------------------------------------------------------------//
void Bubble_Sort(uint8_t volatile* num, int n) {
	static uint32_t i, j;
	for (i = 0; i < n; i++) {
		for (j = 0; i + j < n - 1; j++) {
			if (num[j] > num[j + 1]) {
				uint8_t temp = num[j];
				num[j] = num[j + 1];
				num[j + 1] = temp;
			}
		}
	}
	return;
}
//---------------------------------------------------------------------//
void F2S(double d, char* str) {
	char str1[20];
	int j = 0, k, i;
	i = (int) d;  //浮点数的整数部分
	//d = d-(int)d;
	if (i == 0)
		str1[j++] = '0';
	while (i > 0) {
		str1[j++] = i % 10 + '0';
		i /= 10;
	}
	for (k = 0; k < j; k++)
		str[k] = str1[j - 1 - k]; //
	str[j++] = '.';
	d -= (int) d;
	if (d < 0.00000000000000000001){
		str[j++] = '0';
		str[j++] = '\0';
		return str;
	}
	for (i = 0; i < 10; i++) {
		d *= 10;
		str[j++] = (int) d + '0';
		d -= (int) d;
	}
	while (str[--j] == '0')
		;
	str[++j] = '\0';
	str[10] = '\0';
	return str;
}
