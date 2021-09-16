#ifndef UART_DRIVER0_INCLUDED_H
#define UART_DRIVER0_INCLUDED_H

#include <stdint.h>
#include "stm32f10x.h"


#define DMA_CCR_MINC     ((uint16_t)0x0080)   //memory increment mode
#define DMA_CCR_CIRC     ((uint16_t)0x0020)   //circuilar mode 
#define DMA_CCR_TCIE     ((uint16_t)0x0002)   //transfer complete interrupt enable
#define DMA_CCR_EN       ((uint16_t)0x0001)   //enable the channel
#define DMA_CCR_PINC     ((uint16_t)0x0040)   //periheral increment enable


typedef enum{   //a enum for DMA priority levels
	DMA_PL_LOW    = (uint16_t)0x0000,
	DMA_PL_MEDIUM = (uint16_t)0x1000,
	DMA_PL_HIGH   = (uint16_t)0x2000,
	DMA_PL_VHIGH  = (uint16_t)0x3000
}DMA_PL;
/*
typedef enum{   //a enum for DMA_CHANNEL
	DMA1_CHANNEL1 = DMA1_Channel1,
	DMA1_CHANNEL2 = DMA1_Channel2,
	DMA1_CHANNEL3 = DMA1_Channel3,
	DMA1_CHANNEL4 = DMA1_Channel4,
	DMA1_CHANNEL5 = DMA1_Channel5,
	DMA1_CHANNEL6 = DMA1_Channel6,
	DMA1_CHANNEL7 = DMA1_Channel7,
	
	DMA2_CHANNEL1 = DMA1_Channel1,
	DMA2_CHANNEL2 = DMA2_Channel2,
	DMA2_CHANNEL3 = DMA3_Channel3,
	DMA2_CHANNEL4 = DMA4_Channel4,
	DMA2_CHANNEL5 = DMA5_Channel5
	
}DMA_CHANNEL;
*/

//static void printMsg(char *msg, ...);
void UART_Setup(void);
void UART_Tx(char data);
void UART_Send(uint8_t arr[], uint8_t arr_size);
void USART_Transfer_Info(uint8_t arr_ptr[], uint8_t arr_size);
void USART_Erase_Info(void);
void USART_Receive_DMA(DMA_Channel_TypeDef* DMA_channel, DMA_PL DMA_priority, uint8_t arr[], int arr_size);   



#endif
