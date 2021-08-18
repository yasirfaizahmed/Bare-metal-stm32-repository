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
	USART_TypeDef* USART = '\0';	//A USART_TypeDef pointer pointing to NULL
	if(self->uartx == UARTx1) USART = USART1;	//depending on the instance's selected UARTx our pointer will point to different address(UART1,2,3,4)
	else if(self->uartx == UARTx2) USART = USART2;
	else if(self->uartx == UARTx3) USART = USART3;
	else if(self->uartx == UARTx4) USART = UART4;
	else USART = USART1;	//A default case 
	
	if(self->Auto_BaudRate == true){	//sets Baudrate to standard 9600b/s for any given __SysFrequency
		switch(__SysFrequency){
		case 2:
			USART->BRR = 0x00D3;
			break;
		case 8:
			USART->BRR = 0x0341;
			break;
		case 16:
			USART->BRR = 0x0682;
			break;
		case 32:
			USART->BRR = 0x0D05;
			break;
		case 48:
			USART->BRR = 0x1388;
			break;
		default:	//A default case
			USART->BRR = 0x0341;
			break;
		}
	}
	else USART->BRR = self->BaudRate;	//BaudRate entered manually
	
	
	USART->CR1 |= USART_CR1_TE;	//Enabeling TX
	USART->CR1 |= USART_CR1_RE;	//Enabeling RX
	USART->CR1 |= USART_CR1_UE;	//Finally Enabeling UART hardware
	
	
}