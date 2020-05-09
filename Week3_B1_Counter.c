#define F_CPU 8E6
#include <avr/io.h>      
#include <util/delay.h>
#include <avr/interrupt.h>
#include "lcd.h"

int volatile TimerPreset = 0;
int volatile OC = 0;		 // Overflow counter.

void wait(int ms) {			 // Wait methode
	for (int i = 0; i < ms; i++)
		_delay_ms(1);
}

ISR(TIMER2_OVF_vect)		 // Wordt getriggered bij een overflow.
{
	TCNT2 = TimerPreset;	 // Zet terug naar standaard waarde.
	OC++;					 // OverflowCounter met één ophogen.
}

void timerInitialize(void)	 // Initialiseren van de timer.
{
	TCNT2 = TimerPreset;	 // Timer initialiseren op 0 (er is immers nog geen Overflow opgetreden).
	TIMSK |= 1<<6;			 // TIMSK Overflow Interrupt Enable (pagina 162)
	TCCR2 = 0x07;			 // Counter standaard modus, uitvoeren
	sei();					 // Interrupts enablen.
}


int main(void) {
	lcdInit();
	lcdBlinkingCursor();
	
	char[10] num;
	
	DDRD &= ~(1 << 7);				 // Pin D7 naar input zetten.
	DDRA = 0xFF;					 // Output mode.
	DDRB = 0xFF;				     // Output mode.
	
	timerInitialize();				 // Initialiseren van Timer.
	
	while (1)  {	
		PORTA = TCNT2;				 // Counter waarde toewijzen op LED rij a.
		PORTB = OC;
		sprintf(num, "%d", TCNT2);   // OverflowCounter waarde toewijzen op LED rij b
		lcdString()
		wait(10);					 // Korte delay van ongeveer 10 ms.
	}
	return 0;
}

/*
int main()
{
	lcdInit();
	lcdString("-Dustin-");
	lcdNextLine();
	lcdString("LCD - test");
	lcdBlinkingCursor();
	lcdSetCursorPos(16);
	while (1) {
		lcdShiftRight();
		wait(1000);
	}
	return 1;
}
*/