/***********************************************************************//**
 * @file		debug_frmwrk.h
 * @brief		Contains some utilities that used for debugging through UART
 * @version		2.0
 * @date		21. May. 2010
 * @author		NXP MCU SW Application Team
 *----------------------------------------------------------------------------
 * Software that is described herein is for illustrative purposes only
 * which provides customers with programming information regarding the
 * products. This software is supplied "AS IS" without any warranties.
 * NXP Semiconductors assumes no responsibility or liability for the
 * use of the software, conveys no license or title under any patent,
 * copyright, or mask work right to the product. NXP Semiconductors
 * reserves the right to make changes in the software without
 * notification. NXP Semiconductors also make no representation or
 * warranty that such application will be suitable for the specified
 * use without further testing or modification.
 **********************************************************************/

#ifndef DEBUG_FRMWRK_H_
#define DEBUG_FRMWRK_H_


#include "Uart.h"

#define USED_UART_DEBUG_PORT	0

#if (USED_UART_DEBUG_PORT==0)
#define DEBUG_UART_PORT	((LPC_UART_TypeDef *)LPC_UART0)
#elif (USED_UART_DEBUG_PORT==1)
#define DEBUG_UART_PORT	((LPC_UART_TypeDef *)LPC_UART1)
#endif

#define _DBG(x)	 	_db_msg((LPC_UART_TypeDef *)DEBUG_UART_PORT, x)
#define _DBG_(x)	_db_msg_((LPC_UART_TypeDef *)DEBUG_UART_PORT, x)
#define _DBC(x)	 	_db_char((LPC_UART_TypeDef *)DEBUG_UART_PORT, x)
#define _DBD(x)	 	_db_dec((LPC_UART_TypeDef *)DEBUG_UART_PORT, x)
#define _DBD16(x)	 _db_dec_16((LPC_UART_TypeDef *)DEBUG_UART_PORT, x)
#define _DBD32(x)	 _db_dec_32((LPC_UART_TypeDef *)DEBUG_UART_PORT, x)
#define _DBH(x)	 	_db_hex((LPC_UART_TypeDef *)DEBUG_UART_PORT, x)
#define _DBH16(x)	 _db_hex_16((LPC_UART_TypeDef *)DEBUG_UART_PORT, x)
#define _DBH32(x)	 _db_hex_32((LPC_UART_TypeDef *)DEBUG_UART_PORT, x)
#define _DG			_db_get_char((LPC_UART_TypeDef *)DEBUG_UART_PORT)
//void  _printf (const  char *format, ...);

extern void (*_db_msg)(LPC_UART_TypeDef *UARTx, const void *s);
extern void (*_db_msg_)(LPC_UART_TypeDef *UARTx, const void *s);
extern void (*_db_char)(LPC_UART_TypeDef *UARTx, uint8_t ch);
extern void (*_db_dec)(LPC_UART_TypeDef *UARTx, uint8_t decn);
extern void (*_db_dec_16)(LPC_UART_TypeDef *UARTx, uint16_t decn);
extern void (*_db_dec_32)(LPC_UART_TypeDef *UARTx, uint32_t decn);
extern void (*_db_hex)(LPC_UART_TypeDef *UARTx, uint8_t hexn);
extern void (*_db_hex_16)(LPC_UART_TypeDef *UARTx, uint16_t hexn);
extern void (*_db_hex_32)(LPC_UART_TypeDef *UARTx, uint32_t hexn);
extern uint8_t (*_db_get_char)(LPC_UART_TypeDef *UARTx);

void UARTPutChar (LPC_UART_TypeDef *UARTx, uint8_t ch);
void UARTPuts(LPC_UART_TypeDef *UARTx, const void *str);
void UARTPuts_(LPC_UART_TypeDef *UARTx, const void *str);
void UARTPutDec(LPC_UART_TypeDef *UARTx, uint8_t decnum);
void UARTPutDec16(LPC_UART_TypeDef *UARTx, uint16_t decnum);
void UARTPutDec32(LPC_UART_TypeDef *UARTx, uint32_t decnum);
void UARTPutHex (LPC_UART_TypeDef *UARTx, uint8_t hexnum);
void UARTPutHex16 (LPC_UART_TypeDef *UARTx, uint16_t hexnum);
void UARTPutHex32 (LPC_UART_TypeDef *UARTx, uint32_t hexnum);
uint8_t UARTGetChar (LPC_UART_TypeDef *UARTx);
void debug_frmwrk_init(void);
void  Dbg_printf (const  char *format, ...);

//..............uart receive use as debug
#define MAX_ARG_NUM 10

typedef int (*FUNC_P)(int,...);
typedef int (*FUNC_P0)();

#define FUNC0(a)		{\
		FUNC_P0 f = (FUNC_P0)a;\
		f();	}

#define FUNC1(a,p1)	{\
		FUNC_P f = (FUNC_P)a;\
		f(p1);	}

#define FUNC2(a,p1,p2)	{\
		FUNC_P f = (FUNC_P)a;\
		f(p1,p2);	}

#define FUNC3(a,p1,p2,p3)	{\
		FUNC_P f = (FUNC_P)a;\
		f(p1,p2,p3);	}

#define FUNC4(a,p1,p2,p3,p4)	{\
		FUNC_P f = (FUNC_P)a;\
		f(p1,p2,p3,p4);	}

#define FUNC5(a,p1,p2,p3,p4,p5)	{\
		FUNC_P f = (FUNC_P)a;	\
		f(p1,p2,p3,p4,p5);	}

#define FUNC6(a,p1,p2,p3,p4,p5,p6)	{\
		FUNC_P f = (FUNC_P)a;	\
		f(p1,p2,p3,p4,p5,p6);	}

#define FUNC7(a,p1,p2,p3,p4,p5,p6,p7)	{\
		FUNC_P f = (FUNC_P)a;	\
		f(p1,p2,p3,p4,p5,p6,p7);	}

#define FUNC8(a,p1,p2,p3,p4,p5,p6,p7,p8)	{\
		FUNC_P f = (FUNC_P)a;	\
		f(p1,p2,p3,p4,p5,p6,p7,p8);	}


#endif /* DEBUG_FRMWRK_H_ */

