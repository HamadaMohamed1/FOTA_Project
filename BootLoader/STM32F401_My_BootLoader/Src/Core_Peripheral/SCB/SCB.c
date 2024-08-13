/*
 * SCB.c
 *
 *  Created on: Apr 9, 2024
 *      Author: hamada
 */

#include "../../../Inc/Core_Peripheral/SCB/SCB_Interface.h"



/**
 * @brief  : Set priority group from SCB
 * @param  : (priority_group)
 * @return :
 * 			(RET_OK) : The function done successfully
 * 			(RET_ERROR) : The function has a problem to perform this action
 */
Std_RetType_t scb_set_priority_group(uint32_t priority_group)
{
	Std_RetType_t ret = RET_OK ;
	if((GROUP_PRIORITIES_8_SUB_PRIORITIES_2==priority_group)||(GROUP_PRIORITIES_4_SUB_PRIORITIES_4==priority_group)||(GROUP_PRIORITIES_2_SUB_PRIORITIES_8==priority_group)||(GROUP_PRIORITIES_1_SUB_PRIORITIES_16==priority_group))
	{
		SCB->AIRCR = priority_group;
	}
	else
	{
		ret = RET_ERROR;
	}
	return ret;
}

Std_RetType_t scb_system_reset_request()
{
	SCB->AIRCR = RESET_SYSTEM_REQUESI;
	return RET_OK;
}


