#include "LDC1000_cmd.h"

#define DELAYNS  100   //�ӳ�ʱ��
#define AVRTIMES 100//��ƽ������

#define DELAYTIMES(){\
	TimeCounter = DELAYNS;\
	while (TimeCounter--);\
}\

#define LCD1000_CS_UPDATA(){\
	DELAYTIMES();\
	SPI_CS_1;\
	DELAYTIMES();\
	SPI_CS_0;\
	DELAYTIMES();\
}\

static void LDC1000_readByte(char addr, char * data);
static void LDC1000_writeByte(char addr, char data);

volatile static char proxDATA[2]; //��ʱ����
volatile static char freqDATA[3]; //��ʱ����
volatile static int proxDATATEMP; //��ʱ����
volatile static int freqDATATEMP; //��ʱ����

volatile static int TimeCounter = 0;

/*-------------------------------------------------------*
 *
 *LDC1000_READ
 *
 *-------------------------------------------------------*/
void LDC1000_INIT(void) {
	SPI_IO_Init();
	/*LDC CLK for Freq counter (set to output selected clock)-------------------------------------------------------*/
	LCD1000_CLK_DIR |= LCD1000_CLK_PIN;
	LCD1000_CLK_SEL |= LCD1000_CLK_PIN;
	/*write to register-------------------------------------------------------*/

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
}
/*-------------------------------------------------------*
 *
 *LDC1000_ValueGet
 *
 *-------------------------------------------------------*/
void LDC1000_ValueGet(struct LDC1000DATA_Struct *m_pLDCs) {
	int i = 100, m_proxMIN = 0, m_freqMIN = 0, m_proxMAX = 0, m_freqMAX = 0,
			m_prox = 0, m_freq = 0, m_prox_l = 0, m_freq_l = 0;
	int avrnum = AVRTIMES;
	unsigned long proxSum = 0, freqSum = 0;
	/*��ʼ����ֵ-------------------------------------------------------*/
	LDC1000_READ(&m_prox, &m_freq);
	m_proxMIN = m_prox;
	m_freqMIN = m_freq;
	m_proxMAX = m_prox;
	m_freqMAX = m_freq;
	m_prox_l = m_prox;
	m_freq_l = m_freq;
	/*ƽ������-------------------------------------------------------*/
	for (i = 0; i < AVRTIMES; i++) {
		LDC1000_READ(&m_prox, &m_freq);
		if (m_prox < m_prox_l * 0.9 || m_prox > m_prox_l * 1.1
				|| m_freq < m_freq_l * 0.9 || m_freq > m_freq_l * 1.1)  //����ų�
						{
			avrnum--;
			continue;
		}
		m_prox_l = m_prox;
		m_freq_l = m_freq;
		proxSum += m_prox;
		freqSum += m_freq;
		if (m_prox < m_proxMIN)
			m_proxMIN = m_prox;
		if (m_freq < m_freqMIN)
			m_freqMIN = m_freq;
		if (m_prox > m_proxMAX)
			m_proxMAX = m_prox;
		if (m_freq > m_freqMAX)
			m_freqMAX = m_freq;
	}
	/*�������βɼ�-------------------------------------------------------*/
	if (avrnum < 50) {
		m_pLDCs->freq = 0;
		m_pLDCs->prox = 0;
		m_pLDCs->proxMIN = 0;
		m_pLDCs->freqMIN = 0;
		m_pLDCs->proxMAX = 0;
		m_pLDCs->freqMAX = 0;
	}
	/*Result-------------------------------------------------------*/
	m_pLDCs->freq = freqSum / (double) avrnum;
	m_pLDCs->prox = proxSum / (double) avrnum;
	m_pLDCs->proxMIN = m_proxMIN;
	m_pLDCs->freqMIN = m_freqMIN;
	m_pLDCs->proxMAX = m_proxMAX;
	m_pLDCs->freqMAX = m_freqMAX;

}
/*-------------------------------------------------------*
 *
 *LDC1000_READ
 *
 *-------------------------------------------------------*/
void LDC1000_READ(int *prox, int *freq) {
	LDC1000_readByte(LDC1000_CMD_PROXLSB, &proxDATA[0]);
	LDC1000_readByte(LDC1000_CMD_PROXMSB, &proxDATA[1]);
	LDC1000_readByte(LDC1000_CMD_FREQCTRLSB, &freqDATA[0]);
	LDC1000_readByte(LDC1000_CMD_FREQCTRMID, &freqDATA[1]);
	LDC1000_readByte(LDC1000_CMD_FREQCTRMSB, &freqDATA[2]);

	*prox = ((unsigned char) proxDATA[1] << 8) + proxDATA[0];
	*freq = ((unsigned char) freqDATA[2] << 16)
			+ ((unsigned char) freqDATA[1] << 8) + freqDATA[0];
}

/**sub functions**/

/*-------------------------------------------------------*
 *
 *spi_readByte
 *
 *-------------------------------------------------------*/
void LDC1000_readByte(char addr, char * data) {
	SPI_CS_0;

	SPI_SendByte(addr | 0x80);
	*data = SPI_ReceiveByte();

	SPI_CS_1;
}

/*-------------------------------------------------------*
 *
 *LDC1000_writeByte
 *
 *-------------------------------------------------------*/
void LDC1000_writeByte(char addr, char data) {
	SPI_CS_0;

	SPI_SendByte(addr & ~0x80);
	SPI_SendByte(data);

	SPI_CS_1;
}

