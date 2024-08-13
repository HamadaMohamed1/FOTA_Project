/*
 * main.h
 *
 *  Created on: Mar 14, 2024
 *      Author: hamada
 */

#ifndef MAIN_H_
#define MAIN_H_

/******************* Includes *******************/

#include "../Inc/LIBRARY/Common_Macros.h"
#include "../Inc/MCAL/RCC/RCC.h"
#include "../Inc/MCAL/GPIO/GPIO_Interface.h"
#include "Core_Peripheral/SystTick/SystTick_Interface.h"
#include "../Inc/HAL/LCD/lcd.h"
#include "../Inc/HAL/Keypad/keypad_Interface.h"
#include "../Inc/HAL/LED/led_interface.h"
#include "../Inc/Core_Peripheral/NVIC/NVIC_Interface.h"
#include "../Inc/Core_Peripheral/SCB/SCB_Interface.h"
#include "../Inc/MCAL/SYSCFG/syscfg_interface.h"
#include "../Inc/MCAL/EXTI/EXTI_interface.h"
#include "../Inc/MCAL/USART/USART_Interface.h"
#include "../Inc/MCAL/SPI/SPI_Interface.h"
#include "../Inc/MCAL/I2C/I2C_Interface.h"
#include "../Inc/HAL/Dot_Matrix/DotMatrix_Interface.h"
/******************* Interfaces Declaration *******************/

Std_RetType_t SystemClock_Config(void);


#endif /* MAIN_H_ */
