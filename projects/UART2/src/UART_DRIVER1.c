#include "../inc/UART_DRIVER1.h"
#include "stm32f10x.h"

void UART_Enable_Clock(UART_Init_Type* self){
	if(self->uartx == UARTx1){
		RCC->APB2ENR |= RCC_APB2ENR_USART1EN;	//Enabeling clock for APB2 for UART1
		RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;	//Enabeling clock for APB2 for GPIOA
	}
	else if(self->uartx == UARTx2){
		RCC->APB1ENR |= RCC_APB1ENR_USART2EN;
		RCC->APB2ENR |= RCC_APB2ENR_IOPCEN;
	}
	else if(self->uartx == UARTx3){
		RCC->APB1ENR |= RCC_APB1ENR_USART3EN;
		RCC->APB2ENR |= RCC_APB2ENR_IOPBEN;
	}
	
}