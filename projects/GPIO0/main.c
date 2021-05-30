#include <stdint.h>
#include "inc/stm32f10x.h"
#include "inc/GPIO_DRIVER2.h"

int main(){
	pin_mode(IOPC, GPIOC, 13, op_50MHz, op_gppp);
	
	while(1){
		digital_writepin(GPIOC, 13, HIGH);
		for(int i=0;i<100000;i++);
		digital_writepin(GPIOC, 13, LOW);
		for(int i=0;i<100000;i++);
	}
	
}
