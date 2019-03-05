#include "Typedef.h"

/***********************************************************************//**
 * @file		key.h
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
#ifndef KEY_H
#define KEY_H

#define No_Key				0

/*key adc value */
typedef struct{
	unsigned char	StartVal;
	unsigned char	EndVal;
}KEY_ADCVAL;

/*ADC define*/
#define ADC_CLK_KHZ    12500      //ADC clock	 12.5mhz
#define AIN0 0x01
#define AIN1 0x02
#define AIN2 0x04
#define AIN3 0x08
#define AIN4 0x10
#define AIN5 0x20
#define AIN6 0x40
#define AIN7 0x80

#define ADKEY0   AIN2
#define ADKEY1   AIN3
#define ADKEY2	 AIN5

#define AD_SWC0       2	 //AIN2
#define AD_SWC1  	  3	 //AIN3
#define AD_SWC2    	  5	 //AIN5
#define ADC_OFFSET		0x10
#define ADC_INDEX		4

/* key flag define */
#define   F_COMBIN_KEY		   Key_PROCESS.data_Bbit.B3
#define   F_LONG_PROCESS       Key_PROCESS.data_Bbit.B4
#define	  F_NOTLONGKEY		   Key_PROCESS.data_Bbit.B5
#define	  F_KEYTIMER		   Key_PROCESS.data_Bbit.B6
#define   F_SWC_KEY_READ       Key_PROCESS.data_Bbit.B7
EXT byte_field 	 Key_PROCESS;


/*key code  define*/
#define KC00 40//39
#define KC01 KC00+1
#define KC02 KC00+2
#define KC03 KC00+3

#define KC10 44
#define KC11 KC10+1
#define KC12 KC10+2
#define KC13 KC10+3
#define KC14 KC10+4
#define KC15 KC10+5

#define KC20 50
#define KC21 KC20+1
#define KC22 KC20+2
#define KC23 KC20+3
#define KC24 KC20+4
#define KC25 KC20+5
#define PWRKC    57				//power key 

/*Pannel key define */
#define K1   	 KC00
#define K2   	 KC03
#define K3   	 PWRKC
#define K4   	 KC02
#define K5   	 KC01

#define K6   	 KC15
#define K7   	 KC14
#define K8   	 KC13
#define K9   	 KC12
#define K10   	 KC11
#define K11   	 KC10

#define K12   	 KC25
#define K13   	 KC24
#define K14   	 KC23
#define K15   	 KC22
#define K16   	 KC21
#define K17   	 KC20

/*key type define*/
#define PUSHKEY    0x00	 
#define SHORTKEY        0x10000000
#define LONGKEY         0x20000000
#define LONG_RELEASEKEY  0x40000000

/*  Short Key +0x1000 */
#define SK1	    (K1+SHORTKEY)
#define SK2     (K2+SHORTKEY)
#define SK3     (K3+SHORTKEY)
#define SK4     (K4+SHORTKEY)
#define SK5     (K5+SHORTKEY)
#define SK6     (K6+SHORTKEY)
#define SK7     (K7+SHORTKEY)
#define SK8     (K8+SHORTKEY)
#define SK9     (K9+SHORTKEY) 
#define SK10     (K10+SHORTKEY)
#define SK11     (K11+SHORTKEY)
#define SK12     (K12+SHORTKEY)
#define SK13     (K13+SHORTKEY)
#define SK14     (K14+SHORTKEY)
#define SK15     (K15+SHORTKEY)
#define SK16     (K16+SHORTKEY)
#define SK17     (K17+SHORTKEY)

/* Long Key +0x2000 */
#define LK1	    (K1+LONGKEY)
#define LK2     (K2+LONGKEY)
#define LK3     (K3+LONGKEY)
#define LK4     (K4+LONGKEY)
#define LK5     (K5+LONGKEY)
#define LK6     (K6+LONGKEY)
#define LK7     (K7+LONGKEY)
#define LK8     (K8+LONGKEY)
#define LK9     (K9+LONGKEY) 
#define LK10     (K10+LONGKEY)
#define LK11     (K11+LONGKEY)
#define LK12     (K12+LONGKEY)
#define LK13     (K13+LONGKEY)
#define LK14     (K14+LONGKEY)
#define LK15     (K15+LONGKEY)
#define LK16     (K16+LONGKEY)
#define LK17     (K17+LONGKEY)

/* LONG_RELEASE _KEY 0x4000 */
#define LRK1	    (K1+LONG_RELEASEKEY)
#define LRK2     (K2+LONG_RELEASEKEY)
#define LRK3     (K3+LONG_RELEASEKEY)
#define LRK4     (K4+LONG_RELEASEKEY)
#define LRK5     (K5+LONG_RELEASEKEY)
#define LRK6     (K6+LONG_RELEASEKEY)
#define LRK7     (K7+LONG_RELEASEKEY)
#define LRK8     (K8+LONG_RELEASEKEY)
#define LRK9     (K9+LONG_RELEASEKEY) 
#define LRK10     (K10+LONG_RELEASEKEY)
#define LRK11     (K11+LONG_RELEASEKEY)
#define LRK12     (K12+LONG_RELEASEKEY)
#define LRK13     (K13+LONG_RELEASEKEY)
#define LRK14     (K14+LONG_RELEASEKEY)
#define LRK15     (K15+LONG_RELEASEKEY)
#define LRK16     (K16+LONG_RELEASEKEY)
#define LRK17     (K17+LONG_RELEASEKEY)


/*user key define*/
#define Enter                    SK1
#define KeyUp                   SK5
#define KeyDown               SK10
#define EQ_Key                 SK7
#define K_Mode                  SK2
#define SW_VOL_DN       	KC12 /* Push Key */
#define SW_VOL_UP       	KC02
#define  SW_MODE      	KC10
#define	SW_SEEKUP	KC01
#define	SW_SEEKDN	KC11



/*define time*/
#define HALF_SECOND 250
#define ONE_TEN_SECOND 50
#define ONE_SECOND  500

extern void Key_Init(void);
extern void Key_Proc(void);
extern S8 GetWheelKey(void);

EXT U32 KeyCode;
EXT UNINT KeyTimer;

#endif

