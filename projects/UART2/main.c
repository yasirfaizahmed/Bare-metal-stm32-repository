#include "inc/UART_DRIVER1.h"
#include "inc/stm32f10x.h"
#include <stdbool.h>



int main(){
	UART_Init_Type uart1;	//our UART instance
	
	uart1.uartx = UARTx1;
	uart1.Synchronous = false;
	uart1.Auto_BaudRate = false;
	uart1.BaudRate = DEFAULT;
	
	UART_Enable_Clock(&uart1);
	
}
