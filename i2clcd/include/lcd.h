/*
 * disp.h
 *
 * Created: 12/17/2024 8:31:02 AM
 *  Author: ALVIS
 */ #include <avr/io.h>
//#define F_CPU	8000000UL
#include <stddef.h> 

#ifndef SET_H_
#define SET_H_
#define ctr_port PORTC
#define  dataport PORTD
#define rs 0
#define en 1
#define rw 2

void lcd_cmd(unsigned char cmd);
void lcd_data(unsigned char data);
void lcd_rint(char *str);
void lcd_init();


#endif /* DISP_H_ */