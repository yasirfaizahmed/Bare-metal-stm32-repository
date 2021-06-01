#ifndef UART_DRIVER0_INCLUDED_H
#define UART_DRIVER0_INCLUDED_H

#include <stdint.h>




//static void printMsg(char *msg, ...);
void UART_Setup(void);
void UART_Tx(char data);
void UART_Send(uint8_t arr[], uint8_t arr_size);
void USART_Transfer_Info(uint8_t arr_ptr[], uint8_t arr_size);
void USART_Erase_Info();



#endif
