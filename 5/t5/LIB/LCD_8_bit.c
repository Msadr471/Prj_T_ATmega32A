////////////////////////////////////////////////////////////////////////////////////////////////////
// file:	C:\Users\Mohammad\Desktop\AVRCLibrary\AVRCLibrary\LCD_8_bit.c
//
// summary:	LCD 8 bit class
////////////////////////////////////////////////////////////////////////////////////////////////////

/*
 *
 * LCD_8_bit.c
 *
 *
 * |_______AVR LCD library for 8-bit mode_______|
 *
 *
 *
 *
 * Created: 2020-08-19 23:09:46
 *
 * Filename: LCD_8_bit.c
 * Controller: Atmega8/16/32/128
 * Oscillator: 1 MHz
 * Author: XploreLabz
 * website: www.xplorelabz.com
 * Reference:Atmega32 dataSheet
 *
 *
 *
 * Note:
 *
 * Pin connection for LCD display in 8-bit mode is as shown below.By default the LCD is connected to PORTB(databus) and PORTD(controlbus).
 * The code can be modified to connect the LCD to any of the PORTs by changing the "#define".
 * io.h contains the defnition of all ports and SFRs delay.h contains the in built delay routines(us and ms routines).
 *
 */

#include <avr/io.h>
#include "Configuration.h"
#include <util/delay.h>
#include "LCD_8_bit.h"

#define databus_direction		DDRB		 //  LCD databus Direction Configuration
#define controlbus_direction	 DDRA	  //  LCD Control bus Direction Configuration

#define databus					PORTB				 //	LCD databus connected to PORTB
#define control_bus				 PORTA			 //	LCD Control bus connected to PORTD

#define rs			DDRA0					  // Register select pin connected 6th bit(D5) Control bus
#define rw			DDRA1					  // Read Write pin connected to 7th bit(D6) Control bus
#define en			DDRA2					 // Enable pin connected to 8th bit(D7) Control bus

/* 16x2 LCD Specification */
#define LCDMaxLines		2
#define LCDMaxChars		16
#define LineOne			0x80
#define LineTwo			0xc0

#define BlankSpace ' '

/*
 *
 * Description :This function sends a command to LCD in the following steps.
 *
 *		step1: Send the I/P command to LCD.
 *		step2: Select the Control Register by making RS low.
 *		step3: Select Write operation making RW low.
 *		step4: Send a High-to-Low pulse on Enable PIN with some delay_us.
 *
 * I/P Arguments: 8-bit command supported by LCD.
 * Return value : none
 *
 */
void LCD_CmdWrite ( char cmd )
	{
		databus = cmd ;             // Send the command to LCD
		control_bus &= ~ ( 1 << rs ) ;  // Select the Command Register by pulling RS LOW
		control_bus &= ~ ( 1 << rw ) ;  // Select the Write Operation  by pulling RW LOW
		control_bus |= 1 << en ;     // Send a High-to-Low Pusle at Enable Pin
			_delay_us ( 1 ) ;
		control_bus &= ~ ( 1 << en ) ;
		_delay_ms ( 1 );
	}

/*
 *
 * Description  :This function is used to initialize the lcd in 8-bit mode
 * Function name: LCD_Init()
 * I/P Arguments: none.
 * Return value : none
 *
 */
void LCD_Init ( )
	{
		_delay_ms ( 50 ) ;
	   databus_direction = 0xff ;   // Configure both databus and controlbus as output
	   controlbus_direction = 0xff ;
	   LCD_CmdWrite ( 0x38 ) ;			// LCD 2lines, 5*7 matrix
	   LCD_CmdWrite ( 0x0E ) ;			// Display ON cursor ON
	   LCD_CmdWrite ( 0x01 ) ;			// Clear the LCD
	   LCD_CmdWrite ( 0x80 ) ;			// Move the Cursor to First line First Position
	}

/*
 *
 * Description  :This function clears the LCD and moves the cursor to first Position
 * I/P Arguments: none.
 * Return value : none
 *
 */
void LCD_Clear ( )
	{
		LCD_CmdWrite ( 0x01 ) ;	// Clear the LCD and go to First line First Position
		LCD_CmdWrite ( LineOne ) ;
	}

/*
 *
 * Description  :This function moves the Cursor to First line First Position
 * I/P Arguments: none
 * Return value : none
 *
 */
void LCD_GoToLineOne ( )
	{
		LCD_CmdWrite ( LineOne );	// Move the Cursor to First line First Position
	}

/*
 *
 * Description  :This function moves the Cursor to Second line First Position
 * I/P Arguments: none
 * Return value : none
 *
 */
void LCD_GoToLineTwo ( )
	{
		LCD_CmdWrite ( LineTwo ) ;	// Move the Cursor to Second line First Position
	}

/*
 *
 * Description  :This function moves the Cursor to specified position
 * I/P Arguments: char row,char col
 *		row -> line number(line1=0, line2=1),For 2line LCD the I/P argument should be either 0 or 1.
 *		col -> char number.For 16-char LCD the I/P argument should be betwen 0-15.
 * Return value : none
 *
 */
void LCD_GoToXY ( char row , char col )
	{
		char pos ;

		if ( row < LCDMaxLines )
			{
				pos = LineOne | ( row << 6 ) ; // take the line number
				//row0->pos=0x80  row1->pos=0xc0

				if ( col < LCDMaxChars )
				pos = pos + col ;            //take the char number
				//now pos points to the given XY pos

				LCD_CmdWrite ( pos ) ;	       // Move the Cursor to specified Position
			}
	}

/*
 *
 * Description:This function sends a character to be displayed on LCD in the following steps.
 *
 *		step1: Send the character to LCD.
 *		step2: Select the Data Register by making RS high.
 *		step3: Select Write operation making RW low.
 *		step4: Send a High-to-Low pulse on Enable PIN with some delay_us.
 *
 * I/P Arguments: ASCII value of the char to be displayed.
 * Return value : none
 *
 */
void LCD_DataWrite ( char dat )
	{

		databus = dat ;            // Send the data to LCD
		control_bus |= 1 << rs ;	// Select the Data Register by pulling RS HIGH
		control_bus &= ~ ( 1 << rw ) ;	// Select the Write Operation  by pulling RW LOW
		control_bus |= 1 << en ;	// Send a High-to-Low Pusle at Enable Pin
		_delay_us ( 1 ) ;
		control_bus &= ~ ( 1 << en ) ;
		_delay_ms ( 1 ) ;
	}

/*
 *
 * Description  :This function is used to display the ASCII string on the lcd.
 *	The string_ptr points to the first char of the string and traverses till the end(NULL CHAR).
 *	Each time a char is sent to LCD_DataWrite funtion to display.
 * I/P Arguments: String(Address of the string) to be displayed.
 * Return value : None
 *
 */
void LCD_DisplayString ( char *string_ptr )
	{
		while ( *string_ptr )
			LCD_DataWrite ( *string_ptr++ );
	}

/*
 *
 * Description  :This function is used to display a 5-digit integer(0-65535).
 *	ex:
 *		1- if the number is 12345 then 12345 is displayed.
 *		2- if the number is 123 then 00123 is displayed.
 * Function name: LCD_DisplayNumber()
 * I/P Arguments: unsigned int.
 * Return value : none
 *	https://exploreembedded.com/wiki/File:Lcd_displaynumber.png
 *
 */
void LCD_DisplayNumber ( unsigned int num )
	{
		LCD_DataWrite ( ( num / 10000 ) + 0x30 ) ;
			num = num % 10000 ;

		LCD_DataWrite ( ( num / 1000 ) + 0x30 ) ;
			num = num % 1000 ;

		LCD_DataWrite ( ( num / 100 ) + 0x30 ) ;
			num = num % 100 ;

		LCD_DataWrite ( ( num / 10 ) + 0x30 ) ;

		LCD_DataWrite ( ( num % 10 ) + 0x30 ) ;
	}

/*
 *
 * Description  :This function scrolls the given message on the first line.""
 *		16 chars are displayed at atime.
 *		Pointer is incremented to skip a char each time to give the illusion of moving chars.
 *		If the chars are less than 16, then the BlankSpaces are displayed.
 *
 * I/P Arguments: char *msg_ptr (msg_ptr -> pointer to the string to be scrolled)
 * Return value : none
 *
 */
void LCD_ScrollMessage ( char *msg_ptr )
	{
		unsigned char i , j ;
		LCD_CmdWrite ( 0x0c ) ;			 //Disable the Cursor
		for( i = 0 ; msg_ptr [ i ] ; i++ )        //Loop to display the complete string
			{                            //each time 16 chars are displayed and
				//pointer is incremented to point to next char

				LCD_GoToLineOne ( ) ;                   //Move the Cursor to first line

				for ( j = 0 ; j < LCDMaxChars && msg_ptr [ i + j ] ; j++ ) //loop to Display first 16 Chars
					LCD_DataWrite ( msg_ptr [ i + j ] ) ;                 //or till Null char

				for ( j = j ; j < LCDMaxChars ; j++ )               //If the chars are below 16
					LCD_DataWrite ( BlankSpace ) ;              //then display blank spaces

				_delay_ms ( 500 ) ;
			}
		LCD_CmdWrite ( 0x0E ) ;			  //Enable the Cursor
	}

/*
 *
 * Description  :This function display hour,min,sec read from DS1307.
 * I/P Arguments: char hour,char min,char sec(hour,min,sec should be packed BCD format,as read from DS1307)
 * Return value : none
 *
 */
void LCD_DisplayRtcTime (char hour , char min , char sec )
	{
		LCD_DataWrite ( ( ( hour >> 4 ) & 0x0f ) + 0x30 ) ;
		LCD_DataWrite ( ( hour & 0x0f ) + 0x30 ) ;
		LCD_DataWrite ( ':' ) ;

		LCD_DataWrite ( ( ( min >> 4 ) & 0x0f ) + 0x30 ) ;
		LCD_DataWrite ( ( min & 0x0f ) + 0x30 ) ;
		LCD_DataWrite ( ':' ) ;

		LCD_DataWrite ( ( ( sec >> 4 ) & 0x0f ) + 0x30 ) ;
		LCD_DataWrite ( ( sec & 0x0f ) + 0x30 ) ;
	}

/*
 *
 * Description  :This function display day,month,year read from DS1307.
 * I/P Arguments: char day,char month,char year(day,month,year should be packed BCD format,as read from DS1307)
 * Return value : none
 *
 */
void LCD_DisplayRtcDate ( char day , char month , char year )
	{
		LCD_DataWrite ( ( ( day >> 4 ) & 0x0f ) + 0x30 ) ;
		LCD_DataWrite ( ( day & 0x0f ) + 0x30 ) ;
		LCD_DataWrite ( '/' );

		LCD_DataWrite ( ( ( month >> 4 ) & 0x0f ) + 0x30 ) ;
		LCD_DataWrite ( ( month & 0x0f ) + 0x30 ) ;
		LCD_DataWrite ( '/' ) ;

		LCD_DataWrite ( ( ( year >> 4 ) & 0x0f ) + 0x30 ) ;
		LCD_DataWrite ( ( year & 0x0f ) + 0x30 ) ;
	}

////////////////////////////////////////////////////////////////////////////////////////////////////
// End of C:\Users\Mohammad\Desktop\AVRCLibrary\AVRCLibrary\LCD_8_bit Mode.c
////////////////////////////////////////////////////////////////////////////////////////////////////