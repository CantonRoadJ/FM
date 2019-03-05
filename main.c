/***********************************************************************//**
 * @file		main.c
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

#define ROOT
#include "public.h"

void SPI_Test(void);
void devSAF775x_test(void);
void SPI_Flash_Test(void);
void UartTest(void);

/*-----------------------------------------------------------------------
Function name:	main
Input:			N/A
Output:			N/A
Description:	
------------------------------------------------------------------------*/
int main(void)
{
	Init();
	Dbg_printf(" init finish\n");
	
	while(1)
	{
		WatchDog_Feed();
		LED_Flash();
		Key_Proc();
		Clock_Proc();
		Audio_Proc();
		Power_Proc();
		Tuner_Mode_Proc();
		Sys_Mute_Proc();
		DisplayProc();	     
		StandBy_Proc();

		Tuner_Process();

		//SPI_Flash_Test();
		//UartTest();

#ifdef RDS_ENABLE
		RDS_Module();
#endif		
	}
}







