/************************************************************************************/
/* Author : AbdElrahman I.Zaki                                                      */
/* Date   : 14 September 2020                                                       */
/* Version: V01                                                                     */
/* Desc.  : SN74HC595 Serial to Prallel IC Interface with STM32 user manual         */
/************************************************************************************/

#ifndef STP_CONFIG_H
#define STP_CONFIG_H


/* Serial Data Configuration */
#define HSTP_DATA_PORT          GPIOA
#define HSTP_DATA_PIN           PIN0

/* Shift CLK Configuration */
#define HSTP_BIT_LATCH_PORT     GPIOA
#define HSTP_BIT_LATCH_PIN      PIN1

/* Store CLK Configuration */
#define HSTP_BYTE_LATCH_PORT     GPIOA
#define HSTP_BYTE_LATCH_PIN      PIN2




#endif
