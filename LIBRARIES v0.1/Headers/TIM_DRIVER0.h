#ifndef TIM_DRIVER0_INCLUDED_H
#define TIM_DRIVER0_INCLUDED_H

#include "stm32f10x.h"
#include <stdbool.h>
#include "GPIO_DRIVER2.h"


//typedef enum{
//	TIM_1 =  (uint32_t) 0x00000800,
//	TIM_2 =  (uint32_t) 0x00000001,
//	TIM_3 =  (uint32_t) 0x00000002,
//	TIM_4 =  (uint32_t) 0x00000004,
//	TIM_5 =  (uint32_t) 0x00000008,
//	TIM_6 =  (uint32_t) 0x00000010,
//	TIM_7 =  (uint32_t) 0x00000020,
//	TIM_8 =  (uint32_t) 0x00002000,
//	TIM_9 =  (uint32_t) 0x00080000,
//	TIM_10 = (uint32_t) 0x00100000,	
//	TIM_11 = (uint32_t) 0x00200000,
//}TIMx;



/************************************ tim_init function ************************************/
void delay_tim_init();
 

/************************************ delay_us function ************************************/
void delay_us(int us);


/************************************ delay_ms function ***************************************/
void delay_ms(int ms);


/************************************ analog_write function ************************************/
void analog_write(IOP IOP_value, GPIO_TypeDef* port, TIM_TypeDef* TIM, int channel, int pin, int PWM_mode, bool parity_bit, float duty_cycle);
#endif

