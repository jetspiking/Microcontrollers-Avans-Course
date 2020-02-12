#define F_CPU 8E6
#include <avr/io.h>
#include <util/delay.h>

void wait( int ms )
{
	for (int i=0; i<ms; i++)
	_delay_ms( 1 );		// library function (max 30 ms at 8MHz)
}

int main( void )
{
	
	DDRD = 0xFF;			// All pins PORTD are set to output (1111.1111)
	DDRC = 0x00;			// All pins PORTC are set to input (0000.0000)
	
	while (1)
	{
		if (PINC&0x1) {		// Check whether PINC is enabled.
			wait(500);
			PORTD ^= 0x40;
		}
		else PORTD &= ~0x40;		// Set LED 7 exclusively to low
	}
	return 1;
}