/*
 * GPIO.h
 *
 *  Created on: Mar 14, 2024
 *      Author: hamada
 */

#ifndef MCAL_GPIO_GPIO_INTERFACE_H_
#define MCAL_GPIO_GPIO_INTERFACE_H_

/******************* Includes *******************/
#include "GPIO_Private.h"

/******************* Data Type Declarations *******************/
typedef struct
{
	Port_t Port;
    Pin_t Pin;
    Mode_t Mode;
    OutputSpeed_t Speed;
    OutputType_t Type;
    PullUPDown_t PullType;
    AlternateFunction_t AltFunc;
}PinConfig_t;

/******************* Interfaces Declarations *******************/
/**
 * @brief  : Initialize the GPIO Pin
 * @param  : (pinConfig) Pointer to the configuration @ref PinConfig_t
 * @return :
 * 			(RET_OK) : The function done successfully
 * 			(RET_ERROR) : The function has a problem to perform this action
 */
Std_RetType_t GPIO_Pin_init(const PinConfig_t *pinConfig);
/**
 * @brief  : Write the logic on the GPIO Pin
 * @param  : (port)   GPIO Port 	  @ref Port_t
 * 			 (pinNum) GPIO Pin Number @ref Pin_t
 * 			 (pinVal) GPIO Pin Value  @ref PinValue_t
 * @return :
 * 			(RET_OK) : The function done successfully
 * 			(RET_ERROR) : The function has a problem to perform this action
 */
Std_RetType_t GPIO_Set_Pin_Value(Port_t port , Pin_t pinNum,PinValue_t pinVal);
/**
 * @brief  : Toggle the logic on the GPIO Pin
 * @param  : (port)   GPIO Port 	  @ref Port_t
 * 			 (pinNum) GPIO Pin Number @ref Pin_t
 * @return :
 * 			(RET_OK) : The function done successfully
 * 			(RET_ERROR) : The function has a problem to perform this action
 */
Std_RetType_t GPIO_Toggle_Pin_Value(Port_t port , Pin_t pinNum);
/**
 * @brief  : Read the logic on the GPIO Pin
 * @param  : (port)   GPIO Port 	  						 @ref Port_t
 * 			 (pinNum) GPIO Pin Number 						 @ref Pin_t
 * 			 (pinVal) Pointer to store the value of GPIO Pin @ref PinValue_t
 * @return :
 * 			(RET_OK) : The function done successfully
 * 			(RET_ERROR) : The function has a problem to perform this action
 */
Std_RetType_t GPIO_Get_Pin_Value(Port_t port , Pin_t pinNum,PinValue_t *pinVal);


Std_RetType_t GPIO_Set_Port_Value(Port_t port ,uint8_t portVal);


#endif /* MCAL_GPIO_GPIO_INTERFACE_H_ */
