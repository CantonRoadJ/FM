/***********************************************************************//**
 * @file		Lcd.c
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
#include <stdarg.h>
/* ---------------------------------------------------------- */
 /*   * 7 segment:
 *
 *            A
 *       ---------
 *   F|\    I|     /| B
        |H\  | J/  |
 *     |   \  | /    |
 *      -G-- --K-
 *  E |    / |\     | C
 *     |M/  | \L  |
        |/    I|  \   |
 *      ---------
 *            D
 *-------------------------------------------------------------*/
const unsigned int tblLC_char_segments[] = {
/*
       A       B       C      D       E       F          
       G       H       I      J       K       L       M
 */
     0x0140, 0x0240, 0x0280, 0x0120, 0x0080, 0x0040,
     0x0008, 0x0004, 0x0180, 0x0104, 0x0108, 0x0102, 0x0002,           /* Digtal 1  */

     0x0304, 0x0404, 0x0408, 0x0302, 0x0208, 0x0204,
     0x0380, 0x0340, 0x0308, 0x0440, 0x0480, 0x0420, 0x0320,           /* Digtal 2  */

     0x0640, 0x0740, 0x0780, 0x0620, 0x0580, 0x0540,
     0x0508, 0x0504, 0x0680, 0x0604, 0x0608, 0x0602, 0x0502,           /* Digtal 3  */

     0x0804, 0x0904, 0x0908, 0x0802, 0x0708, 0x0704,
     0x0880, 0x0840, 0x0808, 0x0940, 0x0980, 0x0920, 0x0820,           /* Digtal 4  */

     0x0b40, 0x0c40, 0x0c80, 0x0b20, 0x0a80, 0x0a40,
     0x0a08, 0x0a04, 0x0b80, 0x0b04, 0x0b08, 0x0b02, 0x0a02,           /* Digtal 5 */

     0x0d04, 0x0e04, 0x0e08, 0x0d02, 0x0c08, 0x0c04,
     0x0d80, 0x0d40, 0x0d08, 0x0e40, 0x0e80, 0x0e20, 0x0d20,           /* Digtal 6 */

     0x1040, 0x1140, 0x1180, 0x1020, 0x0f80, 0x0f40,
     0x0f08, 0x0f04, 0x1080, 0x1004, 0x1008, 0x1002, 0x0f02,           /* Digtal 7 */

     0x1204, 0x1304, 0x1308, 0x1202, 0x1108, 0x1104,
     0x1280, 0x1240, 0x1208, 0x1340, 0x1380, 0x1320, 0x1220,            /* Digtal 8  */   

     0x0202, 0x0520, 0x0a20, 0x1120, 0x1102, 0x1302,
     0x0702, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x000,            /* Digtal 9  */   
};

#define	SEG_A		0x0001
#define	SEG_B		0x0002
#define	SEG_C		0x0004
#define	SEG_D		0x0008
#define	SEG_E		0x0010
#define	SEG_F		0x0020
#define	SEG_G		0x0040
#define	SEG_H		0x0080
#define	SEG_I		0x0100
#define	SEG_J		0x0200
#define	SEG_K		0x0400
#define	SEG_L		0x0800
#define	SEG_M		0x1000

/*ascii code display table*/
const unsigned int  tblLC_ASCII_SEGMENT[]={
	0x0000,	//20 " " 
	SEG_I,	//21 "!" 
	SEG_G|SEG_H,	//22 """ 
	0X0000,	//23 "#" 
	0x0000,	//24 "$" 
	0x0000,	//25 "%" 
	0x0000,	//26 "&" 
	SEG_J, //27 "'" 
	SEG_J|SEG_L,	//28 "(" 
	SEG_H|SEG_M,	//29 ")" 
	SEG_H|SEG_J|SEG_L|SEG_M,	//2A "*" 
	SEG_I|SEG_G|SEG_K,	//2B "+" 
	0x0000,	//2C " " 
	SEG_G|SEG_K,	//2D "-" 
	0x0000,	//2E "." 
	SEG_J|SEG_M,	//2F "/" 

	SEG_A | SEG_B | SEG_C | SEG_D | SEG_E | SEG_F,	//30 "0"	
	SEG_B | SEG_C,	//31 "1" 
	SEG_A | SEG_B | SEG_G| SEG_E | SEG_D|SEG_K,	//32 "2"	
	SEG_A | SEG_B | SEG_G| SEG_C | SEG_D|SEG_K,	//33 "3"	
	SEG_F | SEG_G| SEG_B | SEG_C|SEG_K,	//34 "4"	
	SEG_A | SEG_F | SEG_C | SEG_D  | SEG_G|SEG_K,	//35 "5"	
	SEG_A | SEG_F | SEG_E | SEG_G | SEG_C | SEG_D|SEG_K,	//36 "6" 
	SEG_A | SEG_B | SEG_C,	//37 "7" 
	SEG_A | SEG_B | SEG_C | SEG_D | SEG_E | SEG_F | SEG_G|SEG_K,	//38 "8" 
	SEG_A | SEG_B | SEG_C | SEG_D | SEG_F | SEG_G|SEG_K,	//39 "9" 
	0x0000,	//3A ":" 
	SEG_G|SEG_M,	//3B ";" 
	SEG_J|SEG_L,	//3C "<" 
	SEG_G|SEG_K|SEG_D,	//3D "=" 
	SEG_H|SEG_M,	//3E ">" 
	0x0000,	//3F " " 

	0x0000,	//40 "@" 
	SEG_F | SEG_E | SEG_A | SEG_B | SEG_C | SEG_G|SEG_K,	//41 "A" 	
	SEG_A | SEG_J | SEG_L | SEG_D | SEG_E | SEG_F | SEG_G,//42 "B" 
	SEG_A | SEG_F | SEG_E | SEG_D,	//43 "C" 
	SEG_A | SEG_B | SEG_C | SEG_D | SEG_E|SEG_F,	//44 "D" 
	SEG_F | SEG_E | SEG_A | SEG_D | SEG_G|SEG_K,	//45 "E" 
	SEG_F | SEG_E | SEG_A | SEG_G|SEG_K,	//46 "F" 
	SEG_A | SEG_F | SEG_E | SEG_C | SEG_D | SEG_K,	//47 "G" 
	SEG_F | SEG_E | SEG_G| SEG_B | SEG_C|SEG_K,	//48 "H" 
	SEG_I,	//49 "I" 
	SEG_B | SEG_C | SEG_D,	//4A "J" 
	SEG_F | SEG_E | SEG_L | SEG_J,	//4B "K"
	SEG_F | SEG_E | SEG_D,	//4C "L" 
	SEG_B | SEG_C | SEG_E | SEG_F | SEG_H | SEG_J,	//4D "M" 
	SEG_B | SEG_C | SEG_E | SEG_F | SEG_H | SEG_L,	//4E "N" 
	SEG_A | SEG_B | SEG_C | SEG_D | SEG_E | SEG_F,	//4F "O" 

	SEG_F | SEG_E | SEG_A | SEG_B | SEG_G |SEG_K,	//50 "P" 
	SEG_A | SEG_B | SEG_C | SEG_D | SEG_E | SEG_F | SEG_L,	//51 "Q" 
	SEG_A | SEG_B | SEG_E | SEG_F | SEG_G| SEG_K|SEG_L,	//52 "R" 
	SEG_A | SEG_F | SEG_G| SEG_K|SEG_C | SEG_D,	//53 "S" 
	SEG_A | SEG_I,	//54 "T"
	SEG_F | SEG_E | SEG_D | SEG_C | SEG_B,	//55 "U" 
	SEG_F | SEG_E | SEG_M | SEG_J,	//56 "V" 
	SEG_F | SEG_E | SEG_L | SEG_M | SEG_B | SEG_C,	//57 "W" 
	SEG_M | SEG_L | SEG_J | SEG_H,	//58 "X" 
	SEG_F | SEG_G|SEG_K| SEG_B | SEG_C | SEG_D,	//59 "Y" 
	SEG_A | SEG_D | SEG_J | SEG_M,	//5A "Z" 
	SEG_A|SEG_E|SEG_F|SEG_D,	//5B "[" 
	0x0000,	//5C " " 
	SEG_A|SEG_B|SEG_C|SEG_D,	//5D "]" 
	0x0000,	//5E "^" 
	SEG_D,	//5F "_" 

	SEG_H,	//60 "`" 
	SEG_F | SEG_E | SEG_A | SEG_B | SEG_C | SEG_G|SEG_K,	//61 "a"
	SEG_F | SEG_E | SEG_G|SEG_K| SEG_C | SEG_D,	//62 "b" 
	SEG_K|SEG_G|SEG_E|SEG_D,	//63 "c" <- c 
	SEG_G|SEG_K| SEG_E | SEG_D | SEG_B | SEG_C,	//64 "d" <- 
	SEG_G|SEG_K| SEG_F |SEG_D | SEG_E | SEG_B | SEG_A,	//65 "e" <- 
	SEG_F | SEG_E | SEG_A | SEG_G|SEG_K,	//66 "f" <- 
	SEG_A | SEG_F | SEG_G|SEG_K| SEG_B | SEG_C | SEG_D,	//67 "g" <- 
	SEG_F | SEG_E | SEG_G| SEG_K| SEG_C,	//68 "h" <- 
	SEG_I,	//69 "i" <- 
	SEG_B|SEG_C|SEG_D,	//6A "j" <- 
	SEG_F | SEG_E | SEG_L | SEG_J,	//6B "k" <-
	SEG_F | SEG_E | SEG_D,	//6C "l"  <-
	SEG_B | SEG_C | SEG_E | SEG_F | SEG_H | SEG_J,	//6D "m"  <-
	SEG_F | SEG_E | SEG_A | SEG_B | SEG_C,	//6E "n"  <-
	SEG_C | SEG_D | SEG_E | SEG_G|SEG_K,	//6F "o"  <-

	SEG_F | SEG_E | SEG_A | SEG_B | SEG_G|SEG_K,	//70 "p" 
	SEG_A | SEG_F | SEG_G|SEG_K| SEG_B | SEG_C,	//71 "q" 
	SEG_E | SEG_G,	//72 "r" 
	SEG_A | SEG_F | SEG_G|SEG_K| SEG_C | SEG_D,	//73 "s" 
	SEG_E | SEG_F | SEG_G|SEG_K | SEG_D,	//74 "t"
	SEG_D|SEG_C|SEG_E,	//75 "u" 
	SEG_F | SEG_E | SEG_M | SEG_J,	//76 "v" 
	SEG_F | SEG_E | SEG_L | SEG_M | SEG_B | SEG_C,	//77 "w" 
	SEG_M | SEG_L | SEG_J | SEG_H,	//78 "x" 
	SEG_F | SEG_G|SEG_K| SEG_B | SEG_C | SEG_D,	//79 "y" 
	SEG_A | SEG_D | SEG_J | SEG_M,	//7A "z"  
	0x0000,	//7B "{" 
	SEG_E|SEG_F,	//7C "|" 
	0x0000,	//7D "}" 
	0x0000,	//7E "~" 
	0x0000,	//7F " " 

	0xffff	
} ;
/*display buffer*/
unsigned  char   ShadowRam[LCD_MAX_BUF];





/*-----------------------------------------------------------------------
Function name:	Hex2Bcd
Input:			HEX_data: hex data                          
Output:			BCD code 
Description:	
       This routine takes change hex data to BCD code 
	   e.g:
	          input:120
		  output: 0x0120  
------------------------------------------------------------------------*/
unsigned int Hex2Bcd( unsigned int  HEX_data )
{
	unsigned int   BCD_data = 0;

	if ( HEX_data >= 1000000 ) 
	{
		HEX_data = HEX_data % 1000000;
	}
	if ( HEX_data >= 100000 ) {
		BCD_data = ( HEX_data / 100000 ) * 0x100000;
		HEX_data = HEX_data % 100000;
	}
	if ( HEX_data >= 10000 )        
	{
		BCD_data += ( HEX_data / 10000 ) * 0x10000;
		HEX_data = HEX_data % 10000;
	}
	if ( HEX_data >= 1000 ) {
		BCD_data += ( HEX_data / 1000 ) * 0x1000;
		HEX_data = HEX_data % 1000;
	}
	if ( HEX_data >= 100 ) {
		BCD_data += ( HEX_data / 100 ) * 0x100;
		HEX_data = HEX_data % 100;
	}

	BCD_data += ( HEX_data / 10 ) * 0x10;
	BCD_data += HEX_data % 10;
	return BCD_data;
}
/*-----------------------------------------------------------------------
Function name:	Hex2Ascii
Input:			datHEX: hex data     strASC:Poiter to array that save the output ascii;                    
Output:			N/A 
Description:	
       This routine takes change hex BCD to ascii   
	   e.g:
	     	        datHEX=0x20
			strASC=" 20"
------------------------------------------------------------------------*/ 
void Hex2Ascii(unsigned char  datHEX , unsigned char *strASC ) 
{
	unsigned char  bitMSB;
	unsigned char  bitLSB;

	bitMSB = (datHEX  & 0xf0) >> 4;
	bitLSB =  datHEX  & 0x0f;
	if (bitMSB < 10 ){
		*strASC++ =  (unsigned char) (bitMSB + '0') ;
	}
	else{
		*strASC++ =  (unsigned char) (bitMSB - 10 + 'A') ;
	}
	if (bitLSB < 10 ){
		*strASC++ =  (unsigned char) (bitLSB + '0') ;
	}
	else{
		*strASC++ =  (unsigned char) (bitLSB - 10 + 'A') ;
	}
	*strASC   =  '\0' ;

	return ;
}
/*-----------------------------------------------------------------------
Function name:	Asii2Segment
Input:			ascii                
Output:			segments  
Description:	
       This routine get char's segments that will display in LCD   
------------------------------------------------------------------------*/
unsigned int Asii2Segment( unsigned char ascii ) 
{
	unsigned char Data=ascii;
	unsigned int Segment;
	switch ( Data )
	{
		case 0x00:
			Segment = tblLC_ASCII_SEGMENT[Data];
			break;
		default:
			if ( Data < 0x20 || Data >= 0x80 ) 
			{
				Data = '*';
			}
			Data -= 0x20;
			Segment =tblLC_ASCII_SEGMENT[Data];
	}
	return Segment;
}
/*-----------------------------------------------------------------------
Function name:	Update_ShadowRam
Input:			*pSeg:poiter to tblLC_char_segments,  char_segments:char's char_segments             
Output:			N/A  
Description:	
               This routine update display data in ShadowRam 
------------------------------------------------------------------------*/
void Update_ShadowRam(unsigned int *pSeg,  unsigned int char_segments)
{
	unsigned char i,B1;
	unsigned int *seg=pSeg;
	unsigned int temp_16 = char_segments;

	for (i = 0; i < MAX_SEG; ++i) 
	{
		B1 = (unsigned char) (temp_16 & 0x0001);
		LCD_clear_lite_anode(*seg, B1);
		++seg;
		temp_16 >>= 1;
	}
}
/*-----------------------------------------------------------------------
Function name:	FillRam
Input:			*pAddr:poiter to Ram address,  data:data will be filled ram        
                 count :the count of be filled     
Output:			N/A  
Description:	
               This routine fill ram 
------------------------------------------------------------------------*/
void FillRam(unsigned char *pAddr,unsigned char data,unsigned char count)
{
	unsigned char i; 
	for (i=0;i<count;++i) {
		*pAddr = data;
		++pAddr;
	}
}
/*-----------------------------------------------------------------------
Function name:	LCD_clear_lite_anode
Input:			anode:  position of the icon
                lite£º0-clear 1-lite 2-complement
                
Output:			N/A
Description:	
       This routine takes a G/P position and lite/clear the corresponding anode.    
------------------------------------------------------------------------*/
void LCD_clear_lite_anode(unsigned int anode, unsigned char lite)
{
	unsigned char *pRam;	
	unsigned char TempL = (unsigned char)anode;
	unsigned char TempH=(unsigned char)(anode>>8);

	pRam = ShadowRam;

	pRam += TempH;
	if (lite == 2)
		*pRam ^= TempL;
	else 
	{
		if (lite) 
			*pRam |= TempL;
		else 
		{
			TempL ^= 0xff;
			*pRam &= TempL;
		}
	}
}
/*-----------------------------------------------------------------------
Function name:	LCD_ShowChar
Input:			pos :position in LCD   char_ascii:char that will display in LCD
Output:			N/A  
Description:	
               This routine show a char in fixed position
			   note:this routine do not send display data to LCD driver, 
			   just update display data in  ShadowRam 
------------------------------------------------------------------------*/
void LCD_ShowChar(unsigned char pos,unsigned char char_ascii)
{ 
	unsigned char ramAddr;
	unsigned int *ptr;
	unsigned int char_segments = Asii2Segment(char_ascii);
	if(pos>9)
		return;
	ramAddr = (unsigned char) (pos*MAX_SEG);
	ptr = (unsigned int *) (tblLC_char_segments + ramAddr);
	Update_ShadowRam(ptr, char_segments);//updata data in shadowram

}
#define NUM_MAX_WIDTH  6

/*-----------------------------------------------------------------------
Function name:	LCD_ShowNumber
Input:			pos :position in LCD   Num:number that will display in LCD 
Output:			N/A  
Description:	
               This routine show Number in fixed position
			   note:this routine do not send display data to LCD driver, 
			   just update display data in  ShadowRam 
------------------------------------------------------------------------*/
void LCD_ShowNumber(unsigned char Pos, unsigned int Num,unsigned char BitWidth)
{
	unsigned char ascii[NUM_MAX_WIDTH];
	int i,j;
	unsigned int msgdata;
	unsigned char position = Pos;

	if(BitWidth>NUM_MAX_WIDTH)
		BitWidth=NUM_MAX_WIDTH;
	/* track/chapter nums are in hex */
	msgdata = Hex2Bcd(Num); 
	/*Hex number to ascii code*/
	Hex2Ascii( (unsigned char)( ( msgdata >> 16 ) & 0xFF ) , ascii );
	Hex2Ascii( (unsigned char)( ( msgdata >> 8 ) & 0xFF ) , &ascii[2] );
	Hex2Ascii( (unsigned char)( msgdata & 0xFF ) , &ascii[4] );

	for(i=0;i<NUM_MAX_WIDTH-BitWidth;i++)
	{
		for(j=0;j<NUM_MAX_WIDTH-1-i;j++)
			ascii[j]=ascii[j+1];
	}
	/*Display ascii code*/
	for(i=0;i<BitWidth;i++) 
	{	 
		LCD_ShowChar(position,ascii[i]);
		position++;
	}
	return;
}

/*-----------------------------------------------------------------------
Function name:	LCD_ShowStrings
Input:			pos :position in LCD   
                pStr:poiter to Strings which display in LCD,this strings must with end '\0'
Output:			N/A  
Description:	
               This routine show stings in fixed position
			   note:this routine do not send display data to LCD driver, 
			   just update display data in  ShadowRam 
------------------------------------------------------------------------*/
void LCD_ShowStrings(unsigned char Pos, unsigned char *pStr)
{
	unsigned char *pstring=pStr;
	unsigned char position = Pos;

	while(*pstring!='\0')
	{/*string not end*/	 
		LCD_ShowChar(position,*pstring);
		position++;
		pstring++;
	}
}
/*-----------------------------------------------------------------------
Function name:	LCD_Blank
Input:			pos :position in LCD  
Output:			N/A  
Description:	
               This routine blank lcd			  
------------------------------------------------------------------------*/
void LCD_Blank(unsigned char pos)
{
	unsigned int *ptr;

	if(pos==BLANK_ALL) 
	{/*clear display buffer*/
		FillRam(ShadowRam,0x00,LCD_MAX_BUF);
	}
	else 
	{/*blank lcd some position*/
		pos= (unsigned char)(pos*MAX_SEG);
		ptr = (unsigned int *)(tblLC_char_segments + pos);
		Update_ShadowRam(ptr, 0x00);
	}
}

