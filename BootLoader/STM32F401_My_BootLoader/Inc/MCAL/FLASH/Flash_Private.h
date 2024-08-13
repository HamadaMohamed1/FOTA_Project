/*
 * Flash_Private.h
 *
 *  Created on: Jul 31, 2024
 *      Author: hamada
 */

#ifndef MCAL_FLASH_FLASH_PRIVATE_H_
#define MCAL_FLASH_FLASH_PRIVATE_H_

/******************* Includes *******************/

/******************* Macro Declarations *******************/
#define  KEY1   			(0x45670123)
#define  KEY2   			(0xCDEF89AB)

#define LOCK_BIT_POS 		(31)
#define LOCK_BIT_MASK		(1)

#define BUSY_BIT_POS		(16)
#define BUSY_BIT_MASK		(1)

#define SER_BIT_POS			(1)
#define SER_BIT_MASK		(1)

#define SNB_BITS_POS		(3)

#define STRT_BIT_POS		(16)
#define STRT_BIT_MASK		(1)


#define MER_BIT_POS			(2)
#define MER_BIT_MASK		(1)


#define PG_BIT_POS 			(0)
#define PG_BIT_MASK			(1)




#define OPTKEY1  			(0x08192A3B)
#define OPTKEY2  			(0x4C5D6E7F)

#define OPTLOCK_BIT_POS		(0)
#define OPTLOCK_BIT_MASK	(1)

#define SPRMOD_BIT_POS		(31)

#define nWRP_BITS_POS		(16)

#define OPTSTRT_BIT_POS		(1)
#define OPTSTRT_BIT_MASK	(1)

/******************* Macro Function Declarations *******************/


/******************* Data Type Declarations *******************/
typedef enum
{
	SECTOR0 = 0,
	SECTOR1 ,
	SECTOR2 ,
	SECTOR3 ,
	SECTOR4 ,
	SECTOR5 ,
}FLASH_Sectors_t;

typedef enum
{
	SECTOR_WRITE_PROTECTOIN =0,
	SECTOR_Rw_PROTECTOIN ,
}SECTOR_Protectoin_Type_t;




/******************* Function Declarations *******************/



#endif /* MCAL_FLASH_FLASH_PRIVATE_H_ */
