/***********************************************************************//**
 * @file		audio.c
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
 

#define VOLUME_INIT_LEV 20

/*mute flag*/
U8 SoftMuteState;		//TRUE  = mute,
/*volume level*/
S8 MainVolume_Lev = VOLUME_INIT_LEV;

//function declaration
void Audio_Data_Amend_Process(void);
void VolumeChangeProc(void);

/*-------------------------------------------------------------------------
 Function:Audio_Proc
 Input:      NULL
 OutPut:   NULL
 Description:
                Audio setup process
---------------------------------------------------------------------------*/
void Audio_Proc(void)
{
        /*check system status and work mode*/
	if((F_PowerOff))
		return;
	/* process*/
	Audio_Data_Amend_Process();
}

/*------------------------------------------------------------------------
 Function:Audio_Mute_Key(..)
 Input: NULL
 OutPut: NULL
 Description:mute key proccess
-------------------------------------------------------------------------*/
void Audio_Mute_Key(void)
{
	if(SoftMuteState)	{
              if(MainVolume_Lev>SET_VOLUME_LEV_MIN)     {
			MuteOff();
			SoftMuteState = FALSE;
			Display_DisableTimeout();
              }
	}
	else	{
		MuteOn();
		SoftMuteState = TRUE;
		Display_SetTimeout(DISPLAY_TIMEOUT_MUTE,1000);//mute display for 1s
	}
}
/*------------------------------------------------------------------------
 Function:Audio_Key_Process(..)
 Input: NULL
 OutPut: NULL
 Description:audio setup key proccess
-------------------------------------------------------------------------*/
void Audio_Key_Process(void)
{
	switch(KeyCode)
	{
		case AUDIO_MUTEKEY:
			Audio_Mute_Key();
			KeyCode = 0;			//clear for the next
			break;
	}
}
/*-----------------------------------------------------------------------
Function name:	Audio_Data_CMD		  
Input:	NULL
Output:	NULL		
Description:Do audio setup proccess
------------------------------------------------------------------------*/
void Audio_Data_CMD(void)
{
	VolumeChangeProc();
}

void Audio_Data_Amend_Process(void)
{	
	/*to judge Audio in which work mode according to key value*/
	Audio_Key_Process();

	/*Change Audio Ic data <bass,Mid,treble,balance,fader,volume>*/		
	Audio_Data_CMD();
}


/*-----------------------------------------------------------------------
Input:	
Output:			
Description: init the volume data	 
------------------------------------------------------------------------*/
void VolumeProcInit(void)
{
	Audio_SetVolume(PrimaryStr,MainVolume_Lev); 
}

/*-----------------------------------------------------------------------
Input:	
Output:			
Description: 	 check if volume need to be changed and set the new volume to hero
------------------------------------------------------------------------*/
void VolumeChangeProc(void)
{
	S8 WheelKey=GetWheelKey();   //get the wheel key value
		
	if(WheelKey)//wheel active
	{
		MainVolume_Lev+=WheelKey;//volume change

		if(MainVolume_Lev<=SET_VOLUME_LEV_MIN)//check the volume range
		{
			MainVolume_Lev=SET_VOLUME_LEV_MIN;//min volume= mute

			if(SoftMuteState==FALSE)//check if it is muteed now
			{
				MuteOn();
				SoftMuteState=TRUE;
			}
		}
		else if(MainVolume_Lev>SET_VOLUME_LEV_MAX)//check the volume range
		{
			MainVolume_Lev=SET_VOLUME_LEV_MAX;
				
			if(SoftMuteState==TRUE)////it was muted before
			{
				MuteOff();
				SoftMuteState=FALSE;
			}
		}
		else//not exceed the volume range
		{
			if(SoftMuteState==TRUE)//it was muted before
			{
				MuteOff();
				SoftMuteState=FALSE;
			}
		}

//try---------------------------------------


//-----------------------------------------

		//write the new volume data to hero
		Audio_SetVolume(PrimaryStr, MainVolume_Lev);  //just primary channel with this project
		Display_SetTimeout(DISPLAY_TIMEOUT_VOL,1000);//volume display for 1s
	}
}

