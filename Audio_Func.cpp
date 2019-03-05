#include "public.h"

//-60 … +24 dB volume
static const S8 tblVolLevelTrans_Atomic2[ SET_VOLUME_LEV_MAX + 1 ] = {
	/* Primary/Secondary Volume gain : -62~+12[dB] */
	  -60, -57, -54, -51, -48, -45,-42,-39 ,//  0 -  7
	  -36, -33, -30, -28,-26, -24,  -22,-20,-18,-16, // 8 - 17
	  -14, -12, -10, -8, -6, -4, -2, 0,2, 4,// 18 - 27
	  6,8,10,12,14,16,18,20,22,24 // 28 - 37
};

/*-----------------------------------------------------------------------
Function name:		Audio_SetVolume	  
Input:	Channel: seen the define
		Lev:the level of the volume step ,not the real dB value
Output:			
Description:set volume and the loudness 
------------------------------------------------------------------------*/
void Audio_SetVolume(Audio_Stream_t Channel,U8 Lev)
{
	AUDIO_Set_Volume(tblVolLevelTrans_Atomic2[Lev]);//set volume
}

//mute=1, unmute=0
void Audio_SetMute(bool mute)
{
	AUDIO_Set_Mute(mute? 1 : 0);
}

