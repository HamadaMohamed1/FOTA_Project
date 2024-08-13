/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  *  Created on: Mar 14, 2024
  *      Author: hamada
  ******************************************************************************/
#include "../Inc/main.h"

PinConfig_t PC13 = { .Port = PORTC ,.Pin = PIN13,.Mode = OUTPUT ,.Type=PUSH_PULL
		, .Speed = MEDUIM , .PullType =NO_PULL
};

PinConfig_t LoadButton = { .Port = PORTB ,.Pin = PIN12,.Mode =INPUT  ,.Type=PUSH_PULL
		, .Speed = MEDUIM , .PullType = PULL_UP
};

PinConfig_t UART2RX = { .Port = PORTA ,.Pin = PIN3, .Mode = ALTERNATE_FUNCTION ,.Type=PUSH_PULL
		, .Speed = MEDUIM , .PullType =NO_PULL ,.AltFunc = AF7
};

PinConfig_t UART2TX = { .Port = PORTA ,.Pin = PIN2, .Mode = ALTERNATE_FUNCTION ,.Type=PUSH_PULL
		, .Speed = MEDUIM , .PullType =NO_PULL ,.AltFunc = AF7
};

USART_Config_t uart2  ={.source = USART_2, .baud_rate = 115200 ,.hardware_control_flow =HARDWARE_FLOW_CONTROL_IS_NOT_USED ,
						.mode = RX_TX ,.oversampling = OVERSAMPLING_BY_16 ,.parity = WITHOUT_PARITY ,.rx_mode = POLLING ,
						.tx_mode = POLLING ,.type =ASYNCHRONOUS ,.word_length = EGHIT_BITS,.stop_bits =ONE_STOP_BIT
};



int main(void)
{
	SystemClock_Config();
	Systick_init();
	RCC_GPIOA_CLK_ENABLE();
	RCC_GPIOB_CLK_ENABLE();
	RCC_GPIOC_CLK_ENABLE();
	RCC_USART2_CLK_ENABLE();

	CRC_Init();
	GPIO_Pin_init(&PC13);
	GPIO_Pin_init(&LoadButton);
	GPIO_Pin_init(&UART2TX);
	GPIO_Pin_init(&UART2RX);
	USART_init(&uart2);

	PinValue_t ButtonVal = PIN_HIGH; /*high means released*/

	GPIO_Get_Pin_Value(PORTB,PIN12,&ButtonVal);

	if(ButtonVal == PIN_LOW)		/*low means pressed*/
	{
		BootLoader_UARTReadData();
	}
	else
	{
		BootLoader_JumpToUserApp();
	}

	while(1)
	{

	}

}

void BootLoader_UARTReadData(void)
{
	/*This function it used for reading commands from the Host*/
	uint8_t  Local_u8CMDPacket[255] = {0};
	while(1)
	{
		/*Clear Command Packet every iteration*/
		memset(Local_u8CMDPacket , 0 , 255);
		/*1st step : read the 1st byte which include the "length to follow of the command"*/
		USART_receive_byte_blocking(&uart2, Local_u8CMDPacket);
		/*2nd step : read the rest of the command , its size is the previosly byte value*/
		for(int i = 1 ; i <= Local_u8CMDPacket[0]; i++)
		{
			USART_receive_byte_blocking(&uart2, &Local_u8CMDPacket[i]);
		}
		/*3rd step : check the command code ,then handle the command*/
		switch(Local_u8CMDPacket[1]) /*this byte that include the command code*/
		{
		case BL_GET_VER    		   :
			BL_voidHandleGetVerCmd(Local_u8CMDPacket);
			break;
		case BL_GET_HELP    	   :
			BL_voidHandleGetHelpCmd(Local_u8CMDPacket);
			break;
		case BL_GET_CID    		   :
			BL_voidHandleGetCIDCmd(Local_u8CMDPacket);
			break;
		case BL_GET_RDP_STATUS     :
			BL_voidHandleGetRDPStatusCmd(Local_u8CMDPacket);
			break;
		case BL_GO_TO_ADDR    	   :
			BL_voidHandleGoToAddressCmd(Local_u8CMDPacket);
			break;
		case BL_FLASH_ERASE   	   :
			BL_voidHandleFlashEraseCmd(Local_u8CMDPacket);
			break;
		case BL_MEM_WRITE    	   :
			BL_voidHandleMemWriteCmd(Local_u8CMDPacket);
			break;
		case BL_EN_RW_PROTECT      :
			BL_voidHandleEnableRWCmd(Local_u8CMDPacket);
			break;
		case BL_MEM_READ    	   :
			BL_voidHandleMemReadCmd(Local_u8CMDPacket);
			break;
		case BL_READ_SECTOR_STATUS :
			BL_voidHandleReadSectorStatusCmd(Local_u8CMDPacket);
			break;
		case BL_OTP_READ           :
			BL_voidHandleOTPReadCmd(Local_u8CMDPacket);
			break;
		case BL_DIS_WR_PROTECT     :
			BL_voidHandleDisableWRProtectCmd(Local_u8CMDPacket);
			break;
		case BL_SYSTEM_RESET	   :
			BL_voidHandleResetCmd(Local_u8CMDPacket);
			break;
		}
	}
}

void BootLoader_JumpToUserApp(void)
{
	uint32_t ResetHandlerAddress;
	//pointer that hold reset handler of user app
	void (* App_ResetHandler)(void);
	/*Configure MSP of user app*/
	uint32_t Local_u32MSPVal = *((volatile uint32_t*)(FLASH_SECTOR_2_BASE_ADDRESS));
	/*write the address to msp register*/
	__asm volatile("MSR MSP, %0"::"r"(Local_u32MSPVal));
	/*Get reset handler of user app*/
	ResetHandlerAddress = *((volatile uint32_t*)(FLASH_SECTOR_2_BASE_ADDRESS + 4));

	App_ResetHandler = (void*)ResetHandlerAddress;

	/*jump to the user app reset handler*/
	App_ResetHandler();
}

Std_RetType_t SystemClock_Config(void)
{
	Std_RetType_t ret = RET_OK;
	RCC_OscInitTypedef RCC_OscInitStruct ={0};
	RCC_ClkInitTypedef RCC_ClkInitStruct ={0};

	RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
	RCC_OscInitStruct.HSE_State = RCC_HSE_ON;
	ret = HALL_RCC_OscConfig(&RCC_OscInitStruct);

	RCC_ClkInitStruct.AHBClkDivider  =RCC_SYSCLK_AHB_DIV1;
	RCC_ClkInitStruct.APB1ClkDivider =RCC_HCLK_APB1_DIV1;
	RCC_ClkInitStruct.APB2ClkDivider =RCC_HCLK_APB2_DIV1;
	ret = HALL_RCC_ClockConfig(&RCC_ClkInitStruct);
	return ret;
}


