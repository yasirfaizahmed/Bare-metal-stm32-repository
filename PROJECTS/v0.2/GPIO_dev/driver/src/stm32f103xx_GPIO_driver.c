#include "../inc/stm32f103xx_GPIO_driver.h"
#include <stdint.h>


/*
 * Function prototyping
 */
/**
 *  \brief Initilizes the GPIO pin
 *  
 *  \param [in] GPIO_instance GPIO_Instance
 *  \return nothing
 *  
 *  \details 
 */
void GPIO_Init(GPIO_HandleTypeDef * GPIO_instance){
	if(GPIO_instance->GPIOx == GPIOA) RCC->APB2ENR |= IOPAEN;
	else if(GPIO_instance->GPIOx == GPIOB) RCC->APB2ENR |= IOPBEN;
	else if(GPIO_instance->GPIOx == GPIOC) RCC->APB2ENR |= IOPCEN;
	else if(GPIO_instance->GPIOx == GPIOD) RCC->APB2ENR |= IOPDEN;
	else if(GPIO_instance->GPIOx == GPIOE) RCC->APB2ENR |= IOPEEN;
	else if(GPIO_instance->GPIOx == GPIOF) RCC->APB2ENR |= IOPFEN;
	else if(GPIO_instance->GPIOx == GPIOG) RCC->APB2ENR |= IOPGEN;
	
	if(GPIO_instance->PinNumber <= 7){
		GPIO_instance->GPIOx->CRL &= ~( GPIO_CLEAR_MASK<<((GPIO_instance->PinNumber%8)*4) );
		GPIO_instance->GPIOx->CRL |= ( (GPIO_instance->Conf | GPIO_instance->Mode)<<((GPIO_instance->PinNumber%8)*4) );
	}
	else{
		GPIO_instance->GPIOx->CRH &= ~( GPIO_CLEAR_MASK<<((GPIO_instance->PinNumber%8)*4) );
		GPIO_instance->GPIOx->CRH |= ( (GPIO_instance->Conf | GPIO_instance->Mode)<<((GPIO_instance->PinNumber%8)*4) );
	}
}

/**
 *  \brief De-Initilizes the GPIO pin
 *  
 *  \param [in] GPIO_Instance GPIO_Instance
 *  \return nothing
 *  
 *  \details 
 */
void GPIO_DeInit(GPIO_HandleTypeDef* GPIO_instance){
	GPIO_instance->GPIOx->BSRR |= (1 << (GPIO_instance->PinNumber + 16));
	GPIO_instance->GPIOx->BSRR &= ~(1 << (GPIO_instance->PinNumber + 16));
}

/**
 *  \brief Writes 16bit value to the port
 *  
 *  \param [in] GPIO_Instance GPIO_Instance
 *  \param [in] value 16bit value
 *  \return nothing
 *  
 *  \details 
 */
void GPIO_WriteToPort(GPIO_HandleTypeDef* GPIO_instance, uint16_t value){
	GPIO_instance->GPIOx->ODR = value;
}

/**
 *  \brief Writes bit either HIGH or LOW
 *  
 *  \param [in] GPIO_Instance GPIO_Ins
 *  \param [in] state HIGH/LOW
 *  \return nothing
 *  
 *  \details 
 */
void GPIO_WriteToPin(GPIO_HandleTypeDef* GPIO_instance, PIN_STATE state){
	GPIO_instance->GPIOx->ODR &= (uint16_t)(~(1<<GPIO_instance->PinNumber));
	GPIO_instance->GPIOx->ODR |= (uint16_t)(state<<GPIO_instance->PinNumber);
}

/**
 *  \brief Reads 16bit value from the port
 *  
 *  \param [in] GPIO_Instance GPIO_Ins
 *  \return the 16 value from the port
 *  
 *  \details 
 */
uint16_t GPIO_ReadFromPort(GPIO_HandleTypeDef* GPIO_instance){
	return GPIO_instance->GPIOx->ODR;
}

/**
 *  \brief Reads bit value from the port
 *  
 *  \param [in] GPIO_Instance GPIO_Ins
 *  \return bit value HIGH/LOW
 *  
 *  \details 
 */
PIN_STATE GPIO_ReadFromPin(GPIO_HandleTypeDef* GPIO_instance){
	if(GPIO_instance->GPIOx->ODR&&(1<<GPIO_instance->PinNumber) == 1) return HIGH;
	else return LOW;
}
