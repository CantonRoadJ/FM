#include "Typedef.h"

/***********************************************************************//**
 * @file		RTC.h
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
#ifndef __RTC_H
#define __RTC_H

#define RTC_DEBUG 0

typedef struct
{
	U8 Second;
	U8 Minute;
	U8 Hour;
	U8 Day;	   //day of month 1~31
	U8 Month;
	U32 Year;
	U8 WeekDay;   //day of a week 0~6
	U32 YearDay;   //day of year 1~365
}RTCTime;
extern RTCTime CurrentTime;

extern void RTC_IRQHandler(void);
extern void RTC_Init(void);
extern void RTC_Start(void);
extern void RTC_Stop(void);
extern void RTC_SetTime(RTCTime Time);
extern RTCTime RTC_GetTime(void);

#endif

