/*
 * USART_Private.h
 *
 *  Created on: Jun 10, 2024
 *      Author: hamada
 */

#ifndef MCAL_USART_USART_PRIVATE_H_
#define MCAL_USART_USART_PRIVATE_H_

/******************* Includes *******************/
#include "../../LIBRARY/Common_Macros.h"
#include "../../LIBRARY/Stm32f401xx.h"
#include "../../Core_Peripheral/NVIC/NVIC_Interface.h"
/******************* Macro Declarations *******************/
#define USART_MAX_NUMBER 3

/*bits in register CR1*/
#define OVERSAMPLING_BIT_POS 15
#define USART_ENABLE_BIT_POS 13
#define USART_M_BIT_POS 	 12
#define USART_PARITY_CONTROL_ENABLE_BIT_POS 10
#define USART_PARITY_SELECTION_BIT_POS 9
#define USART_TRANSMITTER_ENABLE_BIT_POS 3
#define USART_RECEIVER_ENABLE_BIT_POS 2

#define USART_TX_INTERRUPT_ENABLE_BIT_POS  7
#define USART_RX_INTERRUPT_ENABLE_BIT_POS  5


/*bits in register CR2*/
#define USART_STOP_BITS_POS	12

/*bits in register SR*/
#define USART_RX_FLAG_BIT_POS 	0x00000020
#define USART_TX_FLAG_BIT_POS 	0x00000080


/******************* Macro Function Declarations *******************/

/******************* Data Type Declarations *******************/
typedef enum
{
    USART_1=0,
	USART_2,
	USART_6
}USART_source_t;

typedef enum
{
	ASYNCHRONOUS = 0,
	SYNCHRONOUS ,
}USART_type_t;

typedef enum
{
	RX_ONLY = 0,	// for receiving only
	TX_ONLY ,		// for sending only
	RX_TX			// for sending & receiving
}USART_mode_t;

typedef enum
{
	POLLING =0,
	INTERRUPT ,
	DMA
}USART_Rx_Tx_mode_t;

typedef enum {
    BAUD_300     = 300,
    BAUD_600     = 600,
    BAUD_1200    = 1200,
    BAUD_2400    = 2400,
    BAUD_4800    = 4800,
    BAUD_9600    = 9600,
    BAUD_14400   = 14400,
    BAUD_19200   = 19200,
    BAUD_38400   = 38400,
    BAUD_57600   = 57600,
    BAUD_115200  = 115200,
    BAUD_230400  = 230400,
    BAUD_460800  = 460800,
    BAUD_921600  = 921600,
    BAUD_1843200 = 1843200,
    BAUD_3686400 = 3686400
}USART_baud_rate_t;

typedef enum
{
	HALF_STOP_BIT = 0b01,				//0.5 bit
	ONE_STOP_BIT = 0b00,				//1 bit
	ONE_AND_A_HALF_STOP_BIT = 0b11, 	//1.5 bits
	TWO_STOP_BITS = 0b10				//2 bits
}USART_stop_bits_t;

typedef enum
{
	EGHIT_BITS = 0,
	NINE_BITS
}USART_word_length_t;

typedef enum
{
	EVEN_PARITY = 0,
	ODD_PARITY ,
	WITHOUT_PARITY
}USART_parity_t;

typedef enum
{
	OVERSAMPLING_BY_16 = 0,
	OVERSAMPLING_BY_8 ,
}USART_oversampling_t;

typedef enum
{
	HARDWARE_FLOW_CONTROL_IS_NOT_USED =0,
	HARDWARE_FLOW_CONTROL_IS_USED
}USART_hardware_control_flow_t;



#endif /* MCAL_USART_USART_PRIVATE_H_ */
