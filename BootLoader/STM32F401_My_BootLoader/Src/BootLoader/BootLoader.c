/*
 * BootLoader.c
 *
 *  Created on: Jul 31, 2024
 *      Author: hamada
 */
#include "../../Inc/BootLoader/BootLoader.h"


extern USART_Config_t uart2;


static CRC_State_t u8VerifyCRC(uint8_t* copy_pu8DataArr , uint8_t copy_u8Length , uint32_t copy_u32HostCRC)
{
	uint8_t Local_u8Iterator;
	CRC_State_t Local_u8CRCStatus;
	uint32_t Local_u32AccCRC , Local_u32Temp;
	for(Local_u8Iterator = 0 ; Local_u8Iterator < copy_u8Length ; Local_u8Iterator++)
	{
		Local_u32Temp = copy_pu8DataArr[Local_u8Iterator];
		Local_u32AccCRC = CRC_Calculate(&Local_u32Temp , 1);
	}
	/*Reset CRC Calculation unit عشان ميحسبش المره الجايه ع القيمه القديمه اللى مخزنها عنده*/
	CRC_Reset();

	if(Local_u32AccCRC == copy_u32HostCRC)
	{
		Local_u8CRCStatus = CRC_SUCCSSES;
	}
	else
	{
		Local_u8CRCStatus = CRC_FAIL;
	}
	return Local_u8CRCStatus;
}

static void voidSendAck(uint8_t copy_u8ReplyLength)
{
	uint8_t Local_u8AckBuffer[2] = {BL_ACK , copy_u8ReplyLength	};
	USART_send_byte_blocking(&uart2, Local_u8AckBuffer[0]);
	USART_send_byte_blocking(&uart2, Local_u8AckBuffer[1]);
}

static void voidSendNAck()
{
	uint8_t Local_u8NAckBuffer = BL_NACK ;
	USART_send_byte_blocking(&uart2, Local_u8NAckBuffer);
}

static Address_State_t u8ValidateAddress(uint32_t copy_u32address)
{
	Address_State_t Local_u8AddressStatus;

	if((copy_u32address >= FLASH_BASE_ADDRESS) && (copy_u32address <= FLASH_END_ADDRESS))
	{
		Local_u8AddressStatus = VALID_ADDRESS;
	}
	else if((copy_u32address >= SRAM_BASE_ADDRESS) && (copy_u32address <= SRAM_END_ADDRESS))
	{
		Local_u8AddressStatus = VALID_ADDRESS;
	}
	else
	{
		Local_u8AddressStatus = IN_VALID_ADDRESS;
	}
	return Local_u8AddressStatus;
}

static Std_RetType_t u8ExecuteFlashErase(uint8_t copy_u8SectorNumber , uint8_t copy_u8NumberOfSectors)
{
	Std_RetType_t Local_ErrorStatus = RET_OK;

	if((copy_u8NumberOfSectors > 8) && (copy_u8SectorNumber != 0xff))
	{
		Local_ErrorStatus = RET_ERROR;
	}
	else if((copy_u8SectorNumber > 7) && (copy_u8SectorNumber != 0xff))
	{
		Local_ErrorStatus = RET_ERROR;
	}
	else
	{
		Flash_Unlock();
		if(copy_u8SectorNumber == 0xff)
		{
			/*Mass Erase*/
			Local_ErrorStatus = Flash_Mass_Erase();
		}
		else
		{
			/*Sector Erase*/
			uint8_t Local_u8RemainingSectors = 8 - copy_u8SectorNumber;  // 2  3
			if(copy_u8NumberOfSectors > Local_u8RemainingSectors)
			{
				copy_u8NumberOfSectors = Local_u8RemainingSectors;
			}
			else
			{
				/*Nothing*/
			}
			Local_ErrorStatus = Flash_Sector_Erase(copy_u8SectorNumber, copy_u8NumberOfSectors);
		}
		Flash_Lock();
	}
	return Local_ErrorStatus;
}

static Writing_State_t u8ExecuteMemWrite(uint8_t *Copy_pu8Buffer , uint32_t Copy_u32Address , uint8_t Copy_u8Length)
{
	Writing_State_t Local_u8ErrorStatus = WRITING_SUCCESS;
	uint8_t Local_u8Iterator ;
	if((Copy_u32Address >= FLASH_BASE_ADDRESS) && (Copy_u32Address <= FLASH_END_ADDRESS))
	{
		/*Write in FLASH*/
		Flash_Unlock();
		for(Local_u8Iterator = 0 ; Local_u8Iterator < Copy_u8Length ; Local_u8Iterator++)
		{
			Flash_Program((Copy_u32Address + Local_u8Iterator) ,(uint64_t)Copy_pu8Buffer[Local_u8Iterator] );
		}
		Flash_Lock();
	}
	else
	{
		/*Write in SRAM*/
		uint8_t* Local_u32PDest = (uint8_t *)Copy_u32Address;
		for(Local_u8Iterator = 0 ; Local_u8Iterator < Copy_u8Length ; Local_u8Iterator++)
		{
			Local_u32PDest[Local_u8Iterator] = Copy_pu8Buffer[Local_u8Iterator];
		}

	}
	return Local_u8ErrorStatus;
}

static Std_RetType_t u8ExecuteEnableRWProtection(uint8_t SectorDetails , uint8_t ProtectionMode)
{
	Std_RetType_t ret = RET_OK;

	ret = FLASH_OPT_Unlock();

	if(WRITE_PROTECTION_MODE == ProtectionMode)
	{
		Flash_Enable_Sectors_Protections(SECTOR_WRITE_PROTECTOIN ,(SectorDetails & 0x3f));
	}
	else if(RW_PROTECTION_MODE)
	{
		Flash_Enable_Sectors_Protections(SECTOR_Rw_PROTECTOIN ,(SectorDetails & 0x3f));
	}
	ret = FLASH_OPT_Lock();
	return ret;
}


/**
 * @brief  : Get version of our Boot Loader
 * @param  : (copy_pu8CmdPacket) Pointer to the Command Packet
 * @return : (void)
 *
 */
void BL_voidHandleGetVerCmd(uint8_t* copy_pu8CmdPacket)
{
	uint8_t Local_u8BLVercion , Local_u8RCRStatus , Local_u8CmdLength;
	uint32_t Local_u32HostCRC;

	Local_u8CmdLength = copy_pu8CmdPacket[0]+1;/*value inside length to follow + 1(size of length to follow itself)*/

	Local_u32HostCRC = *((uint32_t*)(copy_pu8CmdPacket+Local_u8CmdLength-4));

	Local_u8RCRStatus = u8VerifyCRC(copy_pu8CmdPacket , Local_u8CmdLength-4 , Local_u32HostCRC);

	if(Local_u8RCRStatus == CRC_SUCCSSES)
	{
		voidSendAck(1U); /*Bootloader version has size of 1 byte*/
		Local_u8BLVercion = BL_Version;
		USART_send_byte_blocking(&uart2,Local_u8BLVercion );
	}
	else
	{
		voidSendNAck();
	}

}

/**
 * @brief  : Get all Boot Loader supported commands
 * @param  : (copy_pu8CmdPacket) Pointer to the Command Packet
 * @return : (void)
 *
 */
void BL_voidHandleGetHelpCmd(uint8_t* copy_pu8CmdPacket)
{
	uint8_t  Local_u8RCRStatus , Local_u8CmdLength;
	uint32_t Local_u32HostCRC;

	Local_u8CmdLength = copy_pu8CmdPacket[0]+1;/*value inside length to follow + 1(size of length to follow itself)*/

	Local_u32HostCRC = *((uint32_t*)(copy_pu8CmdPacket+Local_u8CmdLength-4));

	Local_u8RCRStatus = u8VerifyCRC(copy_pu8CmdPacket , Local_u8CmdLength-4 , Local_u32HostCRC);

	if(Local_u8RCRStatus == CRC_SUCCSSES)
	{
		uint8_t Local_Pu8BLCommands[] = {	BL_GET_VER    		  ,
				                            BL_GET_HELP    		  ,
				                            BL_GET_CID    		  ,
				                            BL_GET_RDP_STATUS     ,
				                            BL_GO_TO_ADDR    	  ,
				                            BL_FLASH_ERASE   	  ,
				                            BL_MEM_WRITE    	  ,
											BL_EN_RW_PROTECT      ,
											BL_MEM_READ    		  ,
	                                        BL_READ_SECTOR_STATUS ,
	                                        BL_OTP_READ    		  ,
	                                        BL_DIS_WR_PROTECT	  ,
											BL_SYSTEM_RESET
		};
		voidSendAck(sizeof(Local_Pu8BLCommands));
		for(uint8_t local_iterator = 0 ; local_iterator < sizeof(Local_Pu8BLCommands) ; local_iterator++)
		{
			USART_send_byte_blocking(&uart2,Local_Pu8BLCommands[local_iterator]);
		}
	}
	else
	{
		voidSendNAck();
	}

}
/**
 * @brief  : Get Chip Id(CID) of our Micro Controller
 * @param  : (copy_pu8CmdPacket) Pointer to the Command Packet
 * @return : (void)
 *
 */
void BL_voidHandleGetCIDCmd(uint8_t* copy_pu8CmdPacket)
{
	uint8_t  Local_u8RCRStatus , Local_u8CmdLength;
	uint32_t Local_u32HostCRC;
	uint16_t Local_u16CID;
	Local_u8CmdLength = copy_pu8CmdPacket[0]+1;/*value inside length to follow + 1(size of length to follow itself)*/

	Local_u32HostCRC = *((uint32_t*)(copy_pu8CmdPacket+Local_u8CmdLength-4));

	Local_u8RCRStatus = u8VerifyCRC(copy_pu8CmdPacket , Local_u8CmdLength-4 , Local_u32HostCRC);

	if(Local_u8RCRStatus == CRC_SUCCSSES)
	{
		Local_u16CID = (uint16_t)(DBGMCU_IDCODE & 0x0fff);
		voidSendAck(2U);
		USART_send_byte_blocking(&uart2,Local_u16CID);
		USART_send_byte_blocking(&uart2,(Local_u16CID>>8));
	}
	else
	{
		voidSendNAck();
	}
}
/**
 * @brief  : Get Reading protection level of FLASH memory
 * @param  : (copy_pu8CmdPacket) Pointer to the Command Packet
 * @return : (void)
 *
 */
void BL_voidHandleGetRDPStatusCmd(uint8_t* copy_pu8CmdPacket)
{
	uint8_t  Local_u8RCRStatus , Local_u8CmdLength , Local_u8RDPVal;
	uint32_t Local_u32HostCRC;

	Local_u8CmdLength = copy_pu8CmdPacket[0]+1;/*value inside length to follow + 1(size of length to follow itself)*/

	Local_u32HostCRC = *((uint32_t*)(copy_pu8CmdPacket+Local_u8CmdLength-4));

	Local_u8RCRStatus = u8VerifyCRC(copy_pu8CmdPacket , Local_u8CmdLength-4 , Local_u32HostCRC);

	if(Local_u8RCRStatus == CRC_SUCCSSES)
	{
		voidSendAck(1U);
		Local_u8RDPVal = ((uint8_t)(RDP_USER_OPTION_WORDS >> 8) &(0xff));
		USART_send_byte_blocking(&uart2,Local_u8RDPVal);
	}
	else
	{
		voidSendNAck();
	}
}
/**
 * @brief  : Jump to a specific address in SRAM or FLASH
 * @param  : (copy_pu8CmdPacket) Pointer to the Command Packet
 * @return : (void)
 *
 */
void BL_voidHandleGoToAddressCmd(uint8_t* copy_pu8CmdPacket)
{
	uint8_t  Local_u8RCRStatus , Local_u8CmdLength ;
	uint32_t Local_u32HostCRC  , Local_u32Address;
	Address_State_t Local_u8AddressStatus;
	Local_u8CmdLength = copy_pu8CmdPacket[0]+1;/*value inside length to follow + 1(size of length to follow itself)*/
	Local_u32HostCRC = *((uint32_t*)(copy_pu8CmdPacket+Local_u8CmdLength-4));
	Local_u8RCRStatus = u8VerifyCRC(copy_pu8CmdPacket , Local_u8CmdLength-4 , Local_u32HostCRC);
	if(Local_u8RCRStatus == CRC_SUCCSSES)
	{
		voidSendAck(1U);
		Local_u32Address = *((uint32_t *)&copy_pu8CmdPacket[2]);
		Local_u8AddressStatus = u8ValidateAddress(Local_u32Address);
		if(VALID_ADDRESS == Local_u8AddressStatus)
		{
			USART_send_byte_blocking(&uart2,Local_u8AddressStatus);
			void (*Local_PFunc)(void) = NULL;
			Local_PFunc = (void*)Local_u32Address;
			Local_PFunc();
		}
		else
		{
			USART_send_byte_blocking(&uart2,Local_u8AddressStatus);
		}
	}
	else
	{
		voidSendNAck();
	}
}
/**
 * @brief  : Erasing specific sectors or Mass erase in FLASH
 * @param  : (copy_pu8CmdPacket) Pointer to the Command Packet
 * @return : (void)
 *
 */
void BL_voidHandleFlashEraseCmd(uint8_t* copy_pu8CmdPacket)
{
	uint8_t  Local_u8RCRStatus , Local_u8CmdLength;
	uint32_t Local_u32HostCRC;
	Std_RetType_t Localu8_ErrorStatus;

	Local_u8CmdLength = copy_pu8CmdPacket[0]+1;/*value inside length to follow + 1(size of length to follow itself)*/

	Local_u32HostCRC = *((uint32_t*)(copy_pu8CmdPacket+Local_u8CmdLength-4));

	Local_u8RCRStatus = u8VerifyCRC(copy_pu8CmdPacket , Local_u8CmdLength-4 , Local_u32HostCRC);

	if(Local_u8RCRStatus == CRC_SUCCSSES)
	{
		voidSendAck(1U);
		Localu8_ErrorStatus = u8ExecuteFlashErase(copy_pu8CmdPacket[2] , copy_pu8CmdPacket[3]);
		USART_send_byte_blocking(&uart2,Localu8_ErrorStatus);
	}
	else
	{
		voidSendNAck();
	}
}
/**
 * @brief  : Writing specific data to memory (SRAM or FLASH)
 * @param  : (copy_pu8CmdPacket) Pointer to the Command Packet
 * @return : (void)
 *
 */
void BL_voidHandleMemWriteCmd(uint8_t* copy_pu8CmdPacket)
{
	uint8_t  Local_u8RCRStatus , Local_u8CmdLength;
	uint32_t Local_u32HostCRC  , Local_u32Address;
	Address_State_t Local_u8AddressStatus;
	Writing_State_t Local_u8WritingStatus;
	Local_u8CmdLength = copy_pu8CmdPacket[0]+1;/*value inside length to follow + 1(size of length to follow itself)*/

	Local_u32HostCRC = *((uint32_t*)(copy_pu8CmdPacket+Local_u8CmdLength-4));

	Local_u8RCRStatus = u8VerifyCRC(copy_pu8CmdPacket , Local_u8CmdLength-4 , Local_u32HostCRC);

	if(Local_u8RCRStatus == CRC_SUCCSSES)
	{
		Local_u32Address = *((uint32_t*)&copy_pu8CmdPacket[2]);
		Local_u8AddressStatus = u8ValidateAddress(Local_u32Address);

		voidSendAck(1U);

		if(VALID_ADDRESS == Local_u8AddressStatus)
		{
			uint8_t Local_u8PayLoadLength = copy_pu8CmdPacket[6];
			Local_u8WritingStatus = u8ExecuteMemWrite(&copy_pu8CmdPacket[7] , Local_u32Address , Local_u8PayLoadLength);
		}
		else
		{
			Local_u8WritingStatus = WRITING_ERROR;
		}
		USART_send_byte_blocking(&uart2,Local_u8WritingStatus);
	}
	else
	{
		voidSendNAck();
	}
}
/**
 * @brief  : Enable Read/Write protection in FLASH
 * @param  : (copy_pu8CmdPacket) Pointer to the Command Packet
 * @return : (void)
 *
 */
void BL_voidHandleEnableRWCmd(uint8_t* copy_pu8CmdPacket)
{
	uint8_t  Local_u8RCRStatus , Local_u8CmdLength;
	uint32_t Local_u32HostCRC;
	uint8_t Local_u8SectorDetails , Local_u8Protectionmode;
	Std_RetType_t ret = RET_OK;
	Local_u8CmdLength = copy_pu8CmdPacket[0]+1;/*value inside length to follow + 1(size of length to follow itself)*/

	Local_u32HostCRC = *((uint32_t*)(copy_pu8CmdPacket+Local_u8CmdLength-4));

	Local_u8RCRStatus = u8VerifyCRC(copy_pu8CmdPacket , Local_u8CmdLength-4 , Local_u32HostCRC);

	if(Local_u8RCRStatus == CRC_SUCCSSES)
	{
		Local_u8SectorDetails  =  copy_pu8CmdPacket[2];
		Local_u8Protectionmode = copy_pu8CmdPacket[3];
		ret = u8ExecuteEnableRWProtection(Local_u8SectorDetails , Local_u8Protectionmode);
		voidSendAck(1U);

		USART_send_byte_blocking(&uart2,ret);
	}
	else
	{
		voidSendNAck();
	}
}
/**
 * @brief  : Reading specific data from memory (SRAM or FLASH)
 * @param  : (copy_pu8CmdPacket) Pointer to the Command Packet
 * @return : (void)
 *
 */
void BL_voidHandleMemReadCmd(uint8_t* copy_pu8CmdPacket)
{
	uint8_t  Local_u8RCRStatus , Local_u8CmdLength;
	uint32_t Local_u32HostCRC;

	uint32_t Local_u32Address ;
	uint8_t Local_u8DataLength;

	Local_u8CmdLength = copy_pu8CmdPacket[0]+1;/*value inside length to follow + 1(size of length to follow itself)*/

	Local_u32HostCRC = *((uint32_t*)(copy_pu8CmdPacket+Local_u8CmdLength-4));

	Local_u8RCRStatus = u8VerifyCRC(copy_pu8CmdPacket , Local_u8CmdLength-4 , Local_u32HostCRC);

	if(Local_u8RCRStatus == CRC_SUCCSSES)
	{
		Local_u32Address = *((uint32_t*)&copy_pu8CmdPacket[2]);
		Local_u8DataLength = copy_pu8CmdPacket[6];

		voidSendAck(Local_u8DataLength);
		uint8_t Local_u8Iterator , Local_u8Data;
		for(Local_u8Iterator = 0 ; Local_u8Iterator < Local_u8DataLength ; Local_u8Iterator++)
		{
			Local_u8Data = *((uint8_t*)Local_u32Address + Local_u8Iterator);
			USART_send_byte_blocking(&uart2 , Local_u8Data);
		}
	}
	else
	{
		voidSendNAck();
	}
}
/**
 * @brief  : Read sector status in FLASH
 * @param  : (copy_pu8CmdPacket) Pointer to the Command Packet
 * @return : (void)
 *
 */
void BL_voidHandleReadSectorStatusCmd(uint8_t* copy_pu8CmdPacket)
{
	uint8_t  Local_u8RCRStatus , Local_u8CmdLength;
	uint32_t Local_u32HostCRC;

	Local_u8CmdLength = copy_pu8CmdPacket[0]+1;/*value inside length to follow + 1(size of length to follow itself)*/

	Local_u32HostCRC = *((uint32_t*)(copy_pu8CmdPacket+Local_u8CmdLength-4));

	Local_u8RCRStatus = u8VerifyCRC(copy_pu8CmdPacket , Local_u8CmdLength-4 , Local_u32HostCRC);

	if(Local_u8RCRStatus == CRC_SUCCSSES)
	{
		voidSendAck(1U);
		uint8_t Local_SectorDetails ;
		Flash_Read_Sector_Status(&Local_SectorDetails);
		USART_send_byte_blocking(&uart2,Local_SectorDetails);
	}
	else
	{
		voidSendNAck();
	}
}
/**
 * @brief  :
 * @param  : (copy_pu8CmdPacket) Pointer to the Command Packet
 * @return : (void)
 *
 */
void BL_voidHandleOTPReadCmd(uint8_t* copy_pu8CmdPacket)
{
	uint8_t  Local_u8RCRStatus , Local_u8CmdLength;
		uint32_t Local_u32HostCRC;

		Local_u8CmdLength = copy_pu8CmdPacket[0]+1;/*value inside length to follow + 1(size of length to follow itself)*/

		Local_u32HostCRC = *((uint32_t*)(copy_pu8CmdPacket+Local_u8CmdLength-4));

		Local_u8RCRStatus = u8VerifyCRC(copy_pu8CmdPacket , Local_u8CmdLength-4 , Local_u32HostCRC);

		if(Local_u8RCRStatus == CRC_SUCCSSES)
		{
			voidSendAck(1U);

			//USART_send_byte_blocking(&uart2,Local_Pu8BLCommands[local_iterator]);

		}
		else
		{
			voidSendNAck();
		}
}
/**
 * @brief  : Disable all active protection on all sectors
 * @param  : (copy_pu8CmdPacket) Pointer to the Command Packet
 * @return : (void)
 *
 */
void BL_voidHandleDisableWRProtectCmd(uint8_t* copy_pu8CmdPacket)
{
	uint8_t  Local_u8RCRStatus , Local_u8CmdLength;
	uint32_t Local_u32HostCRC;
	Std_RetType_t ret = RET_ERROR;
	Local_u8CmdLength = copy_pu8CmdPacket[0]+1;/*value inside length to follow + 1(size of length to follow itself)*/

	Local_u32HostCRC = *((uint32_t*)(copy_pu8CmdPacket+Local_u8CmdLength-4));

	Local_u8RCRStatus = u8VerifyCRC(copy_pu8CmdPacket , Local_u8CmdLength-4 , Local_u32HostCRC);

	if(Local_u8RCRStatus == CRC_SUCCSSES)
	{
		voidSendAck(1U);

		//ret = Flash_Disable_All_Sectors_Protections();

		//ret = Flash_Disable_Sectors_Protections(SECTOR_WRITE_PROTECTOIN, 0b00000011);

		//USART_send_byte_blocking(&uart2,ret);
	}
	else
	{
		voidSendNAck();
	}
}

/************************** new commands ****************************/
/**
 * @brief  : Reset the microcontroller
 * @param  : (copy_pu8CmdPacket) Pointer to the Command Packet
 * @return : (void)
 *
 */
void BL_voidHandleResetCmd(uint8_t* copy_pu8CmdPacket)
{
	uint8_t  Local_u8RCRStatus , Local_u8CmdLength;
	uint32_t Local_u32HostCRC;
	Std_RetType_t ret = RET_ERROR;
	Local_u8CmdLength = copy_pu8CmdPacket[0]+1;/*value inside length to follow + 1(size of length to follow itself)*/

	Local_u32HostCRC = *((uint32_t*)(copy_pu8CmdPacket+Local_u8CmdLength-4));

	Local_u8RCRStatus = u8VerifyCRC(copy_pu8CmdPacket , Local_u8CmdLength-4 , Local_u32HostCRC);

	if(Local_u8RCRStatus == CRC_SUCCSSES)
	{
		voidSendAck(1U);
		ret = RET_OK;
		USART_send_byte_blocking(&uart2,ret);
		scb_system_reset_request();
	}
	else
	{
		voidSendNAck();
	}
}

