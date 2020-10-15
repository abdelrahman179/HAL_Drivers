/*************************************************************/
/*  AUTHOR     : AbdElrahman Ibrahim Zaki                    */
/*  DATE       :  					     */
/*  VERSION	   : V0.1				     */
/*  DESCRIPTION: Keypad Program                              */
/*                                                           */
/*************************************************************/
#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "DIO_interface.h"
#include "KEYPAD_interface.h"

#include <util/delay.h>

const u8 switch_Value[4][4] = {
	{1,2,3,'*'},
	{4,5,6,'/'},
	{7,8,9,'+'},
	{'=',0,'.','-'}	
};

u8 keypad_u8GetPressedKey()
{
	// initialized with an initial value not include in the array
	u8 Local_u8PressedKey = 0XFF;
	
	// Send pattern 4 times 
	for (u8 COLUMN = 0 ; COLUMN < 4 ; COLUMN++)
	{
		
		// 1st round the column will be o/p 0 
		DIO_voidSetPinValue(KEYPAD_PORT  ,  COLUMN  ,  LOW);
		
		// Row's check 
		for (u8 ROW = 4 ; ROW < 8 ; ROW++)
		{
			// check if the switch is ON 
			if (DIO_u8GetPinValue(KEYPAD_PORT , ROW) == 0 )
			{
			   // Polling wait till the user stop pressing the switch
			   // < ; > means don't do anything until the user let switch go
			    while ((DIO_u8GetPinValue(KEYPAD_PORT , ROW ) == 0 ));
			   // anti bouncing
			   _delay_ms(5);
			   // get the values from the Array
			   u8 Local_u8PressedKey = switch_Value[ROW - 4][COLUMN];
			}
		}
		
		// end of the round the column will be returned back to o/p 1 
		DIO_voidSetPinValue(KEYPAD_PORT  ,  COLUMN  ,  HIGH);
	}
	return Local_u8PressedKey;
}
