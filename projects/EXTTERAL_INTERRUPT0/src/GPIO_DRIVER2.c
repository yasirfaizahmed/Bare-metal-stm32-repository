#include <stdint.h>
#include "../inc/stm32f10x.h"
#include "../inc/GPIO_DRIVER2.h"



/**
 *  \brief To set the GPIO pin mode
 *  
 *  \param [in] IOP_value  IO port name 
 *  \param [in] port       GPIO port name
 *  \param [in] pin        pin mumber
 *  \param [in] mode_value mode of the pin, ip or op
 *  \param [in] cnf_value  some more details of mode of the pin 
 *  \return nothing
 *  
 *  \details 
 */
void pin_mode(IOP IOP_value, GPIO_TypeDef* port, int pin, MODE mode_value, CNF cnf_value){

	RCC->APB2ENR |= IOP_value;
	
	uint32_t final_value = mode_value | (cnf_value<<2);	//getting the fianl value of the the modes combined
	
	if(pin <= 7){
		port->CRL &= ~((uint32_t)(0xf<<(4*pin)));	//clearing the default bits
		port->CRL |= (final_value<<(4*pin));	//writing in CRL 
	}
	
	if(pin > 7){
		port->CRH &= ~((uint32_t)(0xf<<4*(pin-8)));	//clearing the default bits
		port->CRH |= (final_value<<(4*(pin-8)));	//writing in CRH
	}
	
}



/**
 *  \brief Write digital value 0 or 1
 *  
 *  \param [in] port        GPIO port name
 *  \param [in] pin         pin number
 *  \param [in] state_value HIGH or LOW state
 *  \return nothing
 *  
 *  \details 	
 */
void digital_writepin(GPIO_TypeDef *port, int pin, state state_value){
	if(state_value == HIGH){
		port->ODR |= (state_value<<pin);	//writing 1
	}
	else{
		port->ODR &=  ~(~state_value<<pin);	//writing 0
	}
	
}



/**
 *  \brief Locks the GPIO pin state
 *  
 *  \param [in] port GPIO port name
 *  \param [in] pin  pin number
 *  \return nothing
 *  
 *  \details 	
 */
void digital_lock(GPIO_TypeDef *port, int pin){
	if((port->LCKR & GPIO_LCKR_LCKK) == 1){	//if lock bit is set, reset it to remap the sequence 
		port->LCKR |= GPIO_LCKR_LCKK;
		port->LCKR &= ~(GPIO_LCKR_LCKK);	//To modify the bit, this is the sequence
		port->LCKR |= GPIO_LCKR_LCKK;
		
		port->LCKR &= ~(GPIO_LCKR_LCKK);	//finally clearing the LCKK bit
	}
	
	port->LCKR |= (1<<pin);
	
	port->LCKR |= GPIO_LCKR_LCKK;
	port->LCKR &= ~(GPIO_LCKR_LCKK);	//To modify the bit, this is the sequence
	port->LCKR |= GPIO_LCKR_LCKK;
	
	port->LCKR |= GPIO_LCKR_LCKK;	//finally locking the sequence
	
}



/**
 *  \brief Read the pin digitally 0 or 1
 *  
 *  \param [in] port pin number
 *  \param [in] pin  pin number
 *  \return nothing
 *  
 *  \details 	
 */
state digital_readpin(GPIO_TypeDef *port, int pin){
	uint16_t mask = (1<<pin);
	if((port->IDR & mask) == mask){	//reading 1
		return HIGH;
	}
	else if((port->IDR & mask) == 0){	//reading 0
		return LOW;
	}
	return LOW;
}


/**
 *  \brief Enable EXTIx for port x and pinnumber pin
 *  
 *  \param [in] port GPIO port name
 *  \param [in] pin  pin number
 *  \return nothing
 *  
 *  \details 	
 */
void EXTI_Enable(GPIO_TypeDef* port, int pin){
	RCC->APB2ENR |= RCC_APB2ENR_AFIOEN;    //clock for Alternate functions
	if(pin <= 3){
		if(port == GPIOA) AFIO->EXTICR[0] |= (0x0000<<(pin*4));
		if(port == GPIOB) AFIO->EXTICR[0] |= (0x0001<<(pin*4));
		if(port == GPIOC) AFIO->EXTICR[0] |= (0x0010<<(pin*4));
		if(port == GPIOD) AFIO->EXTICR[0] |= (0x0011<<(pin*4));
	}
	
}

	