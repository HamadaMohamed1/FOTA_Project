/*
 * USART.c
 *
 *  Created on: Jun 10, 2024
 *      Author: hamada
 */


#include "../../../Inc/MCAL/USART/USART_Interface.h"

static USART_source_t USART_source;

static USART_RegDef_t* USART_Array[USART_MAX_NUMBER] = {USART1,USART2,USART6};

/**
 * @brief  : Static function to configure the baudrate of the USART
 * @param  : (USART_obj) Pointer to the configuration @ref USART_Config_t
 * @return : void
 */
static void usart_set_baud_rate(const USART_Config_t* USART_obj);
/**
 * @brief  : Static function to : Select the mode of sending & receiving of USART [POLLING , INTERRUPT , DMA]
 * @param  : (USART_obj) Pointer to the configuration @ref USART_Config_t
 * @return : void
 */
static void USART_set_Tx_Rx_mode(const USART_Config_t* USART_obj);


volatile uint8_t tx_buffer;
volatile uint8_t rx_buffer;
volatile uint8_t tx_ready = 1;
volatile uint8_t rx_ready = 0;

/**
 * @brief  : Initialize the USART peripheral
 * @param  : (USART_obj) Pointer to the configuration @ref USART_Config_t
 * @return :
 * 			(RET_OK) : The function done successfully
 * 			(RET_ERROR) : The function has a problem to perform this action
 */
Std_RetType_t USART_init(const USART_Config_t* USART_obj)
{
	Std_RetType_t ret = RET_OK;
	if(NULL == USART_obj)
	{
		ret = RET_ERROR;
	}
	else
	{
		usart_set_baud_rate(USART_obj);

		USART_Array[USART_obj->source]->USART_CR1 |= (1<<(USART_ENABLE_BIT_POS)); //USART Enable
		USART_Array[USART_obj->source]->USART_CR1 |= ((USART_obj->word_length)<<(USART_M_BIT_POS)); //word length 0-> 8bits , 1-> 9bits
		if(WITHOUT_PARITY == USART_obj->parity)
		{
			USART_Array[USART_obj->source]->USART_CR1 &=~ (1<<(USART_PARITY_CONTROL_ENABLE_BIT_POS)); //Disable parity
		}
		else
		{
			USART_Array[USART_obj->source]->USART_CR1 |= (1<<(USART_PARITY_CONTROL_ENABLE_BIT_POS)); //Enable parity
			USART_Array[USART_obj->source]->USART_CR1 |= ((USART_obj->parity)<<(USART_PARITY_SELECTION_BIT_POS)); //Even or Odd parity
		}
		switch(USART_obj->mode)
		{
			case RX_ONLY :
					USART_Array[USART_obj->source]->USART_CR1 |= (1 << (USART_RECEIVER_ENABLE_BIT_POS));// Receiver enable
			break;
			case TX_ONLY :
					USART_Array[USART_obj->source]->USART_CR1 |= (1 << (USART_TRANSMITTER_ENABLE_BIT_POS)); // Transmitter enable
			break ;
			case RX_TX :
					USART_Array[USART_obj->source]->USART_CR1 |= (1 << (USART_RECEIVER_ENABLE_BIT_POS));// Receiver enable
					USART_Array[USART_obj->source]->USART_CR1 |= (1 << (USART_TRANSMITTER_ENABLE_BIT_POS)); // Transmitter enable
			break ;
			default : break;
		}

		USART_Array[USART_obj->source]->USART_CR2 |= ((USART_obj->stop_bits) << (USART_STOP_BITS_POS)); //Stop bits selection

		USART_Array[USART_obj->source]->USART_CR1 |= ((USART_obj->oversampling) << (OVERSAMPLING_BIT_POS)); //Select oversampling mode

		//USART_Handler[USART_obj->source] = USART_obj->USART_Handler;  // Set ISR
		USART_source = USART_obj->source; // Set USART source

		USART_set_Tx_Rx_mode(USART_obj);
	}
	return ret;
}
/**
 * @brief  : De Initialize the USART peripheral
 * @param  : (USART_obj) Pointer to the configuration @ref USART_Config_t
 * @return :
 * 			(RET_OK) : The function done successfully
 * 			(RET_ERROR) : The function has a problem to perform this action
 */
Std_RetType_t USART_de_init(const USART_Config_t* USART_obj)
{
	Std_RetType_t ret = RET_OK;
	if(NULL == USART_obj)
	{
		ret = RET_ERROR;
	}
	else
	{
		USART_Array[USART_obj->source]->USART_CR1 &=~ ((1)<<(USART_TX_INTERRUPT_ENABLE_BIT_POS));	// Disable Tx interrupt
		USART_Array[USART_obj->source]->USART_CR1 &=~ ((1)<<(USART_RX_INTERRUPT_ENABLE_BIT_POS));	// Disable Rx interrupt

		USART_Array[USART_obj->source]->USART_CR1 &=~ (1<<(USART_ENABLE_BIT_POS)); //USART Disable
		USART_Array[USART_obj->source]->USART_BRR = 0;	// clear buadrate register
		USART_Array[USART_obj->source]->USART_CR1 = 0;	// clear CR1 register
		USART_Array[USART_obj->source]->USART_CR2 = 0;	// clear CR2 register
		USART_Array[USART_obj->source]->USART_CR3 = 0;	// clear CR3 register

		if(USART_1 == USART_obj->source)
		{
			nvic_disable(USART1_IRQn);	//Disable USART1 IRQ
		}
		else if(USART_2 == USART_obj->source)
		{
			nvic_disable(USART2_IRQn);	//Disable USART2 IRQ
		}
		else if(USART_6 == USART_obj->source)
		{
			nvic_disable(USART6_IRQn);	//Disable USART6 IRQ
		}

	}
	return ret;
}
/**
 * @brief  : Send a byte via USART with blocking mode (polling)
 * @param  : (USART_obj) Pointer to the configuration @ref USART_Config_t
 * 		   : (byte) the data(byte) to be sent
 * @return :
 * 			(RET_OK) : The function done successfully
 * 			(RET_ERROR) : The function has a problem to perform this action
 */
Std_RetType_t USART_send_byte_blocking(const USART_Config_t* USART_obj , uint8_t byte)
{
	Std_RetType_t ret = RET_OK;
	if(NULL == USART_obj)
	{
		ret = RET_ERROR;
	}
	else
	{

		while(!((USART_Array[USART_obj->source]->USART_SR) & 0x00000080));

		USART_Array[USART_obj->source]->USART_DR = (uint32_t)byte;

		while(!((USART_Array[USART_obj->source]->USART_SR) & 0x00000040));

	}
	return ret;
}
/**
 * @brief  : Receive a byte via USART with blocking mode (polling)
 * @param  : (USART_obj) Pointer to the configuration @ref USART_Config_t
 * 		   : (byte) pointer to store the data(byte) that received
 * @return :
 * 			(RET_OK) : The function done successfully
 * 			(RET_ERROR) : The function has a problem to perform this action
 */
Std_RetType_t USART_receive_byte_blocking(const USART_Config_t* USART_obj , uint8_t *byte)
{
	Std_RetType_t ret = RET_OK;
	if(NULL == USART_obj)
	{
		ret = RET_ERROR;
	}
	else
	{
		while(!((USART_Array[USART_obj->source]->USART_SR) & 0x00000020));
		*byte = (uint8_t)USART_Array[USART_obj->source]->USART_DR;
	}
	return ret;
}
/**
 * @brief  : Send a String of data via USART with blocking mode (polling)
 * @param  : (USART_obj) Pointer to the configuration @ref USART_Config_t
 * 		   : (data) pointer to the data that to be sent
 * @return :
 * 			(RET_OK) : The function done successfully
 * 			(RET_ERROR) : The function has a problem to perform this action
 */
Std_RetType_t USART_send_string_blocking(const USART_Config_t* USART_obj , uint8_t *data)
{
	Std_RetType_t ret = RET_OK;
	if((NULL == USART_obj) || (NULL == data))
	{
		ret = RET_ERROR;
	}
	else
	{
		while(*data !='\0')
		{
			ret = USART_send_byte_blocking(USART_obj , *data++);
		}
	}
	return ret;
}
/**
 * @brief  : Receive a String of data via USART with blocking mode (polling)
 * @param  : (USART_obj) Pointer to the configuration @ref USART_Config_t
 * 		   : (data) pointer to store the data that received
 * @return :
 * 			(RET_OK) : The function done successfully
 * 			(RET_ERROR) : The function has a problem to perform this action
 */
Std_RetType_t USART_receive_string_blocking(const USART_Config_t* USART_obj , uint8_t *data)
{
	Std_RetType_t ret = RET_OK;
	uint8_t counter = 0;
	if((NULL == USART_obj) || (NULL == data))
	{
		ret = RET_ERROR;
	}
	else
	{
		USART_receive_byte_blocking(USART_obj,&data[counter]);
		while(data[counter] != '\r')
		{
			counter++;
			USART_receive_byte_blocking(USART_obj,&data[counter]);
		}
		data[counter] = '\0';
		ret = RET_OK;
	}
	return ret;
}
/**
 * @brief  : Static function to configure the baudrate of the USART
 * @param  : (USART_obj) Pointer to the configuration @ref USART_Config_t
 * @return : void
 */
void usart_set_baud_rate(const USART_Config_t* USART_obj)
{
	uint32_t baudrate = USART_obj->baud_rate;	//baud = (Fck)/(8*(2-OVER8)*USARTDIV);
	uint32_t result;
	uint32_t mantissa;
	uint32_t fraction;
	if(OVERSAMPLING_BY_16==(USART_obj->oversampling))
	{
		result = ((16000000*100)/(8*2*baudrate));
		fraction = (((result%100)*16)+50)/100;
	}
	else
	{
		result = ((16000000)/(8*baudrate))*100;
		fraction = (((result%100)*8)+50)/100;
	}
	mantissa = result/100;
	USART_Array[USART_obj->source]->USART_BRR |= ((mantissa)<< 4);
	USART_Array[USART_obj->source]->USART_BRR |= ((fraction)<< 0);
}
/**
 * @brief  : Static function to : Select the mode of sending & receiving of USART [POLLING , INTERRUPT , DMA]
 * @param  : (USART_obj) Pointer to the configuration @ref USART_Config_t
 * @return : void
 */
void USART_set_Tx_Rx_mode(const USART_Config_t* USART_obj)
{
	switch(USART_obj->tx_mode)
	{
		case POLLING :
				/*no more configuration*/
			break;
		case INTERRUPT :
				USART_Array[USART_obj->source]->USART_CR1 |= ((1)<<(USART_TX_INTERRUPT_ENABLE_BIT_POS));	// Enable Tx interrupt
			break;
		case DMA :

			break;
		default : break;
	}

	switch(USART_obj->rx_mode)
	{
		case POLLING :
				/*no more configuration*/
			break;
		case INTERRUPT :
				USART_Array[USART_obj->source]->USART_CR1 |= ((1)<<(USART_RX_INTERRUPT_ENABLE_BIT_POS));	// Enable Rx interrupt
			break;
		case DMA :

			break;
		default : break;
	}
	if(USART_1 == USART_obj->source)
	{
		nvic_enable(USART1_IRQn);	//Enable USART IRQ
	}
	else if(USART_2 == USART_obj->source)
	{
		nvic_enable(USART2_IRQn);	//Enable USART IRQ
	}
	else if(USART_6 == USART_obj->source)
	{
		nvic_enable(USART6_IRQn);	//Enable USART IRQ
	}
}
/**
 * @brief  : Send a byte via USART with Interrupt mode
 * @param  : (USART_obj) Pointer to the configuration @ref USART_Config_t
 * 		   : (byte) the data(byte) to be sent
 * @return :
 * 			(RET_OK) : The function done successfully
 * 			(RET_ERROR) : The function has a problem to perform this action
 */
Std_RetType_t USART_send_byte_IT(const USART_Config_t* USART_obj , uint8_t byte)
{
	// Wait until the transmitter is ready
	if (tx_ready)
	{
		// Load the byte into the transmit buffer
		tx_buffer = byte;
		tx_ready = 0;  // Mark the transmitter as busy
	}
	return RET_OK;
}
/**
 * @brief  : Receive a byte via USART with Interrupt mode
 * @param  : (USART_obj) Pointer to the configuration @ref USART_Config_t
 * 		   : (byte) pointer to store the data(byte) that received
 * @return :
 * 			(RET_OK) : The function done successfully
 * 			(RET_ERROR) : The function has a problem to perform this action
 */
Std_RetType_t USART_receive_byte_IT(const USART_Config_t* USART_obj , uint8_t *byte)
{
	if (rx_ready)
	{
		// Read the received byte
		*byte = rx_buffer;
		rx_ready = 0;  // Mark the receiver as ready for the next byte
	}
	return RET_OK;
}
/**
 * @brief  : The ISR of USART2
 * @param  : void
 * @return : void
 */
void USART2_IRQHandler(void)
{
	if (USART_Array[USART_source]->USART_SR & USART_RX_FLAG_BIT_POS)
	{
		// clear the flag
		USART_Array[USART_source]->USART_SR &=~ USART_RX_FLAG_BIT_POS;
		// Read the received data
		rx_buffer = (uint8_t)(USART_Array[USART_source]->USART_DR & 0xFF);
		rx_ready = 1;  // Indicate that a byte has been received
	}

	// Check if the TXE flag is set
	if (USART_Array[USART_source]->USART_SR & USART_TX_FLAG_BIT_POS)
	{
		// clear the flag
		USART_Array[USART_source]->USART_SR &=~ USART_TX_FLAG_BIT_POS;
		// If there is data to transmit
		if (!tx_ready) {
			USART_Array[USART_source]->USART_DR = tx_buffer;  // Send the byte
			tx_ready = 1;  // Indicate that the transmission is complete
		}
	}

}
/**
 * @brief  : The ISR of USART2
 * @param  : void
 * @return : void
 */
void USART1_IRQHandler(void)
{
	if (USART_Array[USART_source]->USART_SR & USART_RX_FLAG_BIT_POS)
	{
		// clear the flag
		USART_Array[USART_source]->USART_SR &=~ USART_RX_FLAG_BIT_POS;
		// Read the received data
		rx_buffer = (uint8_t)(USART_Array[USART_source]->USART_DR & 0xFF);
		rx_ready = 1;  // Indicate that a byte has been received
	}

	// Check if the TXE flag is set
	if (USART_Array[USART_source]->USART_SR & USART_TX_FLAG_BIT_POS)
	{
		// clear the flag
		USART_Array[USART_source]->USART_SR &=~ USART_TX_FLAG_BIT_POS;
		// If there is data to transmit
		if (!tx_ready) {
			USART_Array[USART_source]->USART_DR = tx_buffer;  // Send the byte
			tx_ready = 1;  // Indicate that the transmission is complete
		}
	}
}
/**
 * @brief  : The ISR of USART2
 * @param  : void
 * @return : void
 */
void USART6_IRQHandler(void)
{
	if (USART_Array[USART_source]->USART_SR & USART_RX_FLAG_BIT_POS)
	{
		// clear the flag
		USART_Array[USART_source]->USART_SR &=~ USART_RX_FLAG_BIT_POS;
		// Read the received data
		rx_buffer = (uint8_t)(USART_Array[USART_source]->USART_DR & 0xFF);
		rx_ready = 1;  // Indicate that a byte has been received
	}

	// Check if the TXE flag is set
	if (USART_Array[USART_source]->USART_SR & USART_TX_FLAG_BIT_POS)
	{
		// clear the flag
		USART_Array[USART_source]->USART_SR &=~ USART_TX_FLAG_BIT_POS;
		// If there is data to transmit
		if (!tx_ready) {
			USART_Array[USART_source]->USART_DR = tx_buffer;  // Send the byte
			tx_ready = 1;  // Indicate that the transmission is complete
		}
	}
}
