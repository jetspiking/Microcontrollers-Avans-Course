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
		for (int i = 0x01; i <= 0x80; i<<=1) {
			PORTD = i; 
			wait(50);
		} 
	}
	return 1;
}
