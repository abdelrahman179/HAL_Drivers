/******************************************************************************/
/* Author : AbdElrahman I.Zaki                                                */
/* Date   : 21 September 2020                                                 */
/* Version: V01                                                               */
/* Desc.  : TFT Interfacing with STM32F103C8T6 ARM Cortex M3 - Program file   */
/******************************************************************************/


#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "GPIO_interface.h"
#include "SPI1_interface.h"
#include "STK_interface.h"

#include "TFT_interface.h"
#include "TFT_private.h"
#include "TFT_config.h"

#include "DELAY_interface.h"

/* SPI Configurations required based on TFT Datasheet: 
    - CLK Polarity = 1, idle HIGH
    - CLK Phase    = 1, Write then Read 
    - MSB is sent first  */


/* Init Sequence: 
    - Reset Pulse
    - Sleep Out Command 0x11
    - Delay 150mSec 
    - Set Color Mode ID  0x3A, Parameter 0x05
    - Display On Command 0x29 */
void HTFT_voidInit(void)
{
    /* Reset Puls To initialize all registers */
	MGPIO_voidSetPinValue(TFT_RESET_PORT, TFT_RESET_PIN, LOW);
	_delay_uS(1000);
	MGPIO_voidSetPinValue(TFT_RESET_PORT, TFT_RESET_PIN, HIGH);
	_delay_uS(150000);

	voidWriteCommand(SLP_OUT);   /* Take display out of sleep mode */
	_delay_uS(150000);          /* wait 150mS for TFT driver circuits */

	voidWriteCommand(COLOR_MODE);   /* Select Color Mode: */
	voidWriteData(0x05);            /* Mode 5 = 16bit pixels (RGB565) */

	voidWriteCommand(DISP_ON);   /* Turn on Display */
	_delay_uS(1000);

	/* Remap TFT addresses (x = 0, y = 0 Start From The Left Top Of The TFT) */
	voidWriteCommand(MADCTL);
	voidWriteData(0xC0);
}

void HTFT_voidFillImage(const u16 * Copy_ptrImage)
{
	u8 Local_u8CountX ;
	u8 Local_u8CountY ;
	u16 Local_u8Data  ;

	for(Local_u8CountY = 0 ; Local_u8CountY  < 160 ; Local_u8CountY ++)
	{
		voidWriteCommand(COL_ADD_SET); /* Set Column Range (x0 , x1) */
		voidWriteData(0);
		voidWriteData(0);
		voidWriteCommand(ROW_ADD_SET); /* Set Row Range (y0 , y1) */
		voidWriteData(0);
		voidWriteData(Local_u8CountY);

		voidWriteCommand(RAM_WR) ; /* Write on RAM */

		for (Local_u8CountX = 0 ; Local_u8CountX < 128 ; Local_u8CountX++)
		{
			/* Get Pixel To Send */
			Local_u8Data = *Copy_ptrImage;
			voidWriteData(Local_u8Data >> 8);   /* Write high byte */
			voidWriteData(Local_u8Data & 0xFF); /* write low byte */

			/* Mode to next Pixel */
			Copy_ptrImage ++;
		}
	}
}

void HTFT_voidFillColor(u16 Copy_u16Color) 
{
	u8 Local_u8CountX ;
	u8 Local_u8CountY ;
	for(Local_u8CountY = 0 ; Local_u8CountY < 160 ; Local_u8CountY++)
	{
		voidWriteCommand(COL_ADD_SET) ; /* Set Column Range (x0 , x1) */
		voidWriteData(0);
		voidWriteData(0);
		voidWriteCommand(ROW_ADD_SET) ; /* Set Row Range (y0 , y1) */
		voidWriteData(0);
		voidWriteData(Local_u8CountY);

		voidWriteCommand(RAM_WR); /* Write on RAM */

		for (Local_u8CountX = 0 ; Local_u8CountX < 128 ; Local_u8CountX++)
		{
			voidWriteData(Copy_u16Color >> 8);   /* Write high byte */
			voidWriteData(Copy_u16Color & 0xFF); /* write low byte */
		}
	}
}


/* private function, will be used internally 
    Set A0 > LOW, Command,  */
static void voidWriteCommand(u8 Copy_u8Command)
{
    /* Local variable to receive the garbage data from slave 
        where the MISO is not set. So, data received is garbage "useless" */
    //u8 Local_u8Temp;
    /* Set A0 Pin to low : Command Configuration */
    MGPIO_voidSetPinValue(TFT_A0_PORT, TFT_A0_PIN, LOW);

    /* Send command over SPI 
    Cast to void: not to use the return value should be returned by the func */
    (void)MSPI1_voidSendDataU8(Copy_u8Command);
}

/* lma age ab3at 16 bits baktebha 3ala marten  */
static void voidWriteData(u8 Copy_u8Data)
{
    /* Set A0 Pin to high : Data Configuration  */
    MGPIO_voidSetPinValue(TFT_A0_PORT, TFT_A0_PIN, HIGH);

    /* Send data over SPI 
    Cast to void: not to use the return value should be returned by the func */
    (void)MSPI1_voidSendDataU8(Copy_u8Data);
}


void HTFT_voidDrawHLine(u8 Xaxis, u8 Yaxis, u8 Copy_u8Length, u16 Copy_u8Color) 
{
	for ( ; Copy_u8Length > 0 ; Copy_u8Length--)
    {
		voidWriteCommand(COL_ADD_SET);      /* Set Column Range (x0 , x1) */

		voidWriteData(Xaxis);
		voidWriteData(Xaxis);

		voidWriteCommand(ROW_ADD_SET);      /* Set Row Range (y0 , y1) */

		voidWriteData(Yaxis);
		voidWriteData(Yaxis);

		voidWriteCommand(RAM_WR);           /* Write on RAM */

		voidWriteData(Copy_u8Color >> 8);   /* Write high byte */
		voidWriteData(Copy_u8Color & 0xFF); /* write low byte */

		Xaxis++;
	}

}

void HTFT_voidDrawVLine(u8 Xaxis, u8 Yaxis, u8 Copy_u8Length, u16 Copy_u8Color) 
{
	for ( ; Copy_u8Length > 0 ; Copy_u8Length--)
    {
        voidWriteCommand(COL_ADD_SET);      /* Set Column Range (x0 , x1) */

		voidWriteData(Xaxis);
		voidWriteData(Xaxis);

		voidWriteCommand(ROW_ADD_SET);  /* Set Row Range (y0 , y1) */

		voidWriteData(Yaxis);
		voidWriteData(Yaxis);

		voidWriteCommand(RAM_WR);          /* Write on RAM */   

		voidWriteData(Copy_u8Color >> 8);   /* Write high byte */
		voidWriteData(Copy_u8Color & 0xFF); /* write low byte */ 

		Yaxis++;
	}
}

void HTFT_voidDrawRectangle(u8 Copy_u8Height, u8 Copy_u8Width, u8 Xaxis, u8 Yaxis, u16 Copy_u8Color) 
{
	HTFT_voidDrawHLine(Xaxis, Yaxis, Copy_u8Width, Copy_u8Color                 );
	HTFT_voidDrawVLine(Xaxis, Yaxis, Copy_u8Height, Copy_u8Color                );
	HTFT_voidDrawHLine(Xaxis, Copy_u8Height + Yaxis, Copy_u8Width, Copy_u8Color );
	HTFT_voidDrawVLine(Copy_u8Width + Xaxis, Yaxis, Copy_u8Height, Copy_u8Color );
}

void HTFT_voidWriteChar(u8 * Cop_u8Char, u8 Xaxis, u8 Yaxis, u16 Copy_u8Color)
{
	u8  Local_u8Mask = 0x80;
	u8  Local_u8DataMasked;
	u16 Local_u8Pixel;

	for(u8 Local_u8Iterator1 = 0; Local_u8Iterator1 < 5; Local_u8Iterator1++)
    {
		for(u8 Local_u8Iterator2 = 0; Local_u8Iterator2 < 7; Local_u8Iterator2++)
        {
			/* Set The Position Of 5x7 Character */
			voidWriteCommand(COL_ADD_SET); /* Set Column Range (x0 , x1) */

			voidWriteData(Xaxis + Local_u8Iterator1);
			voidWriteData(Xaxis + Local_u8Iterator1);

			voidWriteCommand(ROW_ADD_SET);  /* Set Row Range (y0 , y1) */

			voidWriteData(Yaxis + Local_u8Iterator2);
			voidWriteData(Yaxis + Local_u8Iterator2);

			voidWriteCommand(RAM_WR);  /* Write on RAM */   

			Local_u8DataMasked = Cop_u8Char[ Local_u8Iterator1 ] & Local_u8Mask ;

			if(Local_u8DataMasked == 0) 
            { 
                Local_u8Pixel = 0x0000; 
            }
			else                       
            { 
                Local_u8Pixel = Copy_u8Color; 
            }

			voidWriteData(Local_u8Pixel >> 8);   /* Write high byte */
			voidWriteData(Local_u8Pixel & 0xFF); /* write low byte */ 

			Local_u8Mask >>= 1;
		}
		Local_u8Mask = 0x80;
	}
}
