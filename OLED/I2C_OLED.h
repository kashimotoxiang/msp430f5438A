/*
 * I2C_OLED.h
 *
 *  Created on: 2014-10-3
 *      Author: ZhouChuGang
 */
#ifndef I2C_OLED_H_
#define I2C_OLED_H_
#include"main.h"

/*************************I2C_OLEDָ�***********************************
 **********************slave address 0X78*********************************
 *д����ָ��0x40 *****˳��***     0x78, 0x40,	data
 *д����ָ��0x00 *****˳��***     0x78, 0x00,	com
 *������öԱȶ�  0x81��com****˳��****0x78,0x00,0x81	0x78,0x00,com		comԽ��Խ��
 *�����/����ʾ 0XAE/0XAF ****˳��***0X78,0X00,0XAE/0XAF	        AE ��  AF ��
 *�����ɱÿ��� 	8D *********˳��***0x78,0x00,0x8D	0x78,0x00,0X14		    ��ʾʱ���뿪��
 *�������ҳ��ַ 0XB0+y********˳��*****0x78,0x00,0xb0+y			y��Ӧ0��7ҳ����0��7�У�
 *��������е�ַ��4λ((x&0xf0)>>4)|0x10)****˳��*****0X78,0X00,((x&0xf0)>>4)|0x10)	X��Ӧ�е�ַ
 *��������е�ַ��4λ((x&0x0f)|0x01)	 ****˳��*****0X78,0X00,((x&0x0f)|0x01)		X��Ӧ�е�ַ							X��Ӧ�е�ַ
 *��������е�ַ��4λ0x10+x1		�����е�ַ��4λ0x00+x0				   X1��x2�ֱ�ΪX�ĸ�4λ����4λ
 */
#define	SlaveAddress   0x78	  //oled ADDRESS

#define PORT_OLED  	P1OUT   //�ܶ˿ں�
#define DIR_OLED  	P1DIR   //�˿ڷ���

#define SDA_Value_OLED  (P1IN & BIT7)    //��ȡSDA���ŵĵ�ƽֵ����֮ǰ�˿ڷ�����Ϊ����!!!!!!

#define SCK_I2C_OUT_OLED DIR_OLED  |=BIT6
#define SCK_I2C_H_OLED	 PORT_OLED  |= BIT6   // SCK
#define SCK_I2C_L_OLED	 PORT_OLED  &= ~BIT6

#define SDA_DIR_OUT_OLED	DIR_OLED  |= BIT7     //���ݶ˿ڷ�����Ϊ���   SDA
#define SDA_DIR_IN_OLED	    DIR_OLED  &= ~BIT7    //���ݶ˿ڷ�����Ϊ����
#define SDA_I2C_H_OLED	    PORT_OLED  |= BIT7
#define SDA_I2C_L_OLED  	PORT_OLED  &= ~BIT7

#define delay_us(x) __delay_cycles((long)(CPU_F*(double)x/1000000.0))
#define delay_ms(x) __delay_cycles((long)(CPU_F*(double)x/1000.0))

extern u8 OLED_GRAM[128][8];	 //�Դ�

void I2C_start_OLED();										//I2C��ʼ�ź�
void I2C_Stop_OLED();										//I2C STOP
void I2C_SendACK_OLED(u8 ack);								//I2C ACK/NACK
u8 I2C_RecvACK_OLED();										//����ACK
void I2C_SendByte_OLED(u8 dat);								//WRITE DATA
u8 I2C_RecvByte_OLED();										//REND DATA
void Single_Write_OLED(u8 REG_Address, u8 REG_data);	//ADDRESS WRITE DATA

void I2C_OLED_Init(void);								    //OLED��ʼ��

void OLED_WRITE_COM(u8 com);							    //д����
void OLED_WRITE_DATA(u8 data);							    //д����
void OLED_Set_Pos(u8 x, u8 y);	 						    //����OLED����
void OLED_All(u8 bmp_dat);								    //OLEDȫ��дͬһ����
void OLED_CLC(void);   									    //����
void OLED_P8x16Str(u8 x, u8 y, u8 ch[]);					//��ʾ8*16һ���׼ASCII�ַ���
void OLED_P6x8Str(u8 x, u8 y, u8 ch[]);						//��ʾ6*8һ���׼ASCII�ַ���

/*****************������������ʾ16*16����  ��ʾ�����꣨x,y����yΪҳ��Χ0��7****************************/
/*****************ϸ������:ֻ��ʾcodetab.h�ļ���F16x16[]�����ڵ���numΪ��ʾ��ģ�������е�λ��**********/
void OLED_P16x16Ch(u8 x, u8 y, u8 num);

/******������������ʾ��ʾBMPͼƬ128��64   ȫ����ʾ*********************/
void Draw_BMP(const u8 *BMP);

/*************ע�⣡���º��������ã�G2533 RAM̫С********************/
void OLED_Fill(u8 x1, u8 y1, u8 x2, u8 y2, u8 dot);			    //���Խ���
void OLED_DrawPoint(u8 x, u8 y, u8 t);					    //����
void OLED_Refresh_Gram(void);							    //�����Դ浽LCD

#endif /* I2C_OLED_H_ */
