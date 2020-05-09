#define F_CPU 8E6
#include <avr/io.h>      
#include <util/delay.h>
#include <avr/interrupt.h>
#include "lcd.h"

int ms = 0;
float last_value=7.8125;
float timer_1=117;
float timer_2=195;

void wait(int ms) {			 // Wait methode
	for (int i = 0; i < ms; i++)
		_delay_ms(1);
}

void counter_init() {
	TCCR2 = 1<<CS22 | 0<<CS21 | 1<<CS20 | 1<<WGM21 | 0<<WGM20;   // Set prescaler on 1024, page 158 on datasheet. Clear timer on interrupt compare match. (CTC flag, page 156)
	TIMSK = 1<<OCIE2;									         // Enable OCIE2 bit for compare match interrupt, page 158 on datasheet.
	OCR2=timer_1;												 // Set value for compare match.
}

/*void adc_init() {
	//Pagina 230, 242, 243 244, 245 (ADCSRA) voor hoofdzakelijke datasheet informatie.
	ADMUX = 1<<REFS1 | 1<<REFS0 | 1<<ADLAR;						 //Internal 2.56V, PORTF0 is used
	ADCSRA = 1<<ADEN | 1<<ADFR | 1<<ADPS2 | 1<<ADPS1 | 0<<ADPS0; //Enable ADC, enable free running mode, set prescaler.
}

void show_adc() {
	
}*/

// Fired when TCNT2 equals OCR2
ISR(TIMER2_COMP_vect) { 
	PORTD^=0xFF;
	PORTB^=0xFF;
	OCR2 = OCR2 == timer_1 ? timer_2 : timer_1;
}

//Timer is hoog van 15-30. 
int main( void )
{
	sei();			//Enable interrupts		
	
	DDRD = 0xFF;	//Port D to output mode		
	PORTD = 0x00;	//Set port D LEDs to 0
	
/*	DDRA = 0xFF;	//Port A to output mode
	PORTA = 0x00;	//Set port A LEDs to 0
	
	DDRB = 0xFF;	//Port B to output mode
	PORTB = 0x00;	//Set port B LEDs to 0 */
	
	lcdInit();		//Initialize LCD
	counter_init();	//Initialize counter
	
	while(1) {
		
		wait(1);
	}
}