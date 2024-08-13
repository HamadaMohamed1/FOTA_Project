/*
 * EXTI.c
 *
 *  Created on: Apr 12, 2024
 *      Author: hamada
 */

/*************************** Includes ******************************/
#include "../../../Inc/MCAL/EXTI/EXTI_interface.h"
/*************************** static global variables ******************************/
static void (* EXTI_Handler[EXTI_MAX_NUMBER])(void) ={NULL};
static EXTI_source_t EXTI_source ;

/**
 * @brief  : Initialize the external interrupt pin
 * @param  : (EXTI_object) pointer to configuration @ref EXTI_config_t
 * @return :
 * 			(RET_OK) : The function done successfully
 * 			(RET_ERROR) : The function has a problem to perform this action
 */
Std_RetType_t EXTI_initialize(const EXTI_config_t* EXTI_object)
{
	Std_RetType_t ret = RET_OK;
	if(NULL == EXTI_object)
	{
		ret =  RET_ERROR;
	}
	else
	{
		//configure edge
		switch(EXTI_object->EXTI_edge)
		{
			case RISING_EDGE :
				EXTI->RTSR |=  (1 << EXTI_object->source);
				EXTI->FTSR &=~ (1 << EXTI_object->source);
			break;
			case FALLING_EDGE :
				EXTI->FTSR |=  (1 << EXTI_object->source);
				EXTI->RTSR &=~ (1 << EXTI_object->source);
			break;
			case RISING_FALLING_EDGE :
				EXTI->RTSR |=  (1 << EXTI_object->source);
				EXTI->FTSR |=  (1 << EXTI_object->source);
			break;
			default : ret = RET_ERROR;
			break;
		}
		// initiate call back
		EXTI_Handler[EXTI_object->source] = EXTI_object->EXTI_handler;
		// initiate EXTI_source
		EXTI_source = EXTI_object->source;
	}
	return ret;
}
/**
 * @brief  : Enable interrupt to specific pin
 * @param  : (EXTI_source) interrupt source pin @ref EXTI_source_t
 * @return :
 * 			(RET_OK) : The function done successfully
 * 			(RET_ERROR) : The function has a problem to perform this action
 */
Std_RetType_t EXTI_enable(EXTI_source_t EXTI_source)
{
	EXTI->IMR |= (1 << EXTI_source);
	return RET_OK;
}
/**
 * @brief  : Disable interrupt to specific pin
 * @param  : (EXTI_source) interrupt source pin @ref EXTI_source_t
 * @return :
 * 			(RET_OK) : The function done successfully
 * 			(RET_ERROR) : The function has a problem to perform this action
 */
Std_RetType_t EXTI_disable(EXTI_source_t EXTI_source)
{
	EXTI->IMR &= ~(1 << EXTI_source);
	return RET_OK;
}
/**
 * @brief  : Set pending flag of external interrupt
 * @param  : (EXTI_object) pointer to configuration @ref EXTI_config_t
 * @return :
 * 			(RET_OK) : The function done successfully
 * 			(RET_ERROR) : The function has a problem to perform this action
 */
Std_RetType_t EXTI_set_pending_flag(const EXTI_config_t* EXTI_object)
{
	Std_RetType_t ret = RET_OK;
	if(NULL == EXTI_object)
	{
		ret =  RET_ERROR;
	}
	else
	{
		EXTI->SWIER |= (1 << EXTI_object->source);
	}
	return ret;
}
/**
 * @brief  : Clear pending flag of external interrupt
 * @param  : (EXTI_source) interrupt source pin @ref EXTI_source_t
 * @return :
 * 			(RET_OK) : The function done successfully
 * 			(RET_ERROR) : The function has a problem to perform this action
 */
Std_RetType_t EXTI_clear_pending_flag(EXTI_source_t EXTI_source)
{
	// clearing pending flag is done by programming the bit to '1'
	EXTI->PR |= (1 << EXTI_source);
	return RET_OK;
}
/**
 * @brief  : Read pending flag of external interrupt
 * @param  : (EXTI_source) interrupt source pin @ref EXTI_source_t
 * @param  : (pending_flag) pointer to store the flag's value  @ref pending_flag_t
 * @return :
 * 			(RET_OK) : The function done successfully
 * 			(RET_ERROR) : The function has a problem to perform this action
 */
Std_RetType_t EXTI_read_pending_flag(EXTI_source_t EXTI_source, pending_flag_t* pending_flag)
{

	*pending_flag = EXTI->PR & (1 << EXTI_source) ? INT_TRIGGERED : INT_NOT_TRIGGERED;
	return RET_OK;
}
/**************************************** EXTI ISRs ********************************************************/
/**
 * @brief  : (ISR)Interrupt service routine for (External interrupt # 0)
 * @param  : void
 * @return : void
 *
 */
void EXTI0_IRQHandler(void)
{
	EXTI_clear_pending_flag(EXTI_source);
	if(NULL != EXTI_Handler[EXTI_source])
	{
		EXTI_Handler[EXTI_source]();
	}
}
/**
 * @brief  : (ISR)Interrupt service routine for (External interrupt # 1)
 * @param  : void
 * @return : void
 *
 */
void EXTI1_IRQHandler(void)
{
	EXTI_clear_pending_flag(EXTI_source);
	if(NULL != EXTI_Handler[EXTI_source])
	{
		EXTI_Handler[EXTI_source]();
	}
}
/**
 * @brief  : (ISR)Interrupt service routine for (External interrupt # 2)
 * @param  : void
 * @return : void
 *
 */
void EXTI2_IRQHandler(void)
{
	EXTI_clear_pending_flag(EXTI_source);
	if(NULL != EXTI_Handler[EXTI_source])
	{
		EXTI_Handler[EXTI_source]();
	}
}
/**
 * @brief  : (ISR)Interrupt service routine for (External interrupt # 3)
 * @param  : void
 * @return : void
 *
 */
void EXTI3_IRQHandler(void)
{
	EXTI_clear_pending_flag(EXTI_source);
	if(NULL != EXTI_Handler[EXTI_source])
	{
		EXTI_Handler[EXTI_source]();
	}
}
/**
 * @brief  : (ISR)Interrupt service routine for (External interrupt # 4)
 * @param  : void
 * @return : void
 *
 */
void EXTI4_IRQHandler(void)
{
	EXTI_clear_pending_flag(EXTI_source);
	if(NULL != EXTI_Handler[EXTI_source])
	{
		EXTI_Handler[EXTI_source]();
	}
}
/**
 * @brief  : (ISR)Interrupt service routine for (External interrupt # 5 : 9)
 * @param  : void
 * @return : void
 *
 */
void EXTI9_5_IRQHandler(void)
{
	pending_flag_t flag = INT_NOT_TRIGGERED;
	EXTI_read_pending_flag(EXTI_5 , &flag);
	if(INT_TRIGGERED == flag)
	{
		EXTI_clear_pending_flag(EXTI_5);
		if(NULL != EXTI_Handler[EXTI_source])
		{
			EXTI_Handler[EXTI_source]();
		}
		flag = INT_NOT_TRIGGERED;
	}
	EXTI_read_pending_flag(EXTI_6 , &flag);
	if(INT_TRIGGERED == flag)
	{
		EXTI_clear_pending_flag(EXTI_6);
		if(NULL != EXTI_Handler[EXTI_source])
		{
			EXTI_Handler[EXTI_source]();
		}
		flag = INT_NOT_TRIGGERED;
	}
	EXTI_read_pending_flag(EXTI_7 , &flag);
	if(INT_TRIGGERED == flag)
	{
		EXTI_clear_pending_flag(EXTI_7);
		if(NULL != EXTI_Handler[EXTI_source])
		{
			EXTI_Handler[EXTI_source]();
		}
		flag = INT_NOT_TRIGGERED;
	}
	EXTI_read_pending_flag(EXTI_8 , &flag);
	if(INT_TRIGGERED == flag)
	{
		EXTI_clear_pending_flag(EXTI_8);
		if(NULL != EXTI_Handler[EXTI_source])
		{
			EXTI_Handler[EXTI_source]();
		}
		flag = INT_NOT_TRIGGERED;
	}
	EXTI_read_pending_flag(EXTI_9 , &flag);
	if(INT_TRIGGERED == flag)
	{
		EXTI_clear_pending_flag(EXTI_9);
		if(NULL != EXTI_Handler[EXTI_source])
		{
			EXTI_Handler[EXTI_source]();
		}
		flag = INT_NOT_TRIGGERED;
	}
}
/**
 * @brief  : (ISR)Interrupt service routine for (External interrupt # 10 : 15)
 * @param  : void
 * @return : void
 *
 */
void EXTI15_10_IRQHandler(void)
{
	pending_flag_t flag = INT_NOT_TRIGGERED;
	EXTI_read_pending_flag(EXTI_10 , &flag);
	if(INT_TRIGGERED == flag)
	{
		EXTI_clear_pending_flag(EXTI_10);
		if(NULL != EXTI_Handler[EXTI_source])
		{
			EXTI_Handler[EXTI_source]();
		}
		flag = INT_NOT_TRIGGERED;
	}
	EXTI_read_pending_flag(EXTI_11 , &flag);
	if(INT_TRIGGERED == flag)
	{
		EXTI_clear_pending_flag(EXTI_11);
		if(NULL != EXTI_Handler[EXTI_source])
		{
			EXTI_Handler[EXTI_source]();
		}
		flag = INT_NOT_TRIGGERED;
	}
	EXTI_read_pending_flag(EXTI_12 , &flag);
	if(INT_TRIGGERED == flag)
	{
		EXTI_clear_pending_flag(EXTI_12);
		if(NULL != EXTI_Handler[EXTI_source])
		{
			EXTI_Handler[EXTI_source]();
		}
		flag = INT_NOT_TRIGGERED;
	}
	EXTI_read_pending_flag(EXTI_13 , &flag);
	if(INT_TRIGGERED == flag)
	{
		EXTI_clear_pending_flag(EXTI_13);
		if(NULL != EXTI_Handler[EXTI_source])
		{
			EXTI_Handler[EXTI_source]();
		}
		flag = INT_NOT_TRIGGERED;
	}
	EXTI_read_pending_flag(EXTI_14 , &flag);
	if(INT_TRIGGERED == flag)
	{
		EXTI_clear_pending_flag(EXTI_14);
		if(NULL != EXTI_Handler[EXTI_source])
		{
			EXTI_Handler[EXTI_source]();
		}
		flag = INT_NOT_TRIGGERED;
	}
	EXTI_read_pending_flag(EXTI_15 , &flag);
	if(INT_TRIGGERED == flag)
	{
		EXTI_clear_pending_flag(EXTI_15);
		if(NULL != EXTI_Handler[EXTI_source])
		{
			EXTI_Handler[EXTI_source]();
		}
		flag = INT_NOT_TRIGGERED;
	}
}
/**
 * @brief  : EXTI Line 16 interrupt /PVD through EXTI line detection interrupt
 * @param  : void
 * @return : void
 *
 */
void EXTI16_PVD_IRQHandler(void)
{
	EXTI_clear_pending_flag(EXTI_source);
	if(NULL != EXTI_Handler[EXTI_source])
	{
		EXTI_Handler[EXTI_source]();
	}
}
/**
 * @brief  : EXTI Line 17 interrupt / RTC Alarms (A and B) through EXTI line interrupt
 * @param  : void
 * @return : void
 *
 */
void EXTI17_RTC_Alarm_IRQHandler(void)
{
	EXTI_clear_pending_flag(EXTI_source);
	if(NULL != EXTI_Handler[EXTI_source])
	{
		EXTI_Handler[EXTI_source]();
	}
}
/**
 * @brief  : EXTI Line 18 interrupt / USBUSB On-The-Go FS Wakeup through EXTI line interrupt
 * @param  : void
 * @return : void
 *
 */
void EXTI18_OTG_FS_WKUP_IRQHandler(void)
{
	EXTI_clear_pending_flag(EXTI_source);
	if(NULL != EXTI_Handler[EXTI_source])
	{
		EXTI_Handler[EXTI_source]();
	}
}
/*	EXTI19 & EXTI20 are reserved*/
/**
 * @brief  : EXTI Line 22 interrupt /RTC Wakeup interrupt through the EXTI line
 * @param  : void
 * @return : void
 *
 */
void EXTI22_RTC_WKUP_IRQHandler(void)
{
	EXTI_clear_pending_flag(EXTI_source);
	if(NULL != EXTI_Handler[EXTI_source])
	{
		EXTI_Handler[EXTI_source]();
	}
}

