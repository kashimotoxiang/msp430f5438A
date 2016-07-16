/*
 * delay.h
 *
 *  Created on: 2014-9-29
 *      Author: ZhouChuGang
 */

#ifndef DELAY_H_
#define DELAY_H_
#include"main.h"
#ifndef u8
#define u8 unsigned char
#endif
#ifndef u16
#define u16 unsigned int
#endif

#ifndef u32
#define u32 unsigned long
#endif

#define DCO_16M							//DCOΪ16M  MCLK=SMCLK
//#define DCO_12M						//DCOΪ12M  MCLK=SMCLK
//#define DCO_8M						//DCOΪ8M  MCLK=SMCLK
//#define DCO_1M						//DCOΪ1M  MCLK=SMCLK

#define ACLK_LFXT1()    {BCSCTL3 |= LFXT1S_2;} //LFXT1 = VLO  ��Ƶʱ��ѡ��ΪVLO ACLKѡΪVLO
	  //BCSCTL2 |= SELM_3 + DIVM_3;            // MCLK = LFXT1/8
	 //��Ϊǰ���Ѿ�ѡ����LFXT1 = VLO ����MCLKѡΪVLO  8��Ƶ  ����CPU��MCLK��ԼΪ1.5KHz*/

#ifdef DCO_16M
#define CPU_F ((double)16000000)//cpu 16000000HZ
#define system_clock()  { WDTCTL = WDTPW | WDTHOLD;BCSCTL1=CALBC1_16MHZ;DCOCTL =CALDCO_16MHZ;}

#elif defined DCO_12M
#define CPU_F ((double)12000000)//cpu 12000000HZ
#define system_clock()  { WDTCTL = WDTPW | WDTHOLD;BCSCTL1=CALBC1_12MHZ;DCOCTL =CALDCO_12MHZ;}

#elif defined DCO_8M
#define CPU_F ((double)8000000)//cpu 8000000HZ
#define system_clock()  { WDTCTL = WDTPW | WDTHOLD;BCSCTL1=CALBC1_8MHZ;DCOCTL =CALDCO_8MHZ;}


#elif defined DCO_1M
#define CPU_F ((double)1000000)//cpu 1000000HZ
#define system_clock()  { WDTCTL = WDTPW | WDTHOLD;BCSCTL1=CALBC1_1MHZ;DCOCTL =CALDCO_1MHZ;}

#endif

#define delay_us(x) __delay_cycles((long)(CPU_F*(double)x/1000000.0))
#define delay_ms(x) __delay_cycles((long)(CPU_F*(double)x/1000.0))


#endif /* DELAY_H_ */
