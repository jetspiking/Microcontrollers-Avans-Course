#define F_CPU 8E6
#include <avr/io.h>      
#include <util/delay.h>
#include <avr/interrupt.h>
#include "lcd.h"

void wait(int ms) {
	for (int i = 0; i < ms; i++)
		_delay_ms(1);
}

void adc_init() {
	//Pagina 230, 242, 243 244, 245 (ADCSRA) voor hoofdzakelijke datasheet informatie.
	ADMUX =  1<<REFS0 | 0<<ADLAR | 1<<MUX0 | 1<<MUX1;						 //AVCC with external capacitor at AREF pin, Internal 2.56V, PORTF3 ADC3 is used
	ADCSRA = 1<<ADEN | 1<<ADSC | 0<<ADFR | 1<<ADPS2 | 1<<ADPS1 | 0<<ADPS0;	 //Enable ADC, disable free running mode, set prescaler.
}

void show_adc() {
	PORTB = ADCL;
	PORTA = ADCH;			
}

int main( void )
{	
	DDRF = 0x00;	//Port F to input mode
	DDRA = 0xFF;	//Port A to output mode
	DDRB = 0xFF;	//Port B to output mode
	PORTA=0xFF;
	PORTB=0xFF; 	
	adc_init();     //Initialize ADC	
	while(1) {
		ADCSRA|=1<<ADFR;
		show_adc();
		wait(100);
	}
}