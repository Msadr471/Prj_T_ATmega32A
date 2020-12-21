#include <avr/io.h>
#define F_CPU 1000000UL
#include <util/delay.h>
#include <stdio.h>
#include "LIB/Configuration.h"
#include "LIB/UART.h"
int main(void)
{
	unsigned char data_tx;
	DDRB = 0x00;
	PORTB = 0xFF;
	UART_Init();
    while (1)
    {
		data_tx = PINB;
		UART_TxChar (data_tx);
		_delay_ms(250);
    }
}