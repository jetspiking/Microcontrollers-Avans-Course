#define F_CPU 8E6
#include <avr/io.h>      
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lcd.h"

#define DDR_SPI  DDRB
#define PORT_SPI PORTB
#define SPI_SCK  1
#define SPI_MOSI 2
#define SPI_MISO 3
#define SPI_SS	 0

char character;

void wait(int ms) {
	for (int i = 0; i < ms; i++)
		_delay_ms(1);
}

void spi_masterInit(void) {
	DDR_SPI = 0xff;
	DDR_SPI &= ~(1<<SPI_MISO);
	PORT_SPI |= 1<<(SPI_SS);
	SPCR = (1<<SPE)|(1<<MSTR)|(1<<SPR1);
}

void spi_write( unsigned char data ) {
	SPDR = data;
	while(!(SPSR & 1<<SPIF));
}

char spi_writeRead( unsigned char data )
{
	SPDR = data;
	while(!(SPSR & 1<<SPIF)); 
	data = SPDR;
	return data;
}

void spi_slaveSelect(unsigned char chipNumber) {
	PORTB &= ~1<<chipNumber; 
}

void spi_slaveDeSelect(unsigned char chipNumber) {
	PORTB |= 1<<chipNumber; 
}

void segmentInit()
{
	 //Set BCD decode mode for digits DIG0-DIG3
	spi_slaveSelect(0);		//CS pin is pulled low
	spi_write(0x09);		//Select decode mode register
	spi_write(0x0F);		//Select BCD mode for digits 0 t/m 3
	spi_slaveDeSelect(0);	//CS pin is pulled high
	
	//Set display brightness
	spi_slaveSelect(0);		//CS pin is pulled low
	spi_write(0x0A);		//Select intensity register
	spi_write(0x0A);		//Set maximum brightness
	spi_slaveDeSelect(0);   //CS pin is pulled high
	
	//Set display refresh
	spi_slaveSelect(0);		//CS pin is pulled low
	spi_write(0x0B);		//Select scan limit register
	spi_write(0x03);		//Select digits 0 t/m 3
	spi_slaveDeSelect(0);   //CS pin is pulled high
	
	//Disable shutdown mode
	spi_slaveSelect(0);		//CS pin is pulled low
	spi_write(0x0C);		//Select display test register
	spi_write(0x01);		//Enable display test
	spi_slaveDeSelect(0);	//CS pin is pulled high
}

void displayOn()
{
	//Disable shutdown mode
	spi_slaveSelect(0);		//CS pin is pulled low
	spi_write(0x0C);		//Select display test register
	spi_write(0x01);		//Enable display test
	spi_slaveDeSelect(0);	//CS pin is pulled high
}

void displayOff()
{
	//Enable shutdown mode
	spi_slaveSelect(0);		//CS pin is pulled low
	spi_write(0x0C);		//Select display test register
	spi_write(0x00);		//Disable display test
	spi_slaveDeSelect(0);	//CS pin is pulled high
}

void spi_writeWord(unsigned char address, unsigned char data) 
{
		spi_slaveSelect(0);		//CS pin is pulled low
		spi_write(address);		//Select register
		spi_write(data);		//Command function
		spi_slaveDeSelect(0);	//CS pin is pulled high
}

int main() {
	DDRB=0x01;
	spi_masterInit();
	segmentInit();
	lcdInit();
	lcdSetCursorPos(0);
	lcdBlinkingCursor();
	lcdString("Week4 SPI C1 B");	
	
	wait(1000);					//Delay 1s
	
	while(1) {
	for (char i = 1; i<=4; i++) 
	{
		spi_slaveSelect(0);		//CS pin is pulled low
		spi_write(i);			//Write to segment display address "i"
		spi_write(0);			//Set to "0"
		spi_slaveDeSelect(0);	//CS pin is pulled high
	}
	wait(1000);					//Delay 1s
	
	for (char i = 1; i <=4; i++) 
	{
		spi_slaveSelect(0);		//CS pin is pulled low
		spi_write(i);			//Write to segment display address "i"
		spi_write(i);			//Display number "i"
		spi_slaveDeSelect(0);   //CS pin is pulled high
		wait(1000);				//Delay 1s
	}
		wait(1000);
	}
	return (1);
}