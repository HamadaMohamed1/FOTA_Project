/*
 * led_interface.h
 *
 *  Created on: Mar 18, 2024
 *      Author: hamada
 */

#ifndef HAL_LED_LED_INTERFACE_H_
#define HAL_LED_LED_INTERFACE_H_

/******************* Includes *******************/
#include "../../MCAL/GPIO/GPIO_Interface.h"
#include "../../LIBRARY/Common_Macros.h"
/******************* Data Type Declarations *******************/
typedef struct
{
	Port_t 		port; //LED port
	Pin_t  		pin;  //LED pin Num
	PinValue_t  logic;//LED default state
}led_t;
/******************* Interfaces Declarations *******************/
/**
 * @brief  : Initialize the LED pin
 * @param  : (led) Pointer to the configuration @ref led_t
 * @return :
 * 			(RET_OK) : The function done successfully
 * 			(RET_ERROR) : The function has a problem to perform this action
 */
Std_RetType_t led_initialize(const led_t *led);
/**
 * @brief  : Turn on the LED
 * @param  : (led) Pointer to the configuration @ref led_t
 * @return :
 * 			(RET_OK) : The function done successfully
 * 			(RET_ERROR) : The function has a problem to perform this action
 */
Std_RetType_t led_turn_on(const led_t *led);
/**
 * @brief  : Turn off the LED
 * @param  : (led) Pointer to the configuration @ref led_t
 * @return :
 * 			(RET_OK) : The function done successfully
 * 			(RET_ERROR) : The function has a problem to perform this action
 */
Std_RetType_t led_turn_off(const led_t *led);
/**
 * @brief  : Turn toggle the LED
 * @param  : (led) Pointer to the configuration @ref led_t
 * @return :
 * 			(RET_OK) : The function done successfully
 * 			(RET_ERROR) : The function has a problem to perform this action
 */
Std_RetType_t led_turn_toggle(const led_t *led);
#endif /* HAL_LED_LED_INTERFACE_H_ */
