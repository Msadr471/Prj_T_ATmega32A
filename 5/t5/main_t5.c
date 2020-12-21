#include <avr/io.h>
#include <stdlib.h>
#include <stdio.h>
#include <avr/interrupt.h>
#define F_CPU 1000000UL
#include <util/delay.h>
#include "LIB/Configuration.h"
#include "LIB/LCD_8_bit.h"
int tenth = 0, Sec = 0, Min = 0, Hour = 0;
char st [20], a = 0;
ISR (TIMER1_COMPA_vect)
{
	tenth++;
	if (tenth == 10)
	{
		Sec++; tenth = 0;
		if (Sec == 60)
		{
			Min++; Sec = 0;
			if (Min == 60)
			{
				Hour++; Min = 0;
				if (Hour == 24)
				{
					Hour = 0;
				}
			}
		}
	}
}
ISR(INT1_vect)
{
	Min++;
}
ISR(INT0_vect)
{
	Sec++;
}
int main(void)
{
	TCCR1B = (1<<WGM12) | (1<<CS11);
	OCR1AH = 0x30;
	OCR1AL = 0xD3;
	TIMSK = (1<<OCIE1A);
	GICR|=(1<<INT1) | (1<<INT0) | (0<<INT2);
	MCUCR=(1<<ISC11) | (0<<ISC10) | (1<<ISC01) | (0<<ISC00);
	MCUCSR=(0<<ISC2);
	GIFR=(1<<INTF1) | (1<<INTF0) | (0<<INTF2);
	PORTD |= (1 << PORTD2) | (1 << PORTD3) ;
	sei();
	LCD_Init();
	while (1)
	{
		sprintf (st, "%02d:%02d:%02d " , Hour, Min, Sec);
		LCD_GoToXY (0,0);
		LCD_DisplayString (st);
	}
}