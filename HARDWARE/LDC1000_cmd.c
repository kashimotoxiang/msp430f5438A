#include "LDC1000_cmd.h"

#define DELAYNS  1

#define DELAYTIMES(){\
	i = DELAYNS;\
	while (i--);\
}\

#define LCD1000_CS_UPDATA(){\
	DELAYTIMES();\
	LCD1000_CS_SET;\
	DELAYTIMES();\
	LCD1000_CS_CLR;\
	DELAYTIMES();\
}\

static void LDC1000_readByte(char addr, char * data);
static void LDC1000_writeByte(char addr, char data);

volatile static int i = 0;

struct LDC1000DATA_Struct LDC1000 = { 0 };
/*-------------------------------------------------------*
 *
 *LDC1000_READ
 *
 *-------------------------------------------------------*/
void LDC1000_INIT(void) {

	/*write to register-------------------------------------------------------*/

	LCD1000_CS_CLR;
	DELAYTIMES();

	LDC1000_writeByte(LDC1000_CMD_RPMAX, RPMAX);
	LDC1000_writeByte(LDC1000_CMD_RPMIN, RPMIN);
	LDC1000_writeByte(LDC1000_CMD_SENSORFREQ, 0x94);
	LDC1000_writeByte(LDC1000_CMD_LDCCONFIG, 0x17);
	LDC1000_writeByte(LDC1000_CMD_CLKCONFIG, 0x00);
	LDC1000_writeByte(LDC1000_CMD_INTCONFIG, 0x02);
	LDC1000_writeByte(LDC1000_CMD_THRESHILSB, 0x50);
	LDC1000_writeByte(LDC1000_CMD_THRESHIMSB, 0x14);
	LDC1000_writeByte(LDC1000_CMD_THRESLOLSB, 0xC0);
	LDC1000_writeByte(LDC1000_CMD_THRESLOMSB, 0x12);
	LDC1000_writeByte(LDC1000_CMD_PWRCONFIG, 0x01);

	DELAYTIMES();
	LCD1000_CS_SET;
}
/*-------------------------------------------------------*
 *
 *LDC1000_READ
 *
 *-------------------------------------------------------*/
void LDC1000_READ(void) {

	LCD1000_CS_CLR;
	DELAYTIMES();

	LDC1000_readByte(LDC1000_CMD_PROXLSB, &LDC1000.proxDATA[0]);
	LDC1000_readByte(LDC1000_CMD_PROXMSB, &LDC1000.proxDATA[1]);
	LDC1000_readByte(LDC1000_CMD_FREQCTRLSB, &LDC1000.freqDATA[0]);
	LDC1000_readByte(LDC1000_CMD_FREQCTRMID, &LDC1000.freqDATA[1]);
	LDC1000_readByte(LDC1000_CMD_FREQCTRMSB, &LDC1000.freqDATA[2]);



	DELAYTIMES();
	LCD1000_CS_SET;
}

/**sub functions**/

/*-------------------------------------------------------*
 *
 *spi_readByte
 *
 *-------------------------------------------------------*/
void LDC1000_readByte(char addr, char * data) {
	LCD1000_CS_CLR;
	SPI_SendByte(addr | 0x80);
	SPI_ReceiveByte(*data);
	LCD1000_CS_SET;
}

/*-------------------------------------------------------*
 *
 *LDC1000_writeByte
 *
 *-------------------------------------------------------*/
void LDC1000_writeByte(char addr, char data) {
	LCD1000_CS_CLR;
	SPI_SendByte(addr & ~0x80);
	SPI_SendByte(data);
	LCD1000_CS_SET;
}

