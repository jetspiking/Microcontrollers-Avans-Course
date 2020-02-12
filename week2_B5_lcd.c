#include "lcd.h"

void lcdCommand( unsigned char commands )
{
	lcdPort &= ~ (1<<rs);							// register select
	lcdSplitSend(commands);
}

void lcdChar( unsigned char string )
{
	lcdPort |= (1<<rs);                             // rs=1 selecteren data register
	lcdSplitSend(string);
}

void lcdSplitSend(unsigned char string) {
	lcdPort = (lcdPort & 0x0F) | (string & 0xF0);  // Stuur de hoge nibble
	lcdPort|= (1<<en);							   // Hoge puls naar enable pin
	_delay_us(1);
	lcdPort &= ~ (1<<en);						   // Lage puls naar enable pin
	_delay_us(200);
	lcdPort = (lcdPort & 0x0F) | (string << 4);    // Stuur de lage nibble
	lcdPort |= (1<<en);							   // Hoge puls naar enable pin
	_delay_us(1);
	lcdPort &= ~ (1<<en);						   // Lage puls naar enable pin
	_delay_ms(2);
}

void lcdString (char *str)
{
	int j;
	for(j=0;str[j]!=0;j++)
	lcdChar (str[j]);
}

void lcdClear()
{
	lcdCommand (0x01);						//Leeg display
	_delay_ms(2);
	lcdCommand (0x80);						//Cursor terug naar start
}

void lcdCursorHome() {
	lcdCommand(0x80);
}

void lcdInit() {
	lcdDirection = 0xFF;				    // LCD = output directie
	_delay_ms(20);
	lcdCommand(0x02);						// 4-bit initialisatie
	lcdCommand(0x28);                       // 2 line, 5*7 matrix in 4-bit mode geselecteerd
	lcdCommand(0x0c);                       // Scherm aan cursor uit.
	lcdCommand(0x06);                       // Cursor 1 naar rechts
	lcdCommand(0x01);                       // Leeg display
	_delay_ms(2);
}

void lcdNextLine() {
	lcdCommand(0xC0);						// Naar tweede rij
}

void lcdSetCursorPos(int position) {
	lcdCommand(position < 16 ? 0x80+position : position<32 ? 0xC0+(position-16) : 0xC0); // Cursor naar betreffende positie zetten.
}

void lcdOff() {
	lcdCommand(0x08); // LCD uitzetten.
}

void lcdBlinkingCursor() {
	lcdCommand(0x0F); // Knipperende cursor
}

void lcdSteadyCursor() {
	lcdCommand(0x0E); // LCD "static" cursor
}

void lcdShiftLeft() {
	lcdCommand(0x18); // LCD naar links shiften
}

void lcdShiftRight() {
	lcdCommand(0x1C); // LCD naar rechts shiften
}

void lcdShiftCursorLeft() {
	lcdCommand(0x10); // Cursor naar links shiften
}

void lcdShiftCursorRight() {
	lcdCommand(0x14); // Cursor naar rechts shiften
}