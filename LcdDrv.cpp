/***********************************************************************//**
 * @file		LcdDrv.c
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


#define LCD_DATA_LENGTH     (26)


static U8   mLC_TxDataBuffer[LCD_DATA_LENGTH+1];


/* PCF 8534A init config table*/
const U8 tbl_lcd_init[]=
{
	TRANS_CONTINUE_COMMAND,//Format:transt continue command
	0xc8	, //Mode set,[7..4] 	 1100b:fixed
	          //		   [3]       1b:enable blank,0b:disable
		  //		   [2]       0b:1/3bias,1b:1/2bias
		  //         [1..0]    01b:static,	10b:1/2duty,11b:1/3duty,00b:1/4duty
	          //bank enable,1/3bias,1/3duty
	TRANS_CONTINUE_COMMAND,
	0x00,                 	 //data pointer ,[7] 	 0b:fixed
	              			//               [6..0]  0~59
	TRANS_LAST_COMMAND,
	0xe0,                  //device select,[7..3]   11100b:fixed
	                       //              [2..0]	0~7
};
/*-----------------------------------------------------------------------
Function name:	LcdInit
Input:			N/A
Output:			1:sucess   0:failed
Description:	init Lcd Driver PCF8534A
                PCF8534A power on at least for 1ms
                before call this function,must call I2c init
------------------------------------------------------------------------*/
U8 LcdInit(void)
{
     U8 ret;
     ret=I2C2_WriteData(LCD_SLAVE_ADDR,(U8*)tbl_lcd_init,sizeof(tbl_lcd_init)/sizeof(U8));
     return ret;
}

/*-----------------------------------------------------------------------
Function name:	SetLcdRamAddr
Input:			addr(must be in rang 0~59) 
Output:			1:sucess   0:failed
Description:	
               set lcd driver PCF8534A ram data poiter address
------------------------------------------------------------------------*/
static U8 SetLcdRamAddr(U8 addr)
{
	U8 sendbuf[2];

	sendbuf[0] = TRANS_CONTINUE_COMMAND;
	sendbuf[1] = addr > LCD_RAM_ADDR_MAX? LCD_RAM_ADDR_MAX : addr;
	
	return I2C2_WriteData(LCD_SLAVE_ADDR,sendbuf,2);
}

/*-----------------------------------------------------------------------
Function name:	SetLcdTxBuffer
Input:			pTxdata poiter to lcd data buffer 
Output:			1:need to send data to lcd   0:no need
Description:	
               compare data in buffer *pTxdata and mLC_TxDataBuffer
			   if diffrent need to send data to lcd 
------------------------------------------------------------------------*/
U8 SetLcdTxBuffer( U8 *pTxdata )
{
	U8 i,not_equ=FALSE;
	U8 *pTxBuffer = &mLC_TxDataBuffer[1];//note that start from 1

	for(i=0;i<LCD_DATA_LENGTH;i++)
	{
		if(pTxBuffer[i] != pTxdata[i])
		{
			pTxBuffer[i] = pTxdata[i];
			not_equ = TRUE;
		}
	}

	return not_equ;
}
/*-----------------------------------------------------------------------
Function name:	LcdDataTranfer
Input:			N/A
Output:			N/A
Description:	
              send data to LCD driver PCF8534A
------------------------------------------------------------------------*/
void LcdDataTranfer(void)
{
  	if(SetLcdTxBuffer(ShadowRam))	 //if display date new
  	{
		if(SetLcdRamAddr(0) == ERROR) 
		    return;

		mLC_TxDataBuffer[0] = TRANS_DATA;
		I2C2_WriteData(LCD_SLAVE_ADDR,mLC_TxDataBuffer,sizeof(mLC_TxDataBuffer)/sizeof(U8));
  	}
}

