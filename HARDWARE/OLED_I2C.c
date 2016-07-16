//*****************************************************************************
//
// include
//
//*****************************************************************************
#include "OLED_I2C.h"
#include "codetab.h"

/**
 * @brief  I2C_Configuration，初始化硬件IIC引脚
 * @param  无
 * @retval 无
 */
void I2C_Configuration(void) {
	IIC_Init();
}
/**
 * @brief  WriteCmd，向OLED写入命令
 * @param  I2C_Command：命令代码
 * @retval 无
 */
inline void WriteCmd(unsigned char I2C_Command) //写命令
{
	IICSendByte(0x00, I2C_Command);
}

/**
 * @brief  WriteDat，向OLED写入数据
 * @param  I2C_Data：数据
 * @retval 无
 */
inline void WriteData(unsigned char I2C_Data) //写数据
{
	IICSendByte(0x40, I2C_Data);
}

/**
 * @brief  OLED_Init，初始化OLED
 * @param  无
 * @retval 无
 */
void OLED_Init(void) {
	I2C_Configuration();
	delayms(100); //这里的延时很重要

	WriteCmd(0xAE); //display off
	WriteCmd(0x20);	//Set Memory Addressing Mode	
	WriteCmd(0x10);	//00,Horizontal Addressing Mode;01,Vertical Addressing Mode;10,Page Addressing Mode (RESET);11,Invalid
	WriteCmd(0xb0);	//Set Page Start Address for Page Addressing Mode,0-7
	WriteCmd(0xc8);	//Set COM Output Scan Direction
	WriteCmd(0x00); //---set low column address
	WriteCmd(0x10); //---set high column address
	WriteCmd(0x40); //--set start line address
	WriteCmd(0x81); //--set contrast control register
	WriteCmd(0xff); //亮度调节 0x00~0xff
	WriteCmd(0xa1); //--set segment re-map 0 to 127
	WriteCmd(0xa6); //--set normal display
	WriteCmd(0xa8); //--set multiplex ratio(1 to 64)
	WriteCmd(0x3F); //
	WriteCmd(0xa4); //0xa4,Output follows RAM content;0xa5,Output ignores RAM content
	WriteCmd(0xd3); //-set display offset
	WriteCmd(0x00); //-not offset
	WriteCmd(0xd5); //--set display clock divide ratio/oscillator frequency
	WriteCmd(0xf0); //--set divide ratio
	WriteCmd(0xd9); //--set pre-charge period
	WriteCmd(0x22); //
	WriteCmd(0xda); //--set com pins hardware configuration
	WriteCmd(0x12);
	WriteCmd(0xdb); //--set vcomh
	WriteCmd(0x20); //0x20,0.77xVcc
	WriteCmd(0x8d); //--set DC-DC enable
	WriteCmd(0x14); //
	WriteCmd(0xaf); //--turn on oled panel

	OLED_ON();
}

/**
 * @brief  OLED_SetPos，设置光标
 * @param  x,光标x位置
 *					y，光标y位置
 * @retval 无
 */
void OLED_SetPos(unsigned char x, unsigned char y) //设置起始点坐标
{
	WriteCmd(0xb0 + y);
	WriteCmd(((x & 0xf0) >> 4) | 0x10);
	WriteCmd((x & 0x0f) | 0x01);
}

/**
 * @brief  OLED_Fill，填充整个屏幕
 * @param  fill_Data:要填充的数据
 * @retval 无
 */
void OLED_Fill(unsigned char fill_Data) //全屏填充
{
	unsigned char m, n;
	for (m = 0; m < 8; m++) {
		WriteCmd(0xb0 + m);		//page0-page1
		WriteCmd(0x00);		//low column start address
		WriteCmd(0x10);		//high column start address
		for (n = 0; n < 128; n++) {
			WriteData(fill_Data);
		}
	}
}

/**
 * @brief  OLED_CLS，清屏
 * @param  无
 * @retval 无
 */
void OLED_CLS(void)		//清屏
{
	OLED_Fill(0x00);
}

/**
 * @brief  OLED_ON，将OLED从休眠中唤醒
 * @param  无
 * @retval 无
 */
void OLED_ON(void) {
	WriteCmd(0X8D);  //设置电荷泵
	WriteCmd(0X14);  //开启电荷泵
	WriteCmd(0XAF);  //OLED唤醒
}

/**
 * @brief  OLED_OFF，让OLED休眠 -- 休眠模式下,OLED功耗不到10uA
 * @param  无
 * @retval 无
 */
void OLED_OFF(void) {
	WriteCmd(0X8D);  //设置电荷泵
	WriteCmd(0X10);  //关闭电荷泵
	WriteCmd(0XAE);  //OLED休眠
}

/**
 * @brief  OLED_ShowStr，显示codetab.h中的ASCII字符,有6*8和8*16可选择
 * @param  x,y : 起始点坐标(x:0~127, y:0~7);
 *					ch[] :- 要显示的字符串;
 *					TextSize : 字符大小(1:6*8 ; 2:8*16)
 * @retval 无
 */
void OLED_ShowStr(unsigned char x, unsigned char y, unsigned char ch[],
		unsigned char TextSize) {
	unsigned char c = 0, i = 0, j = 0;
	switch (TextSize) {
	case 1: {
		while (ch[j] != '\0') {
			c = ch[j] - 32;
			if (x > 126) {
				x = 0;
				y++;
			}
			OLED_SetPos(x, y);
			for (i = 0; i < 6; i++)
				WriteData(F6x8[c][i]);
			x += 6;
			j++;
		}
	}
		break;
	case 2: {
		while (ch[j] != '\0') {
			c = ch[j] - 32;
			if (x > 120) {
				x = 0;
				y++;
			}
			OLED_SetPos(x, y);
			for (i = 0; i < 8; i++)
				WriteData(F8X16[c * 16 + i]);
			OLED_SetPos(x, y + 1);
			for (i = 0; i < 8; i++)
				WriteData(F8X16[c * 16 + i + 8]);
			x += 8;
			j++;
		}
	}
		break;
	}
}

/**
 * @brief  OLED_DrawBMP，显示BMP位图
 * @param  x0,y0 :起始点坐标(x0:0~127, y0:0~7);
 *					x1,y1 : 起点对角线(结束点)的坐标(x1:1~128,y1:1~8)
 * @retval 无
 */
void OLED_DrawBMP(unsigned char x0, unsigned char y0, unsigned char x1,
		unsigned char y1, unsigned char BMP[]) {
	unsigned int j = 0;
	unsigned char x, y;

	if (y1 % 8 == 0)
		y = y1 / 8;
	else
		y = y1 / 8 + 1;
	for (y = y0; y < y1; y++) {
		OLED_SetPos(x0, y);
		for (x = x0; x < x1; x++) {
			WriteData(BMP[j++]);
		}
	}
}
