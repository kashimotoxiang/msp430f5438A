#pragma once
//*****************************************************************************
//
// include
//
//*****************************************************************************
#include "main.h"
//*****************************************************************************
//
// define
//
//*****************************************************************************
#define	NumOfResult	    8
#define	MAXVOLT        3.3
#define	ACCUADC        4095
/*-------------------------------------------------------*/
#define ADC_SEL   (P6SEL)
#define ADC_DIR   (P6DIR)
#define ADC_PIN   (BIT0)
/*-------------------------------------------------------*/
#define mSelect_Potentiometer_Ad (Potentiometer_Ad_SEL |= Potentiometer_Ad_IO) 
#define mSetIn_Potentiometer_Ad  (Potentiometer_Ad_DIR &= (~Potentiometer_Ad_IO))

//*****************************************************************************
//
// declartion
//
//*****************************************************************************
/*单次ADC-------------------------------------------------------*/
void ADCs_Init(void);
double ADCs_Get(void) ;
/*连续ADC-------------------------------------------------------*/
void ADCc_Init(u8 DMAInitFlag);
void ADC_Disable(void);
void Open_ADC12_A(void);
void Close_ADC12_A(void);
void ADC_ReSet(void);

