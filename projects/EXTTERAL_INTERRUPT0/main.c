#include "inc/CLOCK_DRIVER0.h"
#include "inc/cmsis.h"
#include "inc/GPIO_DRIVER2.h"
#include "inc/stm32f10x.h"
#include "inc/UART_DRIVER0.h"


int main(){

	Set_Sysclock_Frequency(HSE_PRE_DIV1, RCC_CFGR_PLLMULL2, RCC_CFGR_HPRE_DIV8, RCC_CFGR_PPRE1_DIV1, RCC_CFGR_PPRE2_DIV1);

	UART_Setup();

	pin_mode(IOPA, GPIOA, 4, ip, ip_pupd);
	pin_mode(IOPC, GPIOC, 13, op_10MHz, op_gppp);
	digital_writepin(GPIOA, 13, LOW);
	
	EXTI_Enable(GPIOA, 4);
	//EXTI->IMR |= (1<<4);  
	//EXTI->RTSR |= (1<<4);
	EXTI_Set_Mode(DOUBLE_EDGE, 4);
	
	NVIC_EnableIRQ(EXTI4_IRQn);
	
	
	
	
	
}

void EXTI4_Handler(void){
    EXTI_Clear_PendingReq(4); // clear pending interrupt
	UART_Tx(0x69);
    
}