/*
 * lcd.c
 *
 *  Created on: Mar 17, 2024
 *      Author: hamada
 */
#include "../../../Inc/HAL/LCD/lcd.h"


static Std_RetType_t lcd_4bit_pin_init(Port_t port , Pin_t pinNum);
static Std_RetType_t lcd_send_4bits(const lcd_4bit_t *lcd, uint8_t _data_command);
static Std_RetType_t lcd_4bit_send_enable_signal(const lcd_4bit_t *lcd);
static Std_RetType_t lcd_4bit_set_cursor(const lcd_4bit_t *lcd, uint8_t row, uint8_t coulmn);


Std_RetType_t lcd_4bit_intialize(const lcd_4bit_t *lcd)
{
	Std_RetType_t ret = RET_OK;
	uint8_t pins_counter = 0;
	if(NULL == lcd)
	{
		ret = RET_ERROR;
	}
	else
	{
		ret = lcd_4bit_pin_init(lcd->lcd_port ,lcd->lcd_rs_pin);
		ret = lcd_4bit_pin_init(lcd->lcd_port ,lcd->lcd_en_pin);
		for(pins_counter=0; pins_counter<4; pins_counter++)
		{
			ret = lcd_4bit_pin_init(lcd->lcd_port , lcd->lcd_data[pins_counter]);
		}
		delay_ms(20);
		ret = lcd_4bit_send_command(lcd, _LCD_8BIT_MODE_2_LINE);
		delay_ms(5);
		ret = lcd_4bit_send_command(lcd, _LCD_8BIT_MODE_2_LINE);
		delay_us(150);
		ret = lcd_4bit_send_command(lcd, _LCD_8BIT_MODE_2_LINE);

		ret = lcd_4bit_send_command(lcd, _LCD_CLEAR);
		ret = lcd_4bit_send_command(lcd, _LCD_RETURN_HOME);
		ret = lcd_4bit_send_command(lcd, _LCD_ENTRY_MODE_INC_SHIFT_OFF);
		ret = lcd_4bit_send_command(lcd, _LCD_DISPLAY_ON_UNDERLINE_OFF_CURSOR_OFF);
		ret = lcd_4bit_send_command(lcd, _LCD_4BIT_MODE_2_LINE);
		ret = lcd_4bit_send_command(lcd, 0x80);
	}
	return ret;
}

Std_RetType_t lcd_4bit_send_char_data(const lcd_4bit_t *lcd, uint8_t data)
{
	Std_RetType_t ret = RET_OK;
    if(NULL == lcd)
    {
        ret = RET_ERROR;
    }
    else
    {
        /* R/W Pin connected to the GND -> Logic (0) "Hard Wired" */
        /* Write Logic (1) to the "Register Select" Pin to select the "Data Register"  */
        ret = GPIO_Set_Pin_Value(lcd->lcd_port, lcd->lcd_rs_pin, PIN_HIGH);
        /* Send the Data through the (4-Pins" Data lines */
        ret = lcd_send_4bits(lcd, data >> 4);
        /* Send the Enable Signal on the "E" Pin */
        ret = lcd_4bit_send_enable_signal(lcd);
        /* Send the Data through the (4-Pins" Data lines */
        ret = lcd_send_4bits(lcd, data);
        /* Send the Enable Signal on the "E" Pin */
        ret = lcd_4bit_send_enable_signal(lcd);
    }
    return ret;
}

Std_RetType_t lcd_4bit_send_string(const lcd_4bit_t *lcd, uint8_t *str)
{
	Std_RetType_t ret = RET_OK;
	if(NULL == lcd)
	{
		ret = RET_ERROR;
	}
	else
	{
		while(*str)
		{
			ret = lcd_4bit_send_char_data(lcd,*str++);
		}
	}
	return ret;
}

Std_RetType_t lcd_4bit_send_command(const lcd_4bit_t *lcd, uint8_t command)
{
	Std_RetType_t ret = RET_OK;
	if(NULL == lcd)
	{
		ret = RET_ERROR;
	}
	else
	{
		/* R/W Pin connected to the GND -> Logic (0) "Hard Wired" */
		/* Write Logic (0) to the "Register Select" Pin to select the "Instruction Register"  */
		ret = GPIO_Set_Pin_Value(lcd->lcd_port, lcd->lcd_rs_pin, PIN_LOW);
		/* Send the Command through the (4-Pins" Data lines */
		ret = lcd_send_4bits(lcd, command >> 4);
		/* Send the Enable Signal on the "E" Pin */
		ret = lcd_4bit_send_enable_signal(lcd);
		/* Send the Command through the (4-Pins" Data lines */
		ret = lcd_send_4bits(lcd, command);
		/* Send the Enable Signal on the "E" Pin */
		ret = lcd_4bit_send_enable_signal(lcd);
	}
	return ret;
}

Std_RetType_t lcd_4bit_clear(const lcd_4bit_t *lcd)
{
	Std_RetType_t ret = RET_OK;
	if(NULL == lcd)
	{
		ret = RET_ERROR;
	}
	else
	{
		ret = lcd_4bit_send_command(lcd,_LCD_CLEAR);
		delay_ms(2);
	}
	return ret;
}


Std_RetType_t lcd_4bit_send_string_pos(const lcd_4bit_t *lcd, uint8_t row, uint8_t column, uint8_t *str)
{
	Std_RetType_t ret = RET_OK;
	ret = lcd_4bit_set_cursor(lcd , row , column);
	ret = lcd_4bit_send_string(lcd, str);
	return ret;
}

static Std_RetType_t lcd_send_4bits(const lcd_4bit_t *lcd, uint8_t _data_command){
	Std_RetType_t ret = RET_OK;
    ret = GPIO_Set_Pin_Value(lcd->lcd_port,lcd->lcd_data[0], (_data_command >> 0) & (uint8_t)0x01);
    ret = GPIO_Set_Pin_Value(lcd->lcd_port,lcd->lcd_data[1], (_data_command >> 1) & (uint8_t)0x01);
    ret = GPIO_Set_Pin_Value(lcd->lcd_port,lcd->lcd_data[2], (_data_command >> 2) & (uint8_t)0x01);
    ret = GPIO_Set_Pin_Value(lcd->lcd_port,lcd->lcd_data[3], (_data_command >> 3) & (uint8_t)0x01);
    return ret;
}


static Std_RetType_t lcd_4bit_send_enable_signal(const lcd_4bit_t *lcd)
{
	Std_RetType_t ret = RET_OK;
    ret = GPIO_Set_Pin_Value(lcd->lcd_port,lcd->lcd_en_pin, PIN_HIGH);
    delay_us(11);
    ret = GPIO_Set_Pin_Value(lcd->lcd_port,lcd->lcd_en_pin, PIN_LOW);
    return ret;
}


static Std_RetType_t lcd_4bit_set_cursor(const lcd_4bit_t *lcd, uint8_t row, uint8_t coulmn){
	Std_RetType_t ret = RET_OK;
    coulmn--;
    switch(row){
        case ROW1 : ret = lcd_4bit_send_command(lcd, (0x80 + coulmn)); break;
        case ROW2 : ret = lcd_4bit_send_command(lcd, (0xc0 + coulmn)); break;
        case ROW3 : ret = lcd_4bit_send_command(lcd, (0x94 + coulmn)); break;
        case ROW4 : ret = lcd_4bit_send_command(lcd, (0xd4 + coulmn)); break;
        default : ;
    }
    return ret;
}

static Std_RetType_t lcd_4bit_pin_init(Port_t port , Pin_t pinNum)
{
	Std_RetType_t ret = RET_OK;
	PinConfig_t pin = {.Port = port,.Pin=pinNum,.Mode=OUTPUT,.Type=PUSH_PULL,.Speed=LOW,.PullType=NO_PULL};
	ret = GPIO_Pin_init(&pin);
	return ret;
}
