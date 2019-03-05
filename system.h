#include "Typedef.h"

/***********************************************************************//**
 * @file		system.h
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
#ifndef SYSTEM_H
#define SYSTEM_H

/*-----sleep or power down define-------------*/
#define SLEEPMODE 0
#define DEEPSLEEPMODE 1
#define POWERDOWNMODE 0
#define DEEPPOWERDOWNMODE 0

EXT byte_field System_Flag0;
#define F_LCD_Refresh System_Flag0.data_Bbit.B0
#define F_StandBy System_Flag0.data_Bbit.B1
#define F_Sys_Reset System_Flag0.data_Bbit.B2
#define F_PowerOff System_Flag0.data_Bbit.B3
#define F_LowV System_Flag0.data_Bbit.B4
#define F_ACC_Buf System_Flag0.data_Bbit.B5
#define F_PowerKey_Buf System_Flag0.data_Bbit.B6
#define F_PowerKey System_Flag0.data_Bbit.B7

EXT byte_field System_Flag1;
#define F_REVPin System_Flag1.data_Bbit.B0
#define F_Refresh System_Flag1.data_Bbit.B1
#define 		F_HalfSecond System_Flag1.data_Bbit.B2
#define 		F_HalfSecBuf System_Flag1.data_Bbit.B3
#define 		F_2Hz		 System_Flag1.data_Bbit.B4
#define 		F_Clock_On		 System_Flag1.data_Bbit.B5
#define	F_High_Freq System_Flag1.data_Bbit.B6
#define	F_Backup_Rls System_Flag1.data_Bbit.B7

EXT byte_field System_Flag2;
#define F_LED_Status System_Flag2.data_Bbit.B0


EXT UNCHAR PowerONTimer;
EXT UNCHAR Curr_Work_Mode;	
EXT UNCHAR Next_Work_Mode;	
EXT UNCHAR Last_Work_Mode;
EXT UNCHAR Save_Work_Mode; /*saved the work mode when power off or ACC off */
#define 	Tuner		0
#define	USB			1
#define	SD			2
#define	AUX			3
#define	Demo		4
#define   GUI               5
#define 	Align  6


EXT UNCHAR PowerKeyCnt;
EXT UNINT AccOffCnt;

extern void Init(void);
extern void WatchDog_Feed(void);
extern void MuteOn(void);
extern void MuteOff(void);
extern void Power_Proc(void);
extern void PowerOn(void);
extern void PowerOff(void);
extern void Do_savemode(void);
extern void StandBy_Proc(void);
extern void MCU_Sleep(void);
extern void Sys_Mute_Proc(void);
extern void LED_Flash(void);



#ifndef NELEMS
#define NELEMS(arr) (sizeof(arr) / sizeof(arr[0]))
#endif

#endif

