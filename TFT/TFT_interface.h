/******************************************************************************************/
/* Author : AbdElrahman I.Zaki                                                            */
/* Date   : 21 September 2020                                                             */
/* Version: V01                                                                           */
/* Desc.  : TFT Interfacing with STM32F103C8T6 ARM Cortex M3 - Public functions prototype */
/******************************************************************************************/


#ifndef TFT_INTERFACE_H
#define TFT_INTERFACE_H

/* TFT Commands */
#define SW_RESET 0x01        /* SW Reset */
#define SLP_OUT 0x11         /* Sleep Out */
#define DISP_OFF 0x28        /* Display Off */
#define DISP_ON 0x29         /* Display On */
#define COL_ADD_SET 0x2A     /* Column Add Set */
#define ROW_ADD_SET 0x2B     /* Row Add Set */
#define RAM_WR 0x2C          /* RAM Write */
#define MADCTL 0x36          /* Axis Control */
#define COLOR_MODE 0x3A      /* Color Mode */
/* 1.8" TFT display constants */ 
#define X_SIZE 128           /* X-axis Size */
#define Y_SIZE 160           /* Y-axis Size */
#define XMAX XSIZE -1        /* X max size */ 
#define YMAX YSIZE -1        /* Y max size */
/* Color constants */   
#define BLACK 0x0000
#define BLUE 0x001F
#define RED 0xF800
#define GREEN 0x0400
#define LIME 0x07E0
#define CYAN 0x07FF
#define MAGENTA 0xF81F
#define YELLOW 0xFFE0
#define WHITE 0xFFFF

void HTFT_voidInit(void);
void HTFT_voidFillColor(u16 Copy_u16Color);
void HTFT_voidFillImage(const u16 *Copy_ptrImage);


void HTFT_voidDrawHLine(u8 Xaxis, u8 Yaxis, u8 Copy_u8Length, u16 Copy_u8Color);
void HTFT_voidDrawVLine(u8 Xaxis, u8 Yaxis, u8 Copy_u8Length, u16 Copy_u8Color);

void HTFT_voidDrawRectangle(u8 Copy_u8Height, u8 Copy_u8Width, u8 Xaxis, u8 Yaxis, u16 Copy_u8Color);

void HTFT_voidWriteChar(u8 * Cop_u8Char, u8 Xaxis, u8 Yaxis, u16 Copy_u8Color);



#endif
