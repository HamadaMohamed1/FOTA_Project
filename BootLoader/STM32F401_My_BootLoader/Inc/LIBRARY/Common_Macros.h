/*
 * Common_Macros.h
 *
 *  Created on: Mar 14, 2024
 *      Author: hamada
 */

#ifndef LIBRARY_COMMON_MACROS_H_
#define LIBRARY_COMMON_MACROS_H_

/******************* Includes *******************/
#include <stdint.h>
/******************* Macro Declarations *******************/
#define NULL			0

/******************* Macro Function Declarations *******************/
#define SET_BIT(REG,BIT)	((REG) |= (1<<BIT))
#define CLEAR_BIT(REG,BIT)	((REG) &= ~(1<<BIT))
#define TOGGLE_BIT(REG,BIT)	((REG) ^= (1<<BIT))
#define READ_BIT(REG,BIT)	((REG)&(1<<BIT))

#define READ_REG(REG)		((REG))
#define WRITE_REG(REG,VAL)	((REG) = (VAL))
#define MODIFY_REG(REG, CLEARMASK, SETMASK) 	WRITE_REG((REG),(((READ_REG(REG)) & (~(CLEARMASK))) | (SETMASK)))


/******************* Data Type Declarations *******************/
typedef enum
{
	RET_OK    = 0x00,
	RET_ERROR =	0x01
}Std_RetType_t;





#endif /* LIBRARY_COMMON_MACROS_H_ */
