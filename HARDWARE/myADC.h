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
#define	Max_Volt        3.3
#define	Accu_Adc        4095
/*-------------------------------------------------------*/
#define ADC_SEL  (P6SEL)
#define ADC_DIR  (P6DIR)
#define ADC_PIN   (BIT0)
/*-------------------------------------------------------*/
#define mSelect_Potentiometer_Ad (Potentiometer_Ad_SEL |= Potentiometer_Ad_IO) 
#define mSetIn_Potentiometer_Ad (Potentiometer_Ad_DIR &= (~Potentiometer_Ad_IO))  

//*****************************************************************************
//
// declartion
//
//*****************************************************************************
void ADC_Init(u8 DMAInitFlag);
void ADC_Disable(void);
void Open_ADC12_A(void);
void Close_ADC12_A(void);
void ADC_ReSet(void);

