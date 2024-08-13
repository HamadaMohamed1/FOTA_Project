/*
 * SPI_Private.h
 *
 *  Created on: Jun 11, 2024
 *      Author: hamada
 */

#ifndef MCAL_SPI_SPI_PRIVATE_H_
#define MCAL_SPI_SPI_PRIVATE_H_

/******************* Includes *******************/
#include "../../LIBRARY/Common_Macros.h"
#include "../../LIBRARY/Stm32f401xx.h"
/******************* Macro Declarations *******************/
#define SPI_MAX_NUMBER 	4


							/*SPI_CR1 register bits*/
#define BIDIRECTIONAL_DATA_MODE_ENABLE_BIT_POS 		(15)
#define OUTPUT_ENABLE_IN_BIDIRECTIONAL_MODE_BIT_POS (14)
#define CRC_ENABLE_BIT_POS							(13)
#define DATA_FRAME_FORMAT_BIT_POS 					(11)
#define SOFTWARE_SLAVE_MANAGMENT_BIT_POS 			(9)
#define LSB_FIRST_BIT_POS 							(7)
#define SPI_ENABLE_BIT_POS 							(6)
#define BUAD_RATE_BITS_POS 							(3)
#define MASTER_SELECTION_BIT_POS 					(2)
#define CLOCK_POLARITY_BIT_POS 						(1)
#define CLOCK_PHASE_BIT_POS 						(0)
							/*SPI_SR register bits*/





/******************* Data Type Declarations *******************/
typedef enum
{
	SPI_1 = 0,
	SPI_2 ,
	SPI_3 ,
	SPI_4
}SPI_source_t;

typedef enum
{
	SLAVE =0,
	MASTER
}SPI_master_slave_t;

typedef enum
{
	FULL_DUPLEX =0,
	HALF_DUPLEX,
	SIMPLEX
}SPI_comm_type_t;

typedef enum
{
	FRAME_8_BIT =0,
	FRAME_16_BIT
}SPI_frame_length_t;

typedef enum
{
	MSB_FIRST =0,
	LSB_FIRST
}SPI_LSB_first_t;

typedef enum
{
	CRC_DISABLE =0,
	CRC_ENABLE
}SPI_CRC_t;

typedef enum
{
	SOFTWARE_SLAVE_MANG_DISABLED =0,
	SOFTWARE_SLAVE_MANG_ENABLED
}SPI_SSM_t;

typedef enum
{
	F_PCLK_BY2 =0,
	F_PCLK_BY4,
	F_PCLK_BY8,
	F_PCLK_BY16,
	F_PCLK_BY32,
	F_PCLK_BY64,
	F_PCLK_BY128,
	F_PCLK_BY256
}SPI_buad_rate_t;

#endif /* MCAL_SPI_SPI_PRIVATE_H_ */
