#pragma once

//*****************************************************************************
//
// include
//
//*****************************************************************************
#include "main.h"

//*****************************************************************************
//
// #define
//
//*****************************************************************************
#define uchar unsigned char
#define uint unsigned int

#define CPU_F ((double)24000000)
#define delay_us(x) __delay_cycles((long)(CPU_F*(double)x/1000000.0))
#define delay_ms(x) __delay_cycles((long)(CPU_F*(double)x/1000.0))

#define  SPI_DIR  P4DIR
#define  SPI_OUT  P4OUT
#define  SPI_REN  P4REN
#define  SPI_IN   P4IN

#define  SPI_CS_PIN   BIT0
#define  SPI_CLK_PIN  BIT1
#define  SPI_DIO_PIN  BIT2
#define  SPI_DO_PIN   BIT3

#define  SPI_CS_1    SPI_OUT|=SPI_CS_PIN
#define  SPI_CS_0    SPI_OUT&=~SPI_CS_PIN
#define  SPI_CLK_1   SPI_OUT|=SPI_CLK_PIN
#define  SPI_CLK_0   SPI_OUT&=~SPI_CLK_PIN
#define  SPI_DIO_1   SPI_OUT|=SPI_DIO_PIN
#define  SPI_DIO_0   SPI_OUT&=~SPI_DIO_PIN
#define  SPI_DO_IN   SPI_IN&SPI_DO_PIN        //输入引脚

//////W25X16 命令指令表定义
#define   WRITE_ENABLE          0X06
#define   WRITE_DISABLE         0X04
#define   READ_STATUSREG        0X05
#define   WRITE_STATUSREG       0X01
#define   READ_DATE             0X03
#define   READ_FAST             0X0B
#define   READ_DOUBLEFAST       0X3B
#define   WRITE_PAGE            0X02
#define   CLEAR_BLOCK           0XD8
#define   CLEAR_PAGE            0X20
#define   CLEAR_SHIP            0XC7
#define   POWER_OFF             0XB9
#define   POWER_ON              0XAB
#define   SHIP_ID               0X90
#define   JEDEC_ID              0X9F

//*****************************************************************************
//
// 宏函数
//
//*****************************************************************************
// UART发送
#define SPI_SendByte(TXData) 		 Spi_WriteByte(TXData)

// UART接受
#define SPI_ReceiveByte()			 Spi_ReadByte()
//*****************************************************************************
//
// declartion
//
//*****************************************************************************
void SPI_IO_Init(void);
void Write_Enable(void);
void Write_Disable(void);
uchar Read_StatReg(void);
void Write_StatReg(uchar com);
void Erase_Page(long address);
uchar Read_Byte(long address);
void Read_Data(long address, uchar Date_Buf[], uint size);
void Write_Byte(long address, uchar byte);
void Write_Date(long address, uchar Date_Buf[], uchar size);
void Spi_WriteByte(uchar data);
uchar Spi_ReadByte(void);
