/*
 * disset.c
 *
 * Created: 12/17/2024 8:49:49 AM
 *  Author: ALVIS
 */ 

#include "lcd.h"
#include <util/delay.h>
void lcd_cmd(unsigned char cmd){
	
	dataport = (cmd>>4);
	ctr_port&= ~(1<<rw);
	ctr_port &=~(1<<rs);//set rs to low
	ctr_port |=(1<<en);//set en to high
	_delay_us(1);
	ctr_port &=~(1<<en);//set en to low
	_delay_us(200);
	dataport =(cmd & 0x0F);
	ctr_port |=(1<<en);
	_delay_us(1);
	ctr_port &= ~(1<<en);
	_delay_ms(2);
}
void lcd_data(unsigned char data){
	dataport = (data >>4);
	ctr_port &= ~(1<<rw);
	ctr_port |=(1<<rs);//set rs to high
	ctr_port |=(1<<en);//set en to high
	_delay_us(1);
	ctr_port&= ~(1<<en);
	_delay_us(200);
	dataport = (data & 0x0f);
	ctr_port|=(1<<en);//set en to high
	_delay_us(1);
	ctr_port &=~(1<<en); // set en to low
	_delay_ms(2);
}

void lcd_init(){
	DDRC = 0xFF;
	DDRD = 0xFF;

	_delay_ms(20);
	lcd_cmd(0x02);
	lcd_cmd(0x28);
	lcd_cmd(0x0C);
	lcd_cmd(0x06);
	lcd_cmd(0x01);
	_delay_ms(2);
}
void lcd_rint(char *str){
	while(*str){
		lcd_data(*str++);
	}
}
