#include <avr/io.h>
#define F_CPU 8000000UL
#include <util/delay.h>
#include <stdio.h>
#include "LIB/Configuration.h"
#include "LIB/LCD_8_bit.h"
#include "LIB/UART.h"
int main(void)
{
	char num = 0;
	unsigned char data_rx;
	UART_Init();
	LCD_Init();
	while (1)
	{
		data_rx = UART_RxChar();
		if (data_rx == 0xFE)
		{
			LCD_DisplayNumber(num++);
			_delay_ms(250);
			if (data_rx == 0xFF)
				break;
		}
		if (data_rx == 0xFD)
		{
			LCD_DisplayNumber(num--);
			_delay_ms(250);
			if (data_rx == 0xFF)
				break;
		}
		LCD_GoToXY(0,0);
		LCD_Clear();
	}
}