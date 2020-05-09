#define F_CPU 8E6
#include <avr/io.h>
#include <util/delay.h>

#define seg_a 0x01 //A = 0b00000001
#define seg_b 0x02 //B = 0b00000010
#define seg_c 0x04 //C = 0b00000100
#define seg_d 0x08 //D = 0b00001000
#define seg_e 0x10 //E = 0b00010000
#define seg_f 0x20 //F = 0b00100000
#define seg_g 0x40 //G = 0b01000000
#define seg_error 0x79 //E

int numbers[] = 
{
	seg_a|seg_b|seg_c|seg_d|seg_e|seg_f, //0
	seg_f|seg_e,						 //1
	seg_a|seg_b|seg_g|seg_e|seg_d,		 //2
	seg_a|seg_b|seg_g|seg_c|seg_d,       //3
	seg_f|seg_b|seg_g|seg_c,             //4
	seg_a|seg_f|seg_g|seg_c|seg_d,       //5
	seg_a|seg_f|seg_g|seg_c|seg_d|seg_e, //6
	seg_a|seg_b|seg_c,                   //7
	0xFF^0x80,                           //8
	seg_a|seg_b|seg_g|seg_f|seg_c|seg_d, //9
	0xFF^seg_d^0x80,					 //A
	0xFF^0x80,							 //B
	seg_a|seg_f|seg_e|seg_d,			 //C
	0xFF^seg_g,							 //D
	seg_a|seg_g|seg_d|seg_e|seg_f,		 //E
	seg_a|seg_g|seg_e|seg_f				 //F
};



void wait( int ms )
{
	for (int i=0; i<ms; i++)
		_delay_ms( 1 );		// library function (max 30 ms at 8MHz)
}

void displayHexDigit(int digit) {
	PORTB=digit > -1 && digit < 16 ? numbers[digit] : seg_error;
}


int main( void )
{
	DDRB = 0b11111111;					// PORTD all output 
	while (1)
	{
		for (int i = 0; i < 17; i++) {
			displayHexDigit(i);
			wait(350);
		}
	}
	return 1;
}
