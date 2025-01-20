#include <avr/io.h>
// #define F_CPU 8000000UL
#include <util/delay.h>
#include <stdio.h>
#include "lcd.h"
#include <stdlib.h> 
#define v_ref 5.0			 // reference voltage
#define adc_rsolution 1023.0 // 10bit adc
//#define standardout 220.0  
//#define sens(v_ref) (v_ref / standardout)  // Define a macro that takes a v_ref  


void adc_init();
uint16_t ANALOG_READ(uint8_t channel);
float adc_to_volt(uint8_t adc_value);
int main(void)
{
	uint16_t adc_value;
	// float voltage;
	adc_init();

	// DDRA = 0x00;
	ADMUX = 0X40;
	ADCSRA = 0X87;

	lcd_init();
	// lcd_cmd(0x80);
	lcd_rint("ADC TEST!");
	_delay_ms(3000);

	/* Replace with your application code */
	while (1)
	{
		char strn[20];
		char _voltage[20];
		adc_value = ANALOG_READ(0);
		float voltage = adc_value * (v_ref / adc_rsolution);
       float actualvoltage = voltage / (2.8/220.0);  
		// float value = (float)voltage;
		//  voltage = adc_to_volt(adc_value);
		sprintf(strn, "%d",adc_value );					   // Buffer to hold the string representation of the float
		dtostrf(actualvoltage, 6, 2, _voltage);   // Convert float to string with 2 decimal places
		lcd_cmd(0X01);
		lcd_rint("ADC Value: ");
		lcd_rint(strn);
		lcd_cmd(0xC0);
		lcd_rint("Voltage: ");
		lcd_rint(_voltage);
		_delay_ms(2000);
		/*
		PORTD &= ~(1 << 6);
		_delay_ms(1000);
		PORTD |= (1 << 6);
		_delay_ms(1000);\
		*/
	}
}
void adc_init()
{
	ADMUX = (1 << REFS0);											   // set reference voltage to avcc
	ADCSRA = (1 << ADEN) | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0); // enabling adc and seting the adpsc(128)
}

uint16_t ANALOG_READ(uint8_t channel)
{
	int result;
	int Ahigh;
	int Alow;
	ADMUX = ADMUX | (channel & 0x0F);
	ADCSRA |= (1 << ADSC);
	while ((ADCSRA & (1 << ADIF)) == 0)
		;
	_delay_us(10);
	Alow = (int)ADCL;
	Ahigh = (int)ADCH * 256;
	result = Alow + Ahigh;
	return result;
}
// float adc_to_volt( uint8_t adc_value){
//  return (adc_value * v_ref) / adc_rsolution ;//converting adc to voltage
//}