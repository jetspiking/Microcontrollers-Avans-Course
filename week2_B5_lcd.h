#define F_CPU 8E6
#define en 3
#define rs 2
#define lcdDirection  DDRC
#define lcdPort PORTC

#include <avr/io.h>
#include <util/delay.h>

void lcdCommand(unsigned char);
void lcdChar(unsigned char);
void lcdSplitSend(unsigned char);
void lcdString(char*);
void lcdClear();
void lcdInit();
void lcdNextLine();
void lcdSetCursorPos(int);
void lcdOff();
void lcdBlinkingCursor();
void lcdSteadyCursor();
void lcdShiftLeft();
void lcdShiftRight();
void lcdShiftCursorLeft();
void lcdShiftCursorRight();
