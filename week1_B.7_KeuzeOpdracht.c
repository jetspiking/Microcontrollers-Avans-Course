#define F_CPU 8E6
#include <avr/io.h>
#include <util/delay.h>

enum states {
START, S1, S2, S3, END	
};

enum events {
NOEVENTS	
	};

enum currentState = START;

void state() {
	switch(currentState) {
	case START: 
		//Do action for START
		break;
	case S1: 
		//Do action for state 1
		break;
	case S2: 
		//Do action for state 2
		break;
	case S3: 
		//Do action for state 3
		break;
	case END: 
		//Do action for state 4
		break;
	}
}

void checkForStateChange() {
	//Read something that could change the state.
}

void wait( int ms )
{
	for (int i=0; i<ms; i++) {
		_delay_ms( 1 );		// library function (max 30 ms at 8MHz)
	}
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
		state();
	}
	return 1;
}