#include "Typedef.h"

/***********************************************************************//**
 * @file		timer.h
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
#ifndef __TIMER_H
#define __TIMER_H

#define Time_LCDHourLen 2
#define Time_LCDMinuteLen 2
#define Time_LCDSecondLen 2

/*-------------------------------------------------------------------------------------------------------------------
function define start
---------------------------------------------------------------------------------------------------------------------*/
extern void Init_Timer0(void);
extern U64 GetSystemWorkTime(void);
extern void Clock_Proc(void);
extern void Timer0_Start(void);


void TimerSet(U32 *STimer, U32 TimeLength);
U8 TimerHasStopped(U32 STimer);
U8 TimerHasExpired (U32 *STimer);
void TimerStop(U32 *STimer);
void TimerDelayMs (U32 ms);
void TimerWaitExpired (U32 *STimer);

/*-------------------------------------------------------------------------------------------------------------------
function define end
---------------------------------------------------------------------------------------------------------------------*/

#endif
