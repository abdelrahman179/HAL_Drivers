/****************************************************************************************/
/* Author : AbdElrahman I.Zaki                                                          */
/* Date   : 28 September 2020                                                           */
/* Version: V02                                                                         */
/* Desc.  : ESP8266 Wifi Module interfacing with STM32F103C8T6 ARM Cortex M3            */
/*            user manual                                                               */
/****************************************************************************************/


#ifndef ESP_CONFIG_H
#define ESP_CONFIG_H


/* Timeout: The gap between each command sent to the module and its reply back 
    Noting that it varies depending on the router, server and clock freq */
    
#define ECHO_TIMEOUT		100
#define MODE_TIMEOUT		150
#define ROUTER_TIMEOUT		1100000
#define SERVER_TIMEOUT		300000
#define PREREQUEST_TIMEOUT	200
#define REQUEST_TIMEOUT		900000



#endif
