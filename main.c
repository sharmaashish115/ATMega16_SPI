/*
 * ATMega16_SPI.c
 *
 * Created: 2023-06-17 10:18:53 PM
 * Author : a_shi
 */ 

#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>

void SPI_Write(unsigned char data)
{
	SPDR = data;
	while (!(SPSR &(1<<SPIF)));
}
unsigned char SPI_Read()
{
	SPDR = 0xFF;
	while (!(SPSR & (1<<SPIF)));
	return SPDR;
	
}
int main(void)
{
    DDRB |= (1<<DDB4) | (1<<DDB5) | (1<<DDB7);		//PB4,5,7 as Output
	DDRB &= (~(1<<DDB6));							//PB6 as Input
	
	SPCR |= (1<<SPE) | (1<<MSTR) | (1<<SPR0);
	SPSR &= (~(1<<SPI2X)); 
	
	
    while (1) 
    {
		PORTB &= (~(1<<PB4));
		SPI_Write('A');
		PORTB |= (1<<PB4);
		_delay_ms(1000);
		
		PORTB &= (~(1<<PB4));
		SPI_Write('B');
		PORTB |= (1<<PB4);
		_delay_ms(1000);
    }
}

