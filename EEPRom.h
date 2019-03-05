#include "Typedef.h"

/***********************************************************************//**
 * @file		I2C.h
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
#ifndef __EEPROM_H
#define __EEPROM_H

#define EEPROM_SlaveAddr 0xA0

#define EEPRom_CurrentBandAddr 0x02	/*	1 byte */


#define EEPRom_ConfigAddr 0x0a	//TEF663x_BufferLen bytes
#define EEPRom_CheckAddr 0x05
#define AvailableDataFlag 0x5A
#define EEPRom_StationRecordDefaultAddr 0x30//aligned



void EEPROM_Write(U8 addr,U8 *data,U8 bytes);
void EEPROM_Read(U8 addr,U8 *data,U8 bytes);

#endif

