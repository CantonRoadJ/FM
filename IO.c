/***********************************************************************//**
 * @file		IO.c
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

volatile GPIOValue Port0Data __attribute__((at(0x2009c014)));
volatile GPIOValue Port1Data __attribute__((at(0x2009c034)));
volatile GPIOValue Port2Data __attribute__((at(0x2009c054)));
volatile GPIOValue Port3Data __attribute__((at(0x2009c074)));
volatile GPIOValue Port4Data __attribute__((at(0x2009c094)));

/*-----------------------------------------------------------------------
Function name:	Port_Init
Input:			N/A
Output:			N/A
Description: 
------------------------------------------------------------------------*/
void Port_Init(void)
{
#if 0
//bit		31-30	29-28	27-26	25-24	23-22	21-20	19-18	17-16	15-14	13-12	11-10	9-8		7-6		5-4		3-2		1-0
//			P0.15	P0.14	P0.13	P0.12	P0.11	P0.10	P0.09	P0.08	P0.07	P0.06	P0.05	P0.04	P0.03	P0.02	P0.01	P0.00
//PINSEL	SPI_SCK						  	SCL2	SDA2  I2STXSDA I2STXWS I2STXCLK GPIO					RXD0	TXD0	SCL1	SDA1
//			11		xx	 	xx		xx		10		10		01		01		01		00		xx		xx		01		01		11		11
//PINMODE	PU								NoP		NoP		PU		PU		PU		NoP						PU		PU		NoP		NoP
//			00		xx		xx		xx		10		10		00		00		00		10		xx		xx		00		00		10		10
//FIODIR																			IN
//			x		x		x		x		x		x		x		x		x		x		x		x		x		x		x		x
	LPC_PINCON->PINSEL0=0xC0A5405F;
	LPC_PINCON->PINMODE0=0x00A0200A;
//bit		31-30	29-28	27-26	25-24	23-22	21-20	19-18	17-16	15-14	13-12	11-10	9-8		7-6		5-4		3-2		1-0	
//			P0.31	P0.30	P0.29	P0.28	P0.27	P0.26	P0.25	P0.24	P0.23	P0.22	P0.21	P0.20	P0.19	P0.18	P0.17	P0.16
//PINSEL			USBD-	USBD+					AD0.3	AD0.2					GPIO						  SPI_MOSI SPI_MISO SPI_SSEL
//			xx		01		01		xx		xx		01		01		xx		xx		00		xx		xx		xx		11		11		11
//PINMODE																			PU								PU		PU		PU
//			xx						xx		xx		xx		xx		xx		xx		00		xx		xx		xx		00		00		00
//FIODIR																			IN
//			x		x		x		x		x		x		x		x		x		0		x		x		x		x		x		x
	LPC_PINCON->PINSEL1=0x1414003F;
	LPC_PINCON->PINMODE1=0x00000000;
	LPC_GPIO0->FIODIR=0x00000000;

//bit		31-30	29-28	27-26	25-24	23-22	21-20	19-18	17-16	15-14	13-12	11-10	9-8		7-6		5-4		3-2		1-0
//			P1.15	P1.14	P1.13	P1.12	P1.11	P1.10	P1.09	P1.08	P1.07	P1.06	P1.05	P1.04	P1.03	P1.02	P1.01	P1.00
//PINSEL	GPIO	GPIO									GPIO	GPIO
//			00		00		xx		xx		xx		xx		00		00		xx		xx		xx		xx		xx		xx		xx		xx
//PINMODE	NoP		RE/1								   	NoP/1	NoP/1
//			10		01		xx		xx		xx		xx		10		10		xx		xx		xx		xx		xx		xx		xx		xx
//FIODIR	IN		OUT										OUT		OUT
// 			x		1		x		x		x		x		1		1		x		x		x		x		x		x		x		x
	LPC_PINCON->PINSEL2=0x00000000;	
	LPC_PINCON->PINMODE2=0x900A0000; 
//bit		31-30	29-28	27-26	25-24	23-22	21-20	19-18	17-16	15-14	13-12	11-10	9-8		7-6		5-4		3-2		1-0	
//			P1.31	P1.30	P1.29	P1.28	P1.27	P1.26	P1.25	P1.24	P1.23	P1.22	P1.21	P1.20	P1.19	P1.18	P1.17	P1.16
//PINSEL	AD0.5	GPIO	GPIO					GPIO			GPIO  QEI_MCI0 USBPWRD 		  QEI_MCI0			GPIO
//			11		00		00		xx		xx		00		xx		00		01		10		xx		01		xx		00		xx		xx
//PINMODE			PuL		NoP						NoP			   NoP										    NoP
//			xx		11		10		xx		xx		10		xx		10		xx		xx		xx		xx		xx		10		xx		xx
//FIODIR			OUT		OUT						OUT				OUT												IN
// 			x		1		1		x		x		1		x		1		x		x		x		x		x		x		x		x
//Default Value		0		1						1				1
	LPC_PINCON->PINSEL3=0xC0006100;
	LPC_PINCON->PINMODE3=0x38220020;
	LPC_GPIO1->FIODIR=0x65004300;
	LPC_GPIO1->FIOSET=0x25004300;
	LPC_GPIO1->FIOCLR=0x40000000;
//bit		31-30	29-28	27-26	25-24	23-22	21-20	19-18	17-16	15-14	13-12	11-10	9-8		7-6		5-4		3-2		1-0
//			P2.15	P2.14	P2.13	P2.12	P2.11	P2.10	P2.09	P2.08	P2.07	P2.06	P2.05	P2.04	P2.03	P2.02	P2.01	P2.00
//PINSEL											EINT0   GPIO  CAN2_TX  CAN2_RX					GPIO	GPIO
//			xx		xx		xx		xx		xx		01		00		01		01		xx		xx		00		00		xx		xx		xx
//PINMODE												   	PuL/0									NoP/1	NoP
//			xx		xx		xx		xx		xx		xx		00			   			xx		xx		10		10		xx		xx		xx
//FIODIR 													OUT										OUT		IN
//			x		x		x		x		x		x		1		x		x		x		x		1		x		x		x		x
	LPC_PINCON->PINSEL4=0x00114000;	 
	LPC_PINCON->PINMODE4=0x00000280;
	LPC_GPIO2->FIODIR=0x00000210;
    LPC_GPIO2->FIOSET=0x00000010;
#endif
}

