
#ifndef _DISPLAY_EPD_W21_AUX_H_
#define _DISPLAY_EPD_W21_AUX_H_
#include "main.h"


#define EPD_W21_MOSI_1	   IncS_OUT|=IncS_SDA
#define EPD_W21_MOSI_0	   IncS_OUT&=~IncS_SDA

#define EPD_W21_CLK_1	   IncS_OUT|=IncS_SCL
#define EPD_W21_CLK_0	   IncS_OUT&=~IncS_SCL

#define EPD_W21_CS_1	   IncS_OUT|=IncS_CS
#define EPD_W21_CS_0	   IncS_OUT&=~IncS_CS

#define EPD_W21_DC_1	   IncS_OUT|=IncS_DC
#define EPD_W21_DC_0	   IncS_OUT&=~IncS_DC

#define EPD_W21_RST_1	   IncS_OUT|=IncS_RST
#define EPD_W21_RST_0	   IncS_OUT&=~IncS_RST

#define EPD_W21_BUSY_LEVEL 0
#define isEPD_W21_BUSY   (IncS_IN&IncS_BUSY_IN_BIT)


void SPI_Write(unsigned char value);
void driver_delay_xms(unsigned long xms);
#endif
/***********************************************************
						end file
***********************************************************/


