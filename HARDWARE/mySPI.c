//******************************************************************************
//   MSP430F543xA Demo - USCI_A2, SPI 3-Wire Slave Data Echo
//
//   Description: SPI slave talks to SPI master using 3-wire mode. Data received
//   from master is echoed back.  USCI RX ISR is used to handle communication,
//   CPU normally in LPM4.  Prior to initial data exchange, master pulses
//   slaves RST for complete reset.
//   ACLK = ~32.768kHz, MCLK = SMCLK = DCO ~ 1048kHz
//
//   Use with SPI Master Incremented Data code example.  If the slave is in
//   debug mode, the reset signal from the master will conflict with slave's
//   JTAG; to work around, use IAR's "Release JTAG on Go" on slave device.  If
//   breakpoints are set in slave RX ISR, master must stopped also to avoid
//   overrunning slave RXBUF.
//
//                   MSP430F5438A
//                 -----------------
//            /|\ |                 |
//             |  |                 |
//    Master---+->|RST          P1.0|-> LED
//                |                 |
//                |             P3.4|-> Data Out (UCA2SIMO)
//                |                 |
//                |             P3.5|<- Data In (UCA2SOMI)
//                |                 |
//                |             P3.0|-> Serial Clock Out (UCA2CLK)
//
//
//   M. Morales
//   Texas Instruments Inc.
//   October 2008
//   Built with CCE Version: 3.2.2 and IAR Embedded Workbench Version: 4.11B
//******************************************************************************
#include "mySPI.h"
//*****************************************************************************
//
// Static Varible
//
//*****************************************************************************
static uint8_t DMASwitch = 0; //��Ϊֻ��һ��ADC������һ��DMA����
static char TxString[] = { 'A', 'b', 'c' };
static char RxString = 'a';
/*Normal-------------------------------------------------------*/
//*****************************************************************************
//
// SPI Master ��ʼ��
//
//*****************************************************************************
void SPI0MasterInit(u8 DMAInitFlag) {
	/*��ʼ��-------------------------------------------------------*/
	P3DIR |= BIT4 | BIT0;
	P3SEL |= 0x31;                            // P3.5,4,0 option select

	UCA2CTL1 |= UCSWRST;                      // **Put state machine in reset**
	UCA2CTL0 |= UCMST + UCSYNC + UCCKPL + UCMSB;    // 3-pin, 8-bit SPI master
													// Clock polarity high, MSB
	UCA2CTL1 |= UCSSEL_2;                     // SMCLK
	UCA2BR0 = 0x02;                           // /2
	UCA2BR1 = 0;                              //
	UCA2MCTL = 0;                             // No modulation
	UCA2CTL1 &= ~UCSWRST;                   // **Initialize USCI state machine**
	UCA2CTL1 &= ~UCSWRST;                   // **Initialize USCI state machine**
	UCA2IE |= UCRXIE;                         // Enable USCI_A2 RX interrupt

	/*-------------------------------------------------------*/
	if (DMAInitFlag) {
		DMASwitch = 1;                         //��ʾ����DMA
		DMACTL0 &= ~DMA0TSEL_31;           //DMA0 is triggered by USCIA2 receive
		DMACTL0 = DMA0TSEL_17;            //DMA0 is triggered by USCIA2 transmit
		//DMA0SA = (int) g_SPITxBuf ;                           // Source �ֵ�ַ
		DMA0DA = (int) &UCA2RXBUF;                                // Ŀ���ֵ�ַ
		//DMA0SZ = sizeof(g_SPITxBuf);                                      //�����С
		DMA0CTL = DMADT_0 + DMADSTINCR_3 + DMASBDB + DMAEN; // �ظ��ֽڴ���
	}
	/*-------------------------------------------------------*/
	P1OUT &= ~0x02;                         // Now with SPI signals initialized,
	P1OUT |= 0x02;                            // reset slave

	__delay_cycles(100);                      // Wait for slave to initialize
	/*-------------------------------------------------------*
	 MST_Data = 0x01;                          // Initialize data values
	 SLV_Data = 0x00;                          //

	 while (!(UCA2IFG & UCTXIFG))
	 ;               // USCI_A2 TX buffer ready?
	 UCA2TXBUF = MST_Data;                     // Transmit first character

	 __bis_SR_register(LPM0_bits + GIE);       // CPU off, enable interrupts
	 *-------------------------------------------------------*/
}
//*****************************************************************************
//
// SPI Slave DMA��ʼ��
//
//*****************************************************************************
void SPI0SlaveDMAInit(void) {
	/*���Ź���ʱ��-------------------------------------------------------*/
	WDTCTL = WDT_ADLY_1_9;                  // WDT 1000ms, ACLK, interval timer
	SFRIE1 |= WDTIE;                          // Enable WDT interrupt

	/*-------------------------------------------------------*/
	P9SEL |= 0x31;                            // P3.0,4,5 = USCI_A2 SPI Option

	UCA2CTL1 |= UCSWRST;                      // **Put state machine in reset**
	UCA2CTL0 = UCMST + UCSYNC + UCCKPL + UCMSB;     // 3-pin, 8-bit SPI master
													// Clock polarity high, MSB
	UCA2CTL1 = UCSSEL_2;                      // SMCLK
	UCA2BR0 = 0x02;                           // /2
	UCA2BR1 = 0x00;                           //
	UCA2MCTL = 0x00;                          // No modulation
	UCA2CTL1 &= ~UCSWRST;                   // **Initialize USCI state machine**

	/*-------------------------------------------------------*/
	DMACTL0 = DMA0TSEL_17;     		    // DMA0 - UCA2TXIFG
	// Setup DMA0(TX)

	DMA0SA = (int) TxString;                           // Source �ֵ�ַ
	DMA0DA = (int) &UCA2TXBUF;                                // Ŀ���ֵ�ַ

	DMA0SZ = 3;                               // Block size
	//DMA0CTL = DMASRCINCR_3 + DMASBDB + DMALEVEL + DMAEN;  // inc src
	DMA0CTL = DMADT_0 + DMADSTINCR_3 + DMASBDB + DMALEVEL + DMAEN; // �ظ��ֽڴ���
//	/*-------------------------------------------------------*/
//	DMACTL0 = DMA1TSEL_16; 				// DMA1 - UCA2RXIFG
//	// Setup DMA1(RX)
//
//	__data16_write_addr((unsigned short) &DMA1SA, (unsigned long) &UCA2RXBUF);
//	// Source block address
//
//	__data16_write_addr((unsigned short) &DMA1DA, (unsigned long) &RxString);
//	// Destination single address
//
//	DMA1SZ = 1;                               // Block size
//	DMA1CTL = DMADSTINCR_3 + DMASBDB + DMALEVEL;  // inc dst
//	DMA1CTL = DMADT_0 + DMADSTINCR_3 + DMASBDB +DMALEVEL+ DMAEN; // �ظ��ֽڴ���
}

//*****************************************************************************
//
// Trigger DMA0 & DMA1 block transfer.
//
//*****************************************************************************
#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector=WDT_VECTOR
__interrupt void WDT_ISR(void)
#elif defined(__GNUC__)
void __attribute__ ((interrupt(WDT_VECTOR))) WDT_ISR (void)
#else
#error Compiler not supported!
#endif
{
	DMA0CTL |= DMAEN;                         // DMA0 Enable
}

