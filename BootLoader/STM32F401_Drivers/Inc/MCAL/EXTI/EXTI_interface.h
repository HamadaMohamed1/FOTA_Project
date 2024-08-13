/*
 * EXTI_interface.h
 *
 *  Created on: Apr 12, 2024
 *      Author: hamada
 */

#ifndef MCAL_EXTI_EXTI_INTERFACE_H_
#define MCAL_EXTI_EXTI_INTERFACE_H_

/******************* Includes *******************/
#include "EXTI_private.h"
#include "../../LIBRARY/Common_Macros.h"
#include "../../LIBRARY/Stm32f401xx.h"
/******************* Data type Declaration *******************/
typedef struct
{
	void (* EXTI_handler)(void);
	EXTI_edge_t EXTI_edge;
	EXTI_source_t source;
}EXTI_config_t;


/******************* Interfaces Declaration *******************/

/**
 * @brief  : Initialize the external interrupt pin
 * @param  : (EXTI_object) pointer to configuration @ref EXTI_config_t
 * @return :
 * 			(RET_OK) : The function done successfully
 * 			(RET_ERROR) : The function has a problem to perform this action
 */
Std_RetType_t EXTI_initialize(const EXTI_config_t* EXTI_object);
/**
 * @brief  : Enable interrupt to specific pin
 * @param  : (EXTI_source) interrupt source pin @ref EXTI_source_t
 * @return :
 * 			(RET_OK) : The function done successfully
 * 			(RET_ERROR) : The function has a problem to perform this action
 */
Std_RetType_t EXTI_enable(EXTI_source_t EXTI_source);
/**
 * @brief  : Disable interrupt to specific pin
 * @param  : (EXTI_source) interrupt source pin @ref EXTI_source_t
 * @return :
 * 			(RET_OK) : The function done successfully
 * 			(RET_ERROR) : The function has a problem to perform this action
 */
Std_RetType_t EXTI_disable(EXTI_source_t EXTI_source);
/**
 * @brief  : Set pending flag of external interrupt
 * @param  : (EXTI_object) pointer to configuration @ref EXTI_config_t
 * @return :
 * 			(RET_OK) : The function done successfully
 * 			(RET_ERROR) : The function has a problem to perform this action
 */
Std_RetType_t EXTI_set_pending_flag(const EXTI_config_t* EXTI_object);
/**
 * @brief  : Clear pending flag of external interrupt
 * @param  : (EXTI_source) interrupt source pin @ref EXTI_source_t
 * @return :
 * 			(RET_OK) : The function done successfully
 * 			(RET_ERROR) : The function has a problem to perform this action
 */
Std_RetType_t EXTI_clear_pending_flag(EXTI_source_t EXTI_source);
/**
 * @brief  : Read pending flag of external interrupt
 * @param  : (EXTI_source) interrupt source pin @ref EXTI_source_t
 * @param  : (pending_flag) pointer to store the flag's value  @ref pending_flag_t
 * @return :
 * 			(RET_OK) : The function done successfully
 * 			(RET_ERROR) : The function has a problem to perform this action
 */
Std_RetType_t EXTI_read_pending_flag(EXTI_source_t EXTI_source, pending_flag_t* pending_flag);

#endif /* MCAL_EXTI_EXTI_INTERFACE_H_ */
