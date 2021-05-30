#include "inc\stm32f10x.h"
#include <stdint.h>


#define data      (uint8_t)0x69
#define delay     for(int i=0;i<500000;i++)
	
void UART_tx(uint8_t arr[], int length);

//static void printMsg(char *msg, ...);
uint8_t arr[] = {6,9,6,9};

int main(){
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
	USART1->BRR = 0x1d4c;	//9600
	USART1->CR1 |= USART_CR1_TE;
	USART1->CR1 |= USART_CR1_UE;
	
	
	while(1){
		//printMsg("hello %d", 69);
		//UART_tx(arr, 4);
		USART1->DR = 0x69;
		while( !(USART1->SR & USART_SR_TXE) );
		delay;
		
	}
	
	
	
}

void UART_tx(uint8_t arr[], int length){
	//int i=0;
	//while(length--){
		USART1->DR = 0x69;
		while( !(USART1->SR & USART_SR_TXE) );
		//i++;
	//}
}