//*****************************************************************************
//
// include
//
//*****************************************************************************
#include "myADC.h"
//*****************************************************************************
//
// note：
// ADC12一个
//
//*****************************************************************************

//*****************************************************************************
//
// static varaible
//
//*****************************************************************************
static uint32_t ADC12SHT0_x = ADC12SHT0_15; //采样保持时间
static uint8_t DMASwitch = 0; //因为只有一个ADC，设置一个DMA开关
//*****************************************************************************
//
// ADC_DMA初始化
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
	ADC_SEL |= ADC_PIN; //配置引脚为"外围模块功能"引脚
	ADC_DIR &= (~ADC_PIN);   //配置引脚为"输入"
	/*-------------------------------------------------------*/
	ADC12CTL0 = ADC12SHT0_x + ADC12REFON + ADC12MSC + ADC12REF2_5V; // Turn on ADC12, Sampling time  On Reference Generator and set to 2.5V
	ADC12CTL1 = ADC12CSTARTADD_0 + ADC12SHP + ADC12SSEL_3 + ADC12CONSEQ_2; // Use sampling timer
	ADC12CTL2 = ADC12RES_0;  //选择ADC 为12位
	ADC12MCTL0 = ADC12INCH_0 + ADC12SREF_0;	 // Vr+=Vref+ and Vr-=AVss
	/*-------------------------------------------------------*/
	if (DMAInitFlag) {
		DMASwitch = 1;
		DMACTL0 &= ~DMA0TSEL_31;                   //DMA0 is triggered by DMAREQ
		DMACTL0 = DMA0TSEL_24;                     //DMA0 is triggered by DMAREQ
		DMA0SA = (int) &ADC12MEM0;                           // Source 字地址
		DMA0DA = (int) g_ADCConvBuf;                                // 目的字地址
		DMA0SZ = sizeof(g_ADCConvBuf);                                      //传输大小
		DMA0CTL = DMADT_0 + DMADSTINCR_3 + DMASBDB + DMAEN; // 重复字节传输
	}
	/*-------------------------------------------------------*/
	TA0CTL = TASSEL_2 + MC_2;                   // SMCLK, 连续模式
	Open_ADC12_A();
	ADC12CTL0 |= ADC12SC;
}

//*****************************************************************************
//
// 失能ADC
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
// 打开ADC
//
//*****************************************************************************
void Open_ADC12_A(void) //打开ADC12_A模块
{
	ADC12CTL0 |= ADC12ON;   // 1  ADC12_A打开
	ADC12CTL0 |= ADC12ENC;	//0  ADC12_A禁止//1  ADC12_A使能 // Enable conversions
	ADC12CTL0 |= ADC12SC;
}

//*****************************************************************************
//
// 关闭ADC
//
//**************************************** *************************************
void Close_ADC12_A(void) //关闭ADC12_A模块
{
	ADC12CTL0 &= ~ADC12ON;  // 0  ADC12_A关闭
	ADC12CTL0 &= ~ADC12ENC;	 //0  ADC12_A禁止
}

//*****************************************************************************
//
// 重置ADC
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
	ADC12CTL2 = ADC12RES_0;  //选择ADC 为12位
	ADC12MCTL0 = ADC12INCH_0 + ADC12SREF_0;	 // Vr+=Vref+ and Vr-=AVss
	/*-------------------------------------------------------*/
	if (DMASwitch)
		DMA0CTL = DMADT_0 + DMADSTINCR_3 + DMASBDB + DMAEN; // 重复字节传输
	Open_ADC12_A();
	ADC12CTL0 |= ADC12SC;
}

//*****************************************************************************
//
// 重置ADC_Timer
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
	ADC12CTL2 = ADC12RES_0;  //选择ADC 为12位
	ADC12MCTL0 = ADC12INCH_0 + ADC12SREF_0;	 // Vr+=Vref+ and Vr-=AVss
	/*-------------------------------------------------------*/
	Open_ADC12_A();
	Init_Timer0_A();
}
