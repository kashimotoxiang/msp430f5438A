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
// UART∑¢ÀÕ
#define SPI_SendByte(TXData) {\
	while (!(UCB2IFG & UCTXIFG));\
	UCB2TXBUF = TXData;\
	while (UCB2STAT & UCBUSY);\
}\

// UARTΩ” ‹
#define SPI_ReceiveByte(RXData) {\
	while (!(UCB2IFG & UCTXIFG));\
	UCB2TXBUF = 0;\
	while (UCB2STAT & UCBUSY);\
	RXData=UCB2RXBUF;\
	while (UCB2STAT & UCBUSY);\
}\
//*****************************************************************************
//
// declartion
//
//*****************************************************************************
void SPI0MasterInit(u8 DMAInitFlag);
void SPI0SlaveDMAInit(void);
