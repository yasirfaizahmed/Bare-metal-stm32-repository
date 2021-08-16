#include "../inc/UART_DRIVER0.h"
#include "stm32f10x.h"
#include "cmsis.h"
#include <stdint.h>
#include <stdlib.h>


/***** some data pointers for handler to transfer data back to main*/
uint8_t* _ARRAY_PTR = NULL;     //for data received 
uint8_t _ARRAY_SIZE = 0x00;     //for data received 
uint8_t _INDEX = 0x00;          //for data received

/**
 *  \brief UART1 setup maily for 9600baud, Asynchronous, 8bit, no parity.
 *  
 *  \return nothing
 *  
 *  \details 
 */
void UART_Setup(void){
	//Enabeling HSI, Not really necessary.
	RCC->CR |= RCC_CR_HSION;
	while( !(RCC->CR & RCC_CR_HSIRDY) );
	
	//Enabeling clock for APB2 for UART1
	RCC->APB2ENR |= RCC_APB2ENR_USART1EN;
	//Enabeling clock for APB2 for GPIOA
	RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
	
	//GPIO config PA10, PA9
	GPIOA->CRH |= GPIO_CRH_CNF9_1 | GPIO_CRH_MODE9_0 | GPIO_CRH_MODE9_1;
	GPIOA->CRH &= ~(GPIO_CRH_CNF9_0);	//clearing the default bit
	
	//USART setup
	/*
	for baud rate of 9600b/s 
	sysclk   BRR 
	-------------
	@2MHz  0x00D3
	@8MHz  0x0341
	@16MHz 0x0682
	@32MHz 0x0D05
	@48MHz 0x1388
	*/
	extern int __SysFrequency;
	
	
	
	switch(__SysFrequency){
		case 2:
			USART1->BRR = 0x00D3;
			break;
		case 8:
			USART1->BRR = 0x0341;
			break;
		case 16:
			USART1->BRR = 0x0682;
			break;
		case 32:
			USART1->BRR = 0x0D05;
			break;
		case 48:
			USART1->BRR = 0x1388;
			break;
		default:
			USART1->BRR = 0x0341;
			break;
	}
	
	USART1->CR1 |= USART_CR1_TE;
	USART1->CR1 |= USART_CR1_RE;
	USART1->CR1 |= USART_CR1_UE;
	
}	
	

/* static void printMsg(char *msg, ...){
	
	char buff[80];
	va_list args;
	va_start(args, msg);
	vsprintf(buff, msg, args);
	
	for(int i=0;i<strlen(buff);i++){
		USART1->DR = buff[i];
		while( !(USART1->SR & USART_SR_TXE) );
	}
} */

/**
 *  \brief UART Tx
 *  
 *  \param [in] data data to be tranmitted
 *  \return nothing
 *  
 *  \details 
 */
void UART_Tx(char data){
	while((USART1->SR & (1<<6)) == 0x00);
	USART1->DR = data;
		
}

/**
 *  \brief tranmitts the uint8_t or uint8_t array 
 *  
 *  \param [in] arr_width size of the array
 *  \return nothing
 *  
 *  \details  max width is 0xFF (256Bytes)
 */
void UART_Send(uint8_t arr[], uint8_t arr_size){
	uint8_t i = 0;
	while(i<arr_size)
	{
		UART_Tx(arr[i]);
		i++;
	}
}

/**
 *  \brief transfers the array info
 *  
 *  \param [in] arr_size array size
 *  \return nothing
 *  
 *  \details More details				
 */
void USART_Transfer_Info(uint8_t arr_ptr[], uint8_t arr_size){
	_ARRAY_PTR = arr_ptr;
	_ARRAY_SIZE = arr_size;
}

/**
 *  \brief to erase the aray info 
 *  
 *  \return nothing
 *  
 *  \details More details
 */
void USART_Erase_Info(void){   //erases the array info, call it when no more array data is to be received
	_INDEX = 0x00;
	_ARRAY_PTR = NULL;
	_ARRAY_SIZE = 0x00;
}

/**
 *  \brief USAT1 gloabal interrupt handler
 *
 *  \return nothing
 *  
 *  \details 
 */ 
void USART1_Handler(void){
	if( ((USART1->SR)&(USART_SR_RXNE)) && _ARRAY_SIZE!=0 ){  //if RX buffer is not empty
		_ARRAY_PTR[_INDEX] = USART1->DR;  //this automatically clears the RXNE bit
		USART1->SR &= ~USART_SR_RXNE;	//clearing it anyway
		_INDEX++;
		if(_INDEX > _ARRAY_SIZE){
			_INDEX = 0x00;	//if overflow? then clear the array and re-write
			for(int i=0;i<_ARRAY_SIZE;i++) _ARRAY_PTR[i] = 0x00;
		}
	}
	UART_Send(_ARRAY_PTR, _ARRAY_SIZE);  //to verify
	
	
}

void USART_Receive_DMA(DMA_Channel_TypeDef* DMA_channel, DMA_PL DMA_priority, uint8_t arr[], int arr_size){   //uses DMA1
	RCC->AHBENR |= RCC_AHBENR_DMA1EN;   //turns on DMA1 on AHB
	USART1->CR3 |= USART_CR3_DMAR;   //DMA mode enabled for reception
	
	DMA_channel->CCR |= DMA_priority;   //setting the DMA priiority
	DMA_channel->CCR |= DMA_CCR_MINC;   //memory increment mode
	DMA_channel->CCR |= DMA_CCR_CIRC;   //circular mode 
	DMA_channel->CCR |= DMA_CCR_TCIE;   //Transfer complete interrupt enable

	
	DMA_channel->CNDTR = arr_size;   //array size
	DMA_channel->CPAR = (uint32_t)&(USART1->DR);
	DMA_channel->CMAR = (uint32_t)arr;
	
	DMA_channel->CCR |= DMA_CCR_EN;   //enable the channel
	
	
}


