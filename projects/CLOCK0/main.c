#include "inc/CLOCK_DRIVER0.h"
#include "inc/UART_DRIVER0.h"
#include "inc/stm32f10x.h"
#include "inc/GPIO_DRIVER2.h"

#include "inc/cmsis.h"

#define data 0x01

void USART1_Handler(void){
	if((USART1->SR)&(USART_SR_RXNE)){
		UART_Tx(data);	//some response
		USART1->SR &= ~USART_SR_RXNE;	//clearing the flag since we are not reading the DR
	}		
	
	
}

int main(){
	//Select_Sysclock_Src(PLL);
	Set_Sysclock_Frequency(HSE_PRE_DIV1, RCC_CFGR_PLLMULL6, RCC_CFGR_HPRE_DIV1, RCC_CFGR_PPRE1_DIV2, RCC_CFGR_PPRE2_DIV1);
	
	UART_Setup();
	
	
	USART1->CR1 |= USART_CR1_RXNEIE;// interrupt at reception of data at RX
	NVIC_EnableIRQ(USART1_IRQn);	//usart1 global interrupt enabling
		
	
	
	
	while(1){
		
		
		
	}
	
	return 1;
}