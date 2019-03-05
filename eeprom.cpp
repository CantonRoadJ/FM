/***********************************************************************//**
 * @file		eeprom.c
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

static U32 eeprom_timer;
/*****************************************************************************
*  Name        : EEPROM_Write
*  Description : eeprom page write, every time with 1 addr and 7 bytes data
*  I2C timing: Start + Slave(W) + Sub + Data(max = 7) + Stop
*  Params      : addr = eeprom's address which want to write, *data  = buf which want to write
*  Returns     : 
*****************************************************************************/
//eeprom page write
//max write 7 bytes every times
void EEPROM_Write(U8 addr,U8 *data,U8 bytes)
{
	int i;
	U8 buf[8];

	while(bytes){
              /*prepare 1 addr + 7 bytes data*/
		buf[0] = addr;
		addr+=7;		//for the next addr
		for(i=1;i<8;i++){
			buf[i] = *data++;
			if(--bytes == 0){
				i++;		//the last one include addr
				break;
			}
		}
		
		TimerWaitExpired(&eeprom_timer);	//wait untill last write finish

		I2C2_WriteData(EEPROM_SlaveAddr,buf,i);	//include sub address

		TimerSet(&eeprom_timer,25);
	}
}
/*****************************************************************************
*  Name        : EEPROM_Read
*  Description : eeprom continue read, 
*  I2C timing: Start + Slave(W) + Sub + Start + Slave(R) + Data + Stop
*  Params      : addr = eeprom's address which want to read, *data  = buf which read out
*  Returns     : 
*****************************************************************************/
void EEPROM_Read(U8 addr,U8 *data,U8 bytes)
{
	TimerWaitExpired(&eeprom_timer);	//wait untill last write finish
	I2C2_ReadSubData(EEPROM_SlaveAddr,addr,data,bytes);
}

