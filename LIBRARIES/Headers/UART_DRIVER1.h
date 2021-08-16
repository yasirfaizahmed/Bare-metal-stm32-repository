#ifndef UART_DRIVER1_H_INCLUDED
#define UART_DRIVER1_H_INCLUDED

#include "stm32f10x.h"
#include <stdint.h>
#include <stdbool.h>


/* UARTx */
typedef enum{
	UARTx1 = 1,	//Synchronous
	UARTx2 = 2,	//Synchronous
	UARTx3 = 3,	//Synchronous
	UARTx4 = 4	//Asynchronous
}UARTx;

/* enum of all popular baudrates */
typedef enum{	
	VERYLOW  = 1200,
	DEFAULT  = 9600,
	HIGH     = 19200,
	VERYHIGH = 115200
}BAUD_RATE;



/* Pointers to Functions */
//void (UART_Enable_Clock*) (UART_Init_Type*);
//void (UART_Init_GPIO*) (UART_Init_Type*);


/* UART init typedef */
typedef struct UART_Init_Type{
	/** struct data memebers **/
	UARTx uartx;	//UART1, 2, 3, 4
	bool Synchronous;	//True if Synchronous else False
	bool Auto_BaudRate;	//True for Auto_BaudRate, false for manual
	BAUD_RATE BaudRate;	//Baudrate of the UART
	 
	
	
	
	
}UART_Init_Type;

/* Function prototyping */
void UART_Enable_Clock(UART_Init_Type* uart_init_type);
void UART_Init_GPIO(UART_Init_Type* uart_init_type);





#endif