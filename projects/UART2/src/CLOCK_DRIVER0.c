#include "../inc/CLOCK_DRIVER0.h"
#include "../inc/stm32f10x.h"
#include "../inc/GPIO_DRIVER2.h"
#include <stdint.h>


/* Some Multifile Global Variables */
int __SysFrequency ;	//This is the final value of the system frequency
int __AHB_Prescalar;	//This is the final value of the AHB_Prescalar

/**
 *  \brief Brief selects the source for the system clock
 *  
 *  \param [in] sysclock_src can be HSI, HSE, or PLL
 *  \return returns 1 if successfull
 *  
 *  \details More details
 */
uint8_t Select_Sysclock_Src(SYSCLK_SRC sysclock_src){
	if(sysclock_src == PLL){ //if selected PLL as sysclock_src then turn on the HSE to source the PLL
		RCC->CR |= RCC_CR_HSEON;	//turn on the HSE, HSE is prefered more to source the PLL than HSI
		while(!((RCC->CR)&(RCC_CR_HSERDY)));
		
		if((RCC->CR)&(RCC_CR_PLLON)) RCC->CR &= ~(RCC_CR_PLLON);//if PLL is on, turn it off to make changes to it
		RCC->CFGR |= RCC_CFGR_PLLSRC;	//HSE as PLL source
		
		RCC->CR |= RCC_CR_PLLON;	//turn on the PLL
		while(!((RCC->CR)&(RCC_CR_PLLRDY)));
		
		RCC->CFGR |= RCC_CFGR_SW_PLL;	//PLL as sysclock source
		RCC->CR &= ~(RCC_CR_HSION);	//turn off HSI since we dont need it here, HSI is the defalut clk src 
	}
	else if(sysclock_src == HSI){
		RCC->CR |= RCC_CR_HSION;	//turn on the HSI
		while(!((RCC->CR)&(RCC_CR_HSIRDY)));
		
		RCC->CFGR |= RCC_CFGR_SW_HSI;	//HSI as sysclock source
		
		RCC->CR &= ~(RCC_CR_HSEON);	//turn off HSE since we dont need it here 
		RCC->CR &= ~(RCC_CR_PLLON);	//turn off PLL since we dont need it here 
	}
	else{
		RCC->CR |= RCC_CR_HSEON;	//turn on the HSI
		while(!((RCC->CR)&(RCC_CR_HSERDY)));
		
		RCC->CFGR |= RCC_CFGR_SW_HSE;	//HSE as sysclock source
		
		RCC->CR &= ~(RCC_CR_HSION);	//turn off HSI since we dont need it here 
		RCC->CR &= ~(RCC_CR_PLLON);	//turn off PLL since we dont need it here 
	}
	
	return 1;
	
}

/**
 *  \brief  This function sets the respective prescallars and multipliers passed, 
			and its sysclock's source is always PLL with HSE as its source
 *  
 *  \param [in] HSE_Prescalar  HSE_Prescalar
 *  \param [in] PLL_Multiplier PLL_Multiplier
 *  \param [in] AHB_Prescalar  AHB_Prescalar
 *  \param [in] APB1_Prescalar APB1_Prescalar
 *  \param [in] APB2_Prescalar APB2_Prescalar
 *  \return nothing
 *  
 *  \details Won't work above 56Mhz, for that have to optimize the flash registers(pending)
 */
void Set_Sysclock_Frequency(HSE_PRE HSE_Prescalar, PLL_MULL PLL_Multiplier, AHB_PRE AHB_Prescalar, APB_PRE1 APB1_Prescalar, APB_PRE2 APB2_Prescalar){
	RCC->CR |= RCC_CR_HSEON;	//turn on the HSE, HSE is prefered more to source the PLL than HSI
	while(!((RCC->CR)&(RCC_CR_HSERDY)));
	
	//RCC->CFGR &= ~(RCC_CFGR_SW);	//clearing the SW bits
	//RCC->CFGR |= RCC_CFGR_SW_HSI;	//making HSI as sysclock source while PLL stays off
	
	if((RCC->CR)&(RCC_CR_PLLON)) RCC->CR &= ~(RCC_CR_PLLON);//if PLL is on, turn it off to make changes to it
	while((RCC->CR)&(RCC_CR_PLLON));
	
	RCC->CFGR |= PLL_Multiplier;	//PLL_Multiplier
	RCC->CFGR |= RCC_CFGR_PLLSRC;	//HSE as PLL source
	RCC->CFGR |= AHB_Prescalar;		//AHB_Prescalar
	RCC->CFGR |= APB1_Prescalar;	//APB1_Prescalar
	RCC->CFGR |= APB2_Prescalar;	//APB2_Prescalar
	
	
	RCC->CR |= RCC_CR_PLLON;	//turn on the PLL
	while(!((RCC->CR)&(RCC_CR_PLLRDY)));
	
	RCC->CFGR &= ~(RCC_CFGR_SW);	//clearing the SW bits
	RCC->CFGR |= RCC_CFGR_SW_PLL;	//PLL as sysclock source
	RCC->CR &= ~(RCC_CR_HSION);	//turn off HSI since we dont need it here, HSI is the defalut clk src 
	while(!(RCC->CFGR & RCC_CFGR_SWS_PLL));
		 
	switch(AHB_Prescalar){
		case (AHB_PRE_DIV1):
			__AHB_Prescalar = 1;
			break;
		case (AHB_PRE_DIV2):
			__AHB_Prescalar = 2;
			break;
		case (AHB_PRE_DIV4):
			__AHB_Prescalar = 4;
			break;
		case (AHB_PRE_DIV8):
			__AHB_Prescalar = 8;
			break;
		case (AHB_PRE_DIV16):
			__AHB_Prescalar = 16;
			break;
		case (AHB_PRE_DIV64):
			__AHB_Prescalar = 64;
			break;
		case (AHB_PRE_DIV128):
			__AHB_Prescalar = 128;
			break;
		case (AHB_PRE_DIV256):
			__AHB_Prescalar = 256;
			break;
		case (AHB_PRE_DIV512):
			__AHB_Prescalar = 512;
			break;
		default:
			__AHB_Prescalar = 8;
	}
	__SysFrequency = ( 8*((PLL_Multiplier/0x40000)+0x2) ) / ( (HSE_Prescalar)*(__AHB_Prescalar) );
	
}


/**
 *  \brief sets MCO clock source and turns it on 
 *  
 *  \param [in] MCO_source MCO source
 *  \return returns the MCO source if sucessfully
 *  
 *  \details More details
 */
uint32_t Set_MCO(MCO_SRC MCO_source){
	pin_mode(IOPA, GPIOA, 8, op_50MHz, op_afpp);
	RCC->CFGR |= MCO_source;
	
	return MCO_source;
}

