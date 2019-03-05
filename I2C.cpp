/***********************************************************************//**
 * @file		I2C.c
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

#include <stdio.h>
#include <stdarg.h>
#include <linux/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <errno.h>
#include <assert.h>
#include <string.h>
#include <linux/i2c.h>
#include <linux/i2c-dev.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <QDebug>

/*--------------------------I2C define-------------------------------*/
//#define I2C_Printf	Dbg_printf
#define I2C_Printf(...)	

#define I2C_BufferLen 220 //don't > 255 for 8bits counter

typedef struct{
	U8 status;	//I2C_IDLE,I2C_ERROR,I2C_BUSY
	U8 rw;		//read=1,write=0
	U8 addr;		//slave addr
	U8 req_num;	//request read/write bytes
	U8 num;		//actual number

	U8 sub_valid;	// sub addr is valid
	U8 sub_addr;	// sub addr

	U8 buffer[I2C_BufferLen];	//read/write buffer
}I2C_DATA;
static I2C_DATA I2C_Data[2];
//static LPC_I2C_TypeDef *pTab_I2CType[2] = {LPC_I2C1,LPC_I2C2};

int fd;


/*-----------------------------------------------------------------------
Function name:	I2C1_Init
Input:			N/A
Output:			N/A
Description:	init I2C1
------------------------------------------------------------------------*/
void I2C1_Init(void)
{

#if 0
	I2C_DATA *pI2C = &I2C_Data[I2C_1];
	
	LPC_SC->PCONP |= PCI2C1;					//I2C1 power on

	LPC_PINCON->PINSEL0 |=0x0f;					//p0.1,p0.2 using as SDA1 and SCL1
	
	LPC_PINCON->PINMODE0 &=~0x0F;		
	LPC_PINCON->PINMODE0 |=0x0A;				//no pull-up,no pull-down
	
	LPC_PINCON->PINMODE_OD0 |=0x03;			//open drain

	LPC_I2C1->I2SCLH=50;                //high = 2.5us,200k
	LPC_I2C1->I2SCLL=50;               //low = 2.5us

	LPC_I2C1->I2CONCLR = STAC|SIC|AAC;		//clear all the flag
	LPC_I2C1->I2CONSET = I2EN;                        //enable the I2C1
	NVIC_EnableIRQ(I2C1_IRQn);				//enable I2C1 interrupt

	pI2C ->status = I2C_IDLE;					//set i2c status
#endif

    //if (fd == 0)
    //{
        QString devName = "/dev/i2c-0";
        fd = ::open(devName.toLatin1().data(),O_RDWR);
    //}

    if (fd <=0)
    {
        qDebug("can not open the device");
        exit(0);
    }
}
/*-----------------------------------------------------------------------
Input:			Mode: 0=master,others=slave
Output:			N/A
Description:	set I2C1 work mode
------------------------------------------------------------------------*/
void I2C1_SetMode(U8 Mode)
{
#if 0
	if(Mode)
	{
		LPC_I2C1->I2ADR0=0x17;				//set slave addr	

		LPC_I2C1->I2CONCLR = STAC|SIC|STO;		//clear all the flag
		LPC_I2C1->I2CONSET = I2EN|AAC;          //enable the I2C1
	}
	else
	{

	}
#endif
}
/*-----------------------------------------------------------------------
Function name:	I2C2_Init
Input:			N/A
Output:			N/A
Description:	init I2C2
------------------------------------------------------------------------*/
void I2C2_Init(void)
{
#if 0
	I2C_DATA *pI2C = &I2C_Data[I2C_2];

	LPC_SC->PCONP |=PCI2C2;                              //I2C2 power on

	LPC_PINCON->PINSEL0&=~(0x0000000F<<20);   	   //clear the config before setting
	LPC_PINCON->PINSEL0+=0x0000000A<<20;            //using as SDA2 and SCL2

	LPC_PINCON->PINMODE0&=~(0x0000000F<<20);        //clear the config before setting
	LPC_PINCON->PINMODE0+=0x0000000A<<20;               //no pull-up,no pull-down
	LPC_PINCON->PINMODE_OD0&=~(0x00000003<<10);        //clear the config before setting
	LPC_PINCON->PINMODE_OD0+=0x00000003<<10;			 //open drain

	LPC_SC->PCLKSEL1&=~(0x00000003<<20);                   //clear the config before setting
	LPC_SC->PCLKSEL1+=0x00000002<<20;                     //I2C clk=cclk/2,
	LPC_I2C2->I2SCLH=500;                                 //clock high pule time
	LPC_I2C2->I2SCLL=500;                                 //clock Low pule time    

	LPC_I2C2->I2CONCLR=0x3C;                        //clear all the flag
	LPC_I2C2->I2CONSET=I2EN;                        //enable the I2C2	
	NVIC_EnableIRQ(I2C2_IRQn);								  //enable I2C2 interrupt

	pI2C ->status = I2C_IDLE;					//set i2c status
#endif

}

static void IRQ_I2C_Master_Write(U8 i2c_num)
{
#if 0
	LPC_I2C_TypeDef *pHW = pTab_I2CType[i2c_num];
	I2C_DATA *pI2C = &I2C_Data[i2c_num];
	register U8 stat = pHW->I2STAT;

	switch(stat)//get the status
	{    
		case 0x08:	//start has been sent,The Slave Address + R/W bit will now be transmitted
		case 0x10:	//repeat start has been sent
			pHW->I2DAT = pI2C->addr + pI2C->rw;         //write slave address
			pHW->I2CONSET=AA;			//set the AA bit
			pHW->I2CONCLR=SIC|STAC;           //clear the start cmd and int flag
			pI2C->num = 0;
			break;

		case 0x18:		//SLA+W has been transmitted; ACK has been received
			pHW->I2DAT=pI2C->buffer[pI2C->num++];		//send byte
			pHW->I2CONSET=AA;			//set the AA bit
			pHW->I2CONCLR=SIC;           //clear int flag
			break;

		case 0x28:		//Data has been transmitted, ACK has been received
		    	if(pI2C->num >= pI2C->req_num)
		    	{
				pHW->I2CONSET=STO|AA;		//set the STO and AA bits
				pHW->I2CONCLR=SIC;           //clear int flag
				pI2C->status = I2C_IDLE;
		    	}
			else{
				pHW->I2DAT=pI2C->buffer[pI2C->num++];		//send byte
				pHW->I2CONSET=AA;			//set the AA bit
				pHW->I2CONCLR=SIC;           //clear int flag
			}
			break;
			
		case 0x38:				//  Arbitration has been lost during Slave Address + Write or data.
			pHW->I2CONSET=STA|AA;		//set the STA and AA bits
			pHW->I2CONCLR=SIC;           //clear int flag
			break;

		case 0x20:		  //SLA+W has been sent,act not received
		case 0x30:		//Data has been transmitted, NOT ACK received. A STOP condition will be transmitted
		case 0x00:
		default:
			pHW->I2CONSET=STO|AA;		//set the STO and AA bits
			pHW->I2CONCLR=SIC;           //clear int flag
			pI2C->status = I2C_ERROR;
			break;
		}

#endif

}
static void IRQ_I2C_Master_Read(U8 i2c_num)
{
#if 0
	LPC_I2C_TypeDef *pHW = pTab_I2CType[i2c_num];
	I2C_DATA *pI2C = &I2C_Data[i2c_num];

	switch(pHW->I2STAT)//get the status
	{
		case 0x08:				//start has been sent
			if(pI2C->sub_valid)
				pHW->I2DAT = pI2C->addr;         //next byte is sub address
			else
				pHW->I2DAT = pI2C->addr | 1;   //read slave address
			
			pHW->I2CONSET=AA;			//set the AA bit
			pHW->I2CONCLR=SIC|STAC;           //clear the start cmd and int flag
			break;
			
		case 0x18:		//SLA+W has been transmitted; ACK has been received
			pHW->I2DAT=pI2C->sub_addr;         //write sub address
			pHW->I2CONSET=AA;			//set the AA bit
			pHW->I2CONCLR=SIC;           //clear int flag
			break;
			
		case 0x28:		//Data has been transmitted, ACK has been received
			pHW->I2CONSET=STA|AA;			//restart
			pHW->I2CONCLR=SIC; 			 //clear int flag
			break;

		case 0x10:				//repeat start has been sent
			pHW->I2DAT = pI2C->addr + 1;		//after restart, start read now
			
			pHW->I2CONSET=AA;			//set the AA bit
			pHW->I2CONCLR=SIC|STAC;           //clear the start cmd and int flag
			break;

		case 0x40:		//SLA+R has been transmitted; ACK has been received
			pHW->I2CONSET=AA;			//read data and return ack
			pHW->I2CONCLR=SIC;		//clear the config
			break;

		case 0x50://Data has been received, ACK has been returned
			pI2C->buffer[pI2C->num]=pHW->I2DAT;	//Read data byte from I2DAT into Master Receive buffer
			pI2C->num ++;

			if(pI2C->num >= pI2C->req_num)
			{
				pHW->I2CONCLR=SIC|AAC; 			 //clear the SI flag and the AA bit.
				pI2C->status = I2C_IDLE;				//set status to idle
			}
			else
			{
				pHW->I2CONSET=AA;			//set the AA bit
				pHW->I2CONCLR=SIC;		//clear the SI flag
			}
			break;

		case 0x58://Data has been received, NOT ACK has been returned.
			pHW->I2CONSET=STO|AA;			//set the STO and AA bits
 			pHW->I2CONCLR=SIC;		//clear the SI flag

			pI2C->status = I2C_IDLE;				//set status to idle
			break;
			
		case 0x48:	//Slave Address + Read has been transmitted, NOT ACK has been received. A STOP will be transmitted
		default:
			pHW->I2CONSET=STO|AA;			//set the STO and AA bits
			pHW->I2CONCLR=SIC; 			 //clear int flag
			pI2C->status = I2C_ERROR;
			break;
	}

#endif
}
/*-----------------------------------------------------------------------
Function name:	I2C1_IRQHandler
Input:			N/A
Output:			N/A
Description:	*Deals with master read and master write only 
------------------------------------------------------------------------*/
void I2C1_IRQHandler(void)
{
	if(I2C_Data[I2C_1].rw)		//read
		IRQ_I2C_Master_Read(I2C_1);
	else						//write
		IRQ_I2C_Master_Write(I2C_1);
}

#define I2C_ERR_COUNT	50000
static U8 I2C_WaitFinish(U8 i2c_num)
{
#if 0
	int retry=0;
	int i2c_err_cnt=0;
	I2C_DATA *pI2C = &I2C_Data[i2c_num];
	LPC_I2C_TypeDef *pHW = pTab_I2CType[i2c_num];

	while(1){
		if(pI2C->status == I2C_IDLE)
			return SUCCESS;

		if(pHW->I2STAT == 0xf8)//busy
		{
			TimerDelayMs(2);	//wait 2ms
			
			i2c_err_cnt++;
		}
		else
			i2c_err_cnt = 0;
		
		if((pI2C->status == I2C_ERROR)||((pHW->I2STAT == 0xf8)&&(i2c_err_cnt > I2C_ERR_COUNT)))
		{
			i2c_err_cnt = 0;
			
			if(++retry > I2C_RETRY_TIMES)
			{
				pI2C->status = I2C_ERROR;
				break;
			}
			
			TimerDelayMs(2);	//wait 2ms

			pI2C->num = 0;	//clear counter
			pHW->I2CONSET=STA;			//set the STA bit, start again
		}
		else{
			WatchDog_Feed();
		}
	}

	return ERROR;
#endif

}

#if 0
//return bytes which write successly
static void I2C_WriteData(U8 i2c_num,U8 SlaveAddr,U8 *BufferP,U8 Num)
{
	I2C_DATA *pI2C = &I2C_Data[i2c_num];
	LPC_I2C_TypeDef *pHW = pTab_I2CType[i2c_num];
	
//-----------------wait untill last trans finish	
	I2C_WaitFinish(i2c_num);

//-----------------fill buffer
	pI2C->status = I2C_BUSY;		//set busy status
#if(Slave_7Bitformat)
	pI2C->addr = SlaveAddr<<1;	//Set up the Slave Address to which data will be transmitted, and add the Write bit
#else
	pI2C->addr = SlaveAddr;
#endif

	if(Num > I2C_BufferLen)	Num = I2C_BufferLen;

	memcpy(pI2C->buffer,BufferP,Num);	//Set up data to be transmitted
	pI2C->req_num = Num;				//Initialize the Master data counter
	pI2C->rw = 0;	//write flag

	pI2C->num = 0;
	pHW->I2CONSET=STA;			//set the STA bit.
}

//return how many bytes had read
static U8 I2C_ReadData(U8 i2c_num,U8 SlaveAddr,U8 *BufferP,U8 Num)
{
	I2C_DATA *pI2C = &I2C_Data[i2c_num];
	LPC_I2C_TypeDef *pHW = pTab_I2CType[i2c_num];
	
//-----------------wait untill last trans finish	
	I2C_WaitFinish(i2c_num);

//-----------------fill buffer
	pI2C->status = I2C_BUSY;		//set busy status
#if(Slave_7Bitformat)
	pI2C->addr = SlaveAddr<<1;	//Set up the Slave Address to which data will be transmitted, and add the Write bit
#else
	pI2C->addr = SlaveAddr;
#endif

	if(Num > I2C_BufferLen)	Num = I2C_BufferLen;

	memset(BufferP,0,Num);	//Set up data to be transmitted
	pI2C->req_num = Num;				//Initialize the Master data counter
	pI2C->rw = 1;	//read flag

	pI2C->num = 0;
	pHW->I2CONSET=STA;			//set the STA bit.

//-----------------wait untill last trans finish	
	I2C_WaitFinish(i2c_num);

	memcpy(BufferP,pI2C->buffer,pI2C->num);

	return pI2C->num;
}
#endif

//return bytes which write successly
static void I2C_WriteData(U8 i2c_num,U8 SlaveAddr,U8 *BufferP,U8 Num)
{
    usleep(10000);

    int ret;
    struct i2c_rdwr_ioctl_data work_queue;

    work_queue.nmsgs = 1;// 消息数量
    work_queue.msgs = (struct i2c_msg *)malloc(work_queue.nmsgs *sizeof(struct i2c_msg));
    if(!work_queue.msgs)
    {
        qDebug("Memery alloc error\n");
        close(fd);
        return;
    }

    ioctl(fd, I2C_TIMEOUT, 2);//设置超时
    ioctl(fd, I2C_RETRIES, 1);//设置重试次数

    //往i2c里面写数据

    work_queue.nmsgs  = 1;
    (work_queue.msgs[0]).len = Num;//buf的长度
    (work_queue.msgs[0]).flags = 0;//write
    (work_queue.msgs[0]).addr = SlaveAddr;//设备地址
    (work_queue.msgs[0]).buf = BufferP;

#if 0
    qDebug("began to write:\n");

    qDebug("\n%d,",Num);

    for (int i=0;i<Num;i++)
    {
        qDebug("%x,",(work_queue.msgs[0]).buf[i]);
    }

    qDebug("\n");
#endif

    ret = ioctl(fd, I2C_RDWR, (unsigned long)&work_queue);

    if(ret < 0)
        return;

    return;
}

//return how many bytes had read
static U8 I2C_ReadData(U8 i2c_num,U8 SlaveAddr,U8 *BufferP,U8 Num)
{
    usleep(1000);

    int ret;
    struct i2c_rdwr_ioctl_data work_queue;

    work_queue.nmsgs = 1;// 消息数量
    work_queue.msgs = (struct i2c_msg *)malloc(work_queue.nmsgs *sizeof(struct i2c_msg));
    if(!work_queue.msgs)
    {
        qDebug("Memery alloc error\n");
        close(fd);
        return ERROR;
    }

    ioctl(fd, I2C_TIMEOUT, 2);//设置超时
    ioctl(fd, I2C_RETRIES, 1);//设置重试次数

    //往i2c里面写数据
    printf("began to write:\n");
    work_queue.nmsgs  = 1;
    (work_queue.msgs[0]).len = Num;//buf的长度
    (work_queue.msgs[0]).flags = I2C_M_RD;//write
    (work_queue.msgs[0]).addr = SlaveAddr;//设备地址
    (work_queue.msgs[0]).buf = BufferP;

    ret = ioctl(fd, I2C_RDWR, (unsigned long)&work_queue);

#if 0
    qDebug("read data:");
    qDebug("len is = %x",Num);

    for (int i=0;i<Num;i++)
    {
        qDebug("data[%d] = %x,",i,BufferP[i]);
    }
#endif

    if(ret < 0)
        return ERROR;

    return SUCCESS;
}

/*-----------------------------------------------------------------------
Function name:	I2C_IsErr
Input:			Num:total bytes will be write to the I2C
Output:			1=I2C err
Description:	 
------------------------------------------------------------------------*/
U8 I2C_IsErr(U8 i2c_num)
{
	I2C_DATA *pI2C = &I2C_Data[i2c_num];

	I2C_WaitFinish(i2c_num);

	return (I2C_ERROR == pI2C->status);

}
U8 I2C1_IsErr(void)
{
	return I2C_IsErr(I2C_1);
}
U8 I2C2_IsErr(void)
{
	return I2C_IsErr(I2C_2);
}
/*-----------------------------------------------------------------------
Function name:	I2C1_WriteData
Input:			SlaveAddr; BufferP:first write data`s pointer; Num:total bytes will be write to the I2C
Output:			0=I2C in using; 1=I2C start to write data;2=too many bytes
Description:	 
------------------------------------------------------------------------*/
U8 I2C1_WriteData(U8 SlaveAddr,U8 *BufferP,U8 Num)
{
	I2C_WriteData(I2C_1,SlaveAddr,BufferP,Num);

	if(I2C1_IsErr())
	{
		return !SUCCESS;
	}

	return SUCCESS;
}
/*-----------------------------------------------------------------------
Function name:	I2C1_ReadData
Input:			Num:total bytes will be write to the I2C
Output:			0=I2C in using; 1=I2C start to write data;2=too many bytes
Description:	 
------------------------------------------------------------------------*/
U8 I2C1_ReadData(U8 SlaveAddr,U8 *BufferP,U8 Num)
{
	U8 r;
	
	r = I2C_ReadData(I2C_1,SlaveAddr,BufferP,Num);

	if(r)	//new data get
		return SUCCESS;
	else
		return !SUCCESS;
}
/*-----------------------------------------------------------------------
Function name:	I2C2_IRQHandler
Input:			N/A
Output:			N/A
Description:	*Deals with master read and master write only 
------------------------------------------------------------------------*/
void I2C2_IRQHandler(void)
{
	if(I2C_Data[I2C_2].rw)		//read
		IRQ_I2C_Master_Read(I2C_2);
	else						//write
		IRQ_I2C_Master_Write(I2C_2);
}
/*-----------------------------------------------------------------------
Function name:	I2C2_WriteData
Input:			SlaveAddr; BufferP:first write data`s pointer; Num:total bytes will be write to the I2C
Output:			0=I2C in using; 1=I2C start to write data; 2=too many bytes
Description:	 
------------------------------------------------------------------------*/
U8 I2C2_WriteData(U8 SlaveAddr,U8 *BufferP,U8 Num)
{
	I2C_WriteData(I2C_2,SlaveAddr,BufferP,Num);
	return SUCCESS;//for temp
}
/*-----------------------------------------------------------------------
Function name:	I2C2_ReadData
Input:			Num:total bytes will be write to the I2C
Output:			0=I2C in using; 1=I2C start to write data;2=too many bytes
Description:	 	Start + Slave(R) + Data + Stop
------------------------------------------------------------------------*/
U8 I2C2_ReadData(U8 SlaveAddr,U8 *BufferP,U8 Num)
{
	I2C_DATA *pI2C = &I2C_Data[I2C_2];
	
	pI2C->sub_valid = FALSE;
	return I2C_ReadData(I2C_2,SlaveAddr,BufferP,Num);
}

/*-----------------------------------------------------------------------
Function name:	I2C2_ReadData
Input:			Slave addr, sub addr
Output:			0=I2C in using; 1=I2C start to write data;2=too many bytes
Description: 		Start + Slave(W) + Sub + Start + Slave(R) + Data + Stop
------------------------------------------------------------------------*/
U8 I2C2_ReadSubData(U8 SlaveAddr,U8 sub,U8 *BufferP,U8 Num)
{
	I2C_DATA *pI2C = &I2C_Data[I2C_2];

	pI2C->sub_addr = sub;
	pI2C->sub_valid = TRUE;
	return I2C_ReadData(I2C_2,SlaveAddr,BufferP,Num);
}
/*-----------------------------------------------------------------------
Function name:	I2C1_Enable
Input:			N/A
Output:			N/A
Description:	
------------------------------------------------------------------------*/
void I2C1_Enable(void)
{
//	LPC_I2C1->I2CONSET=0x40;
}
/*-----------------------------------------------------------------------
Function name:	I2C1_Disable
Input:			N/A
Output:			N/A
Description:	
------------------------------------------------------------------------*/
void I2C1_Disable(void)
{
//	LPC_I2C1->I2CONCLR=0x40;
}



