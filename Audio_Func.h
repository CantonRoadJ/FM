#include "Typedef.h"

#ifndef _AUDIO_FUNC_H
#define _AUDIO_FUNC_H

/*volume value max*/
#define SET_VOLUME_PRIMARY_SECONDARY_MAX	TEF663X_MAINVOLUMEMAX
/*volume value min*/
#define SET_VOLUME_PRIMARY_SECONDARY_MIN	HERO_PCHANNEL_MAINVOLUMEMIN

/*GEQ Mode define*/
#define HERO_GEQMODE_NONE 0
#define HERO_GEQMODE_CLASS 1
#define HERO_GEQMODE_POP 2
#define HERO_GEQMODE_ROCK 3
#define HERO_GEQMODE_USER 4		//the real eq mode is 5,this is the last mode
#define GEQ_MAXBAND 5

/*fader max level define*/
#define FADER_LEVEL_MAX  30

/*banlance max level define*/
#define BANLENCE_LEVEL_MAX  14

/*pdc mode define*/
#define TEF663x_PDCMODESLOW 0
#define TEF663x_PDCMODEMID 1
#define TEF663x_PDCMODEFAST 2
#define TEF663x_PDCMODEROLL 3
#define TEF663x_PDCMODENULL 0xFF

/*scaling config */

/*audio stream define*/
typedef enum Audio_Stream
{
	PrimaryStr     = 1,
	SecondaryStr   ,
	NavigationStr ,
	PhoneStr,
	SecondaryS_2nd
} Audio_Stream_t;

/* Volume Level setting */
#define SET_VOLUME_LEV_MAX	(37)
#define SET_VOLUME_LEV_MIN	(0)

/*volume set*/
void Audio_SetVolume(Audio_Stream_t Channel,U8 Lev);
void Audio_SetMute(bool mute);

#endif

