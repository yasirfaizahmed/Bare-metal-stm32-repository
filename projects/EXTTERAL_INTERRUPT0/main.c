#include "inc/CLOCK_DRIVER0.h"
#include "inc/cmsis.h"
#include "inc/GPIO_DRIVER2.h"
#include "inc/stm32f10x.h"
#include "inc/UART_DRIVER0.h"


int main(){

	Set_Sysclock_Frequency(HSE_PRE_DIV1, RCC_CFGR_PLLMULL2, RCC_CFGR_HPRE_DIV8, RCC_CFGR_PPRE1_DIV1, RCC_CFGR_PPRE2_DIV1);

	UART_Setup();

	pin_mode(IOPA, GPIOA, 1, ip, ip_pupd);
	pin_mode(IOPC, GPIOC, 13, op_10MHz, op_gppp);
	digital_writepin(GPIOA, 13, LOW);
	
	RCC->APB2ENR |= RCC_APB2ENR_AFIOEN;	//EXTI falls under Alternate functions of GPIO
	AFIO->EXTICR[0] |= AFIO_EXTICR1_EXTI1_PA;	// PA[1] pin 
	EXTI->IMR |= (1<<1);  
	EXTI->RTSR |= (1<<1);   
	
	NVIC_EnableIRQ(EXTI1_IRQn);
	
	
	
}