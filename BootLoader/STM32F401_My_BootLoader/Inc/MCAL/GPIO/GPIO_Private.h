/*
 * GPIO_Private.h
 *
 *  Created on: Mar 14, 2024
 *      Author: hamada
 */

#ifndef MCAL_GPIO_GPIO_PRIVATE_H_
#define MCAL_GPIO_GPIO_PRIVATE_H_

/******************* Includes *******************/
#include "../../LIBRARY/Common_Macros.h"
#include "../../LIBRARY/Stm32f401xx.h"
/******************* Macro Declarations *******************/
#define GPIO_PEREPHIRAL_MAX_NUM		6

#define MODER_MASK 					0b11
#define MODER_PIN_ACCESS 			2U

#define PUPDR_MASK 					0b11
#define PUPDR_PIN_ACCESS 			2U

#define OTYPER_MASK 				0b1

#define PSPEEDR_MASK 				0b11
#define PSPEEDR_PIN_ACCESS 			2U

#define AFR_MASK 					0b1111
#define AFR_PIN_ACCESS				4u
#define AFR_PIN_SHIFTING 			8U

/******************* Macro Function Declarations *******************/

/******************* Data Type Declarations *******************/
typedef enum
{
    PORTA=0,
    PORTB,
    PORTC,
    PORTD,
    PORTE,
    PORTH,
}Port_t;

typedef enum
{
    PIN0=0,
    PIN1,
    PIN2,
    PIN3,
    PIN4,
    PIN5,
    PIN6,
    PIN7,
    PIN8,
    PIN9,
    PIN10,
    PIN11,
    PIN12,
    PIN13,
    PIN14,
    PIN15,
}Pin_t;

typedef enum
{
    PIN_LOW=0,
    PIN_HIGH
}PinValue_t;


typedef enum
{
    INPUT=0,
    OUTPUT,
    ALTERNATE_FUNCTION,
    ANALOG
}Mode_t;

typedef enum
{
    LOW=0,
    MEDUIM,
    HIGH,
    VERY_HIGH
}OutputSpeed_t;

typedef enum
{
    PUSH_PULL=0,
    OPEN_DRAIN
}OutputType_t;

typedef enum
{
    NO_PULL=0,
    PULL_UP,
    PULL_DOWN
}PullUPDown_t;

typedef enum
{
    AF0=0,
    AF1,
    AF2,
    AF3,
    AF4,
    AF5,
    AF6,
    AF7,
    AF8,
    AF9,
    AF10,
    AF11,
    AF12,
    AF13,
    AF14,
    AF15
}AlternateFunction_t;


#endif /* MCAL_GPIO_GPIO_PRIVATE_H_ */
