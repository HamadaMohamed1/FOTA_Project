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
#include "../Inc/Core_Peripheral/SCB/SCB_Interface.h"
#include "../Inc/MCAL/SYSCFG/syscfg_interface.h"
#include "../Inc/MCAL/USART/USART_Interface.h"
#include <string.h>
#include "../Inc/BootLoader/BootLoader.h"
#include "../Inc/MCAL/CRC/CRC.h"

/******************* Interfaces Declaration *******************/

Std_RetType_t SystemClock_Config(void);

void BootLoader_UARTReadData(void);

void BootLoader_JumpToUserApp(void);




#endif /* MAIN_H_ */
