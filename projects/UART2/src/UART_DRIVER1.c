#include "../inc/UART_DRIVER1.h"
#include "stm32f10x.h"
#include "../inc/GPIO_DRIVER2.h"
#include <stdint.h>

/**
 *  \brief Enables the Clock for UARTx from RCC 
 *  
 *  \param [in] self A UART_Init_Type instance's pointer 
 *  \return nothing
 *  
 *  \details 
 */
void UART_Enable_Clock(UART_Init_Type* self){
	if(self->UARTx == USART1){
		RCC->APB2ENR |= RCC_APB2ENR_USART1EN;	//Enabeling clock for APB2 for UART1
		RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;	//Enabeling clock for APB2 for GPIOA
	}
	else if(self->UARTx == USART2){
		RCC->APB1ENR |= RCC_APB1ENR_USART2EN;
		RCC->APB2ENR |= RCC_APB2ENR_IOPCEN;
	}
	else if(self->UARTx == USART3){
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
	if(self->UARTx == USART1){
		pin_mode(IOPA, GPIOA , 9, op_50MHz, op_afpp);	//pin 9 as Alternate function, o/p, at IOPA and port GPIOA acting as TX
		pin_mode(IOPA, GPIOA, 10, ip, ip_pupd);	//pin 10 as input push pull, i/p, IOPA, port GPIOA acting as RX 
	}
	else if(self->UARTx == USART2){
		pin_mode(IOPA, GPIOA, 2, op_50MHz, op_afpp);
		pin_mode(IOPA, GPIOA, 3, ip, ip_pupd);
	}
	else if(self->UARTx == USART3){
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
void UART_Tx(UART_Init_Type* self, uint8_t data){
	while((self->UARTx->SR & (USART_SR_TC)) == 0x00);	//checking TransferComplete bit
	self->UARTx->DR = data;
		
}

/**
 *  \brief Transmitts an array of uint8_t type of length arr_size
 *  
 *  \param [in] arr_size length
 *  \return nothing
 *  
 *  \details 
 */
void UART_Send(UART_Init_Type* self, uint8_t arr[], uint8_t arr_size){
	uint8_t i = 0;
	while(i<arr_size)
	{
		UART_Tx(self, arr[i]);
		i++;
	}
} 

/**
 *  \brief UART_Rx
 *  
 *  \param [in] ptr variable pointer 
 *  \return nothing
 *  
 *  \details 
 */
void UART_Rx(UART_Init_Type* self, uint8_t* ptr){
	if((self->UARTx->SR) & (USART_SR_RXNE)){	//RX buffer not empty
		*ptr = self->UARTx->DR;	//reading the Data regester
		//self->UARTx->SR &= ~USART_SR_RXNE;	//clearing it anyway
	}
}

/**
 *  \brief Enables the UART
 *  
 *  \param [in] self A UART_Init_Type pointer
 *  \return nothing
 *  
 *  \details 
 */
void UART_Enable(UART_Init_Type* self){
	if(self->Auto_BaudRate == true){	//sets Baudrate to standard 9600b/s for any given __SysFrequency
		switch(__SysFrequency){
		case 2:
			self->UARTx->BRR = 0x00D3;
			break;
		case 8:
			self->UARTx->BRR = 0x0341;
			break;
		case 16:
			self->UARTx->BRR = 0x0682;
			break;
		case 32:
			self->UARTx->BRR = 0x0D05;
			break;
		case 48:
			self->UARTx->BRR = 0x1388;
			break;
		default:	//A default case
			self->UARTx->BRR = 0x0341;
			break;
		}
	}
	else self->UARTx->BRR = self->BaudRate;	//BaudRate entered manually
	
	if(self->Synchronous == true){
		if(self->UARTx == USART1 || self->UARTx == USART2 || self->UARTx == USART3) self->UARTx->CR2 |= USART_CR2_CLKEN;	//Enable clock
	}
	
	
	self->UARTx->CR1 |= USART_CR1_TE;	//Enabeling TX
	self->UARTx->CR1 |= USART_CR1_RE;	//Enabeling RX
	self->UARTx->CR1 |= USART_CR1_UE;	//Finally Enabeling UART hardware
	
	
}