#pragma once
//******************************************************************************
//  MSP430F543xA Demo - USCI_B0 I2C Master TX single bytes to MSP430 Slave
//
//  Description: This demo connects two MSP430's via the I2C bus. The master
//  transmits to the slave. This is the master code. It continuously
//  transmits 00h, 01h, ..., 0ffh and demonstrates how to implement an I2C
//  master transmitter sending a single byte using the USCI_B0 TX interrupt.
//  ACLK = n/a, MCLK = SMCLK = BRCLK = default DCO = ~1.045MHz
//
//      ***to be used with msp430x54xA_uscib0_i2c_07.c***
//
//                                /|\  /|\
//                MSP430F5438A     10k  10k     MSP430F5438A
//                   slave         |    |         master
//             -----------------   |    |   -----------------
//           -|XIN  P3.1/UCB0SDA|<-|----+->|P3.1/UCB0SDA  XIN|-
//            |                 |  |       |                 |
//           -|XOUT             |  |       |             XOUT|-
//            |     P3.2/UCB0SCL|<-+------>|P3.2/UCB0SCL     |
//            |                 |          |                 |
//
//   F. Chen
//   Texas Instruments Inc.
//   Dec. 2012
//   Built with CCS Version: 5.2.1 and IAR Embedded Workbench Version: 5.51.1
//******************************************************************************
//*****************************************************************************
//
// include
//
//*****************************************************************************
#include "main.h"

//*****************************************************************************
//
// declartion
//
//*****************************************************************************
void IIC_Init(void);
inline void IICSendByte(uint8_t Addr,uint8_t TXData);
