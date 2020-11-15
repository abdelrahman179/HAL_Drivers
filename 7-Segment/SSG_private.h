/****************************************************************************/
/* Author : AbdElrahman I.Zaki                                              */
/* Date   : 10 August 2020                                                  */
/* Version: V02                                                             */
/* Desc.  : 7-Segment private information "interface with STM32"            */
/****************************************************************************/

#ifndef SSG_PRIVATE_H
#define SSG_PRIVATE_H

#define COM_ANOD	0
#define COM_CATHOD	1

//Representing number for seven segments as 0bxgfedcba
#define ZERO	0x3F
#define ONE		0x06
#define TWO		0x5B
#define THREE	0x4F
#define FOUR	0x66
#define FIVE	0x6D
#define SIX		0x7D
#define SEVEN	0x07
#define EIGHT	0x7F
#define NINE	0x6F

#endif
