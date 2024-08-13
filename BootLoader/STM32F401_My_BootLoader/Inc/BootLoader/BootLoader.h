/*
 * BootLoader.h
 *
 *  Created on: Jul 31, 2024
 *      Author: hamada
 */

#ifndef BOOTLOADER_BOOTLOADER_H_
#define BOOTLOADER_BOOTLOADER_H_

/******************* Includes *******************/
#include "BootLoaderPrivate.h"
#include "../../Inc/LIBRARY/Common_Macros.h"
#include "../../Inc/LIBRARY/Stm32f401xx.h"
#include "../../Inc/MCAL/CRC/CRC.h"
#include "../../Inc/MCAL/USART/USART_Interface.h"
#include "../../Inc/MCAL/FLASH/Flash_Interface.h"
#include "../../Inc/Core_Peripheral/SCB/SCB_Interface.h"
/******************* Macro Declarations *******************/
#define BL_GET_VER    			0x51
#define BL_GET_HELP    			0x52
#define BL_GET_CID    			0x53
#define BL_GET_RDP_STATUS    	0x54
#define BL_GO_TO_ADDR    		0x55
#define BL_FLASH_ERASE   		0x56
#define BL_MEM_WRITE    		0x57
#define BL_EN_RW_PROTECT    	0x58
#define BL_MEM_READ    			0x59
#define BL_READ_SECTOR_STATUS   0x5A
#define BL_OTP_READ    			0x5B
#define BL_DIS_WR_PROTECT    	0x5C

/************* new commands *****************/
#define BL_SYSTEM_RESET			0x5D



#define BL_ACK					0xA5
#define BL_NACK					0x7F



/******************* Macro Function Declarations *******************/

/******************* Data Type Declarations *******************/

/******************* Function Declarations *******************/
/**
 * @brief  : Get version of our Boot Loader
 * @param  : (copy_pu8CmdPacket) Pointer to the Command Packet
 * @return : (void)
 *
 */
void BL_voidHandleGetVerCmd(uint8_t* copy_pu8CmdPacket);
/**
 * @brief  : Get all Boot Loader supported commands
 * @param  : (copy_pu8CmdPacket) Pointer to the Command Packet
 * @return : (void)
 *
 */
void BL_voidHandleGetHelpCmd(uint8_t* copy_pu8CmdPacket);
/**
 * @brief  : Get Chip Id(CID) of our Micro Controller
 * @param  : (copy_pu8CmdPacket) Pointer to the Command Packet
 * @return : (void)
 *
 */
void BL_voidHandleGetCIDCmd(uint8_t* copy_pu8CmdPacket);
/**
 * @brief  : Get Reading protection level of FLASH memory
 * @param  : (copy_pu8CmdPacket) Pointer to the Command Packet
 * @return : (void)
 *
 */
void BL_voidHandleGetRDPStatusCmd(uint8_t* copy_pu8CmdPacket);
/**
 * @brief  : Jump to a specific address in SRAM or FLASH
 * @param  : (copy_pu8CmdPacket) Pointer to the Command Packet
 * @return : (void)
 *
 */
void BL_voidHandleGoToAddressCmd(uint8_t* copy_pu8CmdPacket);
/**
 * @brief  : Erasing specific sectors or Mass erase in FLASH
 * @param  : (copy_pu8CmdPacket) Pointer to the Command Packet
 * @return : (void)
 *
 */
void BL_voidHandleFlashEraseCmd(uint8_t* copy_pu8CmdPacket);
/**
 * @brief  : Writing specific data to memory (SRAM or FLASH)
 * @param  : (copy_pu8CmdPacket) Pointer to the Command Packet
 * @return : (void)
 *
 */
void BL_voidHandleMemWriteCmd(uint8_t* copy_pu8CmdPacket);
/**
 * @brief  : Enable Read/Write protection in FLASH
 * @param  : (copy_pu8CmdPacket) Pointer to the Command Packet
 * @return : (void)
 *
 */
void BL_voidHandleEnableRWCmd(uint8_t* copy_pu8CmdPacket);
/**
 * @brief  : Reading specific data from memory (SRAM or FLASH)
 * @param  : (copy_pu8CmdPacket) Pointer to the Command Packet
 * @return : (void)
 *
 */
void BL_voidHandleMemReadCmd(uint8_t* copy_pu8CmdPacket);
/**
 * @brief  : Read sector status in FLASH
 * @param  : (copy_pu8CmdPacket) Pointer to the Command Packet
 * @return : (void)
 *
 */
void BL_voidHandleReadSectorStatusCmd(uint8_t* copy_pu8CmdPacket);
/**
 * @brief  :
 * @param  : (copy_pu8CmdPacket) Pointer to the Command Packet
 * @return : (void)
 *
 */
void BL_voidHandleOTPReadCmd(uint8_t* copy_pu8CmdPacket);
/**
 * @brief  : Disable all active protection on all sectors
 * @param  : (copy_pu8CmdPacket) Pointer to the Command Packet
 * @return : (void)
 *
 */
void BL_voidHandleDisableWRProtectCmd(uint8_t* copy_pu8CmdPacket);



/*********************************** new commands *********************************************/
/**
 * @brief  : Reset the microcontroller
 * @param  : (copy_pu8CmdPacket) Pointer to the Command Packet
 * @return : (void)
 *
 */
void BL_voidHandleResetCmd(uint8_t* copy_pu8CmdPacket);





#endif /* BOOTLOADER_BOOTLOADER_H_ */
