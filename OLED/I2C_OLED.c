/*
 * I2C_OLED.c
 *
 *  Created on: 2014-10-3
 *      Author: ZhouChuGang
 */
#include"I2C_OLED.h"
#include"codetab.h"
#include"zimo.h"

#define delay_us(x)

u8 OLED_GRAM[128][8];	 //显存
void I2C_start_OLED()
{
    SDA_DIR_OUT_OLED;
    SCK_I2C_OUT_OLED;
    SDA_I2C_H_OLED;
    SCK_I2C_H_OLED;
    delay_us(1);                //延时
    SDA_I2C_L_OLED;
    delay_us(1);                //延时
    SCK_I2C_L_OLED;
}

/**************************************
停止信号
**************************************/
void I2C_Stop_OLED()
{
    SCK_I2C_OUT_OLED;
    SDA_DIR_OUT_OLED;
    SDA_I2C_L_OLED;
    SCK_I2C_H_OLED;
    delay_us(1);                //延时
    SDA_I2C_H_OLED;
    delay_us(1);                //延时
    SCK_I2C_H_OLED;
    delay_us(5);
}
/**************************************
发送应答信号
入口参数:ack (0:ACK 1:NAK)
**************************************/
void I2C_SendACK_OLED(u8 ack)
{
    SDA_DIR_OUT_OLED;
    SCK_I2C_OUT_OLED;
    if(ack==1) SDA_I2C_H_OLED;
    else       SDA_I2C_L_OLED;
    SCK_I2C_H_OLED;
    delay_us(1);                //延时
    SCK_I2C_L_OLED;
    delay_us(1);                //延时
}

/**************************************
接收应答信号
**************************************/
u8 I2C_RecvACK_OLED()
{
    u8 temp;
    SDA_DIR_IN_OLED;
    SCK_I2C_H_OLED;             //拉高时钟线
    delay_us(1);                //延时
    _NOP();
    if(SDA_Value_OLED) temp=1;
    else temp=0;
    SCK_I2C_L_OLED;          //拉低时钟线
    delay_us(1);                //延时
    SDA_DIR_OUT_OLED;
    return temp;
}

/**************************************
向IIC总线发送一个字节数据
**************************************/
void I2C_SendByte_OLED(u8 dat)
{
    u8 i;
    SDA_DIR_OUT_OLED;
    SCK_I2C_OUT_OLED;
    for (i=0; i<8; i++)         //8位计数器
    {
        if(dat&0x80) SDA_I2C_H_OLED;
        else SDA_I2C_L_OLED;
        dat <<= 1;              //移出数据的最高位
        SCK_I2C_H_OLED;
        delay_us(1);            //延时
        SCK_I2C_L_OLED;
        delay_us(1);            //延时
    }
    I2C_RecvACK_OLED();
}

/**************************************
从IIC总线接收一个字节数据
**************************************/
u8 I2C_RecvByte_OLED()
{
    u8 i;
    SDA_DIR_IN_OLED;
    u8 dat = 0;
    SDA_I2C_H_OLED;
    for (i=0; i<8; i++)         //8位计数器
    {
        dat <<= 1;             //拉高时钟线
        SCK_I2C_H_OLED;
        delay_us(1);            //延时
        if(SDA_Value_OLED) dat |= 1;    //读数据
        SCK_I2C_L_OLED; //拉低时钟线
        delay_us(1);            //延时
    }
    SDA_DIR_OUT_OLED;
    return dat;
}
//******单字节写入*******************************************
void Single_Write_OLED(u8 REG_Address,u8 REG_data)
{
    I2C_start_OLED();                  //起始信号
    I2C_SendByte_OLED(SlaveAddress);   //发送设备地址+写信号
    I2C_SendByte_OLED(REG_Address);    //内部寄存器地址
    I2C_SendByte_OLED(REG_data);
    I2C_Stop_OLED();                   //发送停止信号
}
void OLED_WRITE_COM(u8 com)				//写指令
{
	Single_Write_OLED(0x00,com);
}

void OLED_WRITE_dat(u8 data)				//写数据
{
	Single_Write_OLED(0x40,data);
}

/*********************OLED 设置坐标************************************/
void OLED_Set_Pos(u8 x, u8 y) //设置OLED坐标
{
	OLED_WRITE_COM(0xb0+y);
	OLED_WRITE_COM(((x&0xf0)>>4)|0x10);
	OLED_WRITE_COM((x&0x0f)|0x01);
}
/*********************OLED全屏************************************/
void OLED_All(u8 bmp_dat) 				//OLED全屏写同一数据
{
	u8 y,x;
	for(y=0;y<8;y++)
	{
		OLED_WRITE_COM(0xb0+y);
		OLED_WRITE_COM(0x01);
		OLED_WRITE_COM(0x10);
		for(x=0;x<128;x++)
		OLED_WRITE_dat(bmp_dat);
	}
}
/*********************OLED复位************************************/
void OLED_CLC(void)   //清屏
{
	OLED_All(0);
}

/***********功能描述：显示显示BMP图片128×64起始点坐标(x,y),x的范围0～127，y为页的范围0～7**********/
void Draw_BMP(const u8 *BMP)
{
	u8 x,y;
	for(y=0;y<8;y++)
	{
		OLED_Set_Pos(0,y);
    for(x=0;x<128;x++)
    	OLED_WRITE_dat(*BMP++);
	}
}
void I2C_OLED_Init(void) //OLED初始化
{
	OLED_WRITE_COM(0xAE); //关闭显示
	OLED_WRITE_COM(0xD5); //设置时钟分频因子,震荡频率
	OLED_WRITE_COM(80);   //[3:0],分频因子;[7:4],震荡频率
	OLED_WRITE_COM(0xA8); //设置驱动路数
	OLED_WRITE_COM(0X3F); //默认0X3F(1/64)
	OLED_WRITE_COM(0xD3); //设置显示偏移
	OLED_WRITE_COM(0X00); //默认为0

	OLED_WRITE_COM(0x40); //设置显示开始行 [5:0],行数.

	OLED_WRITE_COM(0x8D); //电荷泵设置
	OLED_WRITE_COM(0x14); //bit2，开启/关闭
	OLED_WRITE_COM(0x20); //设置内存地址模式
	OLED_WRITE_COM(0x02); //[1:0],00，列地址模式;01，行地址模式;10,页地址模式;默认10;
	OLED_WRITE_COM(0xA1); //段重定义设置,bit0:0,0->0;1,0->127;
	OLED_WRITE_COM(0xC8); //设置COM扫描方向;bit3:0,普通模式;1,重定义模式 COM[N-1]->COM0;N:驱动路数
	OLED_WRITE_COM(0xDA); //设置COM硬件引脚配置
	OLED_WRITE_COM(0x12); //[5:4]配置

	OLED_WRITE_COM(0x81); //对比度设置
	OLED_WRITE_COM(0x10); //1~255;默认0X7F (亮度设置,越大越亮)
	OLED_WRITE_COM(0xD9); //设置预充电周期
	OLED_WRITE_COM(0xf1); //[3:0],PHASE 1;[7:4],PHASE 2;
	OLED_WRITE_COM(0xDB); //设置VCOMH 电压倍率
	OLED_WRITE_COM(0x30); //[6:4] 000,0.65*vcc;001,0.77*vcc;011,0.83*vcc;

	OLED_WRITE_COM(0xA4); //全局显示开启;bit0:1,开启;0,关闭;(白屏/黑屏)
	OLED_WRITE_COM(0xA6); //设置显示方式;bit0:1,反相显示;0,正常显示
	OLED_WRITE_COM(0xAF); //开启显示
	OLED_CLC();
}
//画点
//x:0~127
//y:0~63
//t:1 填充 0,清空
void OLED_DrawPoint(u8 x,u8 y,u8 t)
{
	u8 pos,bx,temp=0;
	if(x>127||y>63)return;//超出范围了.
	pos=7-y/8;
	bx=y%8;
	temp=1<<(7-bx);
	if(t)OLED_GRAM[x][pos]|=temp;
	else OLED_GRAM[x][pos]&=~temp;
}
//x1,y1,x2,y2 填充区域的对角坐标
//确保x1<=x2;y1<=y2 0<=x1<=127 0<=y1<=63
//dot:0,清空;1,填充
void OLED_Fill(u8 x1,u8 y1,u8 x2,u8 y2,u8 dot)
{
	u8 x,y;
	for(x=x1;x<=x2;x++)
	{
		for(y=y1;y<=y2;y++)OLED_DrawPoint(x,y,dot);
	}
	OLED_Refresh_Gram();//更新显示
}
//更新显存到LCD
void OLED_Refresh_Gram(void)
{
	u8 i,n;
	for(i=0;i<8;i++)
	{
		OLED_Set_Pos(0,i);
		for(n=0;n<128;n++)
		OLED_WRITE_dat(OLED_GRAM[n][i]);
	}
}
/***************功能描述：显示6*8一组标准ASCII字符串	显示的坐标（x,y），y为页范围0～7****************/
void OLED_P6x8Str(u8 x,u8 y, u8 ch[])
{
	u8 c=0,i=0,j=0;
	while (ch[j]!='\0')
	{
		c =ch[j]-32;
		if(x>126){x=0;y++;}				//边界限制  强制拉回
		OLED_Set_Pos(x,y);
		for(i=0;i<6;i++)
		OLED_WRITE_dat(F6x8[c][i]);
		x+=6;
		j++;
	}
}
/*******************功能描述：显示8*16一组标准ASCII字符串	 显示的坐标（x,y），y为页范围0～7****************/
void OLED_P8x16Str(u8 x,u8 y,u8 ch[])
{
	u8 c=0,i=0,j=0;
	while (ch[j]!='\0')
	{
		c =ch[j]-32;
		if(x>120){x=0;y++;}					//边界限制  强制拉回
		OLED_Set_Pos(x,y);
		for(i=0;i<8;i++)
		OLED_WRITE_dat(F8X16[c*16+i]);
		OLED_Set_Pos(x,y+1);
		for(i=0;i<8;i++)
		OLED_WRITE_dat(F8X16[c*16+i+8]);
		x+=8;
		j++;
	}
}
/*****************功能描述：显示16*16点阵  显示的坐标（x,y），y为页范围0～7****************************/
void OLED_P16x16Ch(u8 x,u8 y,u8 num)
{
		u8 wm=0;
		u16 adder=32*num;
		OLED_Set_Pos(x , y);
		for(wm = 0;wm < 16;wm++)
		{
			OLED_WRITE_dat(F16x16[adder]);
			adder += 1;
		}
		OLED_Set_Pos(x,y + 1);
		for(wm = 0;wm < 16;wm++)
		{
			OLED_WRITE_dat(F16x16[adder]);
			adder += 1;
		}
}





