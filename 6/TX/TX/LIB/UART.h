////////////////////////////////////////////////////////////////////////////////////////////////////
// file:	C:\Users\Mohammad\Desktop\AVRCLibrary\AVRCLibrary\UART.h
//
// summary:	Declares the uart class
////////////////////////////////////////////////////////////////////////////////////////////////////

/*
 *
 * UART.h
 *
 *
 * |_______AVR UART library for Serial Communication for 9600 baud rate at 1Mhz_______|
 *
 *
 *
 *
 * Created: 2020-08-20 08:39:46
 *
 * Filename: uart.h
 * Controller: Atmega8/16/32/128
 * Oscillator: 1 MHz
 * Author: XploreLabz
 * website: www.xplorelabz.com
 * Reference:Atmega32 dataSheet
 *
 */

#ifndef UART_H_
#define UART_H_

/*
 *
 * Description  :This function is used to initialize the UART at 9600 baud rate by below configuration.
 * I/P Arguments: none
 * Return value: none
 *
 */
 void UART_Init ( ) ;

/*
 *
 * Description :This function is used to receive a char from UART module.
 *		It waits till a char is received ie.till RXC is set,
 *		RXC will be set once a CHAR is received.
 *		Finally returns the received char.
 * I/P Arguments: none
 * Return value : char
 *
 */
char UART_RxChar ( ) ;

/*
 *
 * Description  : This function is used to transmit a char through UART module.
 *		It waits till previous char is transmitted ie.till UDRE is set.
 *		UDRE will be set once a CHAR is transmitted ie UDR becomes empty.
 *		Finally the new Char to be transmitted is loaded into UDR.
 * I/P Arguments: char--> data to be transmitted
 * Return value: none
 *
 */
 void UART_TxChar ( char ch ) ;

/*
 *
 * Description :This function is used to transmit the ASCII string through UART.
 *		The string_ptr points to the first char of the string.
 *		And it is incremented each time to traverse till the end(NULL CHAR).
 *		Each time a char is sent to UART_TxChar() fun to transmit it through UART
 * I/P Arguments: String(Address of the string) to be transmitted.
 * Return value: none
 *
 */
void UART_TxString ( char *string_ptr ) ;

/*
 *
 * Description  :This function is used to receive a ASCII string through UART till the carriage_return/New_line.
 *		TThe string_ptr points to the begining of the string and each time UART_RxChar() function is called to receive a char and copy it into the buffer(STRING) and incrment string_ptr.
 *		Once the carriage_return/New_line is encountered the loop is breaked and the String is NULL terminated.
 * I/P Arguments: *string_ptr(Address of the string where the received data needs to be stored)
 * Return value: none
 *
 *		NOTE:
 *			* The received char is ECHOED back,if not required then comment UART_TxChar(ch) in the code.
 *			* BackSlash is not taken care.
 *
 */
void UART_RxString ( char *string_ptr ) ;

/*
 *
 * Description  :This function is used to transmit a 5-digit integer(0-65535).
 *		ex:
 *			1- if the number is 12345 then 12345 is transmitted.
 *			2- if the number is 123 then 00123 is transmitted.
 * I/P Arguments: unsigned int
 * Return value: none
 *
 */
void UART_TxNumber ( unsigned int num ) ;

#endif /* UART_H_ */

////////////////////////////////////////////////////////////////////////////////////////////////////
// End of C:\Users\Mohammad\Desktop\AVRCLibrary\AVRCLibrary\UART.h
////////////////////////////////////////////////////////////////////////////////////////////////////