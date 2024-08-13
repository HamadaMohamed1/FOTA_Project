/*
 * SPI.c
 *
 *  Created on: Jun 11, 2024
 *      Author: hamada
 */

/******************* Includes *******************/
#include "../../../Inc/MCAL/SPI/SPI_Interface.h"

static SPI_RegDef_t *SPI_Array[SPI_MAX_NUMBER] = {SPI1,SPI2,SPI3,SPI4};
static SPI_source_t SPI_source ;


Std_RetType_t SPI_init(const SPI_config_t *spi_obj)
{
	Std_RetType_t ret = RET_OK;
	if(NULL == spi_obj)
	{
		ret = RET_ERROR;
	}
	else
	{
		SPI_Array[spi_obj->source]->SPI_CR1 |= ((spi_obj->comm_type)<<(BIDIRECTIONAL_DATA_MODE_ENABLE_BIT_POS)); //select Full duplex or Half duplex
		if(HALF_DUPLEX == spi_obj->comm_type)
		{
			SPI_Array[spi_obj->source]->SPI_CR1 |=((spi_obj->comm_type)<<(OUTPUT_ENABLE_IN_BIDIRECTIONAL_MODE_BIT_POS));
		}
		SPI_Array[spi_obj->source]->SPI_CR1 |= ((spi_obj->crc)<<(CRC_ENABLE_BIT_POS)); //Hardware CRC calculation enable or disable
		SPI_Array[spi_obj->source]->SPI_CR1 |= ((spi_obj->frame_length)<<(DATA_FRAME_FORMAT_BIT_POS));//select frame length 8bits or 16bits
		SPI_Array[spi_obj->source]->SPI_CR1 |= ((spi_obj->ssm)<<(SOFTWARE_SLAVE_MANAGMENT_BIT_POS));
		SPI_Array[spi_obj->source]->SPI_CR1 |= ((spi_obj->msb_lsb_1st)<<(LSB_FIRST_BIT_POS)); // LSB or MSB send first

		SPI_Array[spi_obj->source]->SPI_CR1 |= ((spi_obj->buad_rate)<<(BUAD_RATE_BITS_POS)); // set buadrate
		SPI_Array[spi_obj->source]->SPI_CR1 |= ((spi_obj->master_or_slave)<<(MASTER_SELECTION_BIT_POS)); // master or slave

		CLOCK_POLARITY_0_WHEN_IDLE();
		CLOCK_PHASE_LEADING_EDGE();

		SPI_Array[spi_obj->source]->SPI_CR1 |= ((1)<<(SPI_ENABLE_BIT_POS)); // SPI Enable

	}
	return ret;
}

Std_RetType_t SPI_send(const SPI_config_t *spi_obj ,uint8_t *data ,uint16_t size)
{
	Std_RetType_t ret = RET_OK;
	uint16_t counter = 0;
	if((NULL == spi_obj) || (NULL == data))
	{
		ret = RET_ERROR ;
	}
	else
	{
		while(counter < size)
		{
			while(!(SPI_Array[spi_obj->source]->SPI_SR & 0x02));   		//Waits for the TXE flag to ensure the transmit buffer is empty.
			SPI_Array[spi_obj->source]->SPI_DR = data[counter++];   	//Writes data to the SPI data register (DR).
			while(!(SPI_Array[spi_obj->source]->SPI_SR & 0x01));		//Waits for the RXNE flag to ensure data has been received (necessary to clear the RXNE flag).
			volatile uint8_t dummy = SPI_Array[spi_obj->source]->SPI_SR;//Reads the received data (dummy read in this case).
			while(!(SPI_Array[spi_obj->source]->SPI_SR & 0x10));		//Waits for the BSY flag to be reset, ensuring the SPI is not busy.
		}
	}
	return ret;
}

Std_RetType_t SPI_receive(const SPI_config_t *spi_obj ,uint8_t *data ,uint16_t size)
{
	Std_RetType_t ret = RET_OK;
	uint16_t counter = 0;
	if((NULL == spi_obj) || (NULL == data))
	{
		ret = RET_ERROR ;
	}
	else
	{
		while(counter < size)
		{
			while(!(SPI_Array[spi_obj->source]->SPI_SR & 0x02));   		//Waits for the TXE flag to ensure the transmit buffer is empty.
			SPI_Array[spi_obj->source]->SPI_DR = 0xFF;					// Send dummy data to generate clock
			while(!(SPI_Array[spi_obj->source]->SPI_SR & 0x01));		// Wait until RXNE (Receive buffer not empty) flag is set
			data[counter++] = SPI_Array[spi_obj->source]->SPI_DR;		// Read the received data
			while(!(SPI_Array[spi_obj->source]->SPI_SR & 0x10));		//Waits for the BSY flag to be reset, ensuring the SPI is not busy.
		}
	}
	return ret;
}
