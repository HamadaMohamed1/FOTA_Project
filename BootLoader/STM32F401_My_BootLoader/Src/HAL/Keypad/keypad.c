/*
 * keypad.c
 *
 *  Created on: Mar 17, 2024
 *      Author: hamada
 */

#include "../../../Inc/HAL/Keypad/keypad_Interface.h"




static const uint8_t keypad_values[KEYPAD_ROWS][KEYPAD_COLUMNS] =
{
		{'7','8','9','/'},
		{'4','5','6','*'},
		{'1','2','3','-'},
		{'#','0','=','+'}
};

static Std_RetType_t keypad_pins_init(Port_t port, Pin_t pin, Mode_t mode);
/**
 * @brief  : Initialize the Keypad pins
 * @param  : (keypad_obj) Pointer to the configuration @ref keypad_t
 * @return :
 * 			(RET_OK) : The function done successfully
 * 			(RET_ERROR) : The function has a problem to perform this action
 */
Std_RetType_t keypad_initialize(const keypad_t *keypad_obj)
{
	Std_RetType_t ret = RET_OK;
	uint8_t local_counter =0;
	if(NULL == keypad_obj)
	{
		ret  = RET_ERROR ;
	}
	else
	{
		for(local_counter = 0 ; local_counter < KEYPAD_ROWS ;local_counter++)
		{
			/*Assume using rows as output & columns as input*/
			keypad_pins_init(keypad_obj->port , keypad_obj->kpd_row_pins[local_counter] ,OUTPUT);
		}
		for(local_counter = 0 ; local_counter < KEYPAD_COLUMNS ;local_counter++)
		{
			keypad_pins_init(keypad_obj->port , keypad_obj->kpd_col_pins[local_counter] ,INPUT);
		}
	}
	return ret;
}
/**
 * @brief  : Get the key value from keypad
 * @param  : (keypad_obj) Pointer to the configuration @ref keypad_t
 * @return : (value) Pointer to store the key value
 * 			(RET_OK) : The function done successfully
 * 			(RET_ERROR) : The function has a problem to perform this action
 */
Std_RetType_t keypad_get_value(const keypad_t *keypad_obj , uint8_t *value)
{
	Std_RetType_t ret = RET_OK;
	uint8_t local_row_counter =0;
	uint8_t local_col_counter =0;
	uint8_t local_counter =0;
	uint8_t logic;

	if((NULL == keypad_obj) || (NULL == value))
	{
		ret  = RET_ERROR ;
	}
	else
	{
		for(local_row_counter = 0 ; local_row_counter < KEYPAD_ROWS ; local_row_counter++)
		{
			for(local_counter= 0 ; local_counter < KEYPAD_ROWS ; local_counter++)
			{
				/*write to all col pins logic high*/
				ret = GPIO_Set_Pin_Value(keypad_obj->port, keypad_obj->kpd_row_pins[local_counter], PIN_HIGH);
			}
			ret = GPIO_Set_Pin_Value(keypad_obj->port, keypad_obj->kpd_row_pins[local_row_counter], PIN_LOW);
			delay_ms(15);
			for(local_col_counter=0;local_col_counter<KEYPAD_COLUMNS ; local_col_counter++)
			{
				ret = GPIO_Get_Pin_Value(keypad_obj->port, keypad_obj->kpd_col_pins[local_col_counter], &logic);
				if(PIN_LOW == logic)
				{
					*value = keypad_values[local_row_counter][local_col_counter];
				}
			}
		}
	}
	return ret;
}


static Std_RetType_t keypad_pins_init(Port_t port, Pin_t pin , Mode_t mode)
{
	Std_RetType_t ret = RET_OK;
	PinConfig_t keypad_pin = { .Port = port ,.Pin = pin,.Type = PUSH_PULL
			, .Speed = MEDUIM , .PullType = NO_PULL
	};
	if(OUTPUT == mode)
	{
		keypad_pin.Mode = OUTPUT;
		ret = GPIO_Pin_init(&keypad_pin);
	}
	else if(INPUT == mode)
	{
		keypad_pin.Mode = INPUT;
		ret = GPIO_Pin_init(&keypad_pin);
	}
	else
	{
		ret = RET_ERROR;
	}
	return ret;
}
