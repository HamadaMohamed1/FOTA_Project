/*
 * EXTI_private.h
 *
 *  Created on: Apr 12, 2024
 *      Author: hamada
 */

#ifndef MCAL_EXTI_EXTI_PRIVATE_H_
#define MCAL_EXTI_EXTI_PRIVATE_H_


#define EXTI_DISABLE 			0
#define EXTI_ENABLE 			1

#define EXTI_MAX_NUMBER			23



typedef enum
{
	RISING_EDGE = 0 ,
	FALLING_EDGE ,
	RISING_FALLING_EDGE ,
}EXTI_edge_t;



typedef enum
{
	INT_NOT_TRIGGERED = 0 ,
	INT_TRIGGERED ,
}pending_flag_t;



typedef enum
{
	EXTI_0 =0,
	EXTI_1 ,
	EXTI_2 ,
	EXTI_3 ,
	EXTI_4 ,
	EXTI_5 ,
	EXTI_6 ,
	EXTI_7 ,
	EXTI_8 ,
	EXTI_9 ,
	EXTI_10 ,
	EXTI_11 ,
	EXTI_12 ,
	EXTI_13 ,
	EXTI_14 ,
	EXTI_15 ,
	EXTI_16 ,
	EXTI_17 ,
	EXTI_18 ,
	//EXTI_19 , reserved
	//EXTI_20 , reserved
	EXTI_21 = 21,
	EXTI_22 = 22,
}EXTI_source_t;





#endif /* MCAL_EXTI_EXTI_PRIVATE_H_ */
