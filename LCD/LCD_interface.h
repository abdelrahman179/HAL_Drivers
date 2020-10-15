/****************************************************************/
/*   Author             :    AbdElrahman Ibrahim Zaki		    */
/*	 Date 				:    23rd of May 2020 					*/
/*	 Version 			:    1.0V 							 	*/
/*	 Description 		:    LCD Interface                       */
/****************************************************************/

#ifndef LCD_INTERFACE_H
#define LCD_INTERFACE_H

void LCD_Ini(void); //
void LCD_writeChar(u8 DATA);
void LCD_writeCMD(u8 CMD);
void Cursor_Pos(u8 x_pos , u8 y_pos);
void LCD_writeString (char *str);
u16 LCD_u8writeINT(u16 Copy_u16NB);
u16 Private_u16Power(u8 Copy_u8Op1, u8 Copy_u8Op2);

#define CONTROL_PORT    PORTC
#define RS              PIN7
#define RW              PIN6
#define EN              PIN5
#define DATA_PORT       PORTD




#endif
