/****************************************************************/
/*   Author             :    AbdElrahman Ibrahim Zaki		    */
/*	 Date 				:    23rd of May 2020 					*/
/*	 Version 			:    1.0V 							 	*/
/*	 Description 		:    LCD Program                       */
/****************************************************************/

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "DIO_interface.h"
#include "LCD_interface.h"

#include <util/delay.h>  // built in library 

void LCD_Ini(void)   //initialize the LCD
{

	    /* Delay for VDD = 4.5 volt	*/
		_delay_ms(35);

		/* Function set 2lines 5*7 font */
		LCD_writeCMD(0b00111000);
		_delay_ms(1);

		/* Display On */
		LCD_writeCMD(0b00001100);
		_delay_ms(1);

		/* Clear Display */
		LCD_writeCMD(0b00000001);
		_delay_ms(2);

		/* Cursor increase */
		LCD_writeCMD(0b00000110);

}

// Write a String
void LCD_writeString(char *str)
{
	int i;
	for(i=0;str[i]!=0;i++)		// Send characters of string till the NULL
	{
		LCD_writeChar(str[i]);
	}
}

void LCD_writeChar(u8 DATA)
{
	// To send Data to the LCD: Set RS = 1 / RW = 0 / EN Latch
	// Control_Port = PORTA & RS = PIN 7 & Value = HIGH | LOW
	DIO_voidSetPinValue(CONTROL_PORT  ,  RS  , HIGH);
	// Control_Port = PORTA & RW = PIN 6 & Value = HIGH | LOW
	DIO_voidSetPinValue(CONTROL_PORT  ,  RW  , LOW);
	
	// Transfer the Data from AVR MC to LCD MC
	// Data_Port = PORTD & DATA = Hexadecimal Value that enables the Pins
	DIO_voidSetPortValue(DATA_PORT  ,  DATA);
	
	// EN Latch to send the data/commands to LCD
	// Control_Port = PORTA & EN = PIN 5 & Value = HIGH
	DIO_voidSetPinValue(CONTROL_PORT  ,  EN  , HIGH);
	_delay_ms(2);
	// Control_Port = PORTA & EN = PIN 5 & Value = LOW
	DIO_voidSetPinValue(CONTROL_PORT  ,  EN  , LOW);
	_delay_ms(2);
}

void Cursor_Pos(u8 x_pos , u8 y_pos)
{
	// x_position 0-1  & y_position 0-15 Cursor position in rows and columns
   u8 The_Address = 0;
    if (x_pos == 0)
	  The_Address = 0X80;  // Address of 1st line 0X80 , 0X81 ....
    else if (x_pos == 1)
	  The_Address = 0XC0;  // Address of 2nd line 0XC0 , 0XC1 ....

	if (y_pos < 16)
	  The_Address += y_pos; // The_Address = The_Address + y_pos

	  LCD_writeCMD(The_Address); // Send the Address to the command function
}


// to write a command RS = 0 / RW = 0 / EN Latch
void LCD_writeCMD(u8 CMD)
{
	// To send Command to the LCD: Set RS = 0 / RW = 0 / EN Latch
	// Control_Port = PORTA & RS = PIN 7 & Value = HIGH | LOW
	DIO_voidSetPinValue(CONTROL_PORT  ,  RS  , LOW);
	// Control_Port = PORTA & RW = PIN 6 & Value = HIGH | LOW
	DIO_voidSetPinValue(CONTROL_PORT  ,  RW  , LOW);
	
	// transferred the command from AVR MC to LCD MC 
	// Data_Port = PORTD & Command = Hexadecimal Value that enables the Pins
	DIO_voidSetPortValue(DATA_PORT  ,  CMD);
	
	// EN Latch to send the data/commands to LCD
	// Control_Port = PORTA & EN = PIN 5 & Value = HIGH
	DIO_voidSetPinValue(CONTROL_PORT  ,  EN  , HIGH);
	_delay_ms(2);
	// Control_Port = PORTA & EN = PIN 5 & Value = LOW
	DIO_voidSetPinValue(CONTROL_PORT  ,  EN  , LOW);
	_delay_ms(2);
}

/*
Description: Write any number starting from 0 to 65535 on the LCD
Inputs:  Copy_u16NB: a U16 variable to hold the required number
Outputs: Error state -> 0 No Error
					 -> 1 Error
 */
u16 LCD_u8writeINT(u16 Copy_u16NB)
{
	u16 Local_u8Error=0;

	if(Copy_u16NB == 0)
	{

		// Local_u8Error =
		LCD_writeChar(48);
	}
	else
	{
		u8 Local_u8Digits = 0 , Local_u8Counter;
		u16 Local_u16CopyOfNB = Copy_u16NB;
		/*		Get the number of digits of the Number*/
		while(Local_u16CopyOfNB != 0)
		{
			Local_u8Digits++; //Increment no of digits by one
			Local_u16CopyOfNB /= 10; //get rid of the most right digit
		}
		
		Local_u16CopyOfNB = Copy_u16NB;
		
		/* Loop on the number and print every single digit
		 * alone each iteration */
		for(Local_u8Counter=0;Local_u8Counter<Local_u8Digits;Local_u8Counter++)
		{
			/* Get the most left digit */
			Local_u16CopyOfNB /= Private_u16Power(10 , Local_u8Digits-Local_u8Counter-1);

			/* Print the most left digit */
			//Local_u8Error =
			LCD_writeChar(48 + Local_u16CopyOfNB);

			/* Load the original number */
			Local_u16CopyOfNB = Copy_u16NB;

			/* Get rid of the left most digit */
			Local_u16CopyOfNB %= Private_u16Power(10,Local_u8Digits - Local_u8Counter-1);
		}
	}
	return Local_u8Error;
}

u16 Private_u16Power(u8 Copy_u8Op1, u8 Copy_u8Op2)
{
	u8 Local_u8Counter;
	u16 Local_u16Result = 1;
	for(Local_u8Counter = 0 ; Local_u8Counter<Copy_u8Op2 ; Local_u8Counter++)

	{
		Local_u16Result *= Copy_u8Op1;
	}
	return Local_u16Result;
}


