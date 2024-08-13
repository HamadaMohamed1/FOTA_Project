/*
 * RCC.c
 *
 *  Created on: Mar 14, 2024
 *      Author: hamada
 */


#include "../../../Inc/MCAL/RCC/RCC.h"

Std_RetType_t HALL_RCC_OscConfig(RCC_OscInitTypedef *RCC_OscInitStruct)
{
	Std_RetType_t ret = RET_OK;
	if(NULL == RCC_OscInitStruct)
	{
		ret = RET_ERROR;
	}
	else
	{
		if(RCC_OSCILLATORTYPE_HSE == RCC_OscInitStruct->OscillatorType)
		{
			if(RCC_HSE_ON == RCC_OscInitStruct->HSE_State)
			{
				/*HSE oscillator selected as system clock*/
				SET_BIT(RCC->CFGR , RCC_CFGR_SW0_POS);
				CLEAR_BIT(RCC->CFGR,RCC_CFGR_SW1_POS);
				/*HSE oscillator ON*/
				SET_BIT(RCC->CR,RCC_CR_HSEON_POS);
			}
			else
			{
				CLEAR_BIT(RCC->CR,RCC_CR_HSEON_POS);
			}
		}
		else if(RCC_OSCILLATORTYPE_HSI == RCC_OscInitStruct->OscillatorType)
		{
			if(RCC_HSI_ON == RCC_OscInitStruct->HSI_State)
			{
				/*HSI oscillator selected as system clock*/
				CLEAR_BIT(RCC->CFGR,RCC_CFGR_SW0_POS);
				CLEAR_BIT(RCC->CFGR,RCC_CFGR_SW1_POS);
				/*HSI oscillator ON*/
				SET_BIT(RCC->CR,RCC_CR_HSION_POS);
			}
			else
			{
				CLEAR_BIT(RCC->CR,RCC_CR_HSION_POS);
			}
		}
		else if(RCC_OSCILLATORTYPE_LSE == RCC_OscInitStruct->OscillatorType)
		{
			if(RCC_LSE_ON == RCC_OscInitStruct->LSE_State)
			{

			}
			else
			{

			}
		}
		else if(RCC_OSCILLATORTYPE_LSI == RCC_OscInitStruct->OscillatorType)
		{
			if(RCC_LSI_ON == RCC_OscInitStruct->LSI_State)
			{

			}
			else
			{

			}
		}
		else
		{
			/*Nothing*/
		}
	}
	return ret;
}

Std_RetType_t HALL_RCC_ClockConfig(RCC_ClkInitTypedef *RCC_ClockInitStruct)
{
	Std_RetType_t ret = RET_OK;
	if(NULL == RCC_ClockInitStruct)
	{
		ret = RET_ERROR;
	}
	else
	{
		MODIFY_REG(RCC->CFGR ,RCC_CFGR_HPRE_POS, RCC_ClockInitStruct->AHBClkDivider);
		MODIFY_REG(RCC->CFGR ,RCC_CFGR_PPRE1_POS, RCC_ClockInitStruct->APB1ClkDivider);
		MODIFY_REG(RCC->CFGR ,RCC_CFGR_PPRE2_POS, RCC_ClockInitStruct->APB2ClkDivider);
	}
	return ret;
}

