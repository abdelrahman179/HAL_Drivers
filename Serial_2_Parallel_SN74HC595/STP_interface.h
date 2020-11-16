/**********************************************************************************************/
/* Author : AbdElrahman I.Zaki                                                                */
/* Date   : 14 September 2020                                                                 */
/* Version: V01                                                                               */
/* Desc.  : SN74HC595 Serial to Prallel IC Interface with STM32 public functions prototypes   */
/**********************************************************************************************/

#ifndef STP_INTERFACE_H
#define STP_INTERFACE_H

/* Synchronous function that won't show a return untill it 
        finish it's purpose which is sending data to IC*/

void HSTP_voidInit(void);
void HSTP_voidByteOutput(u8 Copy_u8Data);
void HSTP_voiddHalfWordOutput(u16 Copy_u8Data);



#endif
