/****************************************************************************************/
/* Author : AbdElrahman I.Zaki                                                          */
/* Date   : 28 September 2020                                                           */
/* Version: V02                                                                         */
/* Desc.  : ESP8266 Wifi Module interfacing with STM32F103C8T6 ARM Cortex M3            */
/*             public functions prototypes                                              */
/****************************************************************************************/

#ifndef ESP_INTERFACE_H
#define ESP_INTERFACE_H



void HESP_voidInit(void);
/* Connect to local wifi
    i/p: - Wifi SSID 
         - Wifi Pass  */
void HESP_voidConnectToRouter(char* Copy_u8StrSSID, char* Copy_u8StrPassword);

/* Connect to Web-Server TCP Protocol 
    i/p: - Copy_u8StrMode > ex: Station
         - Copy_u8StrIP   > ex: 162.253.155.226
         - Copy_u8StrPort > ex: 80 */
void HESP_voidConnectToServer(char* Copy_u8StrMode, char* Copy_u8StrIP, char* Copy_u8StrPort);

/* Function that executes the http request to the server
    i/p: Copy_u8StrRequest > GET http://ismart.freevar.com/status.txt 
    o/p: value 0 or 1 */
u8 HESP_u8ExecuteRequest(char* Copy_u8StrRequest);







#endif
