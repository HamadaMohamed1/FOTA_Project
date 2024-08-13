/*
 * GPIO.c
 *
 *  Created on: Mar 14, 2024
 *      Author: hamada
 */
#include "../../../Inc/MCAL/GPIO/GPIO_Interface.h"


static GPIO_RegDef_t *GPIO_PORT[GPIO_PEREPHIRAL_MAX_NUM] = {GPIOA,GPIOB,GPIOC,GPIOD,GPIOE,GPIOH};


/**
 * @brief  : Initialize the GPIO Pin
 * @param  : (pinConfig) Pointer to the configuration @ref PinConfig_t
 * @return :
 * 			(RET_OK) : The function done successfully
 * 			(RET_ERROR) : The function has a problem to perform this action
 */
Std_RetType_t GPIO_Pin_init(const PinConfig_t *pinConfig)
{
	Std_RetType_t ret = RET_OK;
	if(NULL == pinConfig)
	{
		ret = RET_ERROR;
	}
	else
	{
		/*select gpio mode */
		/*clear the mode bits*/
		(GPIO_PORT[pinConfig->Port]->MODER) &=~(MODER_MASK << (pinConfig->Pin*MODER_PIN_ACCESS));
		/*set the mode bits*/
		(GPIO_PORT[pinConfig->Port]->MODER) |= ((pinConfig->Mode)<<(pinConfig->Pin*MODER_PIN_ACCESS));

		/*select gpio pull state */
		/*clear the PUPDR bits*/
		(GPIO_PORT[pinConfig->Port]->PUPDR) &=~(PUPDR_MASK << (pinConfig->Pin)*PUPDR_PIN_ACCESS);
		/*set the PUPDR bits*/
		(GPIO_PORT[pinConfig->Port]->PUPDR) |= ((pinConfig->PullType)<<(pinConfig->Pin*PUPDR_PIN_ACCESS));

		/*select output type & output speed in case of output or alternate function*/
		if(OUTPUT ==pinConfig->Mode || ALTERNATE_FUNCTION ==pinConfig->Mode)
		{
			/*select output type {push pull , open drain}*/
			/*clear the OTYPER bit*/
			(GPIO_PORT[pinConfig->Port]->OTYPER) &=~ (OTYPER_MASK<< pinConfig->Pin);
			/*set the OTYPER bit*/
			(GPIO_PORT[pinConfig->Port]->OTYPER) |= ((pinConfig->Type)<<(pinConfig->Pin));

			/*select output speed {low , medium , high , very high}*/
			/*clear the OSPEEDR bits*/
			(GPIO_PORT[pinConfig->Port]->OSPEEDR) &=~(PSPEEDR_MASK << (pinConfig->Pin*PSPEEDR_PIN_ACCESS));
			/*set the OSPEEDR bits*/
			(GPIO_PORT[pinConfig->Port]->OSPEEDR) |= ((pinConfig->Speed) <<(pinConfig->Pin*PSPEEDR_PIN_ACCESS));

			if(ALTERNATE_FUNCTION == pinConfig->Mode)
			{
				/*select the pin alternate function*/
				uint8_t l_reg_num = pinConfig->Pin / AFR_PIN_SHIFTING;
				uint8_t l_bit_num = pinConfig->Pin % AFR_PIN_SHIFTING;
				/*clear the AFR bits*/
				(GPIO_PORT[pinConfig->Port]->AFR[l_reg_num]) &=~(AFR_MASK << (l_bit_num *AFR_PIN_ACCESS));
				/*set the AFR bits*/
				(GPIO_PORT[pinConfig->Port]->AFR[l_reg_num]) |= ((pinConfig->AltFunc) << (l_bit_num *AFR_PIN_ACCESS));
			}
		}
	}
	return ret;
}
/**
 * @brief  : Write the logic on the GPIO Pin
 * @param  : (port)   GPIO Port 	  @ref Port_t
 * 			 (pinNum) GPIO Pin Number @ref Pin_t
 * 			 (pinVal) GPIO Pin Value  @ref PinValue_t
 * @return :
 * 			(RET_OK) : The function done successfully
 * 			(RET_ERROR) : The function has a problem to perform this action
 */
Std_RetType_t GPIO_Set_Pin_Value(Port_t port , Pin_t pinNum,PinValue_t pinVal)
{
	Std_RetType_t ret = RET_OK;
	if((PORTH < port)|(PIN15 < pinNum))
	{
		ret = RET_ERROR;
	}
	else
	{
		if(PIN_LOW == pinVal)
		{
			GPIO_PORT[port]->ODR &=~ (1<< pinNum);
			/*GPIO_PORT[port]->BSRR = 1<< (pin +16);  faster*/
		}
		else if(PIN_HIGH == pinVal)
		{
			GPIO_PORT[port]->ODR |= (1<< pinNum);
			/*GPIO_PORT[port]->BSRR = (1<<pin);  faster*/
		}
	}
	return ret;
}


Std_RetType_t GPIO_Set_Port_Value(Port_t port ,uint8_t portVal)
{
	Std_RetType_t ret = RET_OK;
	if((PORTH < port))
	{
		ret = RET_ERROR;
	}
	else
	{
		GPIO_PORT[port]->ODR = portVal;
		/*GPIO_PORT[port]->BSRR = 1<< (pin +16);  faster*/
	}
	return ret;
}

/**
 * @brief  : Toggle the logic on the GPIO Pin
 * @param  : (port)   GPIO Port 	  @ref Port_t
 * 			 (pinNum) GPIO Pin Number @ref Pin_t
 * @return :
 * 			(RET_OK) : The function done successfully
 * 			(RET_ERROR) : The function has a problem to perform this action
 */
Std_RetType_t GPIO_Toggle_Pin_Value(Port_t port , Pin_t pinNum)
{
	Std_RetType_t ret = RET_OK;
	if((PORTH < port)|(PIN15 < pinNum))
	{
		ret = RET_ERROR;
	}
	else
	{
		GPIO_PORT[port]->ODR ^= (1<< pinNum);
		/*GPIO_PORT[port]->BSRR = 1<< (pin +16);  faster*/
	}
	return ret;
}
/**
 * @brief  : Read the logic on the GPIO Pin
 * @param  : (port)   GPIO Port 	  						 @ref Port_t
 * 			 (pinNum) GPIO Pin Number 						 @ref Pin_t
 * 			 (pinVal) Pointer to store the value of GPIO Pin @ref PinValue_t
 * @return :
 * 			(RET_OK) : The function done successfully
 * 			(RET_ERROR) : The function has a problem to perform this action
 */
Std_RetType_t GPIO_Get_Pin_Value(Port_t port , Pin_t pinNum,PinValue_t *pinVal)
{
	Std_RetType_t ret = RET_OK;
	if((PORTH < port)|(PIN15 < pinNum)|(NULL ==pinVal))
	{
		ret = RET_ERROR;
	}
	else
	{
		if((GPIO_PORT[port]->IDR & (1<<pinNum)))
		{
			*pinVal = PIN_HIGH;
		}
		else
		{
			*pinVal = PIN_LOW;
		}
	}
	return ret;
}
