/***********************************************************************//**
 * @file		timer.c
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

#include	"public.h"
#include "unistd.h"

static U64 SystemWorkTime=0; //use to record the system normal work time ms

RTCTime CurrentTime;

RTCTime PreTime;




/*-------------------------------------------------------------------------------------------------------------------
function declare start
---------------------------------------------------------------------------------------------------------------------*/
void Init_Timer0(void);
/*-------------------------------------------------------------------------------------------------------------------
function define end
---------------------------------------------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------
Function name:	Init_Timer0
Input:			N/A
Output:			N/A
Description:	
------------------------------------------------------------------------*/
void Init_Timer0(void)
{
#if 0
	LPC_SC->PCLKSEL0 &= ~(0x00000003<<2);    //PCLK_TIMER0= CCLK/4=25MHZ
	LPC_TIM0->MR0 = 25000;				   //1ms???
	LPC_TIM0->MCR =3;				/* Interrupt and Reset on MR0 */

	NVIC_EnableIRQ(TIMER0_IRQn);
#endif
}
/*-----------------------------------------------------------------------
Input:			N/A
Output:			N/A
Description:	
------------------------------------------------------------------------*/
/*1ms interval*/
void ISR_1ms_Proc(void)
{
	SystemWorkTime++;/*1ms interval*/

	if (KeyTimer )	KeyTimer--;

#ifdef RDS_ENABLE
	RDSTimer_1ms_Entry();
#endif
}
/*-----------------------------------------------------------------------
Function name:	TIMER0_Start
Input:			N/A
Output:			N/A
Description:	
------------------------------------------------------------------------*/
void Timer0_Start(void)
{
#if 0
	LPC_TIM0->TCR = 1;
#endif

}
/*-----------------------------------------------------------------------
Function name:	TIMER0_IRQHandler
Input:			N/A
Output:			N/A
Description:	
------------------------------------------------------------------------*/
void TIMER0_IRQHandler(void)
{
#if 0
	LPC_TIM0->IR = 1;			/* clear interrupt flag */
	ISR_1ms_Proc();
#endif
}
/*-----------------------------------------------------------------------
Function name:	GetSystemWorkTime
Input:			N/A
Output:			SystemWorkTime: The time of system work in normal mode except sleep time
Description:	get the system work time
------------------------------------------------------------------------*/
U64 GetSystemWorkTime(void)
{
	return(SystemWorkTime);
}
/*-----------------------------------------------------------------------
Function name:	Clock_Proc
Input:			N/A
Output:			N/A
Description:	update the clock, function of clock set
------------------------------------------------------------------------*/
void Clock_Proc(void)
{
	static U8 Clock_Proc_Stat=0;

	if(F_Sys_Reset)
		return;
 
	switch(Clock_Proc_Stat)
    	{
    		case 0:		   //init
		{
			CurrentTime=RTC_GetTime();
			PreTime=CurrentTime;
			Clock_Proc_Stat=1;
		}
		case 1:		  //normal work mode, just update the time,
	 	{
		    	//time update
			PreTime=CurrentTime;
			CurrentTime=RTC_GetTime();
			if(CurrentTime.Second!=PreTime.Second)			 //time change check if the time is error or should be update the lcd
			{
				if((CurrentTime.Second<PreTime.Second)&&(CurrentTime.Minute<=PreTime.Minute)&&(CurrentTime.Hour<=PreTime.Hour)
				&&(CurrentTime.YearDay<=PreTime.YearDay)&&(CurrentTime.Year<=PreTime.Year))		  //error when the second changed from 59 to 60
				{
					CurrentTime=PreTime;
				}
			}
			else	//the time is not changed
			{
			    	;
			}
			break;
		}
		default:	 //should not come here except error
		{
		    	while(1);
		}
	}
}
/*****************************************************************************
*  Name        : TimerSet
*  Description : Sets a timer. timer must not equ 0 because 0 means timer is stop
*  Params      : STimer pointer to timer value
*                TimeLength - timer period
*  Returns     : none
*****************************************************************************/
void TimerSet(U32 *STimer, U32 TimeLength)
{
#if 0
	*STimer = SystemWorkTime + TimeLength;

    if(*STimer == 0)	*STimer = 1; //not set timer to 0 for timer is running
#else
    //sleep(2);
    TimerDelayMs(TimeLength);
    *STimer = 0;
#endif


}
/*****************************************************************************
*  Name        : TimerStop
*  Description : stop timer
*  Params      : STimer pointer to timer value
*  Returns     : 
*****************************************************************************/
void TimerStop(U32 *STimer)
{
	*STimer = 0;
}
/*****************************************************************************
*  Name        : TimerHasStopped
*  Description : Checks whether given timer has stopped
*  Params      : STimer is timer value
*  Returns     : TRUE if timer is stopped
*****************************************************************************/
U8 TimerHasStopped(U32 STimer)
{
	return (STimer == 0);
}

/*****************************************************************************
*  Name        : TimerHasExpired
*  Description : Checks whether given timer has expired
*        With timer tick at 1ms maximum timer period is 10000000 ticks
*        When *STimer is set (SoftTimer-*STimer) has a min value of 0xFFF0BDBF
*            and will be more than this while the timer hasn't expired
*        When the timer expires
*                (SoftTimer-*STimer)==0
*            and (SoftTimer-*STimer)<=7FFF FFFF for the next 60 hours
*  Params      : STimer pointer to timer value
*  Returns     :  TRUE if timer has expired or timer is stopped, otherwise FALSE
*****************************************************************************/
U8 TimerHasExpired (U32 *STimer)
{
#if 0
	if(*STimer == 0)
		return TRUE;
	else if((SystemWorkTime - *STimer) <= 0x7fffffff)
	{
		*STimer = 0;	//set timer to stop
		return TRUE;
	}
	else
		return FALSE;
#endif

    return TRUE;
}

/*****************************************************************************
*  Name        : TimerWaitExpired
*  Description : don't wait if  given timer has expired
*  Params      : STimer pointer to timer value
*  Returns     : 
*****************************************************************************/
//wait untill last write finish
void TimerWaitExpired (U32 *STimer)
{

	while(1)
	{
		if(TimerHasExpired(STimer))
			break;
		WatchDog_Feed();
    }
}
/*****************************************************************************
*  Name        : TimerDelayMs
*  Description : wait untill  given timer has expired
*  Params      : wait ms
*  Returns     : 
*****************************************************************************/

void TimerDelayMs (U32 ms)
{
#if 0
    U32 timer;
	
	TimerSet (&timer, ms);
	while (!TimerHasExpired (&timer))
	{
		WatchDog_Feed();
	}
#endif

    usleep(ms*1000);
}

