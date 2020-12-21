#include <avr/io.h>
#define F_CPU 1000000UL
#include <util/delay.h>
int main(void)
{
	unsigned char Ring_counter [8] = {0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80};
	unsigned char Johnson_counter [17] = {0x00,0x01,0x03,0x07,0x0F,0x1F,0x3F,0x7F,0xFF,0xFE,0xFC,0xF8,0xF0,0xE0,0xC0,0x80,0x00};
	int a = 0, b = 0;
	DDRD |= (0 << DDB2) | (0 << DDB3) ;
	PORTD |= (1 << PORTD2) | (1 << PORTD3);
	DDRA |= 0xFF;
	PORTA = 0x00;

	while (1)
	{
		PORTA = 0x00;
		if (!(PIND & (1 << PIND2)))
		{
			for (a = 0 ; a <= 8 ; a++)
			{
				PORTA = Ring_counter[a];
				_delay_ms(100);
			}
		}
		PORTA = 0x00;
		if (!(PIND & (1 << PIND3)))
		{
			for (b = 0 ; b <= 17 ; b++)
			{
				PORTA = Johnson_counter[b];
				_delay_ms(100);
			}
		}
		PORTA = 0x00;
	}
}