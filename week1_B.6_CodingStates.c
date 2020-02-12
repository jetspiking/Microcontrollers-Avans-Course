#define F_CPU 8E6
#include <avr/io.h>
#include <util/delay.h>

int STATE=0; 

void wait( int ms )
{
	int pressedButton=0;
	for (int i=0; i<ms; i++) {
		_delay_ms( 1 );		// library function (max 30 ms at 8MHz)
		if (pressedButton==0)
		if (checkTactileClick()==1) pressedButton=1;
	}
	if (pressedButton==1) cycleState();
	pressedButton=0;
}

void cycleState() {
	if (STATE>=2) STATE=0;
	else
		STATE+=1;
}

int checkTactileClick() {
	if (PINC&0x1) 
		return 1;	
	return 0;
}

int main( void )
{
	DDRD = 0xFF;			// All pins PORTD are set to output (1111.1111)
	DDRC = 0x00;			// All pins PORTC are set to input (0000.0000)
	
	while (1)
	{
		switch (STATE) {
			case 0: 
			PORTD^=0x40;
			wait(1000);
			break;
			
			case 1: 
			PORTD^=0x40;
			wait(250);
			break;
			
			case 2:
			wait(100);
			break;
		} 
	}
	return 1;
}