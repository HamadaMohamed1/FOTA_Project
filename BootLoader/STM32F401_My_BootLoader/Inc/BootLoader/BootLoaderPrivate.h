/*
 * BootLoaderPrivate.h
 *
 *  Created on: Jul 31, 2024
 *      Author: hamada
 */

#ifndef BOOTLOADER_BOOTLOADERPRIVATE_H_
#define BOOTLOADER_BOOTLOADERPRIVATE_H_
/******************* Includes *******************/
#include "../../Inc/LIBRARY/Common_Macros.h"
/******************* Macro Declarations *******************/
#define BL_Version 				2	/*2nd Version*/

#define DBGMCU_IDCODE 			*((volatile uint32_t*)0xE0042000)
#define RDP_USER_OPTION_WORDS	*((volatile uint32_t*)0x1FFFC000)




#define WRITE_PROTECTION_MODE 	1
#define RW_PROTECTION_MODE 	2




/******************* Macro Function Declarations *******************/


/******************* Data Type Declarations *******************/
typedef enum
{
	CRC_FAIL = 0,
	CRC_SUCCSSES
}CRC_State_t;

typedef enum
{
	VALID_ADDRESS = 0,
	IN_VALID_ADDRESS
}Address_State_t;

typedef enum
{
	WRITING_SUCCESS = 0,
	WRITING_ERROR
}Writing_State_t;

/******************* Function Declarations *******************/
static CRC_State_t u8VerifyCRC(uint8_t* copy_pu8DataArr , uint8_t copy_u8Length , uint32_t copy_u32HostCRC);

static void voidSendNAck();

static void voidSendAck(uint8_t copy_u8ReplyLength);

static Address_State_t u8ValidateAddress(uint32_t copy_u32address);

static uint8_t u8ExecuteFlashErase(uint8_t copy_u8SectorNumber , uint8_t copy_u8NumberOfSectors);

static uint8_t u8ExecuteMemWrite(uint8_t *Copy_pu8Buffer , uint32_t Copy_u32Address , uint8_t Copy_u8Length);









#endif /* BOOTLOADER_BOOTLOADERPRIVATE_H_ */
