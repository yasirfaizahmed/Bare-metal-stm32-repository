#ifndef GPIO_DRIVER2_H_INCLUDED
#define GPIO_DRIVER2_H_INCLUDED


#include <stdint.h>
#include "stm32f10x.h"

/* RCC->APB2ENR bit definition */
/* IOPx values */
typedef enum{
	IOPA = (uint32_t)0x00000004,
	IOPB = (uint32_t)0x00000008,
	IOPC = (uint32_t)0x00000010,
	IOPD = (uint32_t)0x00000020,
	IOPE = (uint32_t)0x00000040,
	IOPF = (uint32_t)0x00000080,
	IOPG = (uint32_t)0x00000100,
	
}IOP;



/* RCC->CRH, CRL bit definition */
/* MODE[1:0] values */
typedef enum{
	//input values
	ip 			= 	(uint32_t)0x00000000,
	//output values
	op_10MHz = 	(uint32_t)0x00000001, 
	op_2MHz  = 	(uint32_t)0x00000002,
	op_50MHz = 	(uint32_t)0x00000003
}MODE;

/* CNF[1:0] values */
typedef enum{
	//input values
	ip_analog   =		(uint32_t)0x00000000,
	ip_floating = 		(uint32_t)0x00000001,
	ip_pupd     = 		(uint32_t)0x00000002,
	//output values
	op_gppp			=  	(uint32_t)0x00000000,
	op_gpod			= 	(uint32_t)0x00000001,
	op_afpp			= 	(uint32_t)0x00000002,
	op_afod			= 	(uint32_t)0x00000003
}CNF;



/* GPIOx->ODR bit definition */
typedef enum{
	LOW = 0, 
	HIGH = 1
}state;


/* function prototyping */
void pin_mode(IOP IOP_value, GPIO_TypeDef* port, int pin, MODE mode_value, CNF cnf_value);
void digital_writepin(GPIO_TypeDef *port, int pin, state state_value);
void digital_lock(GPIO_TypeDef *port, int pin);
state digital_readpin(GPIO_TypeDef *port, int pin);
/* EXTI functions */
void EXTI_Enable(GPIO_TypeDef* port, int pin);
void EXTI_Clear_PendingReq(int pin);


#endif

