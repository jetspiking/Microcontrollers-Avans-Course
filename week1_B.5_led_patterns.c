#define F_CPU 8E6
#include <avr/io.h>
#include <util/delay.h>

int LIGHT_EFFECT_0[] = {0x00,0x01,0x03,0x07, 0x0E, 0x1C, 0x38, 0x70, 0xE0, 0xC0, 0x80, 0x00};
int LIGHT_EFFECT_1[] = {0x00,0x01,0x03,0x06, 0x0C, 0x19, 0x33, 0x64, 0xCC, 0x18, 0x30, 0x60, 0xC0, 0x80, 0x00};
int LIGHT_EFFECT_2[] = {0x00, 0x81, 0x42, 0x24, 0x18, 0x00};

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
		for (int i = 0; i < 12; i++) {
			PORTD = LIGHT_EFFECT_0[i];
			wait(100);
		}
		for (int i = 0; i < 15; i++) {
			PORTD = LIGHT_EFFECT_1[i];
			wait(100);
		}
		for (int i = 0; i < 4; i++)
			for (int i = 0; i < 6; i++) {
				PORTD = LIGHT_EFFECT_2[i];
				wait(100);
			}
	}
	return 1;
}
