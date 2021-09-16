#ifndef UART_DRIVER1_H_INCLUDED
#define UART_DRIVER1_H_INCLUDED

#include "stm32f10x.h"
#include <stdint.h>
#include <stdbool.h>

/* Extern variables */
extern int __SysFrequency;	////This is the final value of the system frequency



/* enum of all popular baudrates */
typedef enum{	
	BAUD_VERYLOW  = 1200,
	BAUD_DEFAULT  = 9600,
	BAUD_HIGH     = 19200,
	BAUD_VERYHIGH = 115200
}BAUD_RATE;



/* Pointers to Functions */
//void (UART_Enable_Clock*) (UART_Init_Type*);
//void (UART_Init_GPIO*) (UART_Init_Type*);


/* UART init typedef */
typedef struct UART_Init_Type{
	/** struct data memebers **/
	USART_TypeDef* UARTx;	//UART1, 2, 3, 4
	bool Synchronous;	//True if Synchronous else False
	bool Auto_BaudRate;	//True for Auto_BaudRate, false for manual
	BAUD_RATE BaudRate;	//Baudrate of the UART
	bool Noice_Error;	//True to enable Noice_Error flag 
	
	
	
	
}UART_Init_Type;

/* Function prototyping */
void UART_Enable_Clock(UART_Init_Type* self);
void UART_Init_GPIO(UART_Init_Type* self);
void UART_Tx(UART_Init_Type* self, uint8_t data);
void UART_Send(UART_Init_Type* self, uint8_t arr[], uint8_t arr_size);
void UART_Rx(UART_Init_Type* self, uint8_t* ptr);
void UART_Enable(UART_Init_Type* self);



#endif