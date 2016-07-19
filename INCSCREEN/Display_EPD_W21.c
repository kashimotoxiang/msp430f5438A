#include "Display_EPD_W21_Aux.h"
#include "Display_EPD_W21_Config.h"

unsigned char FreqStr1[] = "Freq:";
unsigned char ProxStr1[] = "Prox:";

#ifdef GDE0213B1
const unsigned char LUTDefault_full[]= {
	0x32,	// command

	0x22,
	0x55,
	0xAA,
	0x55,
	0xAA,
	0x55,
	0xAA,
	0x11,
	0x00,
	0x00,
	0x00,
	0x00,
	0x00,
	0x00,
	0x00,
	0x00,
	0x1E,
	0x1E,
	0x1E,
	0x1E,
	0x1E,
	0x1E,
	0x1E,
	0x1E,
	0x01,
	0x00,
	0x00,
	0x00,
	0x00,

};

const unsigned char LUTDefault_part[]= {
	0x32,	// command

	0x18,
	0x00,
	0x00,
	0x00,
	0x00,
	0x00,
	0x00,
	0x00,
	0x00,
	0x00,
	0x00,
	0x00,
	0x00,
	0x00,
	0x00,
	0x00,
	0x0F,
	0x01,
	0x00,
	0x00,
	0x00,
	0x00,
	0x00,
	0x00,
	0x00,
	0x00,
	0x00,
	0x00,
	0x00,
};

#else
const unsigned char LUTDefault_part[31] = {
		0x32,	// command

		/*	0x00,0x00,0x00,0x18,
		 0x18,0x18,0x18,0x00,
		 0x00,0x00,0x00,0x00,
		 0x00,0x00,0x00,0x00,
		 0x00,0x00,0x00,0x00,
		 0x40,0x14,0x34,0x01,
		 0x00,0x00,0x00,0x00,
		 0x00,0x00,
		 */
		0x10 //C221 25C partial update waveform
		, 0x18, 0x18, 0x08, 0x18, 0x18, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x13, 0x14, 0x44, 0x12,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00

};

const unsigned char LUTDefault_full[31] = {
		0x32,	// command
		/*	0x11,0x11,0x10,0x02,	// full
		 0x02,0x22,0x22,0x22,
		 0x22,0x22,0x51,0x51,
		 0x55,0x88,0x08,0x08,
		 0x88,0x88,0x00,0x00,
		 0x34,0x23,0x12,0x21,
		 0x24,0x28,0x22,0x21,
		 0xA1,0x01
		 */
		0x02 //C221 25C Full update waveform
		, 0x02, 0x01, 0x11, 0x12, 0x12, 0x22, 0x22, 0x66, 0x69, 0x69, 0x59,
		0x58, 0x99, 0x99, 0x88, 0x00, 0x00, 0x00, 0x00, 0xF8, 0xB4, 0x13, 0x51,
		0x35, 0x51, 0x51, 0x19, 0x01, 0x00 };
#endif

static unsigned char ReadBusy(void) {
	unsigned long i = 0;

	for (i = 0; i < 400; i++) {
		if (isEPD_W21_BUSY == EPD_W21_BUSY_LEVEL) {
			return 1;
		}
		driver_delay_xms(10);
	}
	return 0;
}

static void EPD_W21_WriteCMD(unsigned char command) {
	EPD_W21_CS_0;
	EPD_W21_DC_0;		// command write
	SPI_Write(command);
	EPD_W21_CS_1;
}
//static void EPD_W21_WriteDATA(unsigned char command)
//{
//    EPD_W21_CS_0;                   
//	EPD_W21_DC_1;		// command write
//	SPI_Write(command);
//	EPD_W21_CS_1;
//}

static void EPD_W21_WriteCMD_p1(unsigned char command, unsigned char para) {
	//while(isEPD_W21_BUSY == 1);	// wait
	ReadBusy();

	EPD_W21_CS_0;
	EPD_W21_DC_0;		// command write
	SPI_Write(command);
	EPD_W21_DC_1;		// command write
	SPI_Write(para);
	EPD_W21_CS_1;
}

//static void EPD_W21_WriteCMD_p2(unsigned char command,unsigned char para1,unsigned char para2)
//{
//	while(isEPD_W21_BUSY == 1);	// wait	
//
//    EPD_W21_CS_0;                   
//	EPD_W21_DC_0;		// command write
//	SPI_Write(command);
//	EPD_W21_DC_1;		// command write
//	SPI_Write(para1);
//	SPI_Write(para2);
//	EPD_W21_CS_1;
//} 
/*********************************************
 功能：第一个字节写入的是命令值，剩余的是参数，
 在配置阶段使用

 *********************************************/
static void EPD_W21_Write(unsigned char *value, unsigned char datalen) {
	unsigned char i = 0;
	unsigned char *ptemp;

	ptemp = value;

	EPD_W21_CS_0;
	EPD_W21_DC_0;		// command write

	SPI_Write(*ptemp);
	ptemp++;

	EPD_W21_DC_1;		// data write

	for (i = 0; i < datalen - 1; i++)	// sub the command
			{
		SPI_Write(*ptemp);
		ptemp++;
	}

	EPD_W21_CS_1;

}
/*********************************************
 功能：写显示buffer
 参数： 	XSize  x方向数量  128点方向，调整为8的整数倍
 YSize  y方向数量
 Dispbuff 显示数据保存位置。 要求数据的排列方式必须正确
 *********************************************/
static void EPD_W21_WriteDispRam(unsigned char XSize, unsigned int YSize,
		unsigned char *Dispbuff) {
	int i = 0, j = 0;

	if (XSize % 8 != 0) {
		XSize = XSize + (8 - XSize % 8);
	}
	XSize = XSize / 8;

	//while(isEPD_W21_BUSY == 1);	//wait
	ReadBusy();

	EPD_W21_CS_0;
	EPD_W21_DC_0;		//command write
	SPI_Write(0x24);

	EPD_W21_DC_1;		//data write
	for (i = 0; i < YSize; i++) {
		for (j = 0; j < XSize; j++) {
			SPI_Write(*Dispbuff);
			Dispbuff++;
		}
	}

	EPD_W21_CS_1;
}
/*********************************************
 功能：  写显示buffer 用来将某一个区域写入相同的显示内容。
 参数： 	XSize  x方向数量  128点方向，调整为8的整数倍
 YSize  y方向数量
 dispdata 显示数据。
 *********************************************/
static void EPD_W21_WriteDispRamMono(unsigned char XSize, unsigned int YSize,
		unsigned char dispdata) {
	int i = 0, j = 0;

	if (XSize % 8 != 0) {
		XSize = XSize + (8 - XSize % 8);
	}
	XSize = XSize / 8;
	//while(isEPD_W21_BUSY == 1);	// wait	
	ReadBusy();

	EPD_W21_CS_0;
	EPD_W21_DC_0;		// command write
	SPI_Write(0x24);

	EPD_W21_DC_1;		// data write
	for (i = 0; i < YSize; i++) {
		for (j = 0; j < XSize; j++) {
			SPI_Write(dispdata);
		}
	}

	EPD_W21_CS_1;
}

static void EPD_W21_POWERON(void) {
	EPD_W21_WriteCMD_p1(0x22, 0xc0);
	EPD_W21_WriteCMD(0x20);
	//EPD_W21_WriteCMD(0xff);
}
//static void EPD_W21_POWEROFF(void)
//{  	EPD_W21_WriteCMD_p1(0x22,0xc3);
//	EPD_W21_WriteCMD(0x20);
////	EPD_W21_WriteCMD(0xff);
//}

static void EPD_W21_SetRamArea(unsigned char Xstart, unsigned char Xend,
		unsigned char Ystart, unsigned char Ystart1, unsigned char Yend,
		unsigned char Yend1) {
	IncS_Write_Com(0x44);	// command
	IncS_Write_Data(Xstart);
	IncS_Write_Data(Xend);
	IncS_Write_Com(0x45);	// command
	IncS_Write_Data(Ystart);
	IncS_Write_Data(Ystart1);
	IncS_Write_Data(Yend);
	IncS_Write_Data(Yend1);
}
static void EPD_W21_SetRamPointer(unsigned char addrX, unsigned char addrY,
		unsigned char addrY1) {
	IncS_Write_Com(0x4e);	// command
	IncS_Write_Data(addrX);
	IncS_Write_Com(0x4f);	// command
	IncS_Write_Data(addrY);
	IncS_Write_Data(addrY1);
}
static void part_display(unsigned char RAM_XST, unsigned char RAM_XEND,
		unsigned char RAM_YST, unsigned char RAM_YST1, unsigned char RAM_YEND,
		unsigned char RAM_YEND1) {
	EPD_W21_SetRamArea(RAM_XST, RAM_XEND, RAM_YST, RAM_YST1, RAM_YEND,
			RAM_YEND1); /*set w h*/
	EPD_W21_SetRamPointer(RAM_XST, RAM_YST, RAM_YST1); /*set orginal*/
}
//static void EPD_W21_UpdataDisplay(unsigned char *imgbuff,unsigned char xram,unsigned int yram)
//{
//	EPD_W21_WriteDispRam(xram, yram, imgbuff);
////	EPD_W21_Update();
//}

//=========================functions============================
static void EPD_W21_DispInit(void) {
	EPD_W21_Write(GDOControl, sizeof(GDOControl));// Pannel configuration, Gate selection
	EPD_W21_Write(softstart, sizeof(softstart));	// X decrease, Y decrease
	EPD_W21_Write(VCOMVol, sizeof(VCOMVol));		// VCOM setting
	EPD_W21_Write(DummyLine, sizeof(DummyLine));	// dummy line per gate
	EPD_W21_Write(Gatetime, sizeof(Gatetime));		// Gage time setting
	EPD_W21_Write(RamDataEntryMode, sizeof(RamDataEntryMode));// X increase, Y decrease
	EPD_W21_SetRamArea(0x00, (xDot - 1) / 8, (yDot - 1) % 256, (yDot - 1) / 256,
			0x00, 0x00);	// X-source area,Y-gage area
	EPD_W21_SetRamPointer(0x00, (yDot - 1) % 256, (yDot - 1) / 256);// set ram

}
static void EPD_W21_Init(void) {

	EPD_W21_RST_0;		// Module reset
	driver_delay_xms(100);
	EPD_W21_RST_1;
	driver_delay_xms(100);

	EPD_W21_DispInit();		// pannel configure
}
static void EPD_W21_Update(void) {
	EPD_W21_WriteCMD_p1(0x22, 0xc7);
	EPD_W21_WriteCMD(0x20);
	EPD_W21_WriteCMD(0xff);
}

static void EPD_W21_Update_Part(void) {
	IncS_Write_Com(0x22);
	IncS_Write_Data(0x04);
	//EPD_W21_WriteCMD_p1(0x22,0x08);
	IncS_Write_Com(0x20);
	IncS_Write_Com(0xff);
}
static void EPD_W21_WirteLUT(unsigned char *LUTvalue, unsigned char Size) {
	EPD_W21_Write(LUTvalue, Size);
}
void EPD_init_Full(void) {
	EPD_W21_Init();			// display
	EPD_W21_WirteLUT((unsigned char *) LUTDefault_full,
			sizeof(LUTDefault_full));

	EPD_W21_POWERON();
}

void EPD_init_Part(void) {
	EPD_W21_Init();			// display

	EPD_W21_WirteLUT((unsigned char *) LUTDefault_part,
			sizeof(LUTDefault_part));
	EPD_W21_POWERON();
//	//清除底色
//	//EPD_W21_SetRamArea(0x00,0x0f,0x27,0x01,0x00,0x00);	  
//	//EPD_W21_SetRamPointer(0x00,0x27,0x01);	// set ram
//	part_display(0,xDot/8,yDot%256,yDot/256,0,0);
//	EPD_W21_WriteDispRamMono(xDot, yDot, 0xff);	// white
//	EPD_W21_Update_Part();
//	driver_delay_xms(500);
//	
//	
//	part_display(0,xDot/8,yDot%256,yDot/256,0,0);
//	EPD_W21_WriteDispRamMono(xDot, yDot, 0xff);	// white	

	//driver_delay_xms(2500);

}

/**********************************************************
 参数：
 xStart
 x方向开始坐标
 xEnd
 x方向结束坐标
 yStart
 y方向开始坐标
 yEnd
 y方向结束坐标
 DisBuffer
 显示buffer
 Label
 =1 显示 DisBuffer中的内容
 =0 显示 DisBuffer中第一个字节的内容

 ***********************************************************/

void EPD_Dis_Part(unsigned char xStart, unsigned char xEnd,
		unsigned long yStart, unsigned long yEnd) {
	//part_display(xStart / 8, xEnd / 8, yEnd % 256, yEnd / 256, yStart % 256,
	//		yStart / 256);

	IncS_P8x16Str(5, 0, FreqStr1);
	IncS_Num2StrShow_Double(LDC1000.freq, 5, COUNTOF(FreqStr1));

	IncS_P8x16Str(2, 0, ProxStr1);
	IncS_Num2StrShow_Double(LDC1000.prox, 2, COUNTOF(ProxStr1));

	//EPD_W21_Update_Part();
	//EPD_W21_Update_Part();
	IncS_Updata();
	IncS_P8x16Str(5, 0, ProxStr1);
	IncS_Num2StrShow_Double(LDC1000.freq, 5, COUNTOF(ProxStr1));

	IncS_P8x16Str(2, 0, FreqStr1);
	IncS_Num2StrShow_Double(LDC1000.prox, 2, COUNTOF(FreqStr1));
	IncS_Updata();
}
/***********************************************************
 end file
 ***********************************************************/

