//******************************************************************************
//   MSP430F543xA Demo - USCI_B2, SPI 3-Wire Slave Data Echo
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
//                |             P3.4|-> Data Out (UCB2SIMO)
//                |                 |
//                |             P3.5|<- Data In (UCB2SOMI)
//                |                 |
//                |             P3.0|-> Serial Clock Out (UCB2CLK)
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
static uint8_t DMASwitch = 0; //因为只有一个ADC，设置一个DMA开关
static char TxString[] = { 'A', 'b', 'c' };
static char RxString = 'a';
/*Normal-------------------------------------------------------*/
//*****************************************************************************
//
// SPI Master 初始化
//
//*****************************************************************************
void SPI0MasterInit(u8 DMAInitFlag) {
	P9SEL |= 0x31;                            // P3.0,4,5 = USCI_B2 SPI Option
	/*-------------------------------------------------------*/
	UCB2CTL1 |= UCSWRST;                      // **Put state machine in reset**
	UCB2CTL0 |= UCMST + UCSYNC + UCCKPL + UCMSB;    // 3-pin, 8-bit SPI master
													// Clock polarity high, MSB
	UCB2CTL1 |= UCSSEL_2;                     // SMCLK
	UCB2BR0 = 0x02;                           // /2
	UCB2BR1 = 0;                              //
	UCB2CTL1 &= ~UCSWRST;                   // **Initialize USCI state machine**
	UCB2CTL1 &= ~UCSWRST;                   // **Initialize USCI state machine**
	UCB2IE |= UCRXIE;                         // Enable USCI_B2 RX interrupt

	/*-------------------------------------------------------*/
	if (DMAInitFlag) {
		DMASwitch = 1;                         //表示启动DMA
		DMACTL0 &= ~DMA0TSEL_31;           //DMA0 is triggered by USCIB2 receive
		DMACTL0 = DMA0TSEL_17;            //DMA0 is triggered by USCIB2 transmit
		//DMA0SA = (int) g_SPITxBuf ;                           // Source 字地址
		DMA0DA = (int) &UCB2RXBUF;                                // 目的字地址
		//DMA0SZ = sizeof(g_SPITxBuf);                                      //传输大小
		DMA0CTL = DMADT_0 + DMADSTINCR_3 + DMASBDB + DMAEN; // 重复字节传输
	}
	/*-------------------------------------------------------*/
	P1OUT &= ~0x02;                         // Now with SPI signals initialized,
	P1OUT |= 0x02;                            // reset slave

	__delay_cycles(100);                      // Wait for slave to initialize
	/*-------------------------------------------------------*
	 MST_Data = 0x01;                          // Initialize data values
	 SLV_Data = 0x00;                          //

	 while (!(UCB2IFG & UCTXIFG))
	 ;               // USCI_B2 TX buffer ready?
	 UCB2TXBUF = MST_Data;                     // Transmit first character

	 __bis_SR_register(LPM0_bits + GIE);       // CPU off, enable interrupts
	 *-------------------------------------------------------*/
}
//*****************************************************************************
//
// SPI Slave DMA初始化
//
//*****************************************************************************
void SPI0SlaveDMAInit(void) {
	P9SEL |= BIT1 + BIT2 + BIT3;                // P9.0,4,5 = USCI_B2 SPI Option

	UCB2CTL1 |= UCSWRST;
	UCB2CTL0 |= UCMST + UCMSB + UCSYNC + UCCKPH; // 3-pin, 8-bit SPI master,Clock polarity high, MSB
	UCB2CTL1 |= UCSSEL_1;                 // CLOCK ACLK
	UCB2BR0 = 0x06;
	UCB2BR1 = 0x00;
	UCB2CTL1 &= ~UCSWRST;
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


