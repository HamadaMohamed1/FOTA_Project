/*
 * CRC.c
 *
 *  Created on: Jul 31, 2024
 *      Author: hamada
 */


#include "../../../Inc/MCAL/CRC/CRC.h"

void CRC_Init(void)
{
	RCC_CRC_CLK_ENABLE();
	CRC_Reset();
}

void CRC_Reset(void)
{
	CRC->CRC_CR |= (RESET_BIT_MASK<<RESET_BIT_POS);
}

uint32_t CRC_Calculate(uint32_t *data ,uint8_t length)
{
	uint32_t local_u32Temp  , local_counter;
	for(local_counter = 0 ; local_counter < length ; local_counter++)
	{
		CRC->CRC_DR = data[local_counter];
	}
	local_u32Temp = CRC->CRC_DR;
	return local_u32Temp;
}
