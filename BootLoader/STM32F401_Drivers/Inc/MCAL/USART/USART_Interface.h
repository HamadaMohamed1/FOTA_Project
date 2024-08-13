/*
 * USART_Interface.h
 *
 *  Created on: Jun 10, 2024
 *      Author: hamada
 */

#ifndef MCAL_USART_USART_INTERFACE_H_
#define MCAL_USART_USART_INTERFACE_H_

/******************* Includes *******************/
#include "USART_Private.h"
/******************* Data Type Declarations *******************/
typedef struct
{
	USART_source_t       			source;
	USART_type_t         			type;
	USART_mode_t         			mode;
	USART_baud_rate_t    			baud_rate;
	USART_stop_bits_t    			stop_bits;
	USART_word_length_t  			word_length;
	USART_parity_t       			parity;
	USART_oversampling_t 			oversampling;
	USART_hardware_control_flow_t   hardware_control_flow;
	USART_Rx_Tx_mode_t 				tx_mode;
	USART_Rx_Tx_mode_t 				rx_mode;
}USART_Config_t;

/******************* Interfaces Declarations *******************/
/**
 * @brief  : Initialize the USART peripheral
 * @param  : (USART_obj) Pointer to the configuration @ref USART_Config_t
 * @return :
 * 			(RET_OK) : The function done successfully
 * 			(RET_ERROR) : The function has a problem to perform this action
 */
Std_RetType_t USART_init(const USART_Config_t* USART_obj);
/**
 * @brief  : De Initialize the USART peripheral
 * @param  : (USART_obj) Pointer to the configuration @ref USART_Config_t
 * @return :
 * 			(RET_OK) : The function done successfully
 * 			(RET_ERROR) : The function has a problem to perform this action
 */
Std_RetType_t USART_de_init(const USART_Config_t* USART_obj);
/**
 * @brief  : Send a byte via USART with blocking mode (polling)
 * @param  : (USART_obj) Pointer to the configuration @ref USART_Config_t
 * 		   : (byte) the data(byte) to be sent
 * @return :
 * 			(RET_OK) : The function done successfully
 * 			(RET_ERROR) : The function has a problem to perform this action
 */
Std_RetType_t USART_send_byte_blocking(const USART_Config_t* USART_obj , uint8_t byte);
/**
 * @brief  : Receive a byte via USART with blocking mode (polling)
 * @param  : (USART_obj) Pointer to the configuration @ref USART_Config_t
 * 		   : (byte) pointer to store the data(byte) that received
 * @return :
 * 			(RET_OK) : The function done successfully
 * 			(RET_ERROR) : The function has a problem to perform this action
 */
Std_RetType_t USART_receive_byte_blocking(const USART_Config_t* USART_obj , uint8_t *byte);
/**
 * @brief  : Send a String of data via USART with blocking mode (polling)
 * @param  : (USART_obj) Pointer to the configuration @ref USART_Config_t
 * 		   : (data) pointer to the data that to be sent
 * @return :
 * 			(RET_OK) : The function done successfully
 * 			(RET_ERROR) : The function has a problem to perform this action
 */
Std_RetType_t USART_send_string_blocking(const USART_Config_t* USART_obj , uint8_t *data);
/**
 * @brief  : Receive a String of data via USART with blocking mode (polling)
 * @param  : (USART_obj) Pointer to the configuration @ref USART_Config_t
 * 		   : (data) pointer to store the data that received
 * @return :
 * 			(RET_OK) : The function done successfully
 * 			(RET_ERROR) : The function has a problem to perform this action
 */
Std_RetType_t USART_receive_string_blocking(const USART_Config_t* USART_obj , uint8_t *data);

/*****************************************************************************/
/**
 * @brief  : Send a byte via USART with Interrupt mode
 * @param  : (USART_obj) Pointer to the configuration @ref USART_Config_t
 * 		   : (byte) the data(byte) to be sent
 * @return :
 * 			(RET_OK) : The function done successfully
 * 			(RET_ERROR) : The function has a problem to perform this action
 */
Std_RetType_t USART_send_byte_IT(const USART_Config_t* USART_obj , uint8_t byte);
/**
 * @brief  : Receive a byte via USART with Interrupt mode
 * @param  : (USART_obj) Pointer to the configuration @ref USART_Config_t
 * 		   : (byte) pointer to store the data(byte) that received
 * @return :
 * 			(RET_OK) : The function done successfully
 * 			(RET_ERROR) : The function has a problem to perform this action
 */
Std_RetType_t USART_receive_byte_IT(const USART_Config_t* USART_obj , uint8_t *byte);

/*****************************************************************************/



#endif /* MCAL_USART_USART_INTERFACE_H_ */
