#include "mySPI.h"

#define DEALYUS__   100
void SPI_IO_Init(void)                    //���ų�ʼ��
{
	SPI_DIR |= SPI_CS_PIN + SPI_CLK_PIN + SPI_DIO_PIN;
	SPI_DIR &= ~SPI_DO_PIN;
	SPI_REN|=SPI_DO_PIN;

	SPI_CS_1;
	SPI_CLK_0;
	delay_ms(10);
}

//д��һ���ֽ�
void Spi_WriteByte(uchar data) {
	uchar i;
	SPI_CLK_0;                                    //ģʽ0
	delay_us(DEALYUS__);
	for (i = 0; i < 8; i++) {
		SPI_CLK_0;
		if (0x80 & data)
			SPI_DIO_1;
		else
			SPI_DIO_0;
		delay_us(DEALYUS__);
		SPI_CLK_1;
		delay_us(DEALYUS__);
		data <<= 1;
	}
	SPI_CLK_0;
	SPI_DIO_0;
	delay_us(DEALYUS__);
}

//��ȡһ���ֽ�
uchar Spi_ReadByte(void) {
	uchar i, temp = 0;
	SPI_CLK_0;                                    //ģʽ0
	delay_us(DEALYUS__);
	for (i = 0; i < 8; i++) {
		temp <<= 1;
		SPI_CLK_1;
		delay_us(DEALYUS__);
		if (SPI_DO_IN)        //��ȡ���λ����������ĩβ��ͨ������λ��������ֽ�
			temp |= 0x01;
		SPI_CLK_0;
		delay_us(DEALYUS__);
	}
	SPI_CLK_0;
	SPI_DIO_0;
	delay_us(DEALYUS__);
	return temp;
}

//оƬдʹ��
void Write_Enable(void) {
	SPI_CS_0;
	delay_us(1);
	Spi_WriteByte(WRITE_ENABLE);
	SPI_CS_1;
}

//оƬ��ֹд��
void Write_Disable(void) {
	SPI_CS_0;
	delay_us(1);
	Spi_WriteByte(WRITE_DISABLE);
	SPI_CS_1;
}

//��ȡоƬ״̬�Ĵ���
uchar Read_StatReg(void) {
	uchar temp;
	SPI_CS_0;
	delay_us(1);
	Spi_WriteByte(READ_STATUSREG);
	temp = Spi_ReadByte();
	SPI_CS_1;
	return temp;
}

//д״̬�Ĵ���
void Write_StatReg(uchar com) {
	SPI_CS_0;
	delay_us(1);
	Spi_WriteByte(WRITE_STATUSREG);
	Spi_WriteByte(com);
	SPI_CS_1;
}

void Erase_Page(long address) {
	uchar H, M, L;
	H = address >> 16;
	M = address >> 8;
	L = address & 0xff;

	Write_Enable();             //��ִ��дʹ��
	SPI_CS_0;
	delay_us(1);
	Spi_WriteByte(CLEAR_PAGE);
	Spi_WriteByte(H);
	Spi_WriteByte(M);
	Spi_WriteByte(L);
	SPI_CS_1;
}

//�������ַд��һ���ֽ�
void Write_Byte(long address, uchar byte) {
	uchar H, M, L;
	H = address >> 16;
	M = address >> 8;
	L = address & 0xff;

	SPI_CS_0;
	delay_us(1);
	Spi_WriteByte(WRITE_PAGE);
	Spi_WriteByte(H);
	Spi_WriteByte(M);
	Spi_WriteByte(L);

	Spi_WriteByte(byte);

	SPI_CS_1;
}

//�������ַ��ʼд��һ�����ݰ�����󳤶Ȳ�����256���ֽڣ�
void Write_Date(long address, uchar Date_Buf[], uchar size) {
	uchar i;
	uchar H, M, L;
	H = address >> 16;
	M = address >> 8;
	L = address & 0xff;

	SPI_CS_0;
	delay_us(1);
	Spi_WriteByte(WRITE_PAGE);
	Spi_WriteByte(H);
	Spi_WriteByte(M);
	Spi_WriteByte(L);
	for (i = 0; i < size; i++) {
		Spi_WriteByte(Date_Buf[i]);
	}
	SPI_CS_1;
}

//�������ַ����һ���ֽ�
uchar Read_Byte(long address) {
	uchar temp;
	uchar H, M, L;
	H = address >> 16;
	M = address >> 8;
	L = address & 0xff;

	SPI_CS_0;
	delay_us(1);
	Spi_WriteByte(READ_DATE);
	Spi_WriteByte(H);
	Spi_WriteByte(M);
	Spi_WriteByte(L);
	temp = Spi_ReadByte();
	SPI_CS_1;
	return temp;
}

//�������ַ��ʼ��������
void Read_Data(long address, uchar Date_Buf[], uint size) {
	uchar i;
	uchar H, M, L;
	H = address >> 16;
	M = address >> 8;
	L = address & 0xff;

	SPI_CS_0;
	delay_us(1);
	Spi_WriteByte(READ_DATE);
	Spi_WriteByte(H);
	Spi_WriteByte(M);
	Spi_WriteByte(L);
	for (i = 0; i < size; i++) {
		Date_Buf[i] = Spi_ReadByte();
	}

	SPI_CS_1;
}
