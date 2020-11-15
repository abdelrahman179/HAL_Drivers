/****************************************************************************/
/* Author : AbdElrahman I.Zaki                                              */
/* Date   : 10 August 2020                                                  */
/* Version: V02                                                             */
/* Desc.  : 7-Segment user manual "interface with STM32"                    */
/****************************************************************************/


#ifndef SSG_CONFIG_H
#define SSG_CONFIG_H

/* 7-Segment Mode: COM_ANOD
                   COM_CATHOD        */
#define SSG_MODE	COM_ANOD

/*choose LED output Mode:
						OUTPUT_SPEED_10MHZ_PP	
						OUTPUT_SPEED_10MHZ_OD		
                        OUTPUT_SPEED_10MHZ_AFPP	
                        OUTPUT_SPEED_10MHZ_AFOD	
                        
                        OUTPUT_SPEED_2MHZ_PP	
                        OUTPUT_SPEED_2MHZ_OD	
                        OUTPUT_SPEED_2MHZ_AFPP	
                        OUTPUT_SPEED_2MHZ_AFOD	
                        
                        OUTPUT_SPEED_50MHZ_PP	
                        OUTPUT_SPEED_50MHZ_OD	
						OUTPUT_SPEED_50MHZ_AFPP	
                        OUTPUT_SPEED_50MHZ_AFOD	
						*/
#define SSG_OUTPUT_MODE 	OUTPUT_SPEED_10MHZ_PP

/* Options: - GPIOA
            - GPIOB
            - GPIOC   */
#define SSG_PORT 	GPIOA

/* 7-Segment Pins */
#define SSG_A	PIN0
#define SSG_B	PIN1
#define SSG_C	PIN2
#define SSG_D	PIN3
#define SSG_E	PIN4
#define SSG_F	PIN5
#define SSG_G	PIN6

#endif
