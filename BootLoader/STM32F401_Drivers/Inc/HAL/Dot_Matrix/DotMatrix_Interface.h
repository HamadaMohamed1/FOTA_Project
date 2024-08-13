/*
 * DotMatrix_Interface.h
 *
 *  Created on: Aug 12, 2024
 *      Author: hamada
 */

#ifndef HAL_DOT_MATRIX_DOTMATRIX_INTERFACE_H_
#define HAL_DOT_MATRIX_DOTMATRIX_INTERFACE_H_
/********************************** Includes ********************************************************/
#include "DotMatrix_Private.h"
#include "../../MCAL/GPIO/GPIO_Interface.h"
/********************************** Macro Declaration ***********************************************/


			/*Port B */
#define DotMatrix_Row_Port 		PORTB

#define DotMatrix_PIN9 			PIN0
#define DotMatrix_PIN14			PIN1
#define DotMatrix_PIN8 			PIN2
#define DotMatrix_PIN12 		PIN3
#define DotMatrix_PIN1			PIN4
#define DotMatrix_PIN7 			PIN5
#define DotMatrix_PIN2 			PIN6
#define DotMatrix_PIN5 			PIN7
			/*Port A */
#define DotMatrix_Col_Port 		PORTA

#define DotMatrix_PIN13 		PIN4
#define DotMatrix_PIN3 			PIN5
#define DotMatrix_PIN4			PIN6
#define DotMatrix_PIN10 		PIN7
#define DotMatrix_PIN6 			PIN8
#define DotMatrix_PIN11 		PIN9
#define DotMatrix_PIN15 		PIN10
#define DotMatrix_PIN16 		PIN11
/********************************** Function Declaration ********************************************************/
/**
 * @brief  : Initialize Dot matrix pins
 * @param  : (void)
 * @return :
 * 			(RET_OK) : The function done successfully
 * 			(RET_ERROR) : The function has a problem to perform this action
 */
Std_RetType_t DotMatrix_init(void);
/**
 * @brief  : Turn off all dot matrix leds
 * @param  : (void)
 * @return :
 * 			(RET_OK) : The function done successfully
 * 			(RET_ERROR) : The function has a problem to perform this action
 */
Std_RetType_t DotMatrix_TurnOff(void);
/**
 * @brief  : Turn on or turn off specific led in dot matrix
 * @param  : (row_number) : led's row
 * 			 (col_number) : led's col
 * 			 (value)      : DOT_MATRIX_LED_ON or DOT_MATRIX_LED_ON
 * @return :
 * 			(RET_OK) : The function done successfully
 * 			(RET_ERROR) : The function has a problem to perform this action
 */
Std_RetType_t DotMatrix_Set_Led_Val(uint8_t row_number ,uint8_t col_number  , uint8_t value);









#endif /* HAL_DOT_MATRIX_DOTMATRIX_INTERFACE_H_ */
