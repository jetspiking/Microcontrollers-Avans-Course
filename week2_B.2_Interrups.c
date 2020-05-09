#define F_CPU 8E6
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

int current=0;
int ISR_CALLED = 0;

void next() {
	current = current+1 < 8 ? current+1 : 0; 
}

void wait( int ms )
{
	for (int i=0; i<ms; i++)
		_delay_ms( 1 );		// library function (max 30 ms at 8MHz)
}

ISR( INT0_vect )
{
    //PORTD |= (1<<5);
	ISR_CALLED=1;
}

ISR( INT1_vect )
{
    //PORTD &= ~(1<<5);	
	ISR_CALLED=1;
}

int main( void )
{
	DDRC = 0xFF;
	DDRD = 0xF0;			
	EICRA |= 0x0B;			// INT1 falling edge, INT0 rising edge
	EIMSK |= 0x03;			// Enable INT1 & INT0
	sei();				

	while (1)
	{
		PORTC = (1<<current);
		if (ISR_CALLED) {
			next();
			ISR_CALLED=0;
		}
		wait( 500 );								
	}

	return 1;
}
