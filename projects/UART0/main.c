/* 
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
		UART_tx(arr, 4);
		delay;
		
	}
	
	
	
}

void UART_tx(uint8_t arr[], int length){
	//int i=0;
	//while(length--){
		USART1->DR = 69;
		while( !(USART1->SR & USART_SR_TXE) );
		//i++;
	//}
}
/*
static void printMsg(char *msg, ...){
	
	char buff[80];
	va_list args;
	va_start(args, msg);
	vsprintf(buff, msg, args);
	
	for(int i=0;i<strlen(buff);i++){
		USART1->DR = buff[i];
		while( !(USART1->SR & USART_SR_TXE) );
	}
}
*/
#include <stdint.h>
#define RCC_BASE 0x40021000
#define GPIOC_BASE 0x40011000

#define RCC_APB2ENR	*(volatile uint32_t*) (RCC_BASE + 0x18)	//This means that RCC_APB2ENR is the value 
	//pointed by a int_32bit pointer whos value is RCC_BASE + offset address of RCC_APB2ENR.
#define GPIOC_CRH 	*(volatile uint32_t*)	(GPIOC_BASE + 0x04)
#define GPIOC_ODR		*(volatile uint32_t*)	(GPIOC_BASE + 0x0c)

 
const int a = 7;		// Will be placed in rodata
int b = 3;			// Will be placed in data (LMA)
int c = 0;			// Will be placed in bss
int d;				// Will be placed in bss (but first in COMMON)

int main()
{	RCC_APB2ENR |= (1<<4);
	GPIOC_CRH &= 0xFF0FFFFF;
	GPIOC_CRH |= 0x00200000;
	
	c = a + b;
	while(1){
	if(10 == 10) GPIOC_ODR |= (1<<13);
	else GPIOC_ODR &= ~(1<<13);
	}

	
	return 0;
}