/*
 * SystTick.h
 *
 *  Created on: Mar 15, 2024
 *      Author: hamada
 */

#ifndef CORE_PERIPHERAL_SYSTTICK_SYSTTICK_INTERFACE_H_
#define CORE_PERIPHERAL_SYSTTICK_SYSTTICK_INTERFACE_H_

/******************* Includes *******************/
#include "SystTick_Private.h"
#include "../../LIBRARY/Common_Macros.h"
#include "../../LIBRARY/Stm32f401xx.h"


/******************* Interface Declarations *******************/
/**
 * @brief  : Initialize the Systick timer
 * @param  :
 * @return :
 * 			(RET_OK) : The function done successfully
 * 			(RET_ERROR) : The function has a problem to perform this action
 */
Std_RetType_t Systick_init(void);
/**
 * @brief  : Systick_Wait_Blocking
 * @param  : (NO_Tick) : number of ticks
 * @return :
 * 			(RET_OK) : The function done successfully
 * 			(RET_ERROR) : The function has a problem to perform this action
 */
Std_RetType_t Systick_Wait_Blocking(uint32_t NO_Tick);


/**
 * @brief  : Delay with Blocking
 * @param  : (ms) : number of Millie seconds
 * @return :
 *
 */
void delay_ms(uint32_t ms);
/**
 * @brief  : Delay with Blocking
 * @param  : (us) : number of Micro seconds
 * @return :
 *
 */
void delay_us(uint32_t us);







#endif /* CORE_PERIPHERAL_SYSTTICK_SYSTTICK_INTERFACE_H_ */
