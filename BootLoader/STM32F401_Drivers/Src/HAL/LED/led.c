/*
 * led.c
 *
 *  Created on: Mar 18, 2024
 *      Author: hamada
 */

#include "../../../Inc/HAL/LED/led_interface.h"
/**
 * @brief  : Initialize the LED pin
 * @param  : (led) Pointer to the configuration @ref led_t
 * @return :
 * 			(RET_OK) : The function done successfully
 * 			(RET_ERROR) : The function has a problem to perform this action
 */
Std_RetType_t led_initialize(const led_t *led)
{
	Std_RetType_t ret = RET_OK;
	if(NULL == led)
	{
		ret = RET_ERROR;
	}
	else
	{
		PinConfig_t led_pin = {
							.Port = led->port ,.Pin = led->pin,.Mode = OUTPUT ,.Type=PUSH_PULL,
						    .Speed = MEDUIM , .PullType = NO_PULL
							};
		ret = GPIO_Pin_init(&led_pin);
		ret = GPIO_Set_Pin_Value(led->port, led->pin, led->logic);
	}
	return ret;
}
/**
 * @brief  : Turn on the LED
 * @param  : (led) Pointer to the configuration @ref led_t
 * @return :
 * 			(RET_OK) : The function done successfully
 * 			(RET_ERROR) : The function has a problem to perform this action
 */
Std_RetType_t led_turn_on(const led_t *led)
{
	Std_RetType_t ret = RET_OK;
	if(NULL == led)
	{
		ret = RET_ERROR;
	}
	else
	{
		ret = GPIO_Set_Pin_Value(led->port, led->pin, PIN_HIGH);
	}
	return ret;
}
/**
 * @brief  : Turn off the LED
 * @param  : (led) Pointer to the configuration @ref led_t
 * @return :
 * 			(RET_OK) : The function done successfully
 * 			(RET_ERROR) : The function has a problem to perform this action
 */
Std_RetType_t led_turn_off(const led_t *led)
{
	Std_RetType_t ret = RET_OK;
	if(NULL == led)
	{
		ret = RET_ERROR;
	}
	else
	{
		ret = GPIO_Set_Pin_Value(led->port, led->pin, PIN_LOW);
	}
	return ret;
}
/**
 * @brief  : Turn toggle the LED
 * @param  : (led) Pointer to the configuration @ref led_t
 * @return :
 * 			(RET_OK) : The function done successfully
 * 			(RET_ERROR) : The function has a problem to perform this action
 */
Std_RetType_t led_turn_toggle(const led_t *led)
{
	Std_RetType_t ret = RET_OK;
	if(NULL == led)
	{
		ret = RET_ERROR;
	}
	else
	{
		ret = GPIO_Toggle_Pin_Value(led->port, led->pin);
	}
	return ret;
}
