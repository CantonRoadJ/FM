/***********************************************************************//**
 * @file		IO.h
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
#ifndef __GPIO_H
#define __GPIO_H


#define P_ACC_CHK  1// P3.0 // set p3.0 as ACC_DET

typedef union
{
	U32 Value;
	Bit32 Pin;
}GPIOValue;

extern volatile GPIOValue Port0Data;
extern volatile GPIOValue Port1Data;
extern volatile GPIOValue Port2Data;
extern volatile GPIOValue Port3Data;
extern volatile GPIOValue Port4Data;
#define LED1 Port1Data.Pin.bit9
#define ACC_TestPin Port0Data.Pin.b6			//ACC_TestPin = P0.06
#define SD_WPPin Port0Data.Pin.b22			//SD_WPPin = P0.22
#define PWR_KeyPin Port1Data.Pin.b18			//PWR_KeyPin = P1.18
#define SD_nCDPin Port2Data.Pin.b10			//SD_nCDPin = P2.10

#define p_LED1_ON() LPC_GPIO1->FIOSET=(0x00000001<<9) //P1.9
#define p_LED1_OFF() LPC_GPIO1->FIOCLR=(0x00000001<<9)

#define p_LED2_ON() LPC_GPIO1->FIOSET=(0x00000001<<8) //P1.8
#define p_LED2_OFF() LPC_GPIO1->FIOCLR=(0x00000001<<8)

#define p_PWR_ON() LPC_GPIO1->FIOSET=(0x00000001<<18) //P1.18
#define p_PWR_OFF() LPC_GPIO1->FIOCLR=(0x00000001<<18)

#define p_VR_HOLD_ON() LPC_GPIO1->FIOSET=(0x00000001<<15) //P1.15
#define p_VR_HOLD_OFF() LPC_GPIO1->FIOCLR=(0x00000001<<15)

#define p_Backlight_ON() LPC_GPIO1->FIOSET=(0x00000001<<24) //P1.24
#define p_Backlight_OFF() LPC_GPIO1->FIOCLR=(0x00000001<<24)

#define p_RESET_HERO_ON() LPC_GPIO1->FIOCLR=(0x00000001<<26) //P1.26
#define p_RESET_HERO_OFF() LPC_GPIO1->FIOSET=(0x00000001<<26)

#define p_RESET_CAYMAN_ON() LPC_GPIO1->FIOSET=(0x00000001<<29) //P1.29
#define p_RESET_CAYMAN_OFF() LPC_GPIO1->FIOCLR=(0x00000001<<29)

#define p_CAN2_STB_ON() LPC_GPIO2->FIOSET=(0x00000001<<9) //P2.09
#define p_CAN2_STB_OFF() LPC_GPIO2->FIOCLR=(0x00000001<<9)

#define p_FastMute_High() LPC_GPIO1->FIOSET=(0x00000001<<30) //P1.30
#define p_FastMute_Low() LPC_GPIO1->FIOCLR=(0x00000001<<30) //P1.30

extern void Port_Init(void);
#endif

