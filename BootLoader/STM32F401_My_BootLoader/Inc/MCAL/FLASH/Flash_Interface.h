/*
 * Flash_Interface.h
 *
 *  Created on: Jul 31, 2024
 *      Author: hamada
 */

#ifndef MCAL_FLASH_FLASH_INTERFACE_H_
#define MCAL_FLASH_FLASH_INTERFACE_H_

/******************* Includes *******************/
#include "Flash_Private.h"
#include "../../LIBRARY/Common_Macros.h"
#include "../../LIBRARY/Stm32f401xx.h"
/******************* Macro Declarations *******************/

/******************* Macro Function Declarations *******************/

/******************* Data Type Declarations *******************/



/******************* Function Declarations *******************/
/**
 * @brief  : Flash memory locking
 * @param  : (void)
 * @return :
 * 			(RET_OK) : The function done successfully
 * 			(RET_ERROR) : The function has a problem to perform this action
 */
Std_RetType_t Flash_Lock();
/**
 * @brief  : Flash memory unlocking
 * @param  : (void)
 * @return :
 * 			(RET_OK) : The function done successfully
 * 			(RET_ERROR) : The function has a problem to perform this action
 */
Std_RetType_t Flash_Unlock();
/**
 * @brief  : Erasing entire flash memory
 * @param  : (void)
 * @return :
 * 			(RET_OK) : The function done successfully
 * 			(RET_ERROR) : The function has a problem to perform this action
 */
Std_RetType_t Flash_Mass_Erase();
/**
 * @brief  : Erasing seme sectors in flash memory
 * @param  : SectorNumber    : base sector to erase from it
 * 		     NumberOfSectors : Number Of Sectors to be erased
 * @return :
 * 			(RET_OK) : The function done successfully
 * 			(RET_ERROR) : The function has a problem to perform this action
 */
Std_RetType_t Flash_Sector_Erase(uint8_t SectorNumber , uint8_t NumberOfSectors);
/**
 * @brief  : Writing data inside FLASH memory
 * @param  : TypeProgramByte :
 *		     Adress	:
 *		     Data   :
 * @return :
 * 			(RET_OK) : The function done successfully
 * 			(RET_ERROR) : The function has a problem to perform this action
 */
Std_RetType_t Flash_Program(uint32_t* Address , uint8_t Data);


/**
 * @brief  : option bytes locking
 * @param  : (void)
 * @return :
 * 			(RET_OK) : The function done successfully
 * 			(RET_ERROR) : The function has a problem to perform this action
 */
Std_RetType_t FLASH_OPT_Lock();
/**
 * @brief  : option bytes Unlocking
 * @param  : (void)
 * @return :
 * 			(RET_OK) : The function done successfully
 * 			(RET_ERROR) : The function has a problem to perform this action
 */
Std_RetType_t FLASH_OPT_Unlock();
/**
 * @brief  : enable sectors protections
 * @param  : (ProtectoinType) : Write or Read
 * 			 (SectorDetails)  : Sectors to be protected
 * @return :
 * 			(RET_OK) : The function done successfully
 * 			(RET_ERROR) : The function has a problem to perform this action
 */
Std_RetType_t Flash_Enable_Sectors_Protections(SECTOR_Protectoin_Type_t ProtectoinType , uint8_t SectorDetails);

/**
 * @brief  : disable sectors protections
 * @param  : (ProtectoinType) : Write or Read
 * 			 (SectorDetails)  : Sectors to be protected
 * @return :
 * 			(RET_OK) : The function done successfully
 * 			(RET_ERROR) : The function has a problem to perform this action
 */
Std_RetType_t Flash_Disable_Sectors_Protections(SECTOR_Protectoin_Type_t ProtectoinType ,uint8_t SectorDetails);
/**
 * @brief  : disable all sectors protections
 * @param  : (void)
 * @return :
 * 			(RET_OK) : The function done successfully
 * 			(RET_ERROR) : The function has a problem to perform this action
 */
Std_RetType_t Flash_Disable_All_Sectors_Protections();
/**
 * @brief  : Read all sectors Status
 * @param  : (SectorDetails) : pointer to store sector status
 * @return : (void)
 */
void Flash_Read_Sector_Status(uint8_t* SectorDetails);

#endif /* MCAL_FLASH_FLASH_INTERFACE_H_ */
