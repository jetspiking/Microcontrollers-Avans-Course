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
	
	DDRD = 0b11111111;			// All pins PORTD are set to output 
	
	while (1)
	{
		PORTD = 0x80;			// Write 1000.0000 PORTD
		wait( 500 );				
		PORTD = 0x40;			// Write 0100.0000 PORTD
		wait( 500 );				
	}
	return 1;
}