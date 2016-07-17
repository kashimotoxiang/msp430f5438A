#pragma once
//*****************************************************************************
//
// System Type
//
//*****************************************************************************
typedef volatile unsigned char __uIO8;
typedef volatile unsigned short int __uIO16;
typedef volatile unsigned int __uIO32;

typedef volatile signed char __IO8;
typedef volatile signed short int __IO16;
typedef volatile signed int __IO32;

typedef unsigned char u8_t;
typedef unsigned short int u16_t;
typedef unsigned short int u32_t;

typedef unsigned char uint8_t;
typedef unsigned short int uint16_t;
typedef unsigned short int uint32_t;

typedef u8_t u8;
typedef u16_t u16;
typedef u32_t u32;

//*****************************************************************************
//
// include
//
//*****************************************************************************

/*System-------------------------------------------------------*/
#include <msp430.h>
#include "stdio.h" //用sprintf要用的头文件
#include "math.h"

/*Hardware-------------------------------------------------------*/
#include "mySPI.h"
#include "myADC.h"
#include "myKey.h"
#include "myIIC.h"
#include "mySPI.h"
#include "myUART.h"
#include "myTimer.h"

/*Software-------------------------------------------------------*/
#include "System.h"
#include "KeyBroad.h"
#include "Usual.h"

/*User Hardware-------------------------------------------------------*/
#include "I2C_OLED.h"
#include "I2C_IncSreen.h"

//*****************************************************************************
//
// define
//
//*****************************************************************************
/*Buf大小-------------------------------------------------------*/
#define SPI_TXBUF_SIZE         256
#define SPI_RXBUF_SIZE         256
#define ADC_CONVBUF_SIZE       10

/*通识状态-------------------------------------------------------*/
#define e_SUCCESS 1
#define e_FLASE   0
#define e_ERROR  -1

/*DMA开关标识-------------------------------------------------------*/
#define DMAOPEN   1
#define DMACLOSE  0
/*BIT-------------------------------------------------------*/
#define BIT_0   (0x0001)
#define BIT_1   (0x0002)
#define BIT_2   (0x0004)
#define BIT_3   (0x0008)
#define BIT_4   (0x0010)
#define BIT_5   (0x0020)
#define BIT_6   (0x0040)
#define BIT_7   (0x0080)
#define BIT_8   (0x0100)
#define BIT_9   (0x0200)
/*-------------------------------------------------------*/
#define SLEEPLIEVEL LPM4_bits
//*****************************************************************************
//
// User Type
//
//*****************************************************************************
typedef uint8_t SPIDataType;
typedef uint8_t ADCDataType;

//*****************************************************************************
//
//extern
//
//*****************************************************************************
extern long SystemTimeCounter;
extern SPIDataType g_SPIRxBuf[SPI_RXBUF_SIZE];
extern ADCDataType g_ADCConvBuf[ADC_CONVBUF_SIZE];
