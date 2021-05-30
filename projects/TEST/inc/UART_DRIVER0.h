#ifndef UART_DRIVER0_INCLUDED_H
#define UART_DRIVER0_INCLUDED_H

#include <stdint.h>




//static void printMsg(char *msg, ...);
void UART_Setup(void);
void UART_Tx(char ptr);
void UART_Send(char str[], uint8_t payload_width);





#endif
