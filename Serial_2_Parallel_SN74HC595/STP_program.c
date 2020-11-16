/************************************************************************************/
/* Author : AbdElrahman I.Zaki                                                      */
/* Date   : 14 September 2020                                                       */
/* Version: V01                                                                     */
/* Desc.  : SN74HC595 Serial to Prallel IC Interface with STM32 program             */
/************************************************************************************/



#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "GPIO_interface.h"
#include "STK_interface.h"
#include "DELAY_interface.h"

#include "STP_interface.h"
#include "STP_private.h"
#include "STP_config.h"

/* HSTP Initialization : GPIO Directions based on user configuration */
void HSTP_voidInit(void)
{
    MGPIO_voidSetPinDirection(HSTP_DATA_PORT      , HSTP_DATA_PIN      , OUTPUT_SPEED_2MHZ_PP);
	MGPIO_voidSetPinDirection(HSTP_BIT_LATCH_PORT , HSTP_BIT_LATCH_PIN , OUTPUT_SPEED_2MHZ_PP);
	MGPIO_voidSetPinDirection(HSTP_BYTE_LATCH_PORT, HSTP_BYTE_LATCH_PIN, OUTPUT_SPEED_2MHZ_PP);
}

/* HSTP One IC */
void HSTP_voidByteOutput(u8 Copy_u8Data)
{
	u8 Local_u8Iterator;

	MGPIO_voidSetPinValue(HSTP_BIT_LATCH_PORT, HSTP_BYTE_LATCH_PIN, LOW);

	for(Local_u8Iterator = 8; Local_u8Iterator > 0; Local_u8Iterator--)
    {
        /* Get the 7,6,5,... bits from the input data and send bit by bit starting from MSB */
		MGPIO_voidSetPinValue(HSTP_DATA_PORT, HSTP_DATA_PIN, (GET_BIT(Copy_u8Data , (Local_u8Iterator - 1))));

        /* - CLK to be send to Shift CLK, must be 100nano or above,
                SysTick minimum unit is micro seconds 
           - Once this clock is sent to shift clk, the data bit will be
                set to shift register */
		MGPIO_voidSetPinValue(HSTP_BIT_LATCH_PORT, HSTP_BIT_LATCH_PIN, HIGH);
		_delay_uS(5);
		MGPIO_voidSetPinValue(HSTP_BIT_LATCH_PORT, HSTP_BIT_LATCH_PIN, LOW);
	}
    /* Send pulse to Store CLK, to transfer the data from the shift
		   register to physical pins right away */
	MGPIO_voidSetPinValue(HSTP_BYTE_LATCH_PORT, HSTP_BYTE_LATCH_PIN, HIGH);
	_delay_uS(5);
	MGPIO_voidSetPinValue(HSTP_BYTE_LATCH_PORT, HSTP_BYTE_LATCH_PIN, LOW );
}

/* HSTP Two ICs */
void HSTP_voiddHalfWordOutput(u16 Copy_u8Data)
{
	u8 Local_u8Iterator;

	MGPIO_voidSetPinValue(HSTP_BYTE_LATCH_PORT, HSTP_BYTE_LATCH_PIN, LOW);

	for(Local_u8Iterator = 16 ; Local_u8Iterator > 0 ; Local_u8Iterator--)
    {
		MGPIO_voidSetPinValue(HSTP_DATA_PORT, HSTP_DATA_PIN , (GET_BIT(Copy_u8Data , (Local_u8Iterator - 1))));

		MGPIO_voidSetPinValue(HSTP_BIT_LATCH_PORT, HSTP_BIT_LATCH_PIN, HIGH);
		_delay_uS(5);
		MGPIO_voidSetPinValue(HSTP_BIT_LATCH_PORT, HSTP_BIT_LATCH_PIN, LOW);

	}
	MGPIO_voidSetPinValue(HSTP_BYTE_LATCH_PORT, HSTP_BYTE_LATCH_PIN, HIGH);
	_delay_uS(5);
	MGPIO_voidSetPinValue(HSTP_BYTE_LATCH_PORT, HSTP_BYTE_LATCH_PIN, LOW);
}
