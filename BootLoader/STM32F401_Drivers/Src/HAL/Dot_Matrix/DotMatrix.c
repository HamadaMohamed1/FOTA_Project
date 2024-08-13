/*
 * DotMatrix.c
 *
 *  Created on: Aug 12, 2024
 *      Author: hamada
 */

/********************************** Includes ********************************************************/
#include "../../../Inc/HAL/Dot_Matrix/DotMatrix_Interface.h"
/********************************** static variables ********************************************/
static const uint8_t row_pins_arr[8] = {DotMatrix_PIN9,DotMatrix_PIN14,DotMatrix_PIN8,DotMatrix_PIN12,DotMatrix_PIN1,DotMatrix_PIN7,DotMatrix_PIN2,DotMatrix_PIN5};
static const uint8_t col_pins_arr[8] = {DotMatrix_PIN13,DotMatrix_PIN3,DotMatrix_PIN4,DotMatrix_PIN10,DotMatrix_PIN6,DotMatrix_PIN11,DotMatrix_PIN15,DotMatrix_PIN16};

/**
 * @brief  : Initialize Dot matrix pins
 * @param  : (void)
 * @return :
 * 			(RET_OK) : The function done successfully
 * 			(RET_ERROR) : The function has a problem to perform this action
 */
Std_RetType_t DotMatrix_init(void)
{
	Std_RetType_t ret = RET_OK;

	for(uint8_t i = 0 ; i < 8 ; i++)
	{
		PinConfig_t local1_pinConfig = { .Port = DotMatrix_Row_Port ,.Pin = row_pins_arr[i] ,.Mode = OUTPUT ,.Type=PUSH_PULL
				, .Speed = MEDUIM , .PullType =NO_PULL
		};
		ret = GPIO_Pin_init(&local1_pinConfig);


		PinConfig_t local2_pinConfig = { .Port = DotMatrix_Col_Port ,.Pin = col_pins_arr[i] ,.Mode = OUTPUT ,.Type=PUSH_PULL
				, .Speed = MEDUIM , .PullType = NO_PULL };

		ret = GPIO_Pin_init(&local2_pinConfig);
	}
	DotMatrix_TurnOff();
	return ret;
}
/**
 * @brief  : Turn off all dot matrix leds
 * @param  : (void)
 * @return :
 * 			(RET_OK) : The function done successfully
 * 			(RET_ERROR) : The function has a problem to perform this action
 */
Std_RetType_t DotMatrix_TurnOff(void)
{
	Std_RetType_t ret = RET_OK;
	for(uint8_t i = 0 ; i < 8 ; i++)
	{
		ret = GPIO_Set_Pin_Value(DotMatrix_Col_Port, col_pins_arr[i], PIN_LOW);
		ret = GPIO_Set_Pin_Value(DotMatrix_Row_Port, row_pins_arr[i], PIN_HIGH);
	}
	return ret ;
}
/**
 * @brief  : Turn on or turn off specific led in dot matrix
 * @param  : (row_number) : led's row
 * 			 (col_number) : led's col
 * 			 (value)      : DOT_MATRIX_LED_ON or DOT_MATRIX_LED_ON
 * @return :
 * 			(RET_OK) : The function done successfully
 * 			(RET_ERROR) : The function has a problem to perform this action
 */
Std_RetType_t DotMatrix_Set_Led_Val(uint8_t row_number ,uint8_t col_number  , uint8_t value)
{
	Std_RetType_t ret = RET_OK;

	switch(value)
	{
	case DOT_MATRIX_LED_ON:
		  ret = GPIO_Set_Pin_Value(DotMatrix_Col_Port, col_pins_arr[col_number-1], PIN_HIGH);
		  ret = GPIO_Set_Pin_Value(DotMatrix_Row_Port, row_pins_arr[row_number-1], PIN_LOW);
	break;
	case DOT_MATRIX_LED_OFF:
		  ret = GPIO_Set_Pin_Value(DotMatrix_Col_Port, col_pins_arr[col_number-1], PIN_LOW);
		  ret = GPIO_Set_Pin_Value(DotMatrix_Row_Port, row_pins_arr[row_number-1], PIN_HIGH);
	break;
	}

	return ret;
}
