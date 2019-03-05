/***********************************************************************//**
 * @file		AmpTDF8546.c
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

U8  AmpDiagInfo;

/* for auto detect 8546 iic address*/
U8 Amp8546_IICAddr;
#define TDF8546_ADDR	Amp8546_IICAddr
static const U8  Amp8546_IICAddr_tab[] = {
	0xdc,0xda,0xde,0xd4,
	0xdc,0xda,0xde,0xd4//again for retry
};

/* amplifier init data table*/
unsigned char  tbl_Amp_Init[5]=
{
	/*IDB1 
	D7------ 0: Disable clip detection below 10v,  1:Enable  clip detection below 10v
	D6------ 0: channel 3 clip information on DIAG pin,   1:channel 3 clip information on STB pin
	D5------ 0: channel 1 clip information on DIAG pin,   1:channel 1 clip information on STB pin
	D4------ 0: channel 4 clip information on DIAG pin,   1:channel 4 clip information on STB pin
	D3------ 0: channel 2 clip information on DIAG pin,   1:channel 2 clip information on STB pin
	D2------ 0: disable AC load detection,   1:enable AC Load detection
	D1------ 0: start_up diagnostic disable, 1:start_up diagnostic enable
	D0------ 0: amplifer start not enable,   1:amplifer will start */ 
	
	0x01,

	/*IDB2 
	D7 D6------ 00: clip level detect 2%,  01:clip level detect 5%
	10: clip level detect 10%, 01:disable
	D5------ 0: temperature information on DIAG,   1: no temperature information on DIAG
	D4------ 0: load fault information on DIAG,   1:no load fault information on DIAG
	D3------ null
	D2------ 0: channel 1 and 3 not soft mute,   1:channel 1 and 3 soft mute
	D1------ 0: channel 2 and 4 not soft mute,   1:channel 2and 4 soft mute
	D0------ 0: all amplifer channel not fast mute,   1:fast mute all channel
	*/
	0x40,

	/*IDB3
	D7------ null
	D6------ 0: amplifer channel 1 and 3 gain select 26db,  1:amplifer channel 1 and 3 gain select 16db	  		
	D5------ 0: amplifer channel 2 and 4 gain select 26db,  1:amplifer channel 2 and 4 gain select 16db	
	D4------ 0: temperature warning level is 145c,   1:temperature warning level is 122c
	D3------ 0: channel 3 enable,  1:channel 3 disable
	D2------ 0: channel 1 enable,  1:channel 1 disable
	D1------ 0: channel 4 enable,  1:channel 4 disable
	D0------ 0: channel 2 enable,  1:channel 2 disable*/
	
	0x00,


	/*IDB4
	D7------ 0:SVR capacitor used to filter the common mode voltage,   1:for usage in combination with DC-DC converater
	D6------ 0: active fast mute during shut down via STB,  1:active slow mute during shut down via STB  		
	D5------ 0: 16v over voltage warning not on DIAG pin,  1:16v over voltage warning  on DIAG pin
	D4------ 0: DC load inform on DBX,   1:AC load inform on DBX
	D3------ 
	D2------ 0: line driver mode ,  1:low gain mode
	D1------ 0: AC load detection low measurement,  1:AC load detection high measurement
	D0------ 0: Low Vp Mute set to 5.9V,  1:Low Vp Mute set to 7.5V*/
	
	0x01,


	   /*IDB5
	  D7------ 0: High efficiency diable,   1:High efficiency enable
	  D6------ 0: 4 channels high efficiency mode  1:2*2channel high efficiency mode  		
	  D5------ 
	  D4------ 0: high efficient switch level set to 2 ohm load,   1:high efficient switch level set to 4 ohm load
	  D3------ 
	  D2------ 
	  D1------ 
	  D0------ */
	  
	  0x90,
};

/*-----------------------------------------------------------------------
Function name:	AmpPort_Init
Input:			N/A
Output:			N/A
Description:	init Amp Diagnose information indicate port
------------------------------------------------------------------------*/
 void AmpPort_Init(void)
 {
	//DIAG----P2.3 
	//STB-----P2.4
    //LPC_PINCON -> PINSEL4 &= ~0x000003C0;	/*P2.3,P2.4 pins set as GPIO Function */
    //LPC_PINCON -> PINMODE4&= ~0x000003C0;    /*P2.3,P2.4 Mode set with no pull_up and pull_down*/
    //LPC_PINCON -> PINMODE4|=0x0000028;

    //LPC_GPIO2  ->FIODIR0&=~0x08;			    /*P2.3 DIR set as input*/
    //LPC_GPIO2  ->FIODIR0|=0x10;				/*P2.4 Dir set as output*/
    //LPC_GPIO2  ->FIOSET=0x10;
 }

/*-----------------------------------------------------------------------
Function name:	Amp_DetectAddress
Input:			N/A
Output:			N/A
Description:	auto detect 8546 address by iic
------------------------------------------------------------------------*/
static void Amp_DetectAddress(void)
{
	int i;
	U8 temp[1];

	TDF8546_ADDR = Amp8546_IICAddr_tab[0];

	for(i=0;i<NELEMS(Amp8546_IICAddr_tab);i++){
		if(I2C2_ReadData(Amp8546_IICAddr_tab[i],temp,sizeof(temp)) == sizeof(temp))
		{
			TDF8546_ADDR = Amp8546_IICAddr_tab[i];
			break;
		}
	}
}

/*-----------------------------------------------------------------------
Function name:	Init_Amp
Input:			N/A
Output:			N/A
Description:	init port set,detect  tdf8546 iic address,write init data to tdf8546
------------------------------------------------------------------------*/
void Init_Amp(void)
{ 
	  /*init amp port*/
	 AmpPort_Init();

	 /*detect iic slave address*/
	Amp_DetectAddress();

	 /*send init data to amp*/
	I2C2_WriteData(TDF8546_ADDR,(U8*)tbl_Amp_Init,sizeof(tbl_Amp_Init)/sizeof(U8));
}
/*-----------------------------------------------------------------------
Function name:	AmpMute
Input:			OffOn:AUDIO_ON /AUDIO_OFF
Output:			N/A
Description:	mute on/off
------------------------------------------------------------------------*/
void AmpMute(unsigned char OnOff)
{
	if(OnOff)/*mute on*/
	 {
		tbl_Amp_Init[1]|=0x01; 
	 }
	else/*mute off*/
	{
		tbl_Amp_Init[1]&=~0x01; 
	}

	/*send  data to amp*/
	I2C2_WriteData(TDF8546_ADDR,(U8*)tbl_Amp_Init,sizeof(tbl_Amp_Init)/sizeof(U8));
}


