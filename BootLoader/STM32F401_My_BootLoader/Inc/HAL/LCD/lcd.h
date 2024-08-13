/*
 * lcd.h
 *
 *  Created on: Mar 17, 2024
 *      Author: hamada
 */

#ifndef HAL_LCD_LCD_H_
#define HAL_LCD_LCD_H_

/*---------- Includes ----------*/
#include "../../MCAL/GPIO/GPIO_Interface.h"
#include "../../Core_Peripheral/SystTick/SystTick_Interface.h"
#include "../../LIBRARY/Common_Macros.h"
/*---------- Section: Macro Declarations ----------*/
#define _LCD_CLEAR                    				  	0X01
#define _LCD_RETURN_HOME                				0x02
#define _LCD_ENTRY_MODE_DEC_SHIFT_OFF 					0x04
#define _LCD_ENTRY_MODE_DEC_SHIFT_ON   					0x05
#define _LCD_ENTRY_MODE_INC_SHIFT_OFF   				0x06
#define _LCD_ENTRY_MODE_INC_SHIFT_ON    				0x07
#define _LCD_CURSOR_MOVE_SHIFT_LEFT     				0x10
#define _LCD_CURSOR_MOVE_SHIFT_RIGHT    				0x14
#define _LCD_DISPLAY_SHIFT_LEFT         				0x18
#define _LCD_DISPLAY_SHIFT_RIGHT        				0x1C
#define _LCD_DISPLAY_ON_UNDERLINE_OFF_CURSOR_OFF 		0x0C
#define _LCD_DISPLAY_ON_UNDERLINE_OFF_CURSOR_ON  		0x0D
#define _LCD_DISPLAY_ON_UNDERLINE_ON_CURSOR_OFF  		0x0E
#define _LCD_DISPLAY_ON_UNDERLINE_ON_CURSOR_ON   		0x0F
#define _LCD_DISPLAY_OFF_CURSOR_OFF              		0x08
#define _LCD_8BIT_MODE_2_LINE           				0x38
#define _LCD_4BIT_MODE_2_LINE           				0x28

#define _LCD_CGRAM_START                				0x40
#define _LCD_DDRAM_START                				0x80

#define ROW1 											1
#define ROW2 											2
#define ROW3 											3
#define ROW4 											4

/*---------- Section: Macro Functions Declarations ----------*/

/*---------- Section: Data Type Declarations ----------*/
typedef struct
{
    uint8_t  lcd_port;
    uint8_t	 lcd_rs_pin :4;
    uint8_t  lcd_en_pin :4;
    uint8_t  lcd_data[4];
}lcd_4bit_t;


/*---------- Section: Function Declarations ----------*/

Std_RetType_t lcd_4bit_intialize(const lcd_4bit_t *lcd);
Std_RetType_t lcd_4bit_send_command(const lcd_4bit_t *lcd, uint8_t command);
Std_RetType_t lcd_4bit_send_char_data(const lcd_4bit_t *lcd, uint8_t data);
Std_RetType_t lcd_4bit_send_char_data_pos(const lcd_4bit_t *lcd,uint8_t row, uint8_t column, uint8_t data);
Std_RetType_t lcd_4bit_send_string(const lcd_4bit_t *lcd, uint8_t *str);
Std_RetType_t lcd_4bit_send_string_pos(const lcd_4bit_t *lcd, uint8_t row, uint8_t column, uint8_t *str);
Std_RetType_t lcd_4bit_send_custom_char(const lcd_4bit_t *lcd, uint8_t row, uint8_t column,const uint8_t _chr[], uint8_t mem_pos);
Std_RetType_t lcd_4bit_clear(const lcd_4bit_t *lcd);



Std_RetType_t convert_uint8_to_string(uint8_t value, uint8_t *str);
Std_RetType_t convert_uint16_to_string(uint8_t value, uint8_t *str);
Std_RetType_t convert_uint32_to_string(uint8_t value, uint8_t *str);

#endif /* HAL_LCD_LCD_H_ */
