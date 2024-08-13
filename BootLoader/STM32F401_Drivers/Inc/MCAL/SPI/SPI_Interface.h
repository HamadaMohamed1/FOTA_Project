/*
 * SPI_Interface.h
 *
 *  Created on: Jun 11, 2024
 *      Author: hamada
 */

#ifndef MCAL_SPI_SPI_INTERFACE_H_
#define MCAL_SPI_SPI_INTERFACE_H_

/******************* Includes *******************/
#include "SPI_Private.h"
/******************* Data Type Declarations *******************/
typedef struct
{
	SPI_source_t 		source;
	SPI_comm_type_t 	comm_type;
	SPI_master_slave_t 	master_or_slave ;
	SPI_frame_length_t 	frame_length;
	SPI_LSB_first_t 	msb_lsb_1st;
	SPI_CRC_t 			crc;
	SPI_SSM_t 			ssm;
	SPI_buad_rate_t 	buad_rate;
}SPI_config_t;

/******************* Macro Function Declarations *******************/
#define CLOCK_POLARITY_0_WHEN_IDLE()	(SPI_Array[spi_obj->source]->SPI_CR1 &=~ ((1)<<(CLOCK_POLARITY_BIT_POS)))// clock by default is LOW  (0 when idle)
#define CLOCK_POLARITY_1_WHEN_IDLE()	(SPI_Array[spi_obj->source]->SPI_CR1 |=  ((1)<<(CLOCK_POLARITY_BIT_POS)))// clock by default is HIGH (1 when idle)

#define CLOCK_PHASE_LEADING_EDGE()		(SPI_Array[spi_obj->source]->SPI_CR1 &=~ ((1)<<(CLOCK_PHASE_BIT_POS)))	 //The first clock transition is the first data capture edge (leading)
#define CLOCK_PHASE_TRAILING_EDGE()		(SPI_Array[spi_obj->source]->SPI_CR1 |=  ((1)<<(CLOCK_PHASE_BIT_POS)))	 //The second clock transition is the first data capture edge (trailing)

/******************* Interfaces Declarations *******************/
Std_RetType_t SPI_init(const SPI_config_t *spi_obj);
Std_RetType_t SPI_de_init(const SPI_config_t *spi_obj);
Std_RetType_t SPI_send(const SPI_config_t *spi_obj ,uint8_t *data ,uint16_t size);
Std_RetType_t SPI_receive(const SPI_config_t *spi_obj ,uint8_t *data ,uint16_t size);



#endif /* MCAL_SPI_SPI_INTERFACE_H_ */
