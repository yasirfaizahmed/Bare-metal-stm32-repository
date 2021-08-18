#include "inc/UART_DRIVER1.h"
#include "inc/CLOCK_DRIVER0.h"
#include "inc/stm32f10x.h"
#include <stdbool.h>



int main(){
	Set_Sysclock_Frequency(HSE_PRE_DIV1, PLL_MULL2, AHB_PRE_DIV8, APB_PRE1_DIV1, APB_PRE2_DIV1);
	
	UART_Init_Type uart1;	//our UART instance
	
	uart1.UARTx = USART1;
	uart1.Synchronous = false;
	uart1.Auto_BaudRate = true;
	uart1.BaudRate = BAUD_DEFAULT;
	
	UART_Enable_Clock(&uart1);
	UART_Init_GPIO(&uart1);
	UART_Enable(&uart1);
	
	uint8_t var;
	uint8_t* ptr = &var;
	while(1){
		for(int i=0;i<100000;i++);
		UART_Tx(&uart1, 0x69);
		UART_Rx(&uart1, ptr);
		if(*ptr == 0x69) UART_Tx(&uart1, 0xFF);
	}
	
}
