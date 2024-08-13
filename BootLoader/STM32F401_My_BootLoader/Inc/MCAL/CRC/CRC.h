/*
 * CRC.h
 *
 *  Created on: Jul 31, 2024
 *      Author: hamada
 */

#ifndef MCAL_CRC_CRC_H_
#define MCAL_CRC_CRC_H_
/******************* Includes *******************/
#include "../../LIBRARY/Common_Macros.h"
#include "../../LIBRARY/Stm32f401xx.h"
#include "CRCPrivate.h"
#include "../../MCAL/RCC/RCC.h"
/******************* Macro Declarations *******************/


/******************* Macro Function Declarations *******************/


/******************* Data Type Declarations *******************/

/******************* Function Declarations *******************/
void CRC_Init(void);
void CRC_Reset(void);
uint32_t CRC_Calculate(uint32_t *data ,uint8_t length);

#endif /* MCAL_CRC_CRC_H_ */
