#include <avr/io.h>
#include <stdlib.h>
#include <stdio.h>
#define F_CPU 1000000UL
#include <util/delay.h>
#include "LIB/Configuration.h"
#include "LIB/LCD_8_bit.h"
int main(void)
{
	char a = 0;
	LCD_Init();
	DDRD |= (0 << DDD2) | (0 << DDD3) | (1 << DDD7);
	PORTD |= (1 << PORTD2) | (1 << PORTD3);
	LCD_Clear();
	LCD_GoToXY (0,0);
	LCD_DisplayString ("Hello World!");
	_delay_ms(500);
	LCD_GoToXY (0,0);
	LCD_Clear();
	while (1)
	{
		if (!(PIND & (1 << PIND2)))
		{
			for (a = 0 ; a <= 20 ; a++)
			{
				LCD_DisplayNumber (a);
				LCD_GoToXY (0,0);
				_delay_ms(250);
				PORTD ^= (1 << PORTD7);
			}
		}
		PORTD |= (0 << PORTD7);
		if (!(PIND & (1 << PIND3)))
		{
			for (a = 20 ; a >= 0 ; a--)
			{
				LCD_DisplayNumber (a);
				LCD_GoToXY (0,0);
				_delay_ms(250);
				PORTD ^= (1 << PORTD7);
				if (a == 0)
					break;
			}
		}
	}
}