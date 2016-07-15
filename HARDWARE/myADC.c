//*****************************************************************************
//
// include
//
//*****************************************************************************
#include "myADC.h"
//*****************************************************************************
//
// note��
// ADC12һ��
//
//*****************************************************************************

//*****************************************************************************
//
// static varaible
//
//*****************************************************************************
static uint32_t ADC12SHT0_x = ADC12SHT0_15; //��������ʱ��
static uint8_t DMASwitch = 0; //��Ϊֻ��һ��ADC������һ��DMA����
//*****************************************************************************
//
// ADC_DMA��ʼ��
//
//*****************************************************************************
void ADC_Init(u8 DMAInitFlag) {
	Close_ADC12_A();
	ADC12CTL0 = 0;
	ADC12CTL1 = 0;
	ADC12MCTL0 = 0;
	/*-------------------------------------------------------*/
	REFCTL0 &= ~REFMSTR;
	/*-------------------------------------------------------*/
	ADC_SEL |= ADC_PIN; //��������Ϊ"��Χģ�鹦��"����
	ADC_DIR &= (~ADC_PIN);   //��������Ϊ"����"
	/*-------------------------------------------------------*/
	ADC12CTL0 = ADC12SHT0_x + ADC12REFON + ADC12MSC + ADC12REF2_5V; // Turn on ADC12, Sampling time  On Reference Generator and set to 2.5V
	ADC12CTL1 = ADC12CSTARTADD_0 + ADC12SHP + ADC12SSEL_3 + ADC12CONSEQ_2; // Use sampling timer
	ADC12CTL2 = ADC12RES_0;  //ѡ��ADC Ϊ12λ
	ADC12MCTL0 = ADC12INCH_0 + ADC12SREF_0;	 // Vr+=Vref+ and Vr-=AVss
	/*-------------------------------------------------------*/
	if (DMAInitFlag) {
		DMASwitch = 1;
		DMACTL0 &= ~DMA0TSEL_31;                   //DMA0 is triggered by DMAREQ
		DMACTL0 = DMA0TSEL_24;                     //DMA0 is triggered by DMAREQ
		DMA0SA = (int) &ADC12MEM0;                           // Source �ֵ�ַ
		DMA0DA = (int) g_ADCConvBuf;                                // Ŀ���ֵ�ַ
		DMA0SZ = sizeof(g_ADCConvBuf);                                      //�����С
		DMA0CTL = DMADT_0 + DMADSTINCR_3 + DMASBDB + DMAEN; // �ظ��ֽڴ���
	}
	/*-------------------------------------------------------*/
	TA0CTL = TASSEL_2 + MC_2;                   // SMCLK, ����ģʽ
	Open_ADC12_A();
	ADC12CTL0 |= ADC12SC;
}

//*****************************************************************************
//
// ʧ��ADC
//
//*****************************************************************************
void ADC_Disable(void) {
	Close_ADC12_A();
	ADC12CTL0 = 0;
	ADC12CTL1 = 0;
	ADC12MCTL0 = 0;
	TA0CTL = 0;
	if (DMASwitch)
		DMA0CTL &= ~DMAEN;
}

//*****************************************************************************
//
// ��ADC
//
//*****************************************************************************
void Open_ADC12_A(void) //��ADC12_Aģ��
{
	ADC12CTL0 |= ADC12ON;   // 1  ADC12_A��
	ADC12CTL0 |= ADC12ENC;	//0  ADC12_A��ֹ//1  ADC12_Aʹ�� // Enable conversions
	ADC12CTL0 |= ADC12SC;
}

//*****************************************************************************
//
// �ر�ADC
//
//**************************************** *************************************
void Close_ADC12_A(void) //�ر�ADC12_Aģ��
{
	ADC12CTL0 &= ~ADC12ON;  // 0  ADC12_A�ر�
	ADC12CTL0 &= ~ADC12ENC;	 //0  ADC12_A��ֹ
}

//*****************************************************************************
//
// ����ADC
//
//*****************************************************************************
void ADC_ReSet(void) {
	Close_ADC12_A();
	ADC12CTL0 = 0;
	ADC12CTL1 = 0;
	ADC12MCTL0 = 0;
	/*-------------------------------------------------------*/
	ADC12CTL0 = ADC12SHT0_x + ADC12REFON + ADC12MSC + ADC12REF2_5V; // Turn on ADC12, Sampling time  On Reference Generator and set to 2.5V
	ADC12CTL1 = ADC12CSTARTADD_0 + ADC12SHP + ADC12SSEL_3 + ADC12CONSEQ_2; // Use sampling timer
	ADC12CTL2 = ADC12RES_0;  //ѡ��ADC Ϊ12λ
	ADC12MCTL0 = ADC12INCH_0 + ADC12SREF_0;	 // Vr+=Vref+ and Vr-=AVss
	/*-------------------------------------------------------*/
	if (DMASwitch)
		DMA0CTL = DMADT_0 + DMADSTINCR_3 + DMASBDB + DMAEN; // �ظ��ֽڴ���
	Open_ADC12_A();
	ADC12CTL0 |= ADC12SC;
}

//*****************************************************************************
//
// ����ADC_Timer
//
//*****************************************************************************
void ADC_Timer_ReSet(void) {
	Close_ADC12_A();
	ADC12CTL0 = 0;
	ADC12CTL1 = 0;
	ADC12MCTL0 = 0;
	/*-------------------------------------------------------*/
	ADC12CTL0 = ADC12SHT0_x + ADC12REFON + ADC12MSC; // Turn on ADC12, Sampling time  On Reference Generator and set to 2.5V
	ADC12CTL1 = ADC12CSTARTADD_0 + ADC12SHP + ADC12SSEL0 + ADC12CONSEQ_2; // Use sampling timer
	ADC12IE = 0x01;                           // Enable ADC12IFG.0
	ADC12CTL2 = ADC12RES_0;  //ѡ��ADC Ϊ12λ
	ADC12MCTL0 = ADC12INCH_0 + ADC12SREF_0;	 // Vr+=Vref+ and Vr-=AVss
	/*-------------------------------------------------------*/
	Open_ADC12_A();
	Init_Timer0_A();
}
