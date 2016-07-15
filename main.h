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
#include "HAL_PMM.h"
/*Hardware-------------------------------------------------------*/
#include "mySPI.h"
#include "myADC.h"
#include "myIIC.h"
#include "myKey.h"
#include "mySPI.h"
#include "myTimer.h"

#include "OLED_I2C.h"
#include "System.h"
/*Software-------------------------------------------------------*/
#include "KeyBroad.h"

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
extern SPIDataType g_SPIRxBuf[SPI_RXBUF_SIZE];
extern ADCDataType g_ADCConvBuf[ADC_CONVBUF_SIZE];
