#include "Typedef.h"

/***********************************************************************//**
 * @file		AmpTDF8546.h
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
#define STB  	 (LPC_GPIO2->FIOPIN0&0x10)//p2.4
#define DIAG      (LPC_GPIO2->FIOPIN0&0x08)//p2.3


/*=======diag information bit definition==================*/
#define AMP_OK     0X00
#define AMP_TEMP_WARNING  0x01
#define AMP_TEMP_PROTECT  0x02
#define AMP_OVER_VOLTAGLE_16V  0x04
#define AMP_OVER_VOLTAGLE_20V  0x10
#define AMP_LOW_VOLTAGLE  0x20


extern void Init_Amp(void);
extern void AmpMute(unsigned char OnOff);
