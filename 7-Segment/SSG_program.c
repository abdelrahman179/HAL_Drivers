/****************************************************************************/
/* Author : AbdElrahman I.Zaki                                              */
/* Date   : 10 August 2020                                                  */
/* Version: V02                                                             */
/* Desc.  : 7-Segment program file "interface with STM32"                   */
/****************************************************************************/

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "RCC_interface.h"
#include "DIO_interface.h"

#include "SSG_interface.h"
#include "SSG_private.h"
#include "SSG_config.h" 


u8 SSD_Pins[7]  = {SSG_A, SSG_B, SSG_C, SSG_D, SSG_E, SSG_F, SSG_G};
void SSG_voidInit()
{
	switch(SSG_PORT)
	{
		case GPIOA:	MRCC_voidEnableClock(APB2, 2);	break;
		case GPIOB: MRCC_voidEnableClock(APB2, 3);	break;
		case GPIOC: MRCC_voidEnableClock(APB2, 4);	break;
		default:									break;
	}
	
	for(u8 i = 0 ; i < 7 ; i++)
	{
		MGPIO_voidSetPinDirection(SSG_PORT, SSG_Pins[i], SSG_OUTPUT_MODE);
	}
}

void SSG_voidDisplayNumber(u8 Copy_u8Number)
{
	//Representing the seven segment number in hex decimal
	u8 SSG_NumRep[10] = {ZERO, ONE, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE};
	
	//seperates the number in hex value to each pin status
	u8 A_Val = (SSG_NumRep[Copy_u8Number] & 0x01);
	u8 B_Val = (SSG_NumRep[Copy_u8Number] & 0x02) >> 1;
	u8 C_Val = (SSG_NumRep[Copy_u8Number] & 0x04) >> 2;
	u8 D_Val = (SSG_NumRep[Copy_u8Number] & 0x08) >> 3;
	u8 E_Val = (SSG_NumRep[Copy_u8Number] & 0x10) >> 4;
	u8 F_Val = (SSG_NumRep[Copy_u8Number] & 0x20) >> 5;
	u8 G_Val = (SSG_NumRep[Copy_u8Number] & 0x40) >> 6;
	
	u8 SSG_Values[7] = {A_Val, B_Val, C_Val, D_Val, E_Val, F_Val, G_Val};
	#if SSG_MODE == COM_ANOD
		for(u8 i = 0; i < 7; i++)
		{
			MGPIO_voidSetPinValue(SSG_PORT, SSG_Pins[i], ~(SSG_Values[i]));
		}
	#elif SSG_MODE == COM_CATHOD
		for(u8 i = 0 ; i < 7 ; i++)
		{
			MGPIO_voidSetPinValue(SSG_PORT, SSG_Pins[i], SSG_Values[i]);
		}
}
