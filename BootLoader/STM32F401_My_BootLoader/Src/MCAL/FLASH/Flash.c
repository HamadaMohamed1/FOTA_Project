/*
 * Flash.c
 *
 *  Created on: Jul 31, 2024
 *      Author: hamada
 */
#include "../../../Inc/MCAL/FLASH/Flash_Interface.h"


/**
 * @brief  : Flash memory locking
 * @param  : (void)
 * @return :
 * 			(RET_OK) : The function done successfully
 * 			(RET_ERROR) : The function has a problem to perform this action
 */
Std_RetType_t Flash_Lock()
{
	Std_RetType_t ret = RET_OK;
	FLASH->FLASH_CR |= (LOCK_BIT_MASK << LOCK_BIT_POS);
	return ret;
}

/**
 * @brief  : Flash memory unlocking
 * @param  : (void)
 * @return :
 * 			(RET_OK) : The function done successfully
 * 			(RET_ERROR) : The function has a problem to perform this action
 */
Std_RetType_t Flash_Unlock()
{
	Std_RetType_t ret = RET_OK;
	FLASH->FLASH_KEYR = KEY1;
	FLASH->FLASH_KEYR = KEY2;
	return ret;
}
/**
 * @brief  : Erasing entire flash memory
 * @param  : (void)
 * @return :
 * 			(RET_OK) : The function done successfully
 * 			(RET_ERROR) : The function has a problem to perform this action
 */
Std_RetType_t Flash_Mass_Erase()
{
	Std_RetType_t ret = RET_OK;

	while((FLASH->FLASH_SR &(BUSY_BIT_MASK << BUSY_BIT_POS))); /*checking the BSY bit*/

	FLASH->FLASH_CR |= (MER_BIT_MASK << MER_BIT_POS); /*Set the MER bit */

	FLASH->FLASH_CR |= (STRT_BIT_MASK<< STRT_BIT_POS);/*Set STRT bit*/

	while((FLASH->FLASH_SR &(BUSY_BIT_MASK << BUSY_BIT_POS))); /*checking the BSY bit*/

	return ret;
}
/**
 * @brief  : Erasing seme sectors in flash memory
 * @param  : SectorNumber    : base sector to erase from it
 * 		     NumberOfSectors : Number Of Sectors to be erased
 * @return :
 * 			(RET_OK) : The function done successfully
 * 			(RET_ERROR) : The function has a problem to perform this action
 */
Std_RetType_t Flash_Sector_Erase(uint8_t SectorNumber , uint8_t NumberOfSectors)
{
	Std_RetType_t ret = RET_OK;

	while((FLASH->FLASH_SR &(BUSY_BIT_MASK << BUSY_BIT_POS))); /*checking the BSY bit*/

	FLASH->FLASH_CR |= (SER_BIT_MASK << SER_BIT_POS); /*Set the SER bit */

	FLASH->FLASH_CR |= (SectorNumber << SNB_BITS_POS); /*select the sector in SNB_BITS*/

	FLASH->FLASH_CR |= (STRT_BIT_MASK<< STRT_BIT_POS);/*Set STRT bit*/

	while((FLASH->FLASH_SR &(BUSY_BIT_MASK << BUSY_BIT_POS))); /*checking the BSY bit*/

	return ret;
}


/**
 * @brief  : Writing data inside FLASH memory
 * @param  : TypeProgramByte :
 *		     Adress	:
 *		     Data   :
 * @return :
 * 			(RET_OK) : The function done successfully
 * 			(RET_ERROR) : The function has a problem to perform this action
 */
Std_RetType_t Flash_Program(uint32_t* Address , uint8_t Data)
{
	while((FLASH->FLASH_SR &(BUSY_BIT_MASK << BUSY_BIT_POS))); /*checking the BSY bit*/

	FLASH->FLASH_CR |= ( PG_BIT_MASK << PG_BIT_POS ); /*Set the PG bit*/

	FLASH->FLASH_CR &=~ (0b11 << 8);	/*PSIZE[1:0]: Program size These bits select the program parallelism. */

	//*Adress = Data;
    *(uint8_t*)Address = Data;

	while((FLASH->FLASH_SR &(BUSY_BIT_MASK << BUSY_BIT_POS))); /*waiting the BSY bit to be cleared*/

	return RET_OK;
}
/**
 * @brief  : option bytes locking
 * @param  : (void)
 * @return :
 * 			(RET_OK) : The function done successfully
 * 			(RET_ERROR) : The function has a problem to perform this action
 */
Std_RetType_t FLASH_OPT_Lock()
{
	FLASH->FLASH_OPTCR |= (OPTLOCK_BIT_MASK << OPTLOCK_BIT_POS); /*OPTLOCK: Option lock*/
	return RET_OK;
}
/**
 * @brief  : option bytes Unlocking
 * @param  : (void)
 * @return :
 * 			(RET_OK) : The function done successfully
 * 			(RET_ERROR) : The function has a problem to perform this action
 */
Std_RetType_t FLASH_OPT_Unlock()
{
	FLASH->FLASH_OPTKEYR = OPTKEY1;
	FLASH->FLASH_OPTKEYR = OPTKEY2;
	return RET_OK;
}
/**
 * @brief  : enable sectors protections
 * @param  : (ProtectoinType) : Write or Read
 * 			 (SectorDetails)  : Sectors to be protected
 * @return :
 * 			(RET_OK) : The function done successfully
 * 			(RET_ERROR) : The function has a problem to perform this action
 */
Std_RetType_t Flash_Enable_Sectors_Protections(SECTOR_Protectoin_Type_t ProtectoinType , uint8_t SectorDetails)
{
	while((FLASH->FLASH_SR &(BUSY_BIT_MASK << BUSY_BIT_POS))); /*checking the BSY bit*/

	FLASH->FLASH_OPTCR |= (ProtectoinType << SPRMOD_BIT_POS);  /*Bit 31 SPRMOD: Selection of Protection Mode of nWPRi bits*/

	if(ProtectoinType == SECTOR_WRITE_PROTECTOIN)
	{
		FLASH->FLASH_OPTCR &=~ (SectorDetails << nWRP_BITS_POS);  		    /*in write protection -> 0 : means protection active*/
	}
	else								   			/*in read protection -> 1 : means protection active*/
	{
		FLASH->FLASH_OPTCR |= (SectorDetails << nWRP_BITS_POS);
	}

	FLASH->FLASH_OPTCR |= (OPTSTRT_BIT_MASK << OPTSTRT_BIT_POS);			/*OPTSTRT bit */

	while((FLASH->FLASH_SR &(BUSY_BIT_MASK << BUSY_BIT_POS))); /*wait the BSY bit to be cleared*/

	return RET_OK;
}

/**
 * @brief  : disable sectors protections
 * @param  : (ProtectoinType) : Write or Read
 * 			 (SectorDetails)  : Sectors to be protected
 * @return :
 * 			(RET_OK) : The function done successfully
 * 			(RET_ERROR) : The function has a problem to perform this action
 */
Std_RetType_t Flash_Disable_Sectors_Protections(SECTOR_Protectoin_Type_t ProtectoinType ,uint8_t SectorDetails)
{
	while((FLASH->FLASH_SR &(BUSY_BIT_MASK << BUSY_BIT_POS))); /*checking the BSY bit*/

	FLASH->FLASH_OPTCR |= (ProtectoinType << SPRMOD_BIT_POS);  /*Bit 31 SPRMOD: Selection of Protection Mode of nWPRi bits*/

	if(ProtectoinType == SECTOR_WRITE_PROTECTOIN)
	{
		FLASH->FLASH_OPTCR |= (SectorDetails << nWRP_BITS_POS);  /*in write protection -> 1 : means protection not active*/
	}
	else								   						/*in read protection -> 0 : means protection not active*/
	{
		FLASH->FLASH_OPTCR &=~ (SectorDetails << nWRP_BITS_POS);
	}
	FLASH->FLASH_OPTCR |= (OPTSTRT_BIT_MASK << OPTSTRT_BIT_POS);			/*OPTSTRT bit */

	while((FLASH->FLASH_SR &(BUSY_BIT_MASK << BUSY_BIT_POS))); /*wait the BSY bit to be cleared*/

	return RET_OK;
}
/**
 * @brief  : disable all sectors protections
 * @param  : (ProtectoinType) : Write or Read
 * 			 (SectorDetails)  : Sectors to be protected
 * @return :
 * 			(RET_OK) : The function done successfully
 * 			(RET_ERROR) : The function has a problem to perform this action
 */
Std_RetType_t Flash_Disable_All_Sectors_Protections()
{
	while((FLASH->FLASH_SR &(BUSY_BIT_MASK << BUSY_BIT_POS))); /*checking the BSY bit*/

	FLASH->FLASH_OPTCR &=~ (1 << SPRMOD_BIT_POS);  /*Bit 31 SPRMOD: Selection of Protection Mode of nWPRi bits*/

	FLASH->FLASH_OPTCR |= (0b111111 << nWRP_BITS_POS);

	FLASH->FLASH_OPTCR |= (OPTSTRT_BIT_MASK << OPTSTRT_BIT_POS);						/*OPTSTRT bit */

	while((FLASH->FLASH_SR &(BUSY_BIT_MASK << BUSY_BIT_POS))); /*wait the BSY bit to be cleared*/

	return RET_OK;
}

/**
 * @brief  : Read all sectors Status
 * @param  : (SectorDetails) : pointer to store sector status
 * @return : (void)
 */
void Flash_Read_Sector_Status(uint8_t* SectorDetails)
{
	*SectorDetails = ((uint8_t)(FLASH->FLASH_OPTCR >> nWRP_BITS_POS) & 0x3f);
}



