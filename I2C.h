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
#ifndef __I2C_H
#define __I2C_H

#define Slave_7Bitformat 0

#define I2C_RETRY_TIMES		3
#define I2C_IDLE 0
#define I2C_ERROR 1
#define I2C_BUSY 2
#define I2C_END	3
#define I2C_STARTED 4

#define I2C_1	0
#define I2C_2	1

extern void I2C1_Init(void);
extern void I2C1_SetMode(U8 Mode);
extern void I2C1_IRQHandler(void);
extern U8 I2C1_WriteData(U8 SlaveAddr,U8 *BufferP,U8 Num);
extern U8 I2C1_ReadData(U8 SlaveAddr,U8 *BufferP,U8 Num);
extern void I2C1_Enable(void);
extern void I2C1_Disable(void);


extern void I2C2_Init(void);
extern void I2C2_IRQHandler(void);
extern U8 I2C2_WriteData(U8 SlaveAddr,U8 *BufferP,U8 Num);
extern U8 I2C2_ReadData(U8 SlaveAddr,U8 *BufferP,U8 Num);
U8 I2C2_ReadSubData(U8 SlaveAddr,U8 sub,U8 *BufferP,U8 Num);

U8 I2C1_IsErr(void);
U8 I2C2_IsErr(void);

#endif

