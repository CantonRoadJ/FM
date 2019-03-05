#include "Typedef.h"

/***************************************************************************************
* (C) Copyright Edom semiconductor, All rights reserved
* FILE NAME:	<LcdDrv.h>
* VERSION:		<1.0>
* DESCRIPTION:	
* DOCUMENT REF: <>
* NOTES:		<>
***************************************************************************************/

#ifndef _LCD_DRV_H
#define _LCD_DRV_H


#define LCD_SLAVE_ADDR      		 0x70		   //PCF8534A slave address
#define TRANS_CONTINUE_COMMAND		 0x80   	   //indicate translate continue command
#define TRANS_LAST_COMMAND      	 0x00		   //indicate translate last command
#define TRANS_DATA					 0x40          //indicate translate  ram data

#define LCD_RAM_ADDR_MAX 59

extern U8 LcdInit(void);
extern void LcdDataTranfer(void);
#endif
