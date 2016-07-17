//*****************************************************************************
//
// #include 
//
//*****************************************************************************
#include "main.h"

//*****************************************************************************
//
// define
//
//*****************************************************************************

#define IncS_SEL    		P2SEL
#define IncS_DIR       	    P2DIR
#define IncS_OUT       	    P2OUT
#define IncS_IN       	    P2IN

#define IncS_SDA    		BIT0
#define IncS_SCL       	    BIT1
#define IncS_CS      	    BIT2
#define IncS_DC    			BIT3
#define IncS_BUSY_IN       	BIT4
#define IncS_BUSY_IN_BIT    BIT_4
#define IncS_RST       	    BIT5

#define IncS_SDA_H  IncS_OUT|=IncS_SDA
#define IncS_SDA_L  IncS_OUT&=~IncS_SDA	  

#define IncS_SCLK_H IncS_OUT|=IncS_SCL
#define IncS_SCLK_L IncS_OUT&=~IncS_SCL	

#define IncS_nCS_H  IncS_OUT|=IncS_CS
#define IncS_nCS_L  IncS_OUT&=~IncS_CS	

#define IncS_nDC_H  IncS_OUT|=IncS_DC
#define IncS_nDC_L  IncS_OUT&=~IncS_DC	

#define IncS_nRST_H IncS_OUT|=IncS_RST
#define IncS_nRST_L IncS_OUT&=~IncS_RST	

#define IncS_nBUSY  (IncS_IN&IncS_BUSY_IN_BIT)

#define DELAY_TIME	50    // ¨ª?????¨º?¨ª¨º¨ª¡ê¨¢?¨º¡À??(¦Ì£¤??:??)

#define PIC_WHITE                   255  // ¨¨?¡ã¡Á
#define PIC_BLACK                   254  // ¨¨?o¨²
#define PIC_Orientation             253  // ¡¤??¨°¨ª?
#define PIC_LEFT_BLACK_RIGHT_WHITE  249  // ¡Á¨®o¨²¨®¨°¡ã¡Á
#define PIC_UP_BLACK_DOWN_WHITE     248  // ¨¦?o¨²??¡ã¡Á

#define PIC_A                         1  // 

//*****************************************************************************
//
// declartion
//
//*****************************************************************************
void UpDataIncScreen();
void READBUSY(void);
void IncS_Init(void);
void WRITE_LUT(void);
void IncS_WriteCom(unsigned char INIT_COM);
void IncS_WriteData(unsigned char INIT_DATA);
void IncS_Set_Pos(u8 x, u8 y);
void IncS_P6x8Str(u8 x, u8 y, u8 ch[]);
void IncS_P8x16Str(u8 x, u8 y, u8 ch[]);
void IncS_P16x16Ch(u8 x, u8 y, u8 num);
void DIS_IMG(unsigned char num);
//void IMAGE_WRITE(unsigned char patt_num);
