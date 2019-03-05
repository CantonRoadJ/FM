/***********************************************************************//**
 * @file		system.c
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

#define CLKSRC_RC 0x00
#define CLKSRC_MAIN 0x01
#define CLKSRC_RTC 0x02
#define CLKSRC CLKSRC_MAIN	

#define Fosc 12000000
#define OSC_RANGE1 0   //         //1MHz~20MHz
#define OSC_RANGE2 0x10			//15MHz~25MHz
#define OSCRANGE OSC_RANGE1

#define PLL0_MVALUE	12
#define PLL0_NVALUE	1

#define PLL1_EN 1
#define PLL1CFG_Val 0x00000000

#define WDFEEDNUM 0x00040000 


//extern int define
#define EINT0		0x00000001
#define EINT1		0x00000002
#define EINT2		0x00000004
#define EINT3		0x00000008

#define EINT0_EDGE	0x00000001
#define EINT1_EDGE	0x00000002
#define EINT2_EDGE	0x00000004
#define EINT3_EDGE	0x00000008

#define EINT0_RISING	0x00000001
#define EINT1_RISING	0x00000002
#define EINT2_RISING	0x00000004
#define EINT3_RISING	0x00000008

#define ACC_Pin_GPI 0 //ACC pin is general purpose input port for normal mode
#define ACC_Pin_INT 1 //ACC pin is interrupt port for sleep mode

U8 SysMuteState;
static U32 SysMuteTimer;

U8 PowerOnDemuteReq;


 void CPU_Init(void);
 void MCU_SleepInit(void);
 void ACC_PinInit(U8 ACCPin);
 void WatchDog_Init(void);
 void Init_System(void);
 void SPI_Init(void);

 /*-----------------------------------------------------------------------
Function name:	Init
Input:			N/A
Output:			N/A
Description: Initialize the System 	
------------------------------------------------------------------------*/
void Init(void)
{
    //CPU_Init();
    //Port_Init();
    //p_LED2_ON();
	MCU_SleepInit();
	RTC_Init();
	RTC_Start();
	Init_Timer0();

	ACC_PinInit(ACC_Pin_GPI);
	I2C1_Init();
	I2C2_Init();

	Init_System();

	Key_Init(); 
	Timer0_Start();
	
	Tuner_Para_Init();	   //read eeprom config data
	Init_Amp();

	WatchDog_Init();
	DisplayInit();
    //debug_frmwrk_init();
}
 /*-----------------------------------------------------------------------
Function name:	CPU_Init
Input:			N/A
Output:			N/A
Description: Initialize the System and update the SystemFrequency	
------------------------------------------------------------------------*/
void CPU_Init(void)
{
#if 0
	__disable_irq();
	LPC_SC->FLASHCFG=0x0000503A;		   //to make the flash security
	/* Clock Setup                        */
#if(CLKSRC==CLKSRC_MAIN)
	LPC_SC->SCS=0x00000020;
	while((LPC_SC->SCS&(1<<6))==0);  /* Wait for Oscillator to be ready    */
	LPC_SC->CCLKCFG=0x00000003;          /* Setup Clock Divider       =4         */
	LPC_SC->CLKSRCSEL=0x00000001;        /* Select Clock Source for PLL0       */
	LPC_SC->PLL0CFG=0x00020032;		   //PLL Clock=400MHz, M=50,N=3,CCLK=100MHZ
#endif
	LPC_SC->PLL0CON=0x01;                 /* PLL0 Enable                        */
	LPC_SC->PLL0FEED=0xAA;
	LPC_SC->PLL0FEED=0x55;
	while(!(LPC_SC->PLL0STAT&(1<<26)));  /* Wait for PLOCK0                    */

	LPC_SC->PLL0CON=0x03;                 /* PLL0 Enable & Connect              */
	LPC_SC->PLL0FEED=0xAA;
	LPC_SC->PLL0FEED=0x55;


#if(PLL1_EN)
	LPC_SC->PLL1CFG=PLL1CFG_Val;
	LPC_SC->PLL1CON=0x01;                 /* PLL1 Enable                        */
	LPC_SC->PLL1FEED=0xAA;
	LPC_SC->PLL1FEED=0x55;
	while(!(LPC_SC->PLL1STAT&(1<<10)));  /* Wait for PLOCK1                    */

	LPC_SC->PLL1CON=0x03;                 /* PLL1 Enable & Connect              */
	LPC_SC->PLL1FEED=0xAA;
	LPC_SC->PLL1FEED=0x55;
#else
	LPC_SC->USBCLKCFG=0x00000000;        /* Setup USB Clock Divider            */
#endif

	LPC_SC->PCLKSEL0=0x00000000;         /* Peripheral Clock Selection =cclk/4        */
	LPC_SC->PCLKSEL1=0x00000000;

	LPC_SC->CLKOUTCFG=0x00000000;        /* Clock Output Configuration         */


	__enable_irq();
#endif

}
/*-----------------------------------------------------------------------
Function name:	MCU_SleepInit
Input:			N/A
Output:			N/A
Description: 
------------------------------------------------------------------------*/
void MCU_SleepInit(void)
{
#if 0

#if(SLEEPMODE)
	LPC_SC->PCON&=~0x00000003;
	SCB->SCR&=~0x00000004;
#endif
#if(DEEPSLEEPMODE)
	LPC_SC->PCON&=~0x00000003;
	SCB->SCR|=0x00000004;
#endif
#if(POWERDOWNMODE)
	LPC_SC->PCON&=~0x00000003;
	LPC_SC->PCON|=0x00000001;
	SCB->SCR|=0x00000004;
#endif
#if(DEEPPOWERDOWNMODE)
	LPC_SC->PCON|=0x00000003;
	SCB->SCR|=0x00000004;
#endif

#endif


}

/*-----------------------------------------------------------------------
Function name:	ACC_PinInit
Input:			N/A
Output:			N/A
Description:    
------------------------------------------------------------------------*/
void ACC_PinInit(U8 ACCPin)
{
#if 0

	if(ACCPin == ACC_Pin_GPI)
	{
		LPC_PINCON->PINSEL0&=~(0x00000003<<12);              //P0.6 as GPIO pin
		LPC_PINCON->PINMODE0&=~(0x00000003<<12);              //pull up
		LPC_PINCON->PINMODE_OD0&=~(0x00000001<<6);             //not open drain
		LPC_GPIO0->FIODIR&=~(0x00000001<<6);				  //input
		LPC_GPIOINT->IO0IntEnR&=~(0x00000001<<6);               //disable int
		LPC_GPIOINT->IO0IntEnF&=~(0x00000001<<6);               //disable int

		NVIC_EnableIRQ(EINT3_IRQn);
	}
	else// ACCPin == ACC_Pin_INT
	{
		LPC_PINCON->PINSEL0&=~(0x00000003<<12);              //P0.6 as GPIO pin
		LPC_PINCON->PINMODE0&=~(0x00000003<<12);              //pull up
		LPC_PINCON->PINMODE_OD0&=~(0x00000001<<6);             //not open drain
		LPC_GPIO0->FIODIR&=~(0x00000001<<6);				  //input
		LPC_GPIOINT->IO0IntEnR|=(0x00000001<<6);               //enable int
		LPC_GPIOINT->IO0IntEnF|=(0x00000001<<6);               //enable int

		NVIC_EnableIRQ(EINT3_IRQn);
	}
#endif

}

/*-----------------------------------------------------------------------
Function name:	WatchDog_Init
Input:			N/A
Output:			N/A
Description:	WatchDog_Init
------------------------------------------------------------------------*/
void WatchDog_Init(void)
{
#if 0

	LPC_WDT->WDCLKSEL=0x00;		  //clock select
	LPC_WDT->WDTC=WDFEEDNUM;            //counter set
	LPC_WDT->WDMOD=0x01;          //enable
	LPC_WDT->WDFEED=0xAA;		  
	LPC_WDT->WDFEED=0x55; 		  //start

#endif
}

/*-----------------------------------------------------------------------
Function name:	WatchDog_Feed
Input:			N/A
Output:			N/A
Description:	Clear watchdog
------------------------------------------------------------------------*/
void WatchDog_Feed(void)
{
#if 0
	LPC_WDT->WDTC=0xAA;            //counter set
	LPC_WDT->WDTC=0x55;            //counter set
#endif
}

void Init_System(void)
{
	F_Sys_Reset = 1;
	Curr_Work_Mode = 0xff;
 	Next_Work_Mode = 0xff;
	Next_Work_Mode = 0xff;
}

void Sys_Mute_Proc(void)
{
	if(TimerHasExpired(&SysMuteTimer))
	{
	    	if(SysMuteState==0x10)		 //on -> off
		{
			
			SysMuteState=0x01;
			MuteOff(); 
		}
		else if(SysMuteState==0x20)		 //off ->  on
		{
			SysMuteState=0x02;
			MuteOff(); 		    
		}
	}
}

void MuteOn(void)
{	
	Audio_SetMute(TRUE);
}

void MuteOff(void)
{
	Audio_SetMute(FALSE);
}

void Power_Proc(void)
{
	/*power key press*/
	if (F_PowerOff)		//  power off status
	{
		if(F_PowerKey)
		{
			F_PowerKey = 0;
			Display_DisableTimeout();
			PowerOn();
			PowerOnDemuteReq=1;
		}
	}
	else //  power on status
	{
		if (F_Sys_Reset || F_PowerKey)
		{	//when system reset
			Display_DisableTimeout();
			PowerOff();
			F_PowerKey = 0;	
		}
		else
		{
			if(PowerOnDemuteReq)
			{    
				MuteOff();
				PowerOnDemuteReq=0;
			}
		}
	}
}

void PowerOn(void)
{
	F_PowerOff = 0;
	Next_Work_Mode = Save_Work_Mode;
	APPL_PowerSwitch(TRUE);
}

void PowerOff(void)
{
	F_PowerOff = 1;
	MuteOn();
	Do_savemode();
	APPL_PowerSwitch(FALSE);
}

void Do_savemode(void)
{	
	if(Curr_Work_Mode != 0xff)//temporay
	{
		Save_Work_Mode = Curr_Work_Mode;	/* save current work mode*/
	}
	else
		Save_Work_Mode =  Next_Work_Mode;
		
	if(!F_Sys_Reset)
	{
		Last_Work_Mode =Curr_Work_Mode ;	/* close current work mode*/
 	}
	else				// set init mode
	{
		F_Sys_Reset = 0;
		 Last_Work_Mode=0xff;
		 Save_Work_Mode = Tuner;
	}
		
	Curr_Work_Mode =0xff;
 	Next_Work_Mode =0xff;
}

void StandBy_Proc(void)
{
#if 0
	if(F_ACC_Buf != P_ACC_CHK)
	{
		if (AccOffCnt !=0) 
		{
			 --AccOffCnt;
			return;
		}
		else
		{
			F_ACC_Buf = P_ACC_CHK;
			AccOffCnt=100;
			if(F_ACC_Buf)		//acc become on
			{
				AccOffCnt = 6;
				return;
			}
		}
	}
	else
	{
		if(F_ACC_Buf)
		{
			return;//if acc on, then do not execute following code.
		}
	}
	// *****************below is in ACC off status**********************
	Display_DisableTimeout();
	MuteOn();
	F_StandBy = 1;
	
	if(F_PowerOff == 0)
		PowerOff();	
	
	ACC_PinInit(ACC_Pin_INT);
	MCU_Sleep();				 //goto sleep

	// *****************below is start point from Deep-sleep mode**********************
	WatchDog_Feed();
	F_StandBy=0;	
	F_ACC_Buf = 1;
	//init...
#endif

}

/*-----------------------------------------------------------------------
Function name:	MCU_Sleep
Input:			N/A
Output:			N/A
Description: 
------------------------------------------------------------------------*/
void MCU_Sleep(void)
{	
#if 0
    	__wfi();
#endif

}

/*-----------------------------------------------------------------------
Function name:	EINT3_IRQHandler
Input:			N/A
Output:			N/A
Description:    this int is used as the GPIO int
------------------------------------------------------------------------*/
void EINT3_IRQHandler(void)
{
#if 0

   	U32 iiii;

	LPC_SC->EXTINT=EINT3;		// clear interrupt flag
    	if(LPC_GPIOINT->IO0IntStatR&(0x00000001<<6))  //GPIO int called by ACC pin 
	{
		LPC_GPIOINT->IO0IntClr|=0x00000001<<6;              //clear the int flag before enable int
		LPC_GPIOINT->IO0IntEnR&=~(0x00000001<<6);               //disable int
		CPU_Init();
		iiii=1000000;				//wait for 30ms	  //change the iiii value to suit 30ms
		while(iiii--)
		{
		    	WatchDog_Feed();
		}
		if(P_ACC_CHK)	   //acc high stable
		{
		    	F_ACC_Buf = P_ACC_CHK;
			NVIC_DisableIRQ(EINT3_IRQn);
			return;                        //return to normal run
		}
		else							   //wrong ACC int
		{
			LPC_GPIOINT->IO0IntClr|=0x00000001<<6;              //clear the int flag before enable int
			LPC_GPIOINT->IO0IntEnR|=0x00000001<<6;               //enable int
			NVIC_EnableIRQ(EINT3_IRQn);
			MCU_Sleep();				 //goto sleep		
		}
	}
	else				 //not ACC pin int
	{
		LPC_GPIOINT->IO0IntClr=0xFFFFFFFF;       //clear all the int flag
		LPC_GPIOINT->IO2IntClr=0xFFFFFFFF;       //clear all the int flag
		MCU_Sleep();				 //goto sleep
	}

 #endif

}

void LED_Flash(void)
{
	static U32 LEDFlash_Timer;
	
	if(TimerHasExpired(&LEDFlash_Timer))
	{
		TimerSet(&LEDFlash_Timer,500);

        //if(F_LED_Status)
            //p_LED1_ON();
        //else
            //p_LED1_OFF();
		
		F_LED_Status = ~F_LED_Status;
	}
}

