#define F_CPU 8E6
#include <avr/io.h>      
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lcd.h"

void wait(int ms) {
	for (int i = 0; i < ms; i++)
		_delay_ms(1);
}

void adc_init() {
	//Pagina 230, 242, 243 244, 245 (ADCSRA) voor hoofdzakelijke datasheet informatie.
	ADMUX =  1<<REFS0 | 1<<REFS1 | 1<<ADLAR;					 //Internal 2.56V Voltage Reference with external capacitor at AREF pin, PORTF0 is used
	ADCSRA = 1<<ADEN | 1<<ADSC | 1<<ADFR | 1<<ADPS2 | 1<<ADPS1;	 //Enable ADC, enable free running mode, set prescaler.
}

void show_adc() {
	PORTB = ADCL;
	PORTA = ADCH;			
}

int main( void )
{
	DDRF = 0x00;			//Port F to input mode
	DDRA = 0xFF;			//Port A to output mode
	DDRB = 0xFF;			//Port B to output mode
	
	adc_init();				//Initialize ADC
	lcdInit();				//Initialize LCD

	wait(1000);
	lcdString("Week 4 B3 ADC");
	wait(1000);
		
	char snum[15];
		
	while(1) {
		uint8_t adchValue = ADCH;
		PORTA=adchValue;
		
		itoa(adchValue, snum, 10);
			
		lcdClear();			
		lcdSetCursorPos(0);
		lcdString("Degrees ");
		lcdString(snum);

		wait(1000);
	}
}
