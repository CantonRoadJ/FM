

#include "public.h"


/* Private Functions ---------------------------------------------------------- */
static unsigned char uart_set_divisors(LPC_UART_TypeDef *UARTx,uint32_t pCK, uint32_t baudrate);


/*********************************************************************//**
 * @brief		Determines best dividers to get a target clock rate
 * @param[in]	UARTx	Pointer to selected UART peripheral, should be:
 * 				- LPC_UART0: UART0 peripheral
 * 				- LPC_UART1: UART1 peripheral
 * 				- LPC_UART2: UART2 peripheral
 * 				- LPC_UART3: UART3 peripheral
 * @param[in]	baudrate Desired UART baud rate.
 * @return 		Error status, could be:
 * 				- SUCCESS
 * 				- ERROR
 **********************************************************************/
static unsigned char uart_set_divisors(LPC_UART_TypeDef *UARTx,uint32_t pCK, uint32_t baudrate)
{
	unsigned char errorStatus = ERROR;

	uint32_t uClk;
	uint32_t calcBaudrate = 0;
	uint32_t temp = 0;

	uint32_t mulFracDiv, dividerAddFracDiv;
	uint32_t diviser = 0 ;
	uint32_t mulFracDivOptimal = 1;
	uint32_t dividerAddOptimal = 0;
	uint32_t diviserOptimal = 0;

	uint32_t relativeError = 0;
	uint32_t relativeOptimalError = 100000;




	uClk = pCK >> 4; /* div by 16 */
	/* In the Uart IP block, baud rate is calculated using FDR and DLL-DLM registers
	* The formula is :
	* BaudRate= uClk * (mulFracDiv/(mulFracDiv+dividerAddFracDiv) / (16 * (DLL)
	* It involves floating point calculations. That's the reason the formulae are adjusted with
	* Multiply and divide method.*/
	/* The value of mulFracDiv and dividerAddFracDiv should comply to the following expressions:
	* 0 < mulFracDiv <= 15, 0 <= dividerAddFracDiv <= 15 */
	for (mulFracDiv = 1 ; mulFracDiv <= 15 ;mulFracDiv++)
	{
	for (dividerAddFracDiv = 0 ; dividerAddFracDiv <= 15 ;dividerAddFracDiv++)
	{
	  temp = (mulFracDiv * uClk) / ((mulFracDiv + dividerAddFracDiv));

	  diviser = temp / baudrate;
	  if ((temp % baudrate) > (baudrate / 2))
		diviser++;

	  if (diviser > 2 && diviser < 65536)
	  {
		calcBaudrate = temp / diviser;

		if (calcBaudrate <= baudrate)
		  relativeError = baudrate - calcBaudrate;
		else
		  relativeError = calcBaudrate - baudrate;

		if ((relativeError < relativeOptimalError))
		{
		  mulFracDivOptimal = mulFracDiv ;
		  dividerAddOptimal = dividerAddFracDiv;
		  diviserOptimal = diviser;
		  relativeOptimalError = relativeError;
		  if (relativeError == 0)
			break;
		}
	  } /* End of if */
	} /* end of inner for loop */
	if (relativeError == 0)
	  break;
	} /* end of outer for loop  */

	if (relativeOptimalError < ((baudrate * UART_ACCEPTED_BAUDRATE_ERROR)/100))
	{
		if (((LPC_UART1_TypeDef *)UARTx) == LPC_UART1)
		{
			((LPC_UART1_TypeDef *)UARTx)->LCR |= UART_LCR_DLAB_EN;
			((LPC_UART1_TypeDef *)UARTx)->/*DLIER.*/DLM = UART_LOAD_DLM(diviserOptimal);
			((LPC_UART1_TypeDef *)UARTx)->/*RBTHDLR.*/DLL = UART_LOAD_DLL(diviserOptimal);
			/* Then reset DLAB bit */
			((LPC_UART1_TypeDef *)UARTx)->LCR &= (~UART_LCR_DLAB_EN) & UART_LCR_BITMASK;
			((LPC_UART1_TypeDef *)UARTx)->FDR = (UART_FDR_MULVAL(mulFracDivOptimal) \
					| UART_FDR_DIVADDVAL(dividerAddOptimal)) & UART_FDR_BITMASK;
		}
		else
		{
			UARTx->LCR |= UART_LCR_DLAB_EN;
			UARTx->/*DLIER.*/DLM = UART_LOAD_DLM(diviserOptimal);
			UARTx->/*RBTHDLR.*/DLL = UART_LOAD_DLL(diviserOptimal);
			/* Then reset DLAB bit */
			UARTx->LCR &= (~UART_LCR_DLAB_EN) & UART_LCR_BITMASK;
			UARTx->FDR = (UART_FDR_MULVAL(mulFracDivOptimal) \
					| UART_FDR_DIVADDVAL(dividerAddOptimal)) & UART_FDR_BITMASK;
		}
		errorStatus = SUCCESS;
	}

	return errorStatus;
}


/*****************************************************************************
** Function name:		UARTInit
**
** Descriptions:		Initialize UART0 port, setup pin select,
**						clock, parity, stop bits, FIFO, etc.
**
** parameters:			portNum(0 or 1) and UART baudrate
** Returned value:		true or false, return false only if the 
**						interrupt handler can't be installed to the 
**						VIC table
** 
*****************************************************************************/
uint32_t UARTInit( uint32_t PortNum, uint32_t baudrate )
{
  uint32_t Fdiv;
 
  if ( PortNum == 0 )
  {	 
    LPC_SC->PCONP|= 1<<3;
	LPC_PINCON->PINSEL0 &= ~0x000000F0;
	LPC_PINCON->PINSEL0 |= 0x00000050;       /* RxD0 is P0.3 and TxD0 is P0.2 */

    LPC_UART0->LCR = 0x83;		/* 8 bits, no Parity, 1 Stop bit */
	/* By default, the PCLKSELx value is zero, thus, the PCLK for
	all the peripherals is 1/4 of the SystemFrequency. */ 
   // Fdiv = ( SYS_FRE/4/16 ) / baudrate ;	/*baud rate, Fpclk: 18MHz */
    //LPC_UART0->DLM = Fdiv / 256;							
   // LPC_UART0->DLL = (Fdiv%256)+1;
   uart_set_divisors((LPC_UART_TypeDef*)LPC_UART0,SYS_FRE/4,baudrate);

    LPC_UART0->FCR = 0;		/* disable and reset TX and RX FIFO. */

   	NVIC_EnableIRQ(UART0_IRQn);		//enable UART0 interrupt

    LPC_UART0->IER = IER_RBR | IER_THRE | IER_RLS;	/* Enable UART0 interrupt */
   //	LPC_UART0->IER = 0;
	
	// Set ACR to default state
	LPC_UART0->ACR = 0;
    return (TRUE);
  }
  else if ( PortNum == 1 )
  {
    LPC_SC->PCONP|= 1<<4;
	LPC_PINCON->PINSEL4 |= 0x0000000A;	/* Enable RxD1 P2.1, TxD1 P2.0 */
	
   
    
	LPC_UART1->LCR = 0x83;		/* 8 bits, no Parity, 1 Stop bit */
	/* By default, the PCLKSELx value is zero, thus, the PCLK for
	all the peripherals is 1/4 of the SystemFrequency. */ 
    Fdiv = ( SYS_FRE/4/16 ) / baudrate ;	/*baud rate */
    LPC_UART1->DLM = Fdiv/256;							
    LPC_UART1->DLL = (Fdiv%256)+1;
	LPC_UART1->LCR = 0x03;		/* DLAB = 0 */
    LPC_UART1->FCR = 0x07;		/* Enable and reset TX and RX FIFO. */

   //	NVIC_EnableIRQ(UART1_IRQn);

    //LPC_UART1->IER = IER_RBR | IER_THRE | IER_RLS;	/* Enable UART1 interrupt */
	LPC_UART1->IER = 0;
    return (TRUE);
  }
  return( FALSE ); 
}

/* UART Send/Recieve functions -------------------------------------------------*/
/*********************************************************************//**
 * @brief		Transmit a single data through UART peripheral
 * @param[in]	UARTx	UART peripheral selected, should be:
 *   			- LPC_UART0: UART0 peripheral
 * 				- LPC_UART1: UART1 peripheral
 * 				- LPC_UART2: UART2 peripheral
 * 				- LPC_UART3: UART3 peripheral
 * @param[in]	Data	Data to transmit (must be 8-bit long)
 * @return 		None
 **********************************************************************/
void UART_SendByte(LPC_UART_TypeDef* UARTx, uint8_t Data)
{

	if (((LPC_UART1_TypeDef *)UARTx) == LPC_UART1)
	{
		((LPC_UART1_TypeDef *)UARTx)->/*RBTHDLR.*/THR = Data & UART_THR_MASKBIT;
	}
	else
	{
		UARTx->/*RBTHDLR.*/THR = Data & UART_THR_MASKBIT;
	}

}


/*********************************************************************//**
 * @brief		Receive a single data from UART peripheral
 * @param[in]	UARTx	UART peripheral selected, should be:
 *  			- LPC_UART0: UART0 peripheral
 * 				- LPC_UART1: UART1 peripheral
 * 				- LPC_UART2: UART2 peripheral
 * 				- LPC_UART3: UART3 peripheral
 * @return 		Data received
 **********************************************************************/
uint8_t UART_ReceiveByte(LPC_UART_TypeDef* UARTx)
{
	if (((LPC_UART1_TypeDef *)UARTx) == LPC_UART1)
	{
		return (((LPC_UART1_TypeDef *)UARTx)->/*RBTHDLR.*/RBR & UART_RBR_MASKBIT);
	}
	else
	{
		return (UARTx->/*RBTHDLR.*/RBR & UART_RBR_MASKBIT);
	}
}

/*********************************************************************//**
 * @brief		Send a block of data via UART peripheral
 * @param[in]	UARTx	Selected UART peripheral used to send data, should be:
 *   			- LPC_UART0: UART0 peripheral
 * 				- LPC_UART1: UART1 peripheral
 * 				- LPC_UART2: UART2 peripheral
 * 				- LPC_UART3: UART3 peripheral
 * @param[in]	txbuf 	Pointer to Transmit buffer
 * @param[in]	buflen 	Length of Transmit buffer
 * @param[in] 	flag 	Flag used in  UART transfer, should be
 * 						NONE_BLOCKING or BLOCKING
 * @return 		Number of bytes sent.
 *
 * Note: when using UART in BLOCKING mode, a time-out condition is used
 * via defined symbol UART_BLOCKING_TIMEOUT.
 **********************************************************************/
uint32_t UART_Send(LPC_UART_TypeDef *UARTx, uint8_t *txbuf,
		uint32_t buflen, TRANSFER_BLOCK_Type flag)
{
	uint32_t bToSend, bSent, timeOut, fifo_cnt;
	uint8_t *pChar = txbuf;

	bToSend = buflen;

	// blocking mode
	if (flag == BLOCKING) {
		bSent = 0;
		while (bToSend){
			timeOut = UART_BLOCKING_TIMEOUT;
			// Wait for THR empty with timeout
			while (!(UARTx->LSR & UART_LSR_THRE)) {
				if (timeOut == 0) break;
				timeOut--;
			}
			// Time out!
			if(timeOut == 0) break;
			fifo_cnt = UART_TX_FIFO_SIZE;
			while (fifo_cnt && bToSend){
				UART_SendByte(UARTx, (*pChar++));
				fifo_cnt--;
				bToSend--;
				bSent++;
			}
		}
	}
	// None blocking mode
	else {
		bSent = 0;
		while (bToSend) {
			if (!(UARTx->LSR & UART_LSR_THRE)){
				break;
			}
			fifo_cnt = UART_TX_FIFO_SIZE;
			while (fifo_cnt && bToSend) {
				UART_SendByte(UARTx, (*pChar++));
				bToSend--;
				fifo_cnt--;
				bSent++;
			}
		}
	}
	return bSent;
}
/*********************************************************************//**
 * @brief		Receive a block of data via UART peripheral
 * @param[in]	UARTx	Selected UART peripheral used to send data,
 * 				should be:
 *   			- LPC_UART0: UART0 peripheral
 * 				- LPC_UART1: UART1 peripheral
 * 				- LPC_UART2: UART2 peripheral
 * 				- LPC_UART3: UART3 peripheral
 * @param[out]	rxbuf 	Pointer to Received buffer
 * @param[in]	buflen 	Length of Received buffer
 * @param[in] 	flag 	Flag mode, should be NONE_BLOCKING or BLOCKING

 * @return 		Number of bytes received
 *
 * Note: when using UART in BLOCKING mode, a time-out condition is used
 * via defined symbol UART_BLOCKING_TIMEOUT.
 **********************************************************************/
uint32_t UART_Receive(LPC_UART_TypeDef *UARTx, uint8_t *rxbuf, \
		uint32_t buflen, TRANSFER_BLOCK_Type flag)
{
	uint32_t bToRecv, bRecv, timeOut;
	uint8_t *pChar = rxbuf;

	bToRecv = buflen;

	// Blocking mode
	if (flag == BLOCKING) {
		bRecv = 0;
		while (bToRecv){
			timeOut = UART_BLOCKING_TIMEOUT;
			while (!(UARTx->LSR & UART_LSR_RDR)){
				if (timeOut == 0) break;
				timeOut--;
			}
			// Time out!
			if(timeOut == 0) break;
			// Get data from the buffer
			(*pChar++) = UART_ReceiveByte(UARTx);
			bToRecv--;
			bRecv++;
		}
	}
	// None blocking mode
	else {
		bRecv = 0;
		while (bToRecv) {
			if (!(UARTx->LSR & UART_LSR_RDR)) {
				break;
			} else {
				(*pChar++) = UART_ReceiveByte(UARTx);
				bRecv++;
				bToRecv--;
			}
		}
	}
	return bRecv;
}

/*----------------- INTERRUPT SERVICE ROUTINES --------------------------*/
/* Example group ----------------------------------------------------------- */
/** @defgroup UART_Interrupt	Interrupt
 * @ingroup UART_Examples
 * @{
 */

/************************** PRIVATE DEFINTIONS *************************/
/* buffer size definition */
#define UART_RING_BUFSIZE 256

/* Buf mask */
#define __BUF_MASK (UART_RING_BUFSIZE-1)
/* Check buf is full or not */
#define __BUF_IS_FULL(head, tail) ((tail&__BUF_MASK)==((head+1)&__BUF_MASK))
/* Check buf will be full in next receiving or not */
#define __BUF_WILL_FULL(head, tail) ((tail&__BUF_MASK)==((head+2)&__BUF_MASK))
/* Check buf is empty */
#define __BUF_IS_EMPTY(head, tail) ((head&__BUF_MASK)==(tail&__BUF_MASK))
#define __BUF_IS_VALID(head, tail) ((head&__BUF_MASK)!=(tail&__BUF_MASK))
/* Reset buf */
#define __BUF_RESET(bufidx)	(bufidx=0)
#define __BUF_INCR(bufidx)	(bufidx=(bufidx+1)&__BUF_MASK)

#ifndef __IO
#define     __IO    volatile                  /*!< defines 'read / write' permissions   */
#endif

//typedef enum {RESET = 0, SET = !RESET} FlagStatus, IntStatus, SetState;

/********************************************************************//**
* @brief UART Interrupt Type definitions
**********************************************************************/
typedef enum {
	UART_INTCFG_RBR = 0,	/*!< RBR Interrupt enable*/
	UART_INTCFG_THRE,		/*!< THR Interrupt enable*/
	UART_INTCFG_RLS,		/*!< RX line status interrupt enable*/
	UART1_INTCFG_MS,		/*!< Modem status interrupt enable (UART1 only) */
	UART1_INTCFG_CTS,		/*!< CTS1 signal transition interrupt enable (UART1 only) */
	UART_INTCFG_ABEO,		/*!< Enables the end of auto-baud interrupt */
	UART_INTCFG_ABTO		/*!< Enables the auto-baud time-out interrupt */
} UART_INT_Type;
/*********************************************************************//**
 * Macro defines for Macro defines for UART interrupt enable register
 **********************************************************************/
#define UART_IER_RBRINT_EN		((uint32_t)(1<<0)) 	/*!< RBR Interrupt enable*/
#define UART_IER_THREINT_EN		((uint32_t)(1<<1)) 	/*!< THR Interrupt enable*/
#define UART_IER_RLSINT_EN		((uint32_t)(1<<2)) 	/*!< RX line status interrupt enable*/
#define UART1_IER_MSINT_EN		((uint32_t)(1<<3))	/*!< Modem status interrupt enable */
#define UART1_IER_CTSINT_EN		((uint32_t)(1<<7))	/*!< CTS1 signal transition interrupt enable */
#define UART_IER_ABEOINT_EN		((uint32_t)(1<<8)) 	/*!< Enables the end of auto-baud interrupt */
#define UART_IER_ABTOINT_EN		((uint32_t)(1<<9)) 	/*!< Enables the auto-baud time-out interrupt */
#define UART_IER_BITMASK		((uint32_t)(0x307)) /*!< UART interrupt enable register bit mask */
#define UART1_IER_BITMASK		((uint32_t)(0x38F)) /*!< UART1 interrupt enable register bit mask */

/************************** PRIVATE TYPES *************************/

/** @brief UART Ring buffer structure */
typedef struct
{
    __IO uint32_t tx_head;                /*!< UART Tx ring buffer head index */
    __IO uint32_t tx_tail;                /*!< UART Tx ring buffer tail index */
    __IO uint32_t rx_head;                /*!< UART Rx ring buffer head index */
    __IO uint32_t rx_tail;                /*!< UART Rx ring buffer tail index */
    __IO uint8_t  tx[UART_RING_BUFSIZE];  /*!< UART Tx data ring buffer */
    __IO uint8_t  rx[UART_RING_BUFSIZE];  /*!< UART Rx data ring buffer */
} UART_RING_BUFFER_T;

// UART Ring buffer
UART_RING_BUFFER_T rb;

// Current Tx Interrupt enable state
__IO FlagStatus TxIntStat;


/************************** PRIVATE FUNCTIONS *************************/
/* Interrupt service routines */
void UART0_IRQHandler(void);
void UART_IntErr(uint8_t bLSErrType);
void UART_IntTransmit(void);
void UART_IntReceive(void);


/********************************************************************//**
 * @brief 		Enable or disable specified UART interrupt.
 * @param[in]	UARTx	UART peripheral selected, should be
 *  			- LPC_UART0: UART0 peripheral
 * 				- LPC_UART1: UART1 peripheral
 * 				- LPC_UART2: UART2 peripheral
 * 				- LPC_UART3: UART3 peripheral
 * @param[in]	UARTIntCfg	Specifies the interrupt flag,
 * 				should be one of the following:
				- UART_INTCFG_RBR 	:  RBR Interrupt enable
				- UART_INTCFG_THRE 	:  THR Interrupt enable
				- UART_INTCFG_RLS 	:  RX line status interrupt enable
				- UART1_INTCFG_MS	:  Modem status interrupt enable (UART1 only)
				- UART1_INTCFG_CTS	:  CTS1 signal transition interrupt enable (UART1 only)
				- UART_INTCFG_ABEO 	:  Enables the end of auto-baud interrupt
				- UART_INTCFG_ABTO 	:  Enables the auto-baud time-out interrupt
 * @param[in]	NewState New state of specified UART interrupt type,
 * 				should be:
 * 				- ENALBE: Enable this UART interrupt type.
* 				- DISALBE: Disable this UART interrupt type.
 * @return 		None
 *********************************************************************/
void UART_IntConfig(LPC_UART_TypeDef *UARTx, UART_INT_Type UARTIntCfg, int NewState)
{
	uint32_t tmp;

	switch(UARTIntCfg){
		case UART_INTCFG_RBR:
			tmp = UART_IER_RBRINT_EN;
			break;
		case UART_INTCFG_THRE:
			tmp = UART_IER_THREINT_EN;
			break;
		case UART_INTCFG_RLS:
			tmp = UART_IER_RLSINT_EN;
			break;
		case UART1_INTCFG_MS:
			tmp = UART1_IER_MSINT_EN;
			break;
		case UART1_INTCFG_CTS:
			tmp = UART1_IER_CTSINT_EN;
			break;
		case UART_INTCFG_ABEO:
			tmp = UART_IER_ABEOINT_EN;
			break;
		case UART_INTCFG_ABTO:
			tmp = UART_IER_ABTOINT_EN;
			break;
	}

	if (NewState == ENABLE)
	{
		if ((LPC_UART1_TypeDef *) UARTx == LPC_UART1)
		{
			((LPC_UART1_TypeDef *)UARTx)->/*DLIER.*/IER |= tmp;
		}
		else
		{
			UARTx->/*DLIER.*/IER |= tmp;
		}
	}
	else
	{
		if ((LPC_UART1_TypeDef *) UARTx == LPC_UART1)
		{
			((LPC_UART1_TypeDef *)UARTx)->/*DLIER.*/IER &= (~tmp) & UART1_IER_BITMASK;
		}
		else
		{
			UARTx->/*DLIER.*/IER &= (~tmp) & UART_IER_BITMASK;
		}
	}
}
/*********************************************************************//**
 * @brief		Check whether if UART is busy or not
 * @param[in]	UARTx	UART peripheral selected, should be:
 *  			- LPC_UART0: UART0 peripheral
 * 				- LPC_UART1: UART1 peripheral
 * 				- LPC_UART2: UART2 peripheral
 * 				- LPC_UART3: UART3 peripheral
 * @return		RESET if UART is not busy, otherwise return SET.
 **********************************************************************/
FlagStatus UART_CheckBusy(LPC_UART_TypeDef *UARTx)
{
	if (UARTx->LSR & UART_LSR_TEMT){
		return RESET;
	} else {
		return SET;
	}
}
/********************************************************************//**
 * @brief 		UART receive function (ring buffer used)
 * @param[in]	None
 * @return 		None
 *********************************************************************/
void UART_IntReceive(void)
{
	uint8_t tmpc;
	uint32_t rLen;

	while(1){
		// Call UART read function in UART driver
		rLen = UART_Receive((LPC_UART_TypeDef *)LPC_UART0, &tmpc, 1, NONE_BLOCKING);
		// If data received
		if (rLen){
			/* Check if buffer is more space
			 * If no more space, remaining character will be trimmed out
			 */
			if (!__BUF_IS_FULL(rb.rx_head,rb.rx_tail)){
				rb.rx[rb.rx_head] = tmpc;
				__BUF_INCR(rb.rx_head);
			}
		}
		// no more data
		else {
			break;
		}
	}
}

/********************************************************************//**
 * @brief 		UART transmit function (ring buffer used)
 * @param[in]	None
 * @return 		None
 *********************************************************************/
void UART_IntTransmit(void)
{
    // Disable THRE interrupt
    //UART_IntConfig((LPC_UART_TypeDef *)LPC_UART0, UART_INTCFG_THRE, DISABLE);
	LPC_UART0->IER &= (~UART_IER_THREINT_EN) & UART_IER_BITMASK;

	/* Wait for FIFO buffer empty, transfer UART_TX_FIFO_SIZE bytes
	 * of data or break whenever ring buffers are empty */
	/* Wait until THR empty */
    while (UART_CheckBusy((LPC_UART_TypeDef *)LPC_UART0) == SET);

	while (!__BUF_IS_EMPTY(rb.tx_head,rb.tx_tail))
    {
        /* Move a piece of data into the transmit FIFO */
    	if (UART_Send((LPC_UART_TypeDef *)LPC_UART0, (uint8_t *)&rb.tx[rb.tx_tail], 1, NONE_BLOCKING)){
        /* Update transmit ring FIFO tail pointer */
        __BUF_INCR(rb.tx_tail);
    	} else {
    		break;
    	}
    }

    /* If there is no more data to send, disable the transmit
       interrupt - else enable it or keep it enabled */
	if (__BUF_IS_EMPTY(rb.tx_head, rb.tx_tail)) {
    	//UART_IntConfig((LPC_UART_TypeDef *)LPC_UART0, UART_INTCFG_THRE, DISABLE);
  	LPC_UART0->IER &= (~UART_IER_THREINT_EN) & UART_IER_BITMASK;
	
  	// Reset Tx Interrupt state
    	TxIntStat = RESET;
    }
    else{
      	// Set Tx Interrupt state
		TxIntStat = SET;
    	//UART_IntConfig((LPC_UART_TypeDef *)LPC_UART0, UART_INTCFG_THRE, ENABLE);
  	LPC_UART0->IER |= (UART_IER_THREINT_EN);
    }
}
/*********************************************************************//**
 * @brief		UART Line Status Error
 * @param[in]	bLSErrType	UART Line Status Error Type
 * @return		None
 **********************************************************************/
void UART_IntErr(uint8_t bLSErrType)
{
	while(1);
}

/*********************************************************************//**
 * @brief		UART0 interrupt handler sub-routine
 * @param[in]	None
 * @return 		None
 **********************************************************************/
void UART0_IRQHandler(void)
{
	uint32_t intsrc, tmp, tmp1;

	/* Determine the interrupt source */
	//intsrc = UART_GetIntId(LPC_UART0);
	intsrc = LPC_UART0->IIR & 0x03CF;
	tmp = intsrc & UART_IIR_INTID_MASK;

	// Receive Line Status
	if (tmp == UART_IIR_INTID_RLS){
		// Check line status
		tmp1 = ((LPC_UART0->LSR) & UART_LSR_BITMASK);
		
		// Mask out the Receive Ready and Transmit Holding empty status
		tmp1 &= (UART_LSR_OE | UART_LSR_PE | UART_LSR_FE \
				| UART_LSR_BI | UART_LSR_RXFE);
		// If any error exist
		if (tmp1) {
				UART_IntErr(tmp1);
		}
	}

	// Receive Data Available or Character time-out
	if ((tmp == UART_IIR_INTID_RDA) || (tmp == UART_IIR_INTID_CTI)){
			UART_IntReceive();
	}

	// Transmit Holding Empty
	if (tmp == UART_IIR_INTID_THRE){
			UART_IntTransmit();
	}

}

/*********************************************************************//**
 * @brief		UART read function for interrupt mode (using ring buffers)
 * @param[in]	UARTPort	Selected UART peripheral used to send data,
 * 				should be UART0
 * @param[out]	rxbuf Pointer to Received buffer
 * @param[in]	buflen Length of Received buffer
 * @return 		Number of bytes actually read from the ring buffer
 **********************************************************************/
uint32_t UARTReceive(LPC_UART_TypeDef *UARTPort, char *rxbuf, uint8_t buflen)
{
    uint8_t *data = (uint8_t *) rxbuf;
    uint32_t bytes = 0;

	/* Temporarily lock out UART receive interrupts during this
	   read so the UART receive interrupt won't cause problems
	   with the index values */
	UART_IntConfig(UARTPort, UART_INTCFG_RBR, DISABLE);

	/* Loop until receive buffer ring is empty or
		until max_bytes expires */
	while ((buflen > 0) && (!(__BUF_IS_EMPTY(rb.rx_head, rb.rx_tail))))
	{
		/* Read data from ring buffer into user buffer */
		*data = rb.rx[rb.rx_tail];
		data++;

		/* Update tail pointer */
		__BUF_INCR(rb.rx_tail);

		/* Increment data count and decrement buffer size count */
		bytes++;
		buflen--;
	}

	/* Re-enable UART interrupts */
	UART_IntConfig(UARTPort, UART_INTCFG_RBR, ENABLE);

    return bytes;
}

//receive at least 1 byte
uint32_t UARTReceiveIsValid(void)
{
	return (__BUF_IS_VALID(rb.rx_head, rb.rx_tail));
}

