#include "CLOCK_DRIVER0.h"
#include "GPIO_DRIVER2.h"
#include "stm32f10x.h"
#include "UART_DRIVER0.h"



int main(){
	Set_Sysclock_Frequency(HSE_PRE_DIV1, PLL_MULL2, AHB_PRE_DIV8, APB_PRE1_DIV1, APB_PRE2_DIV1);
	
	UART_Setup();
	
	while(1){
		UART_Tx(0x69);
		for(int i=0;i<100000;i++);
	}
}