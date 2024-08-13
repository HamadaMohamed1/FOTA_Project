/*
 * SCB_Interface.h
 *
 *  Created on: Apr 9, 2024
 *      Author: hamada
 */

#ifndef CORE_PERIPHERAL_SCB_SCB_INTERFACE_H_
#define CORE_PERIPHERAL_SCB_SCB_INTERFACE_H_

/******************* Includes *******************/
#include "SCB_Private.h"
#include "../../LIBRARY/Common_Macros.h"
#include "../../LIBRARY/Stm32f401xx.h"
/******************* Data Type Declarations *******************/

/******************* Function Declarations *******************/

/**
 * @brief  : Set priority group from SCB
 * @param  : (priority_group)
 * @return :
 * 			(RET_OK) : The function done successfully
 * 			(RET_ERROR) : The function has a problem to perform this action
 */
Std_RetType_t scb_set_priority_group(uint32_t priority_group);


Std_RetType_t scb_system_reset_request();



#endif /* CORE_PERIPHERAL_SCB_SCB_INTERFACE_H_ */
