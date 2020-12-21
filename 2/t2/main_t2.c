#include <avr/io.h>
#define F_CPU 1000000UL
#include <util/delay.h>
int main(void)
{
	char hal = 0;
	DDRD |= (0 << DDB2) | (0 << DDB3) | (1 << DDB7);
	PORTD |= (1 << PORTD2) | (1 << PORTD3) | (0 << PORTD7);
	while (1)
	{
		hal = PIND & 0x04;
		if (hal == 0x00)
		{
			while (1)
			{
				PORTD |= (1 << PORTD7);
				_delay_ms(100);
				PORTD &= ~(1 << PORTD7);
				_delay_ms(100);
				hal = PIND & 0x08;
				if (hal == 0x00)
				break;
			}
		}
	}
}