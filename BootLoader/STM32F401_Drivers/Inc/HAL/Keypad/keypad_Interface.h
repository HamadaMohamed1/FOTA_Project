/*
 * keypad.h
 *
 *  Created on: Mar 17, 2024
 *      Author: hamada
 */

#ifndef HAL_KEYPAD_KEYPAD_INTERFACE_H_
#define HAL_KEYPAD_KEYPAD_INTERFACE_H_

/******************* Includes *******************/
#include "Keypad_Private.h"
#include "../../MCAL/GPIO/GPIO_Interface.h"
#include "../../LIBRARY/Common_Macros.h"
#include "../../Core_Peripheral/SystTick/SystTick_Interface.h"

/******************* Data Type Declarations *******************/
typedef struct{
	Port_t port;
	Pin_t  kpd_row_pins[4];
	Pin_t  kpd_col_pins[4];
}keypad_t;

/******************* Interfaces Declarations *******************/
/**
 * @brief  : Initialize the Keypad pins
 * @param  : (keypad_obj) Pointer to the configuration @ref keypad_t
 * @return :
 * 			(RET_OK) : The function done successfully
 * 			(RET_ERROR) : The function has a problem to perform this action
 */
Std_RetType_t keypad_initialize(const keypad_t *keypad_obj);
/**
 * @brief  : Get the key value from keypad
 * @param  : (keypad_obj) Pointer to the configuration @ref keypad_t
 * @return : (value) Pointer to store the key value
 * 			(RET_OK) : The function done successfully
 * 			(RET_ERROR) : The function has a problem to perform this action
 */
Std_RetType_t keypad_get_value(const keypad_t *keypad_obj , uint8_t *value);


#endif /* HAL_KEYPAD_KEYPAD_INTERFACE_H_ */
