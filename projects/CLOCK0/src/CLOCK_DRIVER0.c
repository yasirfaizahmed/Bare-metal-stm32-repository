#include "../inc/CLOCK_DRIVER0.h"
#include "../inc/stm32f10x.h"
#include <stdint.h>



uint8_t Select_Sysclock_Src(SYSCLK_SRC sysclock_src){
	if(SYSCLK_SRC == 2){ //if selected PLL as sysclock_src then turn on the HSE to source the PLL
		RCC->CR |= RCC_CR_HSEON;	//turn on the HSE, HSE is prefered more to source the PLL than HSI
		while(!((RCC->CR)&(RCC_CR_HSERDY)));
		
		if((RCC->CR)&(RCC_CR_PLLON)) RCC->CR &= ~(RCC_CR_PLLON);//if PLL is on, turn it off to make changes to it
		RCC->CFGR |= RCC_CFGR_PLLSRC;	//HSE as PLL source
		
		RCC->CR |= RCC_CR_PLLON;	//turn on the PLL
		while(!((RCC->CR)&(RCC_CR_PLLRDY)));
		
		RCC->CFGR |= RCC_CFGR_SW_PLL;	//PLL as sysclock source
	}
	
}