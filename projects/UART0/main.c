#include "inc/UART_DRIVER0.h"
#include "inc/GPIO_DRIVER2.h"
#include "inc/CLOCK_DRIVER0.h"
#define data 0x69



int main(){
	//since the sys_clock is running at 8MHz,the baudrade is now 9600/8 = 1200
	UART_Setup();
	//pin_mode(IOPC, GPIOC, 13, op_50MHz, op_gppp);
	//digital_writepin(GPIOC, 13, LOW);
	
	while(1){
		UART_Tx(data);
	}
	
}