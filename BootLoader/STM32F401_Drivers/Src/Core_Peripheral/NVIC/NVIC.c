/*
 * NVIC.c
 *
 *  Created on: Mar 19, 2024
 *      Author: hamada
 */

#include "../../../Inc/Core_Peripheral/NVIC/NVIC_Interface.h"


/**
 * @brief  : Enable interrupt from NVIC
 * @param  : (IRQNum) interrupt request number  @ref IRQn_Type
 * @return :
 * 			(RET_OK) : The function done successfully
 * 			(RET_ERROR) : The function has a problem to perform this action
 */
Std_RetType_t nvic_enable(IRQn_Type IRQNum)
{
	Std_RetType_t ret = RET_OK;
	uint8_t l_Reg_num ;
	uint8_t l_Bit_num ;
	if(IRQNum > SPI4_IRQn)
	{
		ret = RET_ERROR;
	}
	else
	{
		/*interrupt enable*/
		l_Reg_num = (IRQNum / 32);
		l_Bit_num = (IRQNum % 32);
		NVIC->ISER[l_Reg_num] = (1<<l_Bit_num);
	}
	return ret;
}
/**
 * @brief  : Disable interrupt from NVIC
 * @param  : (IRQNum) interrupt request number  @ref IRQn_Type
 * @return :
 * 			(RET_OK) : The function done successfully
 * 			(RET_ERROR) : The function has a problem to perform this action
 */
Std_RetType_t nvic_disable(IRQn_Type IRQNum)
{
	Std_RetType_t ret = RET_OK;
	uint8_t l_Reg_num ;
	uint8_t l_Bit_num ;
	if(IRQNum > SPI4_IRQn)
	{
		ret = RET_ERROR;
	}
	else
	{
		l_Reg_num = (IRQNum / 32);
		l_Bit_num = (IRQNum % 32);
		NVIC->ICER[l_Reg_num] = (1<<l_Bit_num);
	}
	return ret;
}

/**
 * @brief  : Set priority of interrupt from NVIC
 * @param  : (IRQNum) interrupt request number  @ref IRQn_Type
 * @return :
 * 			(RET_OK) : The function done successfully
 * 			(RET_ERROR) : The function has a problem to perform this action
 */
Std_RetType_t nvic_set_priority(IRQn_Type IRQNum,uint8_t priority)
{
	Std_RetType_t ret = RET_OK;
	if(IRQNum > SPI4_IRQn)
	{
		ret = RET_ERROR;
	}
	else
	{
		/*set priority of the interrupt */
		NVIC->IPR[IRQNum] = (priority << 4U);
	}
	return ret;
}

/**
 * @brief  : Set pending flag of interrupt from NVIC
 * @param  : (IRQNum) interrupt request number  @ref IRQn_Type
 * @return :
 * 			(RET_OK) : The function done successfully
 * 			(RET_ERROR) : The function has a problem to perform this action
 */
Std_RetType_t nvic_set_pending_flag(IRQn_Type IRQNum)
{
	Std_RetType_t ret = RET_OK;
	uint8_t l_Reg_num ;
	uint8_t l_Bit_num ;
	if(IRQNum > SPI4_IRQn)
	{
		ret = RET_ERROR;
	}
	else
	{
		l_Reg_num = (IRQNum / 32);
		l_Bit_num = (IRQNum % 32);
		NVIC->ISPR[l_Reg_num] = (1<<l_Bit_num);
	}
	return ret;
}
/**
 * @brief  : Clear pending flag of interrupt from NVIC
 * @param  : (IRQNum) interrupt request number  @ref IRQn_Type
 * @return :
 * 			(RET_OK) : The function done successfully
 * 			(RET_ERROR) : The function has a problem to perform this action
 */
Std_RetType_t nvic_clear_pending_flag(IRQn_Type IRQNum)
{
	Std_RetType_t ret = RET_OK;
	uint8_t l_Reg_num ;
	uint8_t l_Bit_num ;
	if(IRQNum > SPI4_IRQn)
	{
		ret = RET_ERROR;
	}
	else
	{
		l_Reg_num = (IRQNum / 32);
		l_Bit_num = (IRQNum % 32);
		NVIC->ICPR[l_Reg_num] = (1<<l_Bit_num);
	}
	return ret;
}
/**
 * @brief  : Get active flag of interrupt from NVIC
 * @param  : (IRQNum) interrupt request number  @ref IRQn_Type
 * @return :
 * 			(RET_OK) : The function done successfully
 * 			(RET_ERROR) : The function has a problem to perform this action
 */
Std_RetType_t nvic_get_active_flag(IRQn_Type IRQNum , uint8_t *active_value)
{
	Std_RetType_t ret = RET_OK;
	uint8_t l_Reg_num ;
	uint8_t l_Bit_num ;
	if(IRQNum > SPI4_IRQn)
	{
		ret = RET_ERROR;
	}
	else
	{
		l_Reg_num = (IRQNum / 32);
		l_Bit_num = (IRQNum % 32);
		*active_value = ((NVIC->IABR[l_Reg_num]) & (1<<l_Bit_num));
	}
	return ret;
}
