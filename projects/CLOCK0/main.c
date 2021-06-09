#include "inc/CLOCK_DRIVER0.h"
#include "inc/UART_DRIVER0.h"
#include "inc/stm32f10x.h"
#include "inc/GPIO_DRIVER2.h"
#include "inc/cmsis.h"
#include <stdint.h>


#define data 0x01


uint8_t array[10] = {};

int main(){
	Set_Sysclock_Frequency(HSE_PRE_DIV1, RCC_CFGR_PLLMULL2, RCC_CFGR_HPRE_DIV8, RCC_CFGR_PPRE1_DIV1, RCC_CFGR_PPRE2_DIV1);
	
	UART_Setup();
	
	Set_MCO(PLL_MCO_SRC);
	
	USART_Transfer_Info(array, 10);
	
	//USART_Receive_DMA(DMA1_Channel1, DMA_PL_MEDIUM, array, 10);

	USART1->CR1 |= USART_CR1_RXNEIE;// interrupt at reception of data at RX
	NVIC_EnableIRQ(USART1_IRQn);	//usart1 global interrupt enabling
	
	
	
	
	while(1)
		
		
	}
	
	return 1;
}