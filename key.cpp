/***********************************************************************//**
 * @file		key.c
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

#define End_of_ADC     LPC_ADC->ADGDR&0x80000000
#define ADVALUE_33V	160

static U32 PREVIOUS_KEY_CODE;
static U32 PREVIOUS_PROCESS_KEY;

static UCHAR ADC_Channel;
static UCHAR SWC_Value[3];

/*resisters lader ,adc value define*/
const KEY_ADCVAL	 SWCKey_6_Interval[] ={  {0,10},{15,40},{45,70},{75,90},{105,120},{135,150}};
/*resisters lader ,adc value define*/
const KEY_ADCVAL	 SWCKey_4_Interval[] ={{0,10},{15,40},{55,70},{90,106}};

typedef struct{
	const KEY_ADCVAL *tab;	//tab of ADC limits
	U8 key_num;		//how many keys in this ADC channel
	U8 index;			//UI index of key
}KEY_ADC_VAL;
static const KEY_ADC_VAL KeyTab[] = {
	{SWCKey_4_Interval, NELEMS(SWCKey_4_Interval),	KC00},
	{SWCKey_6_Interval, NELEMS(SWCKey_6_Interval),	KC10},
	{SWCKey_6_Interval, NELEMS(SWCKey_6_Interval),	KC20},
};
/*-----------------------------------------------------------------------
Function name:	AdcKey_Init
Input:			N/A
Output:			N/A
Description: Initialize Adc Key	
------------------------------------------------------------------------*/
void AdcKey_Init(void)
{
#if 0
	/* Enable CLOCK into ADC controller */
	LPC_SC -> PCONP |= (1 << 12);

	/*  ADC inputs, AD0.2,AD0.3,AD0.5 */
	LPC_PINCON -> PINSEL1 &=~0x003C0000;	/* P0.25,P0.26, AS A0.2 A0.3, function 01 */
	LPC_PINCON -> PINSEL1 |= 0x00140000;
	LPC_PINCON->PINMODE1&=~0x003C0000;		 //mode =0x00
	LPC_PINCON->PINMODE_OD0&=~(3<<25);		   //no open drain

	LPC_PINCON -> PINSEL3 |= 0xC0000000;	/* P1.31, A0.5, function 11 */
	LPC_PINCON->PINMODE3&=~0xC0000000;		 //mode =0x00
	LPC_PINCON->PINMODE_OD1&=0x7FFFFFFF;		   //no open drain


	LPC_ADC -> ADCR = ( 1 << 2 ) | 	/* SEL=1,select channel 2 on ADC0 */
	( /*( 25000 / ADC_CLK_KHZ - 1 )*/3 << 8 ) |  /* CLKDIV = Fpclk / ADC_Clk - 1 */ 			  
	( 0 << 16 ) | 		/* BURST = 0, no BURST, software controlled */
	( 1 << 21 ) |  		/* PDN = 1, normal operation */
	(1 << 24 ) |  		/* START = 0 A/D conversion start */
	( 0 << 27 );		/* EDGE = 0 (CAP/MAT singal falling,trigger A/D conversion) */ 

	ADC_Channel=AD_SWC0;	/*set channel to the first*/
#endif

}

/*-----------------------------------------------------------------------
Function name:	EncodeKey_Init
Input:			N/A
Output:			N/A
Description: Initialize EncodeKey 	
------------------------------------------------------------------------*/
void EncodeKey_Init(void)
{
#if 0
	UINT curPos;

	LPC_PINCON -> PINSEL3 &=~((3<<8)|(3<<14));	  //p1.20,p1.23 set as QEI
	LPC_PINCON -> PINSEL3|=(1<<8)|(1<<14);

	/*  QEI configration
	Set up clock and power for QEI module */
	LPC_SC->PCONP|=(1<<18); 

	/* As default, peripheral clock for QEI module
	* is set to FCCLK / 2 */
	LPC_SC->PCLKSEL1 &= ~(0x03);
	LPC_SC->PCLKSEL1 |= (0x02);

	/*Reset all remaining value in QEI peripheral*/
	LPC_QEI->QEICON = 0x0f;
	LPC_QEI->QEIMAXPOS = 0xFFFFFFFF;
	curPos=LPC_QEI->QEIPOS;
	if(curPos>=4)
	{
		LPC_QEI->CMPOS0 = curPos-4;
	}
	else
	{
	    	LPC_QEI->CMPOS0 =0xFFFFFFFF-3+curPos ;
	} 

	LPC_QEI->CMPOS1 = curPos+4;

	LPC_QEI->CMPOS2 = 0x00;
	LPC_QEI->INXCMP = 0x00;
	LPC_QEI->QEILOAD = 0x00;
	LPC_QEI->VELCOMP = 0x00;
	LPC_QEI->FILTER = 0xff;
	/*Disable all Interrupt*/
	LPC_QEI->QEIIEC = 0x1FFF;
	/* Clear all Interrupt pending*/
	LPC_QEI->QEICLR = 0x1FFF;
	/* Set QEI configuration value corresponding to its setting up value*/
	LPC_QEI->QEICONF = 0x04; //DIRIV 0,SIGMODE 0,CAPMODE=4X,INVINX=0

	/*Set interrupt enable*/
	LPC_QEI->QEIIES = ((1<<6)|(1<<7));	 //
	/*preemption = 1, sub-priority = 1 */
	NVIC_SetPriority(QEI_IRQn, ((0x01<<3)|0x01));
	/* Enable interrupt for QEI  */
	NVIC_EnableIRQ(QEI_IRQn);

#endif

}

static UCHAR EncRightCount=0;
static UCHAR EncLeftCount=0;
static S8 EncCode;
/*-----------------------------------------------------------------------
Function name:		ScanEncoder	  
Input:			
Output:		
Description: 	 calculate EncCode value
------------------------------------------------------------------------*/
void ScanEncoder(void)
 {
	EncCode=0x00;
	
	if(EncRightCount ||EncLeftCount)
	{
		EncCode = EncRightCount - EncLeftCount;	
		EncRightCount=0;
		EncLeftCount=0;		 	  
	}
 }
/*-----------------------------------------------------------------------
Function name:		GetWheelKey	  
Input:	
		
Output:		<0 : left, >0 : right,  abs = counter	
Description: 	 
------------------------------------------------------------------------*/
S8 GetWheelKey(void)
{
	return	EncCode;
}

/*-----------------------------------------------------------------------
Function name:	PwrKey_Init
Input:			N/A
Output:			N/A
Description: Initialize power key 	
------------------------------------------------------------------------*/
void PwrKey_Init(void)
{
	/*pwr key init*/
#if 0
	LPC_PINCON->PINSEL3&=~0x00000030;//p1.18 as gpio
	LPC_PINCON->PINMODE3&=~0x00000030;//pull_up enable
	LPC_GPIO1->FIODIR&=~0x000040000;//set p1.18 input
#endif
}

/*-----------------------------------------------------------------------
Function name:	Power_Key
Input:			N/A
Output:			N/A
Description:  power key detect ,poll every 2ms
------------------------------------------------------------------------*/
static void Power_Key(void)
{
 #if 0
	if(Curr_Work_Mode==GUI)
	{
	    	return;
	}
	if (PWR_KeyPin)			// key is not pressed
	{
		PowerKeyCnt=10;
		if (F_PowerKey_Buf)
		{
			F_PowerKey_Buf = 0;
			F_PowerKey=1; 
		}
	}
	else
	{
		if (PowerKeyCnt !=0 ) 
		{
			PowerKeyCnt-=1;
			if (PowerKeyCnt==0) 
			{
				F_PowerKey_Buf=1; 
			}	
		}	
	}
#endif

}
/*-----------------------------------------------------------------------
Function name:	Proc_Long_Short_Key
Input:			N/A
Output:			N/A
Description: process long short key 	
------------------------------------------------------------------------*/
static void Proc_Long_Short_Key(U32 CURRENT_PROCESS_KEY)
{
        /*key pressed*/
	if (CURRENT_PROCESS_KEY != No_Key)
	{/*valid key push*/
		if(CURRENT_PROCESS_KEY == PREVIOUS_PROCESS_KEY)
     		{
     			if(KeyTimer == 0x00 && !F_KEYTIMER)	//for the first time
     			{
				F_KEYTIMER=1;
				
     	    			switch(CURRENT_PROCESS_KEY)	//set long press time
				{  
					case  SW_VOL_UP:
	                  		case  SW_VOL_DN: 
						KeyTimer = ONE_SECOND;
						break;

					case SW_SEEKUP:
					case SW_SEEKDN:
						//add to make next long press key
						KeyTimer = F_LONG_PROCESS ? ONE_SECOND : 2*ONE_SECOND;
						break; 
							
					case  SW_MODE:			/*also POWER2*/
					default:
						KeyTimer = 2*ONE_SECOND;
						break;
	     	    		}
     			}

			if(KeyTimer == 0x00){
				KeyCode = CURRENT_PROCESS_KEY | LONGKEY;
				F_LONG_PROCESS = TRUE;
			}
			else
				KeyCode = CURRENT_PROCESS_KEY | PUSHKEY;
		}
	}
        /*key released*/
	else if (PREVIOUS_PROCESS_KEY != No_Key)
	{
		KeyCode = (KeyTimer == 0x00)? PREVIOUS_PROCESS_KEY | LONG_RELEASEKEY : PREVIOUS_PROCESS_KEY | SHORTKEY;

		F_KEYTIMER=0;
		KeyTimer = 0;
		F_LONG_PROCESS = FALSE;
      }
    	
      /*key finished*/
      PREVIOUS_PROCESS_KEY = CURRENT_PROCESS_KEY;
 }


/*-----------------------------------------------------------------------
Function name:	Key_Adc_Read
Input:			N/A
Output:			
Description: Read Adc  at regular
------------------------------------------------------------------------*/
static void Key_Adc_Read(void)
{
#if 0
	U8 ADvalue;
	U32 adgr;

	/* get A/D Data Registers*/
	adgr = *(uint32_t *) ((&LPC_ADC->ADDR0) + ADC_Channel);
	
	/* read result of A/D conversion */
	if (adgr & 0x80000000)
	{
		/*26:24 START*/
     		LPC_ADC -> ADCR &= 0xF8FFFFFF;	/* stop ADC now */   

	       /* End of A/D conversion */
		ADvalue = adgr>>8;			/* 15:4 RESULT, Read the converted value high 8 bits */

		switch(ADC_Channel) 
		{
			case AD_SWC0:			  
			default:
				SWC_Value[0]=	ADvalue;		
				ADC_Channel = AD_SWC1;
				break;
				
			case AD_SWC1:
				SWC_Value[1]=	ADvalue;
				ADC_Channel = AD_SWC2;
			break;
			
			case AD_SWC2:
				SWC_Value[2]=	ADvalue;
				ADC_Channel = AD_SWC0;
			break;
		} 

		LPC_ADC -> ADCR &= 0xFFFFFF00; //NEXT CHANNEL
		LPC_ADC -> ADCR |= bit24 | (1<<ADC_Channel);	//start converte
	}

#endif

}
/*-----------------------------------------------------------------------
Function name:	Key_Proc
Input:			N/A
Output:			
Description: key proc
------------------------------------------------------------------------*/
void Key_Proc(void)
{
	static U32 AdcTimer;
	static U8 KeyFilter;
	
	U16 swcval;
	U8  i,channel;
	U32 CURRENT_KEY_CODE;
	const KEY_ADC_VAL *tab = KeyTab;
	const KEY_ADCVAL *limits;

	Key_Adc_Read();//read ADC every 2ms
	ScanEncoder();//proc Encoder 
	
	if(KeyCode & (SHORTKEY | LONG_RELEASEKEY))
		KeyCode =0;	
	
	if(TimerHasExpired(&AdcTimer))	/*get ADC value every 2ms*/
	{
		TimerSet(&AdcTimer,2);	
		
		Power_Key();	//get the pin every 2ms

		//proc adc key and pwr button
		CURRENT_KEY_CODE=No_Key;

                /*-found valid key*/
		for(channel=0;channel<3;channel++,tab++)	//only 3 ADC channel
		{
			swcval = SWC_Value[channel];

			if(swcval > ADVALUE_33V) continue;

			limits = tab->tab;

			for(i=0;i<tab->key_num;i++,limits++){
				if((swcval >=limits->StartVal) && (swcval <=limits->EndVal))
				{
					CURRENT_KEY_CODE=CURRENT_KEY_CODE<<8;
					CURRENT_KEY_CODE+= (i + tab->index);
					break;
				}
			}
		}
		
                 /*judge key value*/
		if(CURRENT_KEY_CODE == PREVIOUS_KEY_CODE)
		{ /* valid key process */          
			if(++KeyFilter>5) 
			{
				KeyFilter=6;
		    	       Proc_Long_Short_Key(CURRENT_KEY_CODE);
			}
		}
		else
		{
			PREVIOUS_KEY_CODE = CURRENT_KEY_CODE;
			KeyFilter=0;
		}    
	}
}


/*-----------------------------------------------------------------------
Function name:	Key_Init
Input:			N/A
Output:			N/A
Description: Initialize Key	
------------------------------------------------------------------------*/
void Key_Init(void)
{
	/*adc key init*/
	AdcKey_Init();
	/*encoder init*/
	EncodeKey_Init();	
	/*power key init*/
	PwrKey_Init();		  
}

/*----------------------------------------------------------------------
 * @brief		QEI interrupt handler.
 * @param[in]	None
 * @return 		None
 *---------------------------------------------------------------------*/
void QEI_IRQHandler(void)
{   
#if 0
	UINT curPos,IntStatus; 

	IntStatus=LPC_QEI->QEIINTSTAT;
	/*compare pos 0 interrupt*/
	if(IntStatus & bit6)
	{	
		EncLeftCount++; 
	} 
	/*compare pos 1 interrupt*/
	else  if(IntStatus&(1<<7))
	{
		EncRightCount++;	
	}

	/*update compare position reg	*/
	curPos=LPC_QEI->QEIPOS;		
	if(LPC_QEI->QEIPOS>=4)  
	{
		LPC_QEI->CMPOS0 = curPos-4;
	}
	else  
	{
		LPC_QEI->CMPOS0 =0xFFFFFFFF-3+curPos ;
	} 

	LPC_QEI->CMPOS1 = curPos+4;	

	/*clear qei interrupt flag*/
	LPC_QEI->QEICLR = 0x1FFF;

#endif


}

