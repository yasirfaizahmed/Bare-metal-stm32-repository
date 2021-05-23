
#include <stdint.h>

#define SRAM_START  0x20000000U
#define SRAM_SIZE   20U * 1024U     //20KB
#define STACK_START ((SRAM_START) + (SRAM_SIZE))

/******* importing symbols defined in linder.ld file here ********/
extern uint32_t _ld_data;
extern uint32_t _sdata;
extern uint32_t _edata;
extern uint32_t _sbss; 
extern uint32_t _ebss;


/******* main function prototype ********/
int main(void);


/************************** ISR Vector function prototyping ***********************************/

/************** System core ISR function prototyping**************/
void Reset_Handler(void);	//only Reset_Handler is not weak
void NMI_Handler(void)									        __attribute__ ((weak, alias("Default_Handler")));
void HardFault_Handler(void)									__attribute__ ((weak, alias("Default_Handler")));
void MemManage_Handler(void)									__attribute__ ((weak, alias("Default_Handler")));
void BusFault_Handler(void)									__attribute__ ((weak, alias("Default_Handler")));
void UsageFault_Handler(void)									__attribute__ ((weak, alias("Default_Handler")));
void SVCall_Handler(void)									__attribute__ ((weak, alias("Default_Handler")));
void DebugMonitor_Handler(void)									__attribute__ ((weak, alias("Default_Handler")));
void PendSV_Handler(void)									__attribute__ ((weak, alias("Default_Handler")));
void SysTick_Handler(void)									__attribute__ ((weak, alias("Default_Handler")));

/************** Prepherals ISR function prototyping**************/
void WWDG_Handler(void)									__attribute__ ((weak, alias("Default_Handler")));
void PVD_Handler(void)									__attribute__ ((weak, alias("Default_Handler")));
void TAMPER_Handler(void)									__attribute__ ((weak, alias("Default_Handler")));
void RTC_Handler(void)									__attribute__ ((weak, alias("Default_Handler")));
void FLASH_Handler(void)									__attribute__ ((weak, alias("Default_Handler")));
void RCC_Handler(void) 									__attribute__ ((weak, alias("Default_Handler")));
void EXT10_Handler(void)									__attribute__ ((weak, alias("Default_Handler")));
void EXT11_Handler(void)									__attribute__ ((weak, alias("Default_Handler")));
void EXT12_Handler(void)									__attribute__ ((weak, alias("Default_Handler")));
void EXT13_Handler(void)									__attribute__ ((weak, alias("Default_Handler")));
void EXT14_Handler(void)									__attribute__ ((weak, alias("Default_Handler")));
void DMA1_Channel1_Handler(void)									__attribute__ ((weak, alias("Default_Handler")));
void DMA1_Channel2_Handler(void)									__attribute__ ((weak, alias("Default_Handler")));
void DMA1_Channel3_Handler(void)									__attribute__ ((weak, alias("Default_Handler")));
void DMA1_Channel4_Handler(void)									__attribute__ ((weak, alias("Default_Handler")));
void DMA1_Channel5_Handler(void)									__attribute__ ((weak, alias("Default_Handler")));
void DMA1_Channel6_Handler(void)									__attribute__ ((weak, alias("Default_Handler")));
void DMA1_Channel7_Handler(void)									__attribute__ ((weak, alias("Default_Handler")));
void ADC1_2_Handler(void)									__attribute__ ((weak, alias("Default_Handler")));
void CAN1_TX_Handler(void)									__attribute__ ((weak, alias("Default_Handler")));
void CAN1_RX0_Handler(void)									__attribute__ ((weak, alias("Default_Handler")));
void CAN1_RX1_Handler(void)									__attribute__ ((weak, alias("Default_Handler")));
void CAN1_SCE_Handler(void)									__attribute__ ((weak, alias("Default_Handler")));
void EXT9_5_Handler(void)									__attribute__ ((weak, alias("Default_Handler")));
void TIM1_BRK_Handler(void)									__attribute__ ((weak, alias("Default_Handler")));
void TIM1_UP_Handler(void)									__attribute__ ((weak, alias("Default_Handler")));
void TIM1_TRG_COM_Handler(void)									__attribute__ ((weak, alias("Default_Handler")));
void TIM1_CC_Handler(void)									__attribute__ ((weak, alias("Default_Handler")));
void TIM2_Handler(void)									__attribute__ ((weak, alias("Default_Handler")));
void TIM3_Handler(void)									__attribute__ ((weak, alias("Default_Handler")));
void TIM4_Handler(void)									__attribute__ ((weak, alias("Default_Handler")));
void I2C1_EV_Handler(void)									__attribute__ ((weak, alias("Default_Handler")));
void I2C1_ER_Handler(void)									__attribute__ ((weak, alias("Default_Handler")));
void I2C2_EV_Handler(void)									__attribute__ ((weak, alias("Default_Handler")));
void I2C2_ER_Handler(void)									__attribute__ ((weak, alias("Default_Handler")));
void SPI1_Handler(void)									__attribute__ ((weak, alias("Default_Handler")));
void SPI2_Handler(void)									__attribute__ ((weak, alias("Default_Handler")));
void USART1_Handler(void)									__attribute__ ((weak, alias("Default_Handler")));
void USART2_Handler(void)									__attribute__ ((weak, alias("Default_Handler")));
void USART3_Handler(void)									__attribute__ ((weak, alias("Default_Handler")));
void EXTI15_10_Handler(void)									__attribute__ ((weak, alias("Default_Handler")));
void RTCAlarm_Handler(void)									__attribute__ ((weak, alias("Default_Handler")));
void OTG_FS_WKUP_Handler(void)									__attribute__ ((weak, alias("Default_Handler")));
void TIM5_Handler(void)									__attribute__ ((weak, alias("Default_Handler")));
void SPI3_Handler(void)									__attribute__ ((weak, alias("Default_Handler")));
void UART4_Handler(void)									__attribute__ ((weak, alias("Default_Handler")));
void UART5_Handler(void)									__attribute__ ((weak, alias("Default_Handler")));
void TIM6_Handler(void)									__attribute__ ((weak, alias("Default_Handler")));
void TIM7_Handler(void)									__attribute__ ((weak, alias("Default_Handler")));
void DMA2_Channel1_Handler(void)									__attribute__ ((weak, alias("Default_Handler")));
void DMA2_Channel2_Handler(void)									__attribute__ ((weak, alias("Default_Handler")));
void DMA2_Channel3_Handler(void)									__attribute__ ((weak, alias("Default_Handler")));
void DMA2_Channel4_Handler(void)									__attribute__ ((weak, alias("Default_Handler")));
void DMA2_Channel5_Handler(void)									__attribute__ ((weak, alias("Default_Handler")));
void ETH_Handler(void)									__attribute__ ((weak, alias("Default_Handler")));
void ETH_WKUP_Handler(void)									__attribute__ ((weak, alias("Default_Handler")));
void CAN2_TX_Handler(void)									__attribute__ ((weak, alias("Default_Handler")));
void CAN2_RX0_Handler(void)									__attribute__ ((weak, alias("Default_Handler")));
void CAN2_RX1_Handler(void)									__attribute__ ((weak, alias("Default_Handler")));
void CAN2_SCE_Handler(void)									__attribute__ ((weak, alias("Default_Handler")));
void OTG_FS_Handler(void)									__attribute__ ((weak, alias("Default_Handler")));


/**************************** ISR vector table *****************************************/
uint32_t vector_table[] __attribute__ ((section(".vectors"))) = {//A user defined section, this array gets stored in .vectors section and not in .data section
	// system core IRQs
	(uint32_t)STACK_START,	
	(uint32_t)&Reset_Handler,
	(uint32_t)&NMI_Handler,
	(uint32_t)&HardFault_Handler,
	(uint32_t)&MemManage_Handler,
	(uint32_t)&BusFault_Handler,
	(uint32_t)&UsageFault_Handler,
	0,
	0,
	0,
	0,
	(uint32_t)&SVCall_Handler,
	(uint32_t)&DebugMonitor_Handler,
	0,
	(uint32_t)&PendSV_Handler,
	(uint32_t)&SysTick_Handler,
	
	// periherals IRQs
	(uint32_t)&WWDG_Handler,
	(uint32_t)&PVD_Handler,
	(uint32_t)&TAMPER_Handler,
	(uint32_t)&RTC_Handler,
	(uint32_t)&FLASH_Handler,
	(uint32_t)&RCC_Handler,
	(uint32_t)&EXT10_Handler,
	(uint32_t)&EXT11_Handler,
	(uint32_t)&EXT12_Handler,
	(uint32_t)&EXT13_Handler,
	(uint32_t)&EXT14_Handler,
	(uint32_t)&DMA1_Channel1_Handler,
	(uint32_t)&DMA1_Channel2_Handler,
	(uint32_t)&DMA1_Channel3_Handler,
	(uint32_t)&DMA1_Channel4_Handler,
	(uint32_t)&DMA1_Channel5_Handler,
	(uint32_t)&DMA1_Channel6_Handler,
	(uint32_t)&DMA1_Channel7_Handler,
	(uint32_t)&ADC1_2_Handler,
	(uint32_t)&CAN1_TX_Handler,
	(uint32_t)&CAN1_RX0_Handler,
	(uint32_t)&CAN1_RX1_Handler,
	(uint32_t)&CAN1_SCE_Handler,
	(uint32_t)&EXT9_5_Handler,
	(uint32_t)&TIM1_BRK_Handler,
	(uint32_t)&TIM1_UP_Handler,
	(uint32_t)&TIM1_TRG_COM_Handler,
	(uint32_t)&TIM1_CC_Handler,
	(uint32_t)&TIM2_Handler,
	(uint32_t)&TIM3_Handler,
	(uint32_t)&TIM4_Handler,
	(uint32_t)&I2C1_EV_Handler,
	(uint32_t)&I2C1_ER_Handler,
	(uint32_t)&I2C2_EV_Handler,
	(uint32_t)&I2C2_ER_Handler,
	(uint32_t)&SPI1_Handler,
	(uint32_t)&SPI2_Handler,
	(uint32_t)&USART1_Handler,
	(uint32_t)&USART2_Handler,
	(uint32_t)&USART3_Handler,
	(uint32_t)&EXTI15_10_Handler,
	(uint32_t)&RTCAlarm_Handler,
	(uint32_t)&OTG_FS_WKUP_Handler,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	(uint32_t)&TIM5_Handler,
	(uint32_t)&SPI3_Handler,
	(uint32_t)&UART4_Handler,
	(uint32_t)&UART5_Handler,
	(uint32_t)&TIM6_Handler,
	(uint32_t)&TIM7_Handler,
	(uint32_t)&DMA2_Channel1_Handler,
	(uint32_t)&DMA2_Channel2_Handler,
	(uint32_t)&DMA2_Channel3_Handler,
	(uint32_t)&DMA2_Channel4_Handler,
	(uint32_t)&DMA2_Channel5_Handler,
	(uint32_t)&ETH_Handler,
	(uint32_t)&ETH_WKUP_Handler,
	(uint32_t)&CAN2_TX_Handler,
	(uint32_t)&CAN2_RX0_Handler,
	(uint32_t)&CAN2_RX1_Handler,
	(uint32_t)&CAN2_SCE_Handler,
	(uint32_t)&OTG_FS_Handler,
 
	

};


/*
 *  \brief Reset_Handler ISR
 *  
 *  \return returns nothing
 *  
 *  \details More details
 */
void Reset_Handler(void){
	uint32_t *src , *dst;	//_ld_data, _sdata are externs symbols from linker.ld
	for(src = &_ld_data,dst = &_sdata; dst<&_edata; src++,dst++){
		*dst = *src; 	//copying
	}
	for(dst = &_sbss; dst<&_ebss; dst++){	// Initialize all uninitialized variables (bss section) to 0
		*dst = 0;
	}
	
	main();
	
	while(1);	//usually main should not return anything, but it does
}

/*
 *  \brief Default_Handler ISR an alias for most of the unneccesory handlers
 *  
 *  \return returns nothing
 *  
 *  \details More details
 */
void Default_Handler(void){
	while(1);
	
}