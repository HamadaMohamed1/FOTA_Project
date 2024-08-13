/*
 * syscfg_private.h
 *
 *  Created on: Apr 12, 2024
 *      Author: hamad
 */

#ifndef MCAL_SYSCFG_SYSCFG_PRIVATE_H_
#define MCAL_SYSCFG_SYSCFG_PRIVATE_H_

#define EXTI_PORT_A 	0
#define EXTI_PORT_B 	1
#define EXTI_PORT_C 	2
#define EXTI_PORT_D 	3
#define EXTI_PORT_E 	4
#define EXTI_PORT_H 	7


typedef enum {
	EXTI_LINE_0 = 0 ,
	EXTI_LINE_1 ,
	EXTI_LINE_2 ,
	EXTI_LINE_3 ,
	EXTI_LINE_4 ,
	EXTI_LINE_5 ,
	EXTI_LINE_6 ,
	EXTI_LINE_7 ,
	EXTI_LINE_8 ,
	EXTI_LINE_9 ,
	EXTI_LINE_10 ,
	EXTI_LINE_11 ,
	EXTI_LINE_12 ,
	EXTI_LINE_13 ,
	EXTI_LINE_14 ,
	EXTI_LINE_15 ,
}EXTI_LINE_t;



#endif /* MCAL_SYSCFG_SYSCFG_PRIVATE_H_ */
