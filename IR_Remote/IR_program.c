/************************************************************/
/* Author : AbdElrahman I.Zaki                              */
/* Date   : 31 August 2020                                  */
/* Version: V01                                             */
/* Desc.  : IR Communication program file                   */
/************************************************************/


/* to detect either the falling edge received is start bit or any other */
volatile u8   u8StartFlag       = 0   ;
/* array to save the data received between falling edge and another el
 * mafrod a5ry 33 bit "32 + start bit bs 5alethom 50" */
volatile u32  u32FrameData[50]  = {0} ;
/* counter to save a new value of the array */
volatile u8   u8EdgeCounter     = 0   ;
/* habos 3ala arr[17] bta3t el data la2en
 * kol zrayer el remote b address sabet */
volatile u8   u8Data            = 0   ;




void HIR_voidInit(void)
{
	MGPIO_voidSetPinDirection(IR_PORT, IR_PIN, INPUT_FLOATING);
	/* Each falling edge, call GetFrame function */
	MEXTI_voidSetCallBack(HIR_voidGetFrame , EXTI_LINE);
	/* EXTI Initialization Set EXTI configuration A0 LINE0 / FALLING EDGE
	Set Callback of interrupt */
	MEXTI_voidInit(EXTI_LINE , FALLING_EDGE);

	/* Enable EXTI0 */
	MNVIC_voidEnablePeripheral(EXTI);

	MSTK_voidSetCallBack(MSTK_voidResetTimer);
	/* Initialize Systick */
	MSTK_voidInit(); /* enable systick AHB/8 = 1MHz each count = 1mSec */
}


void HIR_voidGetFrame(void)
{
	/* if start bit received for the first time , start systick */
	if (u8StartFlag == 0)
	{
		/* Start Timer: i/p > Time, Extract key function */
		MSTK_voidSetIntervalPeriodic(1000000 , HIR_voidExtractKey);
		/* To skip this condition if received next interrupt */
		u8StartFlag = 1;
	}
	else
	{
		/* To get the elapsed time of start bit */
		/* FrameData[0] after first falling edge will be 13500 uSec and save in the frame array */
		u32FrameData[u8EdgeCounter] = MSTK_u32GetElapsedTime();

		/* Reset timer and restart counting */
		MSTK_voidSetIntervalPeriodic(1000000 , HIR_voidExtractKey);

		/* To save new data in a new array element */
		u8EdgeCounter++;
	}
}


void HIR_voidExtractKey(void)
{
	u8Data = 0;
	/* Check if the frame received is valid or not from the start bit
	 * the right start bit time should be around 13500 */
	if ( (u32FrameData[0] >= 10000) && (u32FrameData[0] <= 14000) )
	{
		/* Loop as each frame data consists of 8 bits */
		for (u8 i = 0 ; i < 8 ; i++)
		{
			/* check the first bit of data, if within 2000 & 2300 = 1 */
			if ((u32FrameData[17 + i] >= 2000) && (u32FrameData[17 + i] <= 2300))
			{
				/* after 8 times of checking the variable Data will be containing the data
					 * and I will be able to check the button data transmitted */
				SET_BIT(u8Data , i);
			}
			else
			{
				CLR_BIT(u8Data , i);
			}
		}
	}
	else
	{
		/* Invalid Frame */
	}
	HIR_u8GetKey();
	/* Clear start flag to be ready for receiving another interrupt */
	u8StartFlag     = 0;
	u32FrameData[0] = 0;
	u8EdgeCounter   = 0;
}

u8 HIR_u8GetKey(void)
{
	u8 Loc_Key = u8Data;
	return Loc_Key;
}

