////////////////////////////////////////////////////////////////////////////////////////////////////
// file:	C:\Users\Mohammad\Desktop\AVRCLibrary\AVRCLibrary\LCD_8_bit.h
//
// summary:	Declares the LCD 8 bit class
////////////////////////////////////////////////////////////////////////////////////////////////////

/*
 *
 * LCD_8_bit.h
 *
 *
 * |_______AVR LCD library for 8-bit_______|
 *
 *
 *
 *
 * Created: 2020-08-19 23:09:46
 *
 * Filename: LCD_8_bit.h
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

#ifndef LCD_8_BIT_H_
#define LCD_8_BIT_H_

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
void LCD_CmdWrite ( char cmd ) ;

/*
 *
 * Description  :This function is used to initialize the lcd in 8-bit mode
 * Function name: LCD_Init()
 * I/P Arguments: none.
 * Return value : none
 *
 */
void LCD_Init ( ) ;

/*
 *
 * Description  :This function clears the LCD and moves the cursor to first Position
 * I/P Arguments: none.
 * Return value : none
 *
 */
void LCD_Clear ( ) ;

/*
 *
 * Description  :This function moves the Cursor to First line First Position
 * I/P Arguments: none
 * Return value : none
 *
 */
void LCD_GoToLineOne ( ) ;

/*
 *
 * Description  :This function moves the Cursor to Second line First Position
 * I/P Arguments: none
 * Return value : none
 *
 */
void LCD_GoToLineTwo ( ) ;

/*
 *
 * Description  :This function moves the Cursor to specified position
 * I/P Arguments: char row,char col
 *		row -> line number(line1=0, line2=1),For 2line LCD the I/P argument should be either 0 or 1.
 *		col -> char number.For 16-char LCD the I/P argument should be betwen 0-15.
 * Return value : none
 *
 */
void LCD_GoToXY ( char row , char col ) ;

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
void LCD_DataWrite ( char dat) ;

/*
 *
 * Description  :This function is used to display the ASCII string on the lcd.
 *	The string_ptr points to the first char of the string and traverses till the end(NULL CHAR).
 *	Each time a char is sent to LCD_DataWrite funtion to display.
 * I/P Arguments: String(Address of the string) to be displayed.
 * Return value : None
 *
 */
void LCD_DisplayString ( char *string_ptr ) ;

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
void LCD_DisplayNumber ( unsigned int num ) ;

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
void LCD_ScrollMessage ( char *msg_ptr ) ;

/*
 *
 * Description  :This function display hour,min,sec read from DS1307.
 * I/P Arguments: char hour,char min,char sec(hour,min,sec should be packed BCD format,as read from DS1307)
 * Return value : none
 *
 */
void LCD_DisplayRtcTime (char hour , char min , char sec ) ;

/*
 *
 * Description  :This function display day,month,year read from DS1307.
 * I/P Arguments: char day,char month,char year(day,month,year should be packed BCD format,as read from DS1307)
 * Return value : none
 *
 */
void LCD_DisplayRtcDate ( char day , char month , char year ) ;

#endif /* LCD_8_BIT_H_ */

////////////////////////////////////////////////////////////////////////////////////////////////////
// End of C:\Users\Mohammad\Desktop\AVRCLibrary\AVRCLibrary\LCD_8_bit Mode.h
////////////////////////////////////////////////////////////////////////////////////////////////////