#include "../inc/UART_DRIVER1.h"
#include "stm32f10x.h"
#include "../inc/GPIO_DRIVER2.h"

/**
 *  \brief Enables the Clock for UARTx from RCC 
 *  
 *  \param [in] self A UART_Init_Type instance's pointer 
 *  \return nothing
 *  
 *  \details 
 */
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
	else{	//A default case
		RCC->APB2ENR |= RCC_APB2ENR_USART1EN;
		RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
	}
}


/**
 *  \brief Initilizes the GPIO for UARTx
 *  
 *  \param [in] self A UART_Init_Type instance's pointer
 *  \return nothing
 *  
 *  \details 
 */
void UART_Init_GPIO(UART_Init_Type* self){
	if(self->uartx == UARTx1){
		pin_mode(IOPA, GPIOA , 9, op_50MHz, op_afpp);	//pin 9 as Alternate function, o/p, at IOPA and port GPIOA acting as TX
		pin_mode(IOPA, GPIOA, 10, ip, ip_pupd);	//pin 10 as input push pull, i/p, IOPA, port GPIOA acting as RX 
	}
	else if(self->uartx == UARTx2){
		pin_mode(IOPA, GPIOA, 2, op_50MHz, op_afpp);
		pin_mode(IOPA, GPIOA, 3, ip, ip_pupd);
	}
	else if(self->uartx == UARTx3){
		pin_mode(IOPB, GPIOB, 10, op_50MHz, op_afpp);
		pin_mode(IOPB, GPIOB, 11, ip, ip_pupd);
	}
	else{	//A default case
		pin_mode(IOPA, GPIOA , 9, op_50MHz, op_afpp);
		pin_mode(IOPA, GPIOA, 10, ip, ip_pupd);
	}
	
}

/**
 *  \brief UART_Tx
 *  
 *  \param [in] data data
 *  \return nothing
 *  
 *  \details 
 */
void UART_Tx(char data){
	while((USART1->SR & (1<<6)) == 0x00);
	USART1->DR = data;
		
}

void UART_Enable(UART_Init_Type* self){
	USART1->BRR = 0x00D3;
	
	USART1->CR1 |= USART_CR1_TE;
	USART1->CR1 |= USART_CR1_RE;
	USART1->CR1 |= USART_CR1_UE;
}