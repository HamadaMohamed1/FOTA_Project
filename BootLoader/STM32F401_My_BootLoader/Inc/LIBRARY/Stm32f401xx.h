/*
 * Stm32f401xx.h
 *
 *  Created on: Mar 14, 2024
 *      Author: hamada
 */

#ifndef LIBRARY_STM32F401XX_H_
#define LIBRARY_STM32F401XX_H_

/******************* Various Memory Base Addresses *******************/
#define FLASH_BASE_ADDRESS            (0x08000000UL)
#define FLASH_END_ADDRESS 			  (FLASH_BASE_ADDRESS + 256 * 1024)
#define SRAM_BASE_ADDRESS             (0x20000000UL)
#define SRAM_END_ADDRESS 			  (SRAM_BASE_ADDRESS + 64 * 1024)


#define FLASH_SECTOR_2_BASE_ADDRESS   (0x08008000UL)

#define PERIPHERAL_BASE				  (0x40000000UL)

/******************* Core Peripheral Base Addresses *******************/
						/*SYSTICK Base Address*/
#define SYSTICK_BASE				  (0xE000E010UL)
						/*NVIC Base Address*/
#define NVIC_BASE 					  (0xE000E100UL)
						/*SCB Base Address*/
#define SCB_BASE					  (0xE000E008UL)

/******************* AHB1 Peripheral Base Addresses *******************/
#define AHB1PERIPHERAL_BASE 		  (PERIPHERAL_BASE + 0x00020000UL)

#define CRC_BASE_ADDRESS			  (AHB1PERIPHERAL_BASE + 0x00003000UL)

#define FLASH_INTERFACE_REGISTERS_BASE (AHB1PERIPHERAL_BASE + 0x00003C00UL)



						/*GPIOx Base Address*/
#define GPIOA_BASE_ADDRESS            (AHB1PERIPHERAL_BASE + 0x00000000UL)
#define GPIOB_BASE_ADDRESS            (AHB1PERIPHERAL_BASE + 0x00000400UL)
#define GPIOC_BASE_ADDRESS            (AHB1PERIPHERAL_BASE + 0x00000800UL)
#define GPIOD_BASE_ADDRESS            (AHB1PERIPHERAL_BASE + 0x00000C00UL)
#define GPIOE_BASE_ADDRESS            (AHB1PERIPHERAL_BASE + 0x00001000UL)
#define GPIOH_BASE_ADDRESS            (AHB1PERIPHERAL_BASE + 0x00001C00UL)

						/*RCC Base Address*/
#define RCC_BASE_ADDRESS 			  (AHB1PERIPHERAL_BASE + 0x00003800UL)





/******************* APB2 Peripheral Base Addresses *******************/
#define APB2PERIPHERAL_BASE			  (PERIPHERAL_BASE + 0x00010000UL)
						/*SYSCFG Base Address*/
#define SYSCFG_BASE_ADDRESS			  (APB2PERIPHERAL_BASE + 0x00003800UL)//0x40013800UL
						/*EXTI Base Address*/
#define EXTI_BASE_ADDRESS 			  (APB2PERIPHERAL_BASE + 0x00003C00UL)
						/*USART1 Base Address*/
#define USART1_BASE_ADDRESS 		  (APB2PERIPHERAL_BASE + 0x00001000UL)
						/*USART6 Base Address*/
#define USART6_BASE_ADDRESS 		  (APB2PERIPHERAL_BASE + 0x00001400UL)
						/*SPI1 Base Address*/
#define SPI1_BASE_ADDRESS 			  (APB2PERIPHERAL_BASE + 0x00003000UL)
						/*SPI4 Base Address*/
#define SPI4_BASE_ADDRESS 			  (APB2PERIPHERAL_BASE + 0x00003400UL)
/******************* AHB3 Peripheral Base Addresses *******************/

/******************* APB1 Peripheral Base Addresses *******************/
#define APB1PERIPHERAL_BASE			  (PERIPHERAL_BASE)
						/*USART2 Base Address*/
#define USART2_BASE_ADDRESS 		  (APB1PERIPHERAL_BASE + 0x00004400UL)
						/*SPI2 Base Address*/
#define SPI2_BASE_ADDRESS 			  (APB1PERIPHERAL_BASE + 0x00003800UL)
						/*SPI3 Base Address*/
#define SPI3_BASE_ADDRESS 			  (APB1PERIPHERAL_BASE + 0x00003C00UL)
						/*I2C1 Base Address*/
#define I2C1_BASE_ADDRESS 			  (APB1PERIPHERAL_BASE + 0x00005400UL)
						/*I2C2 Base Address*/
#define I2C2_BASE_ADDRESS 			  (APB1PERIPHERAL_BASE + 0x00005800UL)
						/*I2C3 Base Address*/
#define I2C3_BASE_ADDRESS 			  (APB1PERIPHERAL_BASE + 0x00005C00UL)







						/*APB1ENR Register*/

#define RCC_APB1ENR_USART2_POS		 (17UL)

#define RCC_APB1ENR_SPI3_POS 		 (15UL)
#define RCC_APB1ENR_SPI2_POS 		 (14UL)

#define RCC_APB1ENR_I2C1_POS 		 (21UL)
#define RCC_APB1ENR_I2C2_POS 		 (22UL)
#define RCC_APB1ENR_I2C3_POS 		 (23UL)


/******************* APB2 Peripheral Registers *******************/
#define RCC_APB2ENR_SYSCFG_POS 		(14UL)

#define RCC_APB2ENR_USART1_POS 		(4UL)
#define RCC_APB2ENR_USART6_POS 		(5UL)



#define RCC_APB2ENR_SPI1_POS 		(12UL)
#define RCC_APB2ENR_SPI4_POS 		(13UL)

/******************* AHB1 Peripheral Registers *******************/
/*******************AHB1ENR Register*******************/
#define RCC_AHB1ENR_GPIOA_POS 		(0UL)
#define RCC_AHB1ENR_GPIOB_POS 		(1UL)
#define RCC_AHB1ENR_GPIOC_POS 		(2UL)
#define RCC_AHB1ENR_GPIOD_POS 		(3UL)
#define RCC_AHB1ENR_GPIOE_POS 		(4UL)
#define RCC_AHB1ENR_GPIOH_POS 		(7UL)

#define RCC_AHB1ENR_CRC_POS 		(12UL)




#define RCC_OSCILLATORTYPE_NONE		(0X00000000UL)
#define RCC_OSCILLATORTYPE_HSE		(0X00000001UL)
#define RCC_OSCILLATORTYPE_HSI		(0X00000002UL)
#define RCC_OSCILLATORTYPE_LSE		(0X00000004UL)
#define RCC_OSCILLATORTYPE_LSI		(0X00000008UL)



#define RCC_HSE_OFF					(0x00)
#define RCC_HSE_ON					(0x01)

#define RCC_HSI_OFF					(0x00)
#define RCC_HSI_ON					(0x01)

#define RCC_LSE_OFF					(0x00)
#define RCC_LSE_ON					(0x01)

#define RCC_LSI_OFF					(0x00)
#define RCC_LSI_ON					(0x01)

/*******************RCC_CR Register*******************/
#define RCC_CR_HSEON_POS 		    (16UL)

#define RCC_CR_HSION_POS 		    (0UL)

/*******************RCC_CFGR Register*******************/


#define RCC_CFGR_SW0_POS 		    (0U)
#define RCC_CFGR_SW1_POS 		    (1U)

#define RCC_CFGR_HPRE_POS 		    (4U)

#define RCC_CFGR_HPRE_DIV1			(0x00000000UL)
#define RCC_CFGR_HPRE_DIV2			(0x00000080UL)
#define RCC_CFGR_HPRE_DIV4			(0x00000090UL)
#define RCC_CFGR_HPRE_DIV8			(0x000000A0UL)
#define RCC_CFGR_HPRE_DIV16			(0x000000B0UL)
#define RCC_CFGR_HPRE_DIV64			(0x000000C0UL)
#define RCC_CFGR_HPRE_DIV128		(0x000000D0UL)
#define RCC_CFGR_HPRE_DIV256		(0x000000E0UL)
#define RCC_CFGR_HPRE_DIV512		(0x000000F0UL)


#define RCC_CFGR_PPRE1_POS 		    (10U)

#define RCC_CFGR_PPRE1_DIV1			(0x00000000UL)
#define RCC_CFGR_PPRE1_DIV2	   		(0x00001000UL)
#define RCC_CFGR_PPRE1_DIV4			(0x00001400UL)
#define RCC_CFGR_PPRE1_DIV8			(0x00001800UL)
#define RCC_CFGR_PPRE1_DIV16		(0x00001C00UL)


#define RCC_CFGR_PPRE2_POS 		    (13U)

#define RCC_CFGR_PPRE2_DIV1			(0x00000000UL)
#define RCC_CFGR_PPRE2_DIV2	   		(0x00008000UL)
#define RCC_CFGR_PPRE2_DIV4			(0x0000A000UL)
#define RCC_CFGR_PPRE2_DIV8			(0x0000C000UL)
#define RCC_CFGR_PPRE2_DIV16		(0x0000E000UL)


/******************* NVIC Definition Structure *******************/
typedef struct
{
	volatile uint32_t ISER[8U];			/*Interrupt set enable registers*/
	volatile uint32_t Reserved1[24U];
	volatile uint32_t ICER[8U];			/*Interrupt clear enable registers*/
	volatile uint32_t Reserved2[24U];
	volatile uint32_t ISPR[8U];			/*Interrupt set pending registers*/
	volatile uint32_t Reserved3[24U];
	volatile uint32_t ICPR[8U];			/*Interrupt clear pending registers*/
	volatile uint32_t Reserved4[24U];
	volatile uint32_t IABR[8U];			/*Interrupt active bit registers*/
	volatile uint32_t Reserved5[56U];
	volatile uint8_t IPR[240U];			/*Interrupt priority registers*/
	//volatile uint32_t Reserved6[643U];
	//volatile uint32_t STIR;				/*Software Trigger Interrupt Register*/
}NVIC_RegDef_t;

/******************* SYSTICK Definition Structure *******************/
typedef struct
{
	volatile uint32_t CSR;				 /*SysTick Control and Status Register*/
	volatile uint32_t RVR;				 /*SysTick Reload Value Register*/
	volatile uint32_t CVR;				 /*SysTick Current Value Register*/
	volatile uint32_t CALIB;			 /*SysTick Calibration Value Register*/
}STSTICK_RegDef_t;

/******************* GPIO Register Definition Structure *******************/
typedef struct
{
    volatile uint32_t MODER;             /*GPIO PORT Mode Register*/
    volatile uint32_t OTYPER;            /*GPIO PORT Output Type Register*/
    volatile uint32_t OSPEEDR;           /*GPIO PORT Output Speed Register*/
    volatile uint32_t PUPDR;             /*GPIO PORT Pull up/down Register*/
    volatile uint32_t IDR;               /*GPIO PORT Input Data Register*/
    volatile uint32_t ODR;               /*GPIO PORT Output Data Register*/
    volatile uint32_t BSRR;              /*GPIO PORT Bit Set/Reset Register*/
    volatile uint32_t LCKR;              /*GPIO PORT Lock Register*/
    volatile uint32_t AFR[2];            /*GPIO PORT Alternate Function Registers*/
}GPIO_RegDef_t;
/******************* RCC Register Definition Structure *******************/
typedef struct
{
	volatile uint32_t CR; 				    /*offset:0x00 */
	volatile uint32_t PLLCFGR; 			    /*offset:0x04 */
	volatile uint32_t CFGR;	   		        /*offset:0x08*/
	volatile uint32_t CIR; 				    /*offset:0x0C */
	volatile uint32_t AHB1RSTR;			    /*offset:0x10 */
	volatile uint32_t AHB2RSTR; 			/*offset:0x14 */
    		 uint32_t Reserved0[2]; 		/*offset:0x18-0x1C */
	volatile uint32_t APB1RSTR;			    /*offset:0x20 */
	volatile uint32_t APB2RSTR;			    /*offset:0x24 */
			 uint32_t Reserved1[2]; 		/*offset:0x28-0x2C */
	volatile uint32_t AHB1ENR; 			    /*offset:0x30 */
	volatile uint32_t AHB2ENR; 			    /*offset:0x34 */
 	 	 	 uint32_t Reserved2[2]; 		/*offset:0x38-0x3C */
	volatile uint32_t APB1ENR; 			    /*offset:0x40 */
	volatile uint32_t APB2ENR; 			    /*offset:0x44 */
	 	 	 uint32_t Reserved3[2]; 		/*offset:0x48-0x4C */
	volatile uint32_t AHB1LPENR; 			/*offset:0x50 */
	volatile uint32_t AHB2LPENR; 			/*offset:0x54 */
	 	 	 uint32_t Reserved4[2]; 		/*offset:0x58-0x5C */
	volatile uint32_t APB1LPENR; 			/*offset:0x60 */
	volatile uint32_t APB2LPENR; 			/*offset:0x64 */
	 	 	 uint32_t Reserved5[2];	        /*offset:0x68-0x6C */
	volatile uint32_t BDCR; 				/*offset:0x70 */
	volatile uint32_t CSR; 				    /*offset:0x74 */
	 	 	 uint32_t Reserved6[2]; 		/*offset:0x78-0x7C */
	volatile uint32_t SSCGR; 				/*offset:0x80 */
	volatile uint32_t PLLI2SCFGR;			/*offset:0x84 */
	 	 	 uint32_t Reserved7; 			/*offset:0x88 */
	volatile uint32_t DCKCFGR;			    /*offset:0x8C */
}RCC_RegDef_t;

/******************* SCB Register Definition Structure *******************/
typedef struct
{
    volatile uint32_t ACTLR;   				/*Auxiliary Control Register*/
    volatile uint32_t RESERVED1[829];
    volatile uint32_t CPUID;
    volatile uint32_t ICSR;
    volatile uint32_t VTOR;
    volatile uint32_t AIRCR;                /*Application Interrupt and Reset Control Register*/
    volatile uint32_t SCR;
    volatile uint32_t CCR;
    volatile uint32_t SHPR1;
    volatile uint32_t SHPR2;
    volatile uint32_t SHPR3;
    volatile uint32_t SHCRS;
    volatile uint32_t CFSR;
    /*
     * there are other registers
     * */
}SCB_RegDef_t;

/******************* SYSCFG Register Definition Structure *******************/
typedef struct
{
    volatile uint32_t MEMRMP;
    volatile uint32_t PMC;
    volatile uint32_t EXTICR0;
    volatile uint32_t EXTICR1;
    volatile uint32_t EXTICR2;
    volatile uint32_t EXTICR3;
    volatile uint32_t RESERVED[2];
    volatile uint32_t CMPCR;
}SYSCFG_RegDef_t;
/******************* EXTI Register Definition Structure *******************/
typedef struct
{
    volatile uint32_t IMR;
    volatile uint32_t EMR;
    volatile uint32_t RTSR;
    volatile uint32_t FTSR;
    volatile uint32_t SWIER;
    volatile uint32_t PR;
}EXTI_RegDef_t;

/******************* USART Register Definition Structure *******************/
typedef struct
{
    volatile uint32_t USART_SR;		//Status register
    volatile uint32_t USART_DR;		//Data register
    volatile uint32_t USART_BRR;	//Baud rate register
    volatile uint32_t USART_CR1;	//Control register 1
    volatile uint32_t USART_CR2;	//Control register 2
    volatile uint32_t USART_CR3;	//Control register 3
    volatile uint32_t USART_GTPR;	//Guard time and prescaler register
}USART_RegDef_t;

/******************* SPI Register Definition Structure *******************/
typedef struct
{
    volatile uint32_t SPI_CR1;		//SPI control register 1
    volatile uint32_t SPI_CR2;		//SPI control register 2 (
    volatile uint32_t SPI_SR;		//SPI status register
    volatile uint32_t SPI_DR;		//SPI data register
    volatile uint32_t SPI_CRCPR;	//SPI CRC polynomial register
    volatile uint32_t SPI_RXCRCR;	//SPI RX CRC register
    volatile uint32_t SPI_TXCRCR;	//SPI TX CRC register
    volatile uint32_t SPI_I2SCFGR;	//SPI_I2 S configuration register
    volatile uint32_t SPI_I2SPR;	//SPI_I2 S prescaler register
}SPI_RegDef_t;

/******************* I2C Register Definition Structure *******************/
typedef struct
{
	volatile uint32_t I2C_CR1;		//I2C Control register 1
	volatile uint32_t I2C_CR2;		//I2C Control register 2
	volatile uint32_t I2C_OAR1;		//I2C Own address register 1
	volatile uint32_t I2C_OAR2;		//I2C Control register 2
	volatile uint32_t I2C_DR;		//I2C Data register
	volatile uint32_t I2C_SR1;		//I2C Status register 1
	volatile uint32_t I2C_SR2;		//I2C Status register 2
	volatile uint32_t I2C_CCR;		//I2C Clock control register
	volatile uint32_t I2C_TRISE;	//I2C TRISE register
	volatile uint32_t I2C_FLTR;		//I2C FLTR register
}I2C_RegDef_t;

/******************* CRC Register Definition Structure *******************/

typedef struct
{
	volatile uint32_t CRC_DR;		/*Data register*/
	volatile uint32_t CRC_IDR;		/*Independent data register*/
	volatile uint32_t CRC_CR;		/*Control register*/
}CRC_RegDef_t;

/******************* FLASH INTERFACE Registers Definition Structure *******************/
typedef struct
{
	volatile uint32_t FLASH_ACR;		/*Flash access control register */
	volatile uint32_t FLASH_KEYR;		/*Flash key register */
	volatile uint32_t FLASH_OPTKEYR;	/*Flash option key register */
	volatile uint32_t FLASH_SR;			/*Flash status register */
	volatile uint32_t FLASH_CR;			/*Flash control register */
	volatile uint32_t FLASH_OPTCR;		/*Flash option control register (*/
}FLASH_RegDef_t;

/******************* SYSTICK Peripheral Definition *******************/
#define SYSTICK		   		 ((STSTICK_RegDef_t *)SYSTICK_BASE)
/******************* NVIC Peripheral Definition *******************/
#define NVIC 				 ((NVIC_RegDef_t *) NVIC_BASE)
/******************* RCC Peripheral Definition *******************/
#define RCC 				 ((RCC_RegDef_t *) RCC_BASE_ADDRESS)
/******************* SCB Peripheral Definition *******************/
#define SCB 				 ((SCB_RegDef_t *) SCB_BASE)
/******************* GPIO Peripheral Definition *******************/
#define GPIOA                ((GPIO_RegDef_t *) GPIOA_BASE_ADDRESS)
#define GPIOB                ((GPIO_RegDef_t *) GPIOB_BASE_ADDRESS)
#define GPIOC                ((GPIO_RegDef_t *) GPIOC_BASE_ADDRESS)
#define GPIOD                ((GPIO_RegDef_t *) GPIOD_BASE_ADDRESS)
#define GPIOE                ((GPIO_RegDef_t *) GPIOE_BASE_ADDRESS)
#define GPIOH                ((GPIO_RegDef_t *) GPIOH_BASE_ADDRESS)

/******************* SYSCFG Peripheral Definition *******************/
#define SYSCFG 				 ((SYSCFG_RegDef_t *) SYSCFG_BASE_ADDRESS)
/******************* EXTI Peripheral Definition *******************/
#define EXTI 				 ((EXTI_RegDef_t *) EXTI_BASE_ADDRESS)
/******************* USART1 Peripheral Definition *******************/
#define USART1 				 ((USART_RegDef_t *) USART1_BASE_ADDRESS)
/******************* USART2 Peripheral Definition *******************/
#define USART2 				 ((USART_RegDef_t *) USART2_BASE_ADDRESS)
/******************* USART6 Peripheral Definition *******************/
#define USART6 				 ((USART_RegDef_t *) USART6_BASE_ADDRESS)
/******************* SPI1 Peripheral Definition *******************/
#define SPI1 				 ((SPI_RegDef_t *) SPI1_BASE_ADDRESS)
/******************* SPI2 Peripheral Definition *******************/
#define SPI2 				 ((SPI_RegDef_t *) SPI2_BASE_ADDRESS)
/******************* SPI3 Peripheral Definition *******************/
#define SPI3				 ((SPI_RegDef_t *) SPI3_BASE_ADDRESS)
/******************* SPI4 Peripheral Definition *******************/
#define SPI4 				 ((SPI_RegDef_t *) SPI4_BASE_ADDRESS)
/******************* I2C1 Peripheral Definition *******************/
#define I2C1 				 ((I2C_RegDef_t *)I2C1_BASE_ADDRESS)
/******************* I2C2 Peripheral Definition *******************/
#define I2C2 				 ((I2C_RegDef_t *)I2C2_BASE_ADDRESS)
/******************* I2C3 Peripheral Definition *******************/
#define I2C3 				 ((I2C_RegDef_t *)I2C3_BASE_ADDRESS)
/******************* CRC Peripheral Definition *******************/
#define CRC 				 ((CRC_RegDef_t *)CRC_BASE_ADDRESS)
/******************* FLASH Interface Peripheral Definition *******************/
#define FLASH 				 ((FLASH_RegDef_t*)FLASH_INTERFACE_REGISTERS_BASE)

#endif /* LIBRARY_STM32F401XX_H_ */
