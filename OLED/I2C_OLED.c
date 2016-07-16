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

u8 OLED_GRAM[128][8];	 //�Դ�
void I2C_start_OLED()
{
    SDA_DIR_OUT_OLED;
    SCK_I2C_OUT_OLED;
    SDA_I2C_H_OLED;
    SCK_I2C_H_OLED;
    delay_us(1);                //��ʱ
    SDA_I2C_L_OLED;
    delay_us(1);                //��ʱ
    SCK_I2C_L_OLED;
}

/**************************************
ֹͣ�ź�
**************************************/
void I2C_Stop_OLED()
{
    SCK_I2C_OUT_OLED;
    SDA_DIR_OUT_OLED;
    SDA_I2C_L_OLED;
    SCK_I2C_H_OLED;
    delay_us(1);                //��ʱ
    SDA_I2C_H_OLED;
    delay_us(1);                //��ʱ
    SCK_I2C_H_OLED;
    delay_us(5);
}
/**************************************
����Ӧ���ź�
��ڲ���:ack (0:ACK 1:NAK)
**************************************/
void I2C_SendACK_OLED(u8 ack)
{
    SDA_DIR_OUT_OLED;
    SCK_I2C_OUT_OLED;
    if(ack==1) SDA_I2C_H_OLED;
    else       SDA_I2C_L_OLED;
    SCK_I2C_H_OLED;
    delay_us(1);                //��ʱ
    SCK_I2C_L_OLED;
    delay_us(1);                //��ʱ
}

/**************************************
����Ӧ���ź�
**************************************/
u8 I2C_RecvACK_OLED()
{
    u8 temp;
    SDA_DIR_IN_OLED;
    SCK_I2C_H_OLED;             //����ʱ����
    delay_us(1);                //��ʱ
    _NOP();
    if(SDA_Value_OLED) temp=1;
    else temp=0;
    SCK_I2C_L_OLED;          //����ʱ����
    delay_us(1);                //��ʱ
    SDA_DIR_OUT_OLED;
    return temp;
}

/**************************************
��IIC���߷���һ���ֽ�����
**************************************/
void I2C_SendByte_OLED(u8 dat)
{
    u8 i;
    SDA_DIR_OUT_OLED;
    SCK_I2C_OUT_OLED;
    for (i=0; i<8; i++)         //8λ������
    {
        if(dat&0x80) SDA_I2C_H_OLED;
        else SDA_I2C_L_OLED;
        dat <<= 1;              //�Ƴ����ݵ����λ
        SCK_I2C_H_OLED;
        delay_us(1);            //��ʱ
        SCK_I2C_L_OLED;
        delay_us(1);            //��ʱ
    }
    I2C_RecvACK_OLED();
}

/**************************************
��IIC���߽���һ���ֽ�����
**************************************/
u8 I2C_RecvByte_OLED()
{
    u8 i;
    SDA_DIR_IN_OLED;
    u8 dat = 0;
    SDA_I2C_H_OLED;
    for (i=0; i<8; i++)         //8λ������
    {
        dat <<= 1;             //����ʱ����
        SCK_I2C_H_OLED;
        delay_us(1);            //��ʱ
        if(SDA_Value_OLED) dat |= 1;    //������
        SCK_I2C_L_OLED; //����ʱ����
        delay_us(1);            //��ʱ
    }
    SDA_DIR_OUT_OLED;
    return dat;
}
//******���ֽ�д��*******************************************
void Single_Write_OLED(u8 REG_Address,u8 REG_data)
{
    I2C_start_OLED();                  //��ʼ�ź�
    I2C_SendByte_OLED(SlaveAddress);   //�����豸��ַ+д�ź�
    I2C_SendByte_OLED(REG_Address);    //�ڲ��Ĵ�����ַ
    I2C_SendByte_OLED(REG_data);
    I2C_Stop_OLED();                   //����ֹͣ�ź�
}
void OLED_WRITE_COM(u8 com)				//дָ��
{
	Single_Write_OLED(0x00,com);
}

void OLED_WRITE_dat(u8 data)				//д����
{
	Single_Write_OLED(0x40,data);
}

/*********************OLED ��������************************************/
void OLED_Set_Pos(u8 x, u8 y) //����OLED����
{
	OLED_WRITE_COM(0xb0+y);
	OLED_WRITE_COM(((x&0xf0)>>4)|0x10);
	OLED_WRITE_COM((x&0x0f)|0x01);
}
/*********************OLEDȫ��************************************/
void OLED_All(u8 bmp_dat) 				//OLEDȫ��дͬһ����
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
/*********************OLED��λ************************************/
void OLED_CLC(void)   //����
{
	OLED_All(0);
}

/***********������������ʾ��ʾBMPͼƬ128��64��ʼ������(x,y),x�ķ�Χ0��127��yΪҳ�ķ�Χ0��7**********/
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
void I2C_OLED_Init(void) //OLED��ʼ��
{
	OLED_WRITE_COM(0xAE); //�ر���ʾ
	OLED_WRITE_COM(0xD5); //����ʱ�ӷ�Ƶ����,��Ƶ��
	OLED_WRITE_COM(80);   //[3:0],��Ƶ����;[7:4],��Ƶ��
	OLED_WRITE_COM(0xA8); //��������·��
	OLED_WRITE_COM(0X3F); //Ĭ��0X3F(1/64)
	OLED_WRITE_COM(0xD3); //������ʾƫ��
	OLED_WRITE_COM(0X00); //Ĭ��Ϊ0

	OLED_WRITE_COM(0x40); //������ʾ��ʼ�� [5:0],����.

	OLED_WRITE_COM(0x8D); //��ɱ�����
	OLED_WRITE_COM(0x14); //bit2������/�ر�
	OLED_WRITE_COM(0x20); //�����ڴ��ַģʽ
	OLED_WRITE_COM(0x02); //[1:0],00���е�ַģʽ;01���е�ַģʽ;10,ҳ��ַģʽ;Ĭ��10;
	OLED_WRITE_COM(0xA1); //���ض�������,bit0:0,0->0;1,0->127;
	OLED_WRITE_COM(0xC8); //����COMɨ�跽��;bit3:0,��ͨģʽ;1,�ض���ģʽ COM[N-1]->COM0;N:����·��
	OLED_WRITE_COM(0xDA); //����COMӲ����������
	OLED_WRITE_COM(0x12); //[5:4]����

	OLED_WRITE_COM(0x81); //�Աȶ�����
	OLED_WRITE_COM(0x10); //1~255;Ĭ��0X7F (��������,Խ��Խ��)
	OLED_WRITE_COM(0xD9); //����Ԥ�������
	OLED_WRITE_COM(0xf1); //[3:0],PHASE 1;[7:4],PHASE 2;
	OLED_WRITE_COM(0xDB); //����VCOMH ��ѹ����
	OLED_WRITE_COM(0x30); //[6:4] 000,0.65*vcc;001,0.77*vcc;011,0.83*vcc;

	OLED_WRITE_COM(0xA4); //ȫ����ʾ����;bit0:1,����;0,�ر�;(����/����)
	OLED_WRITE_COM(0xA6); //������ʾ��ʽ;bit0:1,������ʾ;0,������ʾ
	OLED_WRITE_COM(0xAF); //������ʾ
	OLED_CLC();
}
//����
//x:0~127
//y:0~63
//t:1 ��� 0,���
void OLED_DrawPoint(u8 x,u8 y,u8 t)
{
	u8 pos,bx,temp=0;
	if(x>127||y>63)return;//������Χ��.
	pos=7-y/8;
	bx=y%8;
	temp=1<<(7-bx);
	if(t)OLED_GRAM[x][pos]|=temp;
	else OLED_GRAM[x][pos]&=~temp;
}
//x1,y1,x2,y2 �������ĶԽ�����
//ȷ��x1<=x2;y1<=y2 0<=x1<=127 0<=y1<=63
//dot:0,���;1,���
void OLED_Fill(u8 x1,u8 y1,u8 x2,u8 y2,u8 dot)
{
	u8 x,y;
	for(x=x1;x<=x2;x++)
	{
		for(y=y1;y<=y2;y++)OLED_DrawPoint(x,y,dot);
	}
	OLED_Refresh_Gram();//������ʾ
}
//�����Դ浽LCD
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
/***************������������ʾ6*8һ���׼ASCII�ַ���	��ʾ�����꣨x,y����yΪҳ��Χ0��7****************/
void OLED_P6x8Str(u8 x,u8 y, u8 ch[])
{
	u8 c=0,i=0,j=0;
	while (ch[j]!='\0')
	{
		c =ch[j]-32;
		if(x>126){x=0;y++;}				//�߽�����  ǿ������
		OLED_Set_Pos(x,y);
		for(i=0;i<6;i++)
		OLED_WRITE_dat(F6x8[c][i]);
		x+=6;
		j++;
	}
}
/*******************������������ʾ8*16һ���׼ASCII�ַ���	 ��ʾ�����꣨x,y����yΪҳ��Χ0��7****************/
void OLED_P8x16Str(u8 x,u8 y,u8 ch[])
{
	u8 c=0,i=0,j=0;
	while (ch[j]!='\0')
	{
		c =ch[j]-32;
		if(x>120){x=0;y++;}					//�߽�����  ǿ������
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
/*****************������������ʾ16*16����  ��ʾ�����꣨x,y����yΪҳ��Χ0��7****************************/
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





