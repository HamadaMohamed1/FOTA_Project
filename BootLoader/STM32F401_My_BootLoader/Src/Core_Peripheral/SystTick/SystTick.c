/*
 * SystTick.c
 *
 *  Created on: Mar 15, 2024
 *      Author: hamada
 */

#include "../../../Inc/Core_Peripheral/SystTick/SystTick_Interface.h"

/**
 * @brief  : Initialize the Systick timer
 * @param  :
 * @return :
 * 			(RET_OK) : The function done successfully
 * 			(RET_ERROR) : The function has a problem to perform this action
 */
Std_RetType_t Systick_init(void)
{
	uint32_t NO_Tick = 0x00ffffff;
	Std_RetType_t ret = RET_OK;
	if(NO_Tick > (STSTICK_LOAD_VALUE_POS << STSTICK_LOAD_VALUE_ACCESS)) /*resolution = 2^n = 2^24 = 16,777,216 = 1<<24*/
	{
		ret = RET_ERROR;
	}
	else
	{
		/*Disable the SYSTICK counter*/
		SYSTICK->CSR &=~ (SYSTICK_CSR_ENABLE_MASK << SYSTICK_CSR_ENABLE_POS);
		/*load the value into SYST_CVR in the range 0x00000001-0x00FFFFFF*/
		SYSTICK->RVR = NO_Tick;
		/*clear the SYSTICK counter value*/
		SYSTICK->CVR = 0;
		/*Indicates the clock source: (0) = external clock , (1) = processor clock*/
#if SYSTICK_CLOCK_SOURCE==SYSTICK_CLOCK_SOURCE_DIV_1
		SYSTICK->CSR |= (SYSTICK_CSR_CLOCK_MASK<<SYSTICK_CSR_CLOCK_POS);
#elif SYSTICK_CLOCK_SOURCE==SYSTICK_CLOCK_SOURCE_DIV_8
		SYSTICK->CSR &=~(SYSTICK_CSR_CLOCK_MASK<<SYSTICK_CSR_CLOCK_POS);
#else
#endif
	}
	return ret;
}
/**
 * @brief  : Systick_Wait_Blocking
 * @param  : (NO_Tick) : number of ticks
 * @return :
 * 			(RET_OK) : The function done successfully
 * 			(RET_ERROR) : The function has a problem to perform this action
 */
Std_RetType_t Systick_Wait_Blocking(uint32_t NO_Tick)
{
	Std_RetType_t ret = RET_OK;
	if(NO_Tick > (STSTICK_LOAD_VALUE_POS << STSTICK_LOAD_VALUE_ACCESS)) /*resolution = 2^n = 2^24 = 16,777,216 = 1<<24*/
	{
		ret = RET_ERROR;
	}
	else
	{
		/*load the value into SYST_CVR in the range 0x00000001-0x00FFFFFF*/
		SYSTICK->RVR = NO_Tick;
		/*Enable the SYSTICK counter*/
		SYSTICK->CSR |= (SYSTICK_CSR_ENABLE_MASK << SYSTICK_CSR_ENABLE_POS);
		/*COUNTFLAG Returns 1 if timer counted to 0 since last time this was read*/
		while((SYSTICK->CSR &(SYSTICK_CSR_COUNTFLAG_MASK<<SYSTICK_CSR_COUNTFLAG_POS)) == 0);
		/*clear the SYSTICK counter value*/
		SYSTICK->CVR = 0;
	}
	return ret;
}
/**
 * @brief  : Delay with Blocking
 * @param  : (ms) : number of Millie seconds
 * @return :
 *
 */
void delay_ms(uint32_t ms)
{
	if(ms > 0)
	{
		uint32_t number_of_ms = ms;
		while(number_of_ms > 0)
		{
			Systick_Wait_Blocking(0x4189);	/*0x4189 = 1ms*/
			number_of_ms--;
		}
	}
}
/**
 * @brief  : Delay with Blocking
 * @param  : (us) : number of Micro seconds
 * @return :
 *
 */
void delay_us(uint32_t us)
{
	if(us > 10)
	{
		uint32_t number_of_us = (us/10);
		while(number_of_us > 0)
		{
			Systick_Wait_Blocking(0xA7);	/*0xA7 = 10us*/
			number_of_us--;
		}
	}
}
