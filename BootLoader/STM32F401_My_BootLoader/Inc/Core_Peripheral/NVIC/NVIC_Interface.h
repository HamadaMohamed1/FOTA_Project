/*
 * NVIC_Interface.h
 *
 *  Created on: Mar 19, 2024
 *      Author: hamada
 */

#ifndef CORE_PERIPHERAL_NVIC_NVIC_INTERFACE_H_
#define CORE_PERIPHERAL_NVIC_NVIC_INTERFACE_H_

/******************* Includes *******************/
#include "NVIC_Private.h"
#include "../../LIBRARY/Common_Macros.h"
#include "../../LIBRARY/Stm32f401xx.h"
/******************* Data Type Declarations *******************/



/******************* Function Declarations *******************/
/**
 * @brief  : Enable interrupt from NVIC
 * @param  : (IRQNum) interrupt request number  @ref IRQn_Type
 * @return :
 * 			(RET_OK) : The function done successfully
 * 			(RET_ERROR) : The function has a problem to perform this action
 */
Std_RetType_t nvic_enable(IRQn_Type IRQNum);
/**
 * @brief  : Disable interrupt from NVIC
 * @param  : (IRQNum) interrupt request number  @ref IRQn_Type
 * @return :
 * 			(RET_OK) : The function done successfully
 * 			(RET_ERROR) : The function has a problem to perform this action
 */
Std_RetType_t nvic_disable(IRQn_Type IRQNum);
/**
 * @brief  : Set pending flag of interrupt from NVIC
 * @param  : (IRQNum) interrupt request number  @ref IRQn_Type
 * @return :
 * 			(RET_OK) : The function done successfully
 * 			(RET_ERROR) : The function has a problem to perform this action
 */
Std_RetType_t nvic_set_pending_flag(IRQn_Type IRQNum);
/**
 * @brief  : Clear pending flag of interrupt from NVIC
 * @param  : (IRQNum) interrupt request number  @ref IRQn_Type
 * @return :
 * 			(RET_OK) : The function done successfully
 * 			(RET_ERROR) : The function has a problem to perform this action
 */
Std_RetType_t nvic_clear_pending_flag(IRQn_Type IRQNum);
/**
 * @brief  : Set priority of interrupt from NVIC
 * @param  : (IRQNum) interrupt request number  @ref IRQn_Type
 * @return :
 * 			(RET_OK) : The function done successfully
 * 			(RET_ERROR) : The function has a problem to perform this action
 */
Std_RetType_t nvic_set_priority(IRQn_Type IRQNum,uint8_t priority);
/**
 * @brief  : Get active flag of interrupt from NVIC
 * @param  : (IRQNum) interrupt request number  @ref IRQn_Type
 * @return :
 * 			(RET_OK) : The function done successfully
 * 			(RET_ERROR) : The function has a problem to perform this action
 */
Std_RetType_t nvic_get_active_flag(IRQn_Type IRQNum , uint8_t *active_value);



#endif /* CORE_PERIPHERAL_NVIC_NVIC_INTERFACE_H_ */
