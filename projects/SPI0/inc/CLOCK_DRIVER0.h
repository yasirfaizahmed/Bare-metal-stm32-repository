#ifndef CLOCK_DRIVER0_H_INCLUDED
#define CLOCK_DRIVER0_H_INCLUDED

#include <stdint.h>
#include "stm32f10x.h"

/*


											 ------------(sys src selector)sysclk------AHBpre------HCLK---->to peripherals
											/	|	|
										   /	|	|
										  /		|	|
										 /		|	|
HSI-------------------------------------/		|	|
			  \									|	|		
			   \								|	|
				\								|	|
				 \------(src selector)PLLmull----	|
				 /									|
                /									|
               /									|
HSE-----HSEpre/  									|
	  |												|		
	  |												|
	  |----------------------------------------------


if sys_clk <= 8MHz then clk src is HSI
else if sys_clk > 8MHz then clk src is HSE, HCLK = (8MHz of HSE*PLLmull) / (HSE_PRE)*(AHB_PRE)


PLLmull can be from 2 - 16
HSEpre can be from 1 - 2
AHBpre can be from 2^0 - 2^9 i.e., from 1 - 512

*/

typedef enum{
	HSI = 0,
	HSE = 1,
	PLL = 2
}SYSCLK_SRC;



typedef enum{
	//HCLK = 8MHz of HSE * (2 to 9) / (1*1)
	HCLK_72MHz = 72,
	HCLK_64MHz = 64,
	HCLK_56MHz = 56,
	HCLK_48MHz = 48,
	HCLK_45MHz = 45,
	HCLK_32MHz = 32,
	HCLK_24MHz = 24,
	HCLK_16MHz = 16,
	//HCLK = 8MHz of HSE * (2 to 9) / (2*1)
	HCLK_36MHz = 36,
	HCLK_28MHz = 28,
	HCLK_12MHz = 12,
	HCLK_8MHz = 8,
	//HCLK = 8MHz of HSE * (2 to 9) / (2*2)
	HCLK_18MHz = 18,
	HCLK_14MHz = 14,
	HCLK_6MHz = 6,
	HCLK_4MHz = 4,
	//HCLK = 8MHz of HSE * (2 to 9) / (2*8)
	HCLK_1MHz = 1,
	//HCLK = 8MHz of HSE * (2 to 9) / (2*16)
	HCKL_500MHz = 500
	//HCLK = 8MHz of HSE * (2 to 9) / (2*32)
	
}HCLK;

typedef enum{
	HSE_PRE_DIV1 = 1,
	HSE_PRE_DIV2 = 2
}HSE_PRE;

typedef enum{
	PLL_MULL2 = RCC_CFGR_PLLMULL2,
	PLL_MULL3 = RCC_CFGR_PLLMULL3,
	PLL_MULL4 = RCC_CFGR_PLLMULL4,
	PLL_MULL5 = RCC_CFGR_PLLMULL5,
	PLL_MULL6 = RCC_CFGR_PLLMULL6,
	PLL_MULL7 = RCC_CFGR_PLLMULL7,
	PLL_MULL8 = RCC_CFGR_PLLMULL8,
	PLL_MULL9 = RCC_CFGR_PLLMULL9,
	PLL_MULL10 = RCC_CFGR_PLLMULL10,
	PLL_MULL11 = RCC_CFGR_PLLMULL11,
	PLL_MULL12 = RCC_CFGR_PLLMULL12,
	PLL_MULL13 = RCC_CFGR_PLLMULL13,
	PLL_MULL14 = RCC_CFGR_PLLMULL14,
	PLL_MULL15 = RCC_CFGR_PLLMULL15,
	PLL_MULL16 = RCC_CFGR_PLLMULL16
}PLL_MULL;

typedef enum{
	AHB_PRE_DIV1 = RCC_CFGR_HPRE_DIV1,
	AHB_PRE_DIV2 = RCC_CFGR_HPRE_DIV2,
	AHB_PRE_DIV4 = RCC_CFGR_HPRE_DIV4,
	AHB_PRE_DIV8 = RCC_CFGR_HPRE_DIV8,
	AHB_PRE_DIV16 = RCC_CFGR_HPRE_DIV16,
	AHB_PRE_DIV64 = RCC_CFGR_HPRE_DIV64,
	AHB_PRE_DIV128 = RCC_CFGR_HPRE_DIV128,
	AHB_PRE_DIV256 = RCC_CFGR_HPRE_DIV256,
	AHB_PRE_DIV512 = RCC_CFGR_HPRE_DIV512,
}AHB_PRE;

typedef enum{
	APB_PRE1_DIV1 = RCC_CFGR_PPRE1_DIV1,
	APB_PRE1_DIV2 = RCC_CFGR_PPRE1_DIV2,
	APB_PRE1_DIV4 = RCC_CFGR_PPRE1_DIV4,
	APB_PRE1_DIV8 = RCC_CFGR_PPRE1_DIV8,
	APB_PRE1_DIV16 = RCC_CFGR_PPRE1_DIV16
}APB_PRE1;

typedef enum{
	APB_PRE2_DIV1 = RCC_CFGR_PPRE2_DIV1,
	APB_PRE2_DIV2 = RCC_CFGR_PPRE2_DIV2,
	APB_PRE2_DIV4 = RCC_CFGR_PPRE2_DIV4,
	APB_PRE2_DIV8 = RCC_CFGR_PPRE2_DIV8,
	APB_PRE2_DIV16 = RCC_CFGR_PPRE2_DIV16
}APB_PRE2;

typedef enum{
	PLL_MCO_SRC = RCC_CFGR_MCO_PLL,
	HSE_MCO_SRC = RCC_CFGR_MCO_HSE,
	HSI_MCO_SRC = RCC_CFGR_MCO_HSI
}MCO_SRC;

/*********** function prototye ***********/
void Set_Sysclock_Frequency(HSE_PRE HSE_Prescalar, PLL_MULL PLL_Multiplier, AHB_PRE AHB_Prescalar, APB_PRE1 APB1_Prescalar, APB_PRE2 APB2_Prescalar);
uint32_t Set_MCO(MCO_SRC MCO_source);

#endif