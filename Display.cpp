/***********************************************************************//**
 * @file		Display.c
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

DISPLAY_DATA gDisplay;

/*time display chars */
unsigned char Time_LCDChar[7][4]=
{
	{'M','O','N','\0'},
	{'T','U','E','\0'},
	{'W','E','D','\0'},
	{'T','H','U','\0'},
	{'F','R','I','\0'},
	{'S','A','T','\0'},
	{'S','U','N','\0'}    
};
/*station store ok display chars*/
unsigned char Radio_LCDPresetOK[9]={'S','T','O','R','E',' ','O','K','\0'};

/*tuner display chars */
unsigned char Radio_LCDBandChar[MaxBandNum][9]=
{
	{"F1      "},
	{"F2      "},
	{"F3     "},
	{"MW      "},
	{"LW      "},
	{"SW      "},
};
/* clock display*/
void Display_Dot(U8 OnOff);
void DisplayTime(unsigned char hour,unsigned char min,unsigned char sec);
void DisplayVol(signed char vol_lev);
void Radio_StoreOKDisplay(void);
void Radio_LCDShowRadio(void);
void Display_CDWheel(char pos);
void Radio_DisplaySeekSensLev(void);
/*-----------------------------------------------------------------------
Function name:	Display_SetTimeout
Input:		type :display timeout type
                	time : timer period , unit is ms

Output:			N/A 
Description:	Set display type for timeout 	 
------------------------------------------------------------------------*/ 
void Display_SetTimeout(DISPLAY_TIMEOUT_TYPE type,U16 time)
{
	 if(time && gDisplay.type < DISPLAY_TIMEOUT_INVALID)
	  {
		gDisplay.type = type;
		TimerSet(&gDisplay.timeout, time);
	  }
	 else
		TimerStop(&gDisplay.timeout);
}
/*----------------------------------------------------------------------
*  Name        : 	Display_DisableTimeout
*  Description : 	static display immediately
*  Params      : 	none
*  Returns     : 	volume value for display
-----------------------------------------------------------------------*/
void Display_DisableTimeout(void)
{
        Display_SetTimeout(DISPLAY_TIMEOUT_INVALID,0);
}
/*-----------------------------------------------------------------------
*  Name        : 	Display_GetVolume
*  Description : 	convert volume to display
*  Params      : 	none
*  Returns     : 	volume value for display
-----------------------------------------------------------------------*/;
S8 Display_GetVolume(void)
{
        return (MainVolume_Lev);
}
/*----------------------------------------------------------------------
*  Name        : 	DisplayMute
*  Description : 	display MUTE
*  Params      : 	none
*  Returns     : 	none
-----------------------------------------------------------------------*/
void DisplayMute(void)
{
        LCD_ShowStrings(2,(unsigned char *)"MUTE");
}
/*----------------------------------------------------------------------
*  Name        : 	DisplayUnMute
*  Description : 	display UNMUTE
*  Params      : 	none
*  Returns     : 	none
-----------------------------------------------------------------------*/
void DisplayUnMute(void)
{
       LCD_ShowStrings(2,(unsigned char *)"UNMUTE");
}
/*-----------------------------------------------------------------------
*  Name        : 	Display_Timeout
*  Description : 	temporary display
*  Params      : 	none
*  Returns     : 	none
*-----------------------------------------------------------------------*/
void Display_Timeout(void)
{
	/*timer is stopped or timer has expired, do nothing*/
	if(TimerHasExpired(&gDisplay.timeout)){
		return;
	}
		
	/*temp display here*/
	switch(gDisplay.type){
		case DISPLAY_TIMEOUT_VOL:/*display volume*/
			DisplayVol(Display_GetVolume());
			break;
		case DISPLAY_TIMEOUT_MUTE:/*display mute*/
			DisplayMute();
			break;
		case DISPLAY_TIMEOUT_UNMUTE:/*display unmute*/
			DisplayUnMute();
			break;
		case DISPLAY_TIMEOUT_RadioStoreOK:/*display store ok*/
			Radio_StoreOKDisplay();
			break;
		case DISPLAY_TIMEOUT_SeekSensLev:
		    Radio_DisplaySeekSensLev();
		    break;
	}
}
/*-------------------------------------------------------------------------
*  Name        : 	LCD_NormalTimeShow
*  Description : 	
*  Params      : 	
*                		
*  Returns     : 	show current time
*-------------------------------------------------------------------------*/
void LCD_NormalTimeShow(void)
{
	LCD_ShowNumber(0,CurrentTime.Hour,Time_LCDHourLen);
	LCD_ShowChar(2,'-');
	LCD_ShowNumber(3,CurrentTime.Minute,Time_LCDMinuteLen);
	LCD_ShowChar(5,'-');
	LCD_ShowNumber(6,CurrentTime.Second,Time_LCDSecondLen);
	Display_Dot(0);
}
/*-------------------------------------------------------------------------
*  Name        : 	Display_Static
*  Description : 	static display
*  Params      : 	none
*  Returns     : 	none
*--------------------------------------------------------------------------*/
void Display_Static(void)
{
	/*display static only when display timer is stopped*/
	if(TimerHasStopped(gDisplay.timeout) )
	{
		/*-static display*/
		if (F_PowerOff)		//  power off status
		{
		/*-display clock	*/
			LCD_NormalTimeShow();
		}
		else{
			//power on
					Radio_LCDShowRadio();
		}
	}
}
/*-----------------------------------------------------------------------
Function name:	BackLightOnOff
Input:		on/off                    
Output:			N/A 
Description:	 	 
------------------------------------------------------------------------*/ 
void BackLightOnOff(unsigned char OnOff)
{
	/*Backlight contrl Port is P1.24*/

    //if(OnOff){/*Backlight on,set port high */
      //LPC_GPIO1->FIOSET=0x01000000;
    //}
    //else{/*Backlight off,set port low */
      //LPC_GPIO1->FIOCLR=0x01000000;
    //}
}
/*-----------------------------------------------------------------------
Function name:	DisplayInit
Input:		N/A                    
Output:			N/A 
Description:	
       This routine be called in main loop  	 
------------------------------------------------------------------------*/ 
void DisplayInit(void)
{
	/*lcd driver init*/
	LcdInit();

	/*backlight control P1.24 port init*/
    //LPC_PINCON->PINSEL3&=~0x00030000;//p1.24 as gpio
    //LPC_GPIO1->FIODIR|=0x01000000;//set p1.24 output
	/*turn on backlight*/
	BackLightOnOff(ON);
}

/*-----------------------------------------------------------------------
Function name:	DisplayProcTask
Input:		N/A                    
Output:			N/A 
Description:	
       This routine be called in main loop  	 
------------------------------------------------------------------------*/ 
void DisplayProc(void)
{
     /*clear display buffer ram*/
	 LCD_Blank(BLANK_ALL);
	 /*temporary  display*/
	 Display_Timeout();
	 /*normal display*/
	 Display_Static();
	  /*send data to lcd buffer*/
	 LcdDataTranfer();
}


/*-----------------------------------------------------------------------
Function name:	DisplayTime
Input:		hour, min, sec                    
Output:			N/A 
Description:	
       This routine display time in lcd 	  	   	 
------------------------------------------------------------------------*/ 
void DisplayTime(unsigned char hour,unsigned char min,unsigned char sec)
{
	LCD_ShowNumber(0,hour,2);
	LCD_ShowChar(2,'-');
	LCD_ShowNumber(3,min,2);
	LCD_ShowChar(5,'-'); 
	LCD_ShowNumber(6,sec,2); 
}

/*-----------------------------------------------------------------------
Function name:	DisplayVol
Input:		                  
Output:			
Description:	display volume   	 
------------------------------------------------------------------------*/ 
void DisplayVol(signed char vol_lev)
{
	unsigned char show[9]="VOL   ";
	LCD_ShowStrings(0,show);
	LCD_ShowNumber(6,vol_lev,2);
}

void Radio_DisplaySeekSensLev(void)
{
   unsigned char show[9]="SENS";
   if( SeekSensLevel==HIGH)
   {
       LCD_ShowStrings(5,(unsigned char *)"Hi");
   }
   else
   {
        LCD_ShowStrings(5,(unsigned char *)"Low");
   }
   LCD_ShowStrings(0,show);

}
/*-----------------------------------------------------------------------
Function name:	Display_Dot
Input:			
Output:		
Description:	 
------------------------------------------------------------------------*/
void Display_Dot(U8 OnOff)
{
	if(OnOff)
	{
	     LCD_clear_lite_anode(_SEG_P1,1);
	}
	else
	{
	     LCD_clear_lite_anode(_SEG_P1,0);
	}
}
/*-----------------------------------------------------------------------
Function name:			  
Input:
Output:			
Description: 	  
------------------------------------------------------------------------*/
void Radio_StoreOKDisplay(void)
{
	LCD_ShowStrings(0,Radio_LCDPresetOK);
	Display_Dot(0);
}
/*-----------------------------------------------------------------------
Function name:	Display_CDWheel
Input:		pos : position,rang 0~3                 
Output:			
Description:	display wheel   	 
------------------------------------------------------------------------*/ 
void Display_CDWheel(char pos)
{
	switch(pos)
	{ 
		 case 0:
		  	LCD_clear_lite_anode(_SEG_CDP1,ON);
			break;
		 case 1:
			LCD_clear_lite_anode(_SEG_CDP2,ON);
			break;
		 case 2:
			LCD_clear_lite_anode(_SEG_CDP3,ON);
			break;
	}
}
/*-----------------------------------------------------------------------
Function name:	DisplayHexNumber
Input:		pos :lcd position,rang 0~8          
                        num:number is be display
Output:			
Description:	display number as hex
                        e.g:
                            input num=16,will display '10'
------------------------------------------------------------------------*/
void DisplayHexNumber(char pos,U8 num)
{
	char Asii;
	/*display high 4 bit */
	Asii=num>>4;
	if(Asii<10)
	{
	        Asii+='0';
	 }
	else
	 {
		Asii-=10;
		Asii+='a';
	 }
	 LCD_ShowChar(pos,Asii);
	/*display low 4 bit */
	 Asii=num&0x0f;
	 if(Asii<10)
	 {
	        Asii+='0';
	 }
	 else
	 {
		Asii-=10;
		Asii+='a';
	 }
	 LCD_ShowChar(pos+1,Asii);
}

/*-----------------------------------------------------------------------
Function name:	Radio_LCDShowRadio
Input:			
Output:		
Description:	Radio mode display 
------------------------------------------------------------------------*/
void Radio_LCDShowRadio(void)
{
	  /*display band*/
	  U8 band;
	  U16 freq;
	  band=Radio_GetCurrentBand();
	  freq=Radio_GetCurrentFreq();
	  LCD_ShowStrings(0,Radio_LCDBandChar[band]);
	    //display LOC 
	   if( SeekSensLevel==HIGH)
	   	{
                  DispFlag_LOCAL(1);
	   }
	  if(Radio_IsFMBand())			  /*FM*/
	   {
		/*display freq*/
		if(freq>9999)
		{
		      LCD_ShowNumber(3,freq,5);
		}
		else
		{
		      LCD_ShowNumber(4,freq,4);
		}
		Display_Dot(1);

		    /*Stereo,mono display*/
		if(F_Stereo_Disp==1)
		{
		      DispFlag_ST(ON);		 
		}
		else
		{
		      DispFlag_MONO(ON);
		} 
	   }
	 else if(band<MaxStationNum)  /*AM*/
	   {
		    if(freq>999)
		     {
			    LCD_ShowNumber(4,freq,4);
		      }
		    else if(freq>9999)
		     {
			    LCD_ShowNumber(3,freq,5);
		     }
		    else 
		     {
			    LCD_ShowNumber(5,freq,3);
		     }
		    Display_Dot(0);	
	    }
	  /*display station number*/
	  if(Radio_GetCurrentStation())
	         LCD_ShowNumber(8, Radio_GetCurrentStation(), 1);

	
	  switch(TunerWorkMode)
	   {
		case K_SEEK_UP:
		case K_SEEK_DN:
		case K_SCAN:
		                Display_CDWheel(Radio_ScanStepCount%3);
			break;
		default:
			break;
	   }
}

