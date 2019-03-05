/***********************************************************************//**
 * @file		RTC.c
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
#include "public.h"


/*-----------------------------------------------------------------------
Function name:	RTC_IRQHandler
Input:			N/A
Output:			N/A
Description:	
------------------------------------------------------------------------*/
void RTC_IRQHandler(void)
{
#if 0
	 LPC_RTC->ILR=0x00000003;		//clear the RTC interrupt flag
	 //add your branch check code below
#endif
}
/*-----------------------------------------------------------------------
Function name:	RTC_Init
Input:			N/A
Output:			N/A
Description:	init RTC
------------------------------------------------------------------------*/
void RTC_Init(void)
{
#if 0
	if(LPC_RTC->CCR&0x01==0)		   //not enable then init it
	{
		LPC_RTC->CCR=0x00000002;        //reset the RTC
		LPC_RTC->ILR=0x00000003;       //clear all the interrupt flag
		LPC_RTC->AMR=0x000000FF;       //mask the compare interrupt
		LPC_RTC->CIIR=0x00000000;       //disable all the increment interrut
		NVIC_EnableIRQ(RTC_IRQn);								  //enable I2C2 interrupt
		LPC_RTC->CALIBRATION=0x00000000;    //disable the calibration interrupt
	}
	else
	{
		LPC_RTC->CCR=0x00000002;        //reset the RTC
		LPC_RTC->CCR=0x00000001;        //reset the RTC
	}
#endif

	RTC_Stop();
	CurrentTime.Day=1;
	CurrentTime.Month=1;
	CurrentTime.Year=2011;
	CurrentTime.Hour=12;
	CurrentTime.Second=0;
	CurrentTime.Second=0;
	CurrentTime.WeekDay=5;
	CurrentTime.YearDay=1;
	RTC_SetTime(CurrentTime);
	RTC_Start();
}
/*-----------------------------------------------------------------------
Function name:	RTC_Start
Input:			N/A
Output:			N/A
Description:	start the RTC
------------------------------------------------------------------------*/
void RTC_Start(void)
{
#if 0
	LPC_RTC->ILR=0x00000003;       		 //clear all the interrupt
	LPC_RTC->CCR|=0x00000001;            //enable the RTC
	LPC_SC->PCONP|=0x00000001<<9;        //power on the RTC
#endif

}
/*-----------------------------------------------------------------------
Function name:	RTC_Stop
Input:			N/A
Output:			N/A
Description:	stop the RTC
------------------------------------------------------------------------*/
void RTC_Stop(void)
{
#if 0
	LPC_RTC->CCR&=~0x00000001;            //disable the RTC
#endif

}
/*-----------------------------------------------------------------------
Function name:	RTC_SetTime
Input:			Time:RTCTime struct
Output:			N/A
Description:	RTC Set second,minute,hour...,,Should check the value validity before use this function
------------------------------------------------------------------------*/
void RTC_SetTime(RTCTime Time)
{
#if 0
	LPC_RTC->SEC=Time.Second;
	LPC_RTC->MIN=Time.Minute;
	LPC_RTC->HOUR=Time.Hour;
	LPC_RTC->DOM=Time.Day;
	LPC_RTC->DOW=Time.WeekDay;
	LPC_RTC->DOY=Time.YearDay;
	LPC_RTC->MONTH=Time.Month;
	LPC_RTC->YEAR=Time.Year;
#endif

}
/*-----------------------------------------------------------------------
Function name:	RTC_GetTime
Input:			N/A
Output:			Time:RTCTime struct
Description:	RTC Get second,minute,hour...
------------------------------------------------------------------------*/
RTCTime RTC_GetTime(void)
{
	RTCTime Time;

#if 0
	Time.Second=LPC_RTC->SEC;
	Time.Minute=LPC_RTC->MIN;
	Time.Hour=LPC_RTC->HOUR;
	Time.Day=LPC_RTC->DOM;
	Time.Month=LPC_RTC->MONTH;
	Time.Year=LPC_RTC->YEAR;
	Time.WeekDay=LPC_RTC->DOW;
	Time.YearDay=LPC_RTC->DOY;
#endif

    return(Time);
}

