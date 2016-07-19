//*****************************************************************************
//
// #include 
//
//*****************************************************************************
#include "I2C_IncSreen.h"
#include "Display_EPD_W21.h"
#include "codetab.h"
//*****************************************************************************
//
// Variable
//
//*****************************************************************************

//*****************************************************************************
//
// Const
//
//*****************************************************************************
const unsigned char init_data[] = { 0x50, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x11,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0F, 0x0F, 0x0F,
		0x0F, 0x0F, 0x0F, 0x0F, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, };

//*****************************************************************************
//
// WaiteWrite
//
//*****************************************************************************
void IncS_Updata() {
	IncS_Write_Com(0x22);
	IncS_Write_Data(0xC7); // (Enable Clock Signal, Enable CP) (Display update,Disable CP,Disable Clock Signal)
	//  IncS_Write_Data(0xF7);    // (Enable Clock Signal, Enable CP, Load Temperature value, Load LUT) (Display update,Disable CP,Disable Clock Signal)
	IncS_Write_Com(0x20);
	//delayms(1);
	READBUSY();
}

//*****************************************************************************
//
// READBUSY
//
//*****************************************************************************
void READBUSY() {
	/*-------------------------------------------------------*/
	int in = P2IN, result = 0;
	while (1) {	 //=1 BUSY
		result = BIT_4 & P2IN;
		if (result == 0)
			break;
	}
	//delays(2);
}

//*****************************************************************************
//
//  IncS_Init
//	DIS_IMG(PIC_BLACK);
//	DIS_IMG(PIC_WHITE);
//*****************************************************************************
void IncS_Init() {
	/*Pin Init-------------------------------------------------------*/
	IncS_DIR |= IncS_SDA | IncS_SCL | IncS_CS | IncS_DC | IncS_RST;

	/*Reset-------------------------------------------------------*/
	IncS_nRST_L;
	delayms(10); //1ms
	IncS_nRST_H;
	delayms(10); //1ms

	/*READBUSY-------------------------------------------------------*/
	READBUSY();

	/*Init-------------------------------------------------------*/
	IncS_Write_Com(0x01);       // Gate Setting
	IncS_Write_Data(0xF9);    // MUX Gate lines=250-1=249(F9H)
	IncS_Write_Data(0x00); // B[2]:GD=0[POR](G0 is the 1st gate output channel)  B[1]:SM=0[POR](left and right gate interlaced)  B[0]:TB=0[POR](scan from G0 to G319)
	IncS_Write_Com(0x3A); // number of dummy line period   set dummy line for 50Hz frame freq
	IncS_Write_Data(0x06); // Set 50Hz   A[6:0]=06h[POR] Number of dummy line period in term of TGate
	IncS_Write_Com(0x3B); // Gate line width   set gate line for 50Hz frame freq
	IncS_Write_Data(0x0B); // A[3:0]=1011(78us)  Line width in us   78us*(250+6)=19968us=19.968ms
	IncS_Write_Com(0x3C);	      // Select border waveform for VBD
	//    IncS_Write_Data(0x30);    // GS0-->GS0
	//    IncS_Write_Data(0x31);    // GS0-->GS1
	//    IncS_Write_Data(0x32);    // GS1-->GS0
	IncS_Write_Data(0x33);    // GS1-->GS1  ?a?úμúò?′??￠D?Border′ó°×μ?°×
	//    IncS_Write_Data(0x43);    // VBD-->VSS
	//    IncS_Write_Data(0x53);    // VBD-->VSH
	//    IncS_Write_Data(0x63);    // VBD-->VSL
	//    IncS_Write_Data(0x73);    // VBD-->HiZ

	IncS_Write_Com(0x11);	      // Data Entry mode
	IncS_Write_Data(0x01);    // 01 ¨CY decrement, X increment
	IncS_Write_Com(0x44);       // set RAM x address start/end, in page 22
	IncS_Write_Data(0x00);    // RAM x address start at 00h;
	IncS_Write_Data(0x0f);    // RAM x address end at 0fh(15+1)*8->128    2D13
	IncS_Write_Com(0x45);	      // set RAM y address start/end, in page 22
	IncS_Write_Data(0xF9);    // RAM y address start at FAh-1;		    2D13
	IncS_Write_Data(0x00);    // RAM y address end at 00h;		    2D13

	IncS_Write_Com(0x2C);       // Vcom= *(-0.02)+0.01???
	//    IncS_Write_Data(0x82);    //-2.5V
	//    IncS_Write_Data(0x69);    //-2V
	IncS_Write_Data(0x4B);    //-1.4V
	//    IncS_Write_Data(0x50);    //-1.5V
	//    IncS_Write_Data(0x37);    //-1V
	//    IncS_Write_Data(0x1E);    //-0.5V

	WRITE_LUT();
	IncS_Write_Com(0x21);       // Option for Display Update
	IncS_Write_Data(0x83); // A[7]=1(Enable bypass)  A[4]=0è?oú(value will be used as for bypass)

	IncS_Write_Com(0x21);       //
	IncS_Write_Data(0x03);    // oó???￠D????′?y3￡μ??°oó2·ùí?±è??
	IncS_Write_Com(0x3C);       // Select border waveform for VBD
	IncS_Write_Data(0x73);    // VBD-->HiZ  oó???￠D?ê±Border??ê???×è
	/*-------------------------------------------------------*/
	DIS_IMG(PIC_WHITE);    //清屏
	DIS_IMG(PIC_WHITE);
	/*局部更新-------------------------------------------------------*/
	EPD_init_Part();
}

//*****************************************************************************
//
// WRITE_LUT
//
//*****************************************************************************
void WRITE_LUT() {
	unsigned char i;
	IncS_Write_Com(0x32);    //write LUT register
	for (i = 0; i < 29; i++)
		IncS_Write_Data(init_data[i]);    //write LUT register
}

//*****************************************************************************
//
// IncS_Write_Com
//
//*****************************************************************************
void IncS_Write_Com(unsigned char INIT_COM) {
	unsigned char TEMPCOM;
	unsigned char scnt;
	TEMPCOM = INIT_COM;
	IncS_nCS_H;
	IncS_nCS_L;
	IncS_SCLK_L;
	IncS_nDC_L;
	for (scnt = 0; scnt < 8; scnt++) {
		if (TEMPCOM & 0x80)
			IncS_SDA_H;
		else
			IncS_SDA_L;
		IncS_SCLK_H;
		IncS_SCLK_L;
		TEMPCOM = TEMPCOM << 1;
	}
	IncS_nCS_H;
}

//*****************************************************************************
//
// IncS_Write_Data
//
//*****************************************************************************
void IncS_Write_Data(unsigned char INIT_DATA) {
	unsigned char TEMPCOM;
	unsigned char scnt;
	TEMPCOM = INIT_DATA;
	IncS_nCS_H;
	IncS_nCS_L;
	IncS_SCLK_L;
	IncS_nDC_H;
	for (scnt = 0; scnt < 8; scnt++) {
		if (TEMPCOM & 0x80)
			IncS_SDA_H;
		else
			IncS_SDA_L;
		IncS_SCLK_H;
		IncS_SCLK_L;
		TEMPCOM = TEMPCOM << 1;
	}
	IncS_nCS_H;
}

//*****************************************************************************
//
// IncS 设置坐标
//
//*****************************************************************************
void IncS_Set_Pos(u8 x, u8 y) //设置OLED坐标
{
	IncS_Write_Com(0x4E);
	IncS_Write_Data(x);  // set RAM x address count to 0;
	IncS_Write_Com(0x4F);
	IncS_Write_Data(y);  // set RAM y address count to 250-1;	2D13
	//delays(5);
	IncS_Write_Com(0x24);
	//delays(5);
}

/***************功能描述：显示6*8一组标准ASCII字符串	显示的坐标（x,y），y为页范围0～7****************/
void IncS_P6x8Str(u8 x, u8 y, u8 ch[]) {
	u8 c = 0, i = 0, j = 0;
	while (ch[j] != '\0') {
		c = ch[j] - 32;
		if (x > 126) {
			x = 0;
			y++;
		}				//边界限制  强制拉回
		IncS_Set_Pos(x, y);
		for (i = 0; i < 6; i++)
			IncS_Write_Data(F6x8[c][i]);
		x += 6;
		j++;
	}

}
/*******************功能描述：显示8*16一组标准ASCII字符串	 显示的坐标（x,y），y为页范围0～7****************/
void IncS_P8x16Str(u8 x, u8 y, u8 ch[]) {
	u8 c = 0, i = 0, j = 0;
	//x=120-x;
	while (ch[j] != '\0') {
		c = ch[j] - 32;
		if (x > 120) {
			x = 0;
			y++;
		}					//边界限制  强制拉回

		for (i = 0; i < 8; i++) {					//下半部分
			IncS_Set_Pos(x, y + i);
			IncS_Write_Data(F8X16[c * 16 + i + 8]);
		}
		for (i = 0; i < 8; i++) {					//上半部分
			IncS_Set_Pos(x + 1, y + i);
			IncS_Write_Data(F8X16[c * 16 + i]);
		}

		y += 8;
		j++;
	}
}
/*****************功能描述：显示16*16点阵  显示的坐标（x,y），y为页范围0～7****************************/
void IncS_P16x16Ch(u8 x, u8 y, u8 num) {
	u8 wm = 0;
	u16 adder = 32 * num;
	IncS_Set_Pos(x, y);
	for (wm = 0; wm < 16; wm++) {
		IncS_Write_Data(F16x16[adder]);
		adder += 1;
	}
	IncS_Set_Pos(x, y + 1);
	for (wm = 0; wm < 16; wm++) {
		IncS_Write_Data(F16x16[adder]);
		adder += 1;
	}
}

//*****************************************************************************
//
// DIS_IMG
//
//*****************************************************************************
void DIS_IMG(unsigned char num) {
	unsigned int row, col;
	unsigned int pcnt;

	IncS_Set_Pos(0x00, 0xF9);

	pcnt = 0;                 // ?′???ò±￡′?ìáê?×??úDòo?
	for (col = 0; col < 250; col++) // ×ü12250 GATEáD  // send 128x250bits ram 2D13
			{
		for (row = 0; row < 16; row++) // ×ü12128 SOURCEDD￡?????????1bit,?′ 128/8=16 ×??ú
				{
			switch (num) {
			case PIC_WHITE:
				IncS_Write_Data(0xff);
				break;

			case PIC_BLACK:
				IncS_Write_Data(0x00);
				break;
			default:
				break;
			}
			pcnt++;
		}
	}
	IncS_Updata();
}

