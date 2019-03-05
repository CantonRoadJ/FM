#include "Typedef.h"

/***********************************************************************//**
 * @file		Lcd.h
 * @purpose		This example used to test NXP HERO function
 * @version		0.1
 * @date		1. Oct. 2010
 * @author		NXP BU Automotive Car Entertainment Team & Edom ELECTRONICS(SHENZHEN) AE Team
 *---------------------------------------------------------------------
 * Software that is described herein is for illustrative purposes only
 * which provides customers with programming information regarding the
 * products. This software is supplied "AS IS" without any warranties.
 * NXP Semiconductors and Edom Electronics assume no responsibility or liability for the
 * use of the software, convey no license or title under any patent,
 * copyright, or mask work right to the product. NXP Semiconductors and Edom Electronics
 * reserve the right to make changes in the software without
 * notification. NXP Semiconductors and Edom Electronics also make no representation or
 * warranty that such application will be suitable for the specified
 * use without further testing or modification.
 **********************************************************************/
#ifndef _LCD_H
#define _LCD_H

/*display buffer size*/
#define LCD_MAX_BUF      (26)
#define MAX_SEG             (13)
#define MAX_LCD_CHAR_NUM (9)

/*segment define*/
#define  EMPTY                   0x0000
#define  _SEG_VCD               0x1820
#define  _SEG_SCDP             0X1980
#define  _SEG_MP3               0x0220
#define  _SEG_DVD               0x1420
#define  _SEG_REG               0X1902
#define  _SEG_MONO            0X1908
   
#define _SEG_ST                   0x0020
#define _SEG_RING               EMPTY
#define _SEG_LOUD              0x1480
#define _SEG_MUTE              EMPTY
#define _SEG_LOCAL            0x1904

#define _SEG_EQ                  0x1604
#define _SEG_ROCK             0x1580
#define _SEG_CLASS            0x1520
#define _SEG_POP                0x1540   
#define _SEG_CDIN               EMPTY     
#define _SEG_ESP                EMPTY
#define _SEG_PTY                0x0F20
#define _SEG_EON                0x1440
#define _SEG_AF                  0x0402
#define _SEG_TP                  0x0902
#define _SEG_TA                  0x0720
#define _SEG_MECR             0x0C20
#define _SEG_DIR                 0x0C02

#define _SEG_P1                 0x0E02
#define  _SEG_L11               0x1602
#define  _SEG_L12               0x1680
#define  _SEG_L13               0x1640
#define  _SEG_L14               0x1620
#define  _SEG_L15               0x1508
#define  _SEG_L16               0x1504
#define  _SEG_L17               0x1502

#define  _SEG_L21               0x1708
#define  _SEG_L22               0x1704
#define  _SEG_L23               0x1702
#define  _SEG_L24               0x1780
#define  _SEG_L25               0x1740
#define  _SEG_L26               0x1720
#define  _SEG_L27               0x1608

#define  _SEG_L31               0x1940
#define  _SEG_L32               0x1920
#define  _SEG_L33               0x1808
#define  _SEG_L34               0x1804
#define  _SEG_L35               0x1802
#define  _SEG_L36               0x1880
#define  _SEG_L37               0x1840

#define  _SEG_CDP1             0x1408
#define  _SEG_CDP2             0x1404
#define  _SEG_CDP3             0x1402
/*blank all lcd define*/
#define BLANK_ALL       0xff

extern unsigned  char   ShadowRam[LCD_MAX_BUF];
void FillRam(unsigned char *pAddr,unsigned char data,unsigned char count);
extern void LCD_clear_lite_anode(unsigned int anode, unsigned char lite);
extern void LCD_ShowChar(unsigned char pos,unsigned char char_ascii);
extern void LCD_ShowNumber(unsigned char Pos, unsigned int Num,unsigned char BitWidth);
extern void LCD_ShowStrings(unsigned char Pos, unsigned char *pStr);
extern void LCD_Blank(unsigned char pos);

#endif
