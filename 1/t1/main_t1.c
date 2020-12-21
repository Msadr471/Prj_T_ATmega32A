#include <avr/io.h>
#define F_CPU 1000000UL
#include <util/delay.h>
int main(void)
{
	DDRB |= 0x00;
	PORTB |= 0x01;
	DDRD |= 0x80;
    while (1)
    {
		if (PINB == 0)
		{
			PORTD |= 0x80;
			_delay_ms(100);
			PORTD &= ~0x80;
			_delay_ms(100);
		}
		PORTD = 0x00;
    }
}