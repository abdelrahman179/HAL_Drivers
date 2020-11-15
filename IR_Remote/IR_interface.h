/************************************************************/
/* Author : AbdElrahman I.Zaki                              */
/* Date   : 31 August 2020                                  */
/* Version: V01                                             */
/* Desc.  : IR Communication public functions prototypes    */
/************************************************************/

#ifndef _IR_INTERFACE_H_
#define _IR_INTERFACE_H_


#define STOP		69
#define MODE		70
#define MUTE		71
#define PL_RES		68
#define NEXT		64
#define BACK		67
#define EQ			128
#define VOL_DOWN	21
#define VOL_UP		9
#define ZERO		72
#define RPT			25
#define U_SD		13
#define ONE			12
#define TWO			24
#define THREE		94
#define FOUR		132
#define FIVE		28
#define SIX			90
#define SEVEN		66
#define EIGHT		82
#define NINE		74



void HIR_voidInit(void);
void HIR_voidGetFrame(void);
void HIR_voidExtractKey(void);
u8   HIR_u8GetKey(void);


#endif /* IR_INTERFACE_H_ */

