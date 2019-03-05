#include "Typedef.h"

/***********************************************************************//**
 * @file		Display.h
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
#ifndef _DISPLAY_H
#define _DISPLAY_H

#define   ON        1
#define   OFF       0

/*led display status*/
#define F_LED_Status System_Flag2.data_Bbit.B0

/*lcd one seg display define*/
#define DispFlag_VCD(OnOff)   LCD_clear_lite_anode(_SEG_VCD,OnOff);
#define DispFlag_EQ(OnOff)   LCD_clear_lite_anode(_SEG_EQ,OnOff);
#define DispFlag_DOT(OnOff)   LCD_clear_lite_anode(_SEG_P1,OnOff);
#define DispFlag_SCDP(OnOff)   LCD_clear_lite_anode(_SEG_SCDP,OnOff);
#define DispFlag_MECR(OnOff)   LCD_clear_lite_anode(_SEG_MECR,OnOff);
#define DispFlag_DVD(OnOff)   LCD_clear_lite_anode(_SEG_DVD,OnOff);
#define DispFlag_REG(OnOff)   LCD_clear_lite_anode(_SEG_REG,OnOff);

#define DispFlag_MONO(OnOff)   LCD_clear_lite_anode(_SEG_MONO,OnOff);
#define DispFlag_LOUD(OnOff)   LCD_clear_lite_anode(_SEG_LOUD,OnOff);
#define DispFlag_LOCAL(OnOff)   LCD_clear_lite_anode(_SEG_LOCAL,OnOff);
#define DispFlag_EQ(OnOff)   LCD_clear_lite_anode(_SEG_EQ,OnOff);
#define DispFlag_CLASS(OnOff)   LCD_clear_lite_anode(_SEG_CLASS,OnOff);
#define DispFlag_POP(OnOff)   LCD_clear_lite_anode(_SEG_POP,OnOff);
#define DispFlag_PTY(OnOff)   LCD_clear_lite_anode(_SEG_PTY,OnOff);
#define DispFlag_ROCK(OnOff)   LCD_clear_lite_anode(_SEG_ROCK,OnOff);

#define DispFlag_EON(OnOff)   LCD_clear_lite_anode(_SEG_EON,OnOff);
#define DispFlag_AF(OnOff)   LCD_clear_lite_anode(_SEG_AF,OnOff);
#define DispFlag_TP(OnOff)   LCD_clear_lite_anode(_SEG_TP,OnOff);
#define DispFlag_TA(OnOff)   LCD_clear_lite_anode(_SEG_TA,OnOff);
#define DispFlag_DIR(OnOff)   LCD_clear_lite_anode(_SEG_DIR,OnOff);
#define DispFlag_ST(OnOff)  LCD_clear_lite_anode(_SEG_ST,OnOff);

/*temp display type define*/
typedef enum{
	DISPLAY_TIMEOUT_VOL,
	DISPLAY_TIMEOUT_BASS,
	DISPLAY_TIMEOUT_MID,
	DISPLAY_TIMEOUT_TREBBLE,
	DISPLAY_TIMEOUT_BANLANCE,
	DISPLAY_TIMEOUT_FADER,
	DISPLAY_TIMEOUT_BEEP,
	DISPLAY_TIMEOUT_MIX_MIC,
	DISPLAY_TIMEOUT_MUTE,
	DISPLAY_TIMEOUT_UNMUTE,
	DISPLAY_TIMEOUT_GEQBand,
	DISPLAY_TIMEOUT_RadioStoreOK,
	DISPLAY_TIMEOUT_LOUDNESS,
	DISPLAY_TIMEOUT_ClockSetOK,
	DISPLAY_TIMEOUT_SeekSensLev,
	DISPLAY_TIMEOUT_FADE,
	DISPLAY_TIMEOUT_INVALID
}DISPLAY_TIMEOUT_TYPE;

typedef struct{
	U32 timeout;			//time of timeout
	DISPLAY_TIMEOUT_TYPE type;	//type of timeout
}DISPLAY_DATA;

extern unsigned char Time_LCDChar[7][4];

extern void BackLightOnOff(unsigned char OnOff);
extern void DisplayInit(void);
extern void DisplayProc(void);
extern void Display_DisableTimeout(void);
extern void Display_SetTimeout(DISPLAY_TIMEOUT_TYPE type,U16 time);

#endif

