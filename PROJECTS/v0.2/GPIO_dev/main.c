#include <stdint.h>
//#include "inc/RCC.h"
#include "inc/stm32f103xx.h"
#include "driver/inc/stm32f103xx_GPIO_driver.h"

int main(){
    RCC->CR |= (1<<0);   //HSI on
    while(RCC->CR & (1<<2)); //wait till HSI turns on
    
    RCC->CFGR &= ~(3<<0);    //clearing the clock bits
    RCC->CFGR |= (0<<0);     //setting HSI as clock source
    
    GPIO_HandleTypeDef mypin;
	mypin.GPIOx = GPIOC;
	mypin.PinNumber = 13;
	mypin.Mode = SPEED_10MHZ;
	mypin.Conf = GP_PUPD_OUTPUT;
	GPIO_Init(&mypin);
	
	GPIO_HandleTypeDef mpin;
	mpin.GPIOx = GPIOA;
	mpin.PinNumber = 3;
	mpin.Mode = SPEED_10MHZ;
	mpin.Conf = GP_PUPD_OUTPUT;
	GPIO_Init(&mpin);

	GPIO_WriteToPort(&mpin, 0x6900);
	GPIO_WriteToPin(&mpin, HIGH);
	
    while(1){
		
		GPIO_WriteToPin(&mypin, HIGH);
		for(int i=0;i<1000000;i++);
		GPIO_WriteToPin(&mypin, LOW);
		for(int i=0;i<1000000;i++);

	}
    
}