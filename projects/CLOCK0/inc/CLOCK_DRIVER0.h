#ifndef CLOCK_DRIVER0_H_INCLUDED
#define CLOCK_DRIVER0_H_INCLUDED


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
else if sys_clk > 8MHz then clk src is HSE, HCLK = (8MHz of HSE*PLLmull) / (HSEpre)*(AHBpre)


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
	HCKL_500MHz = 500,
	//HCLK = 8MHz of HSE * (2 to 9) / (2*32)
	
}HCLK;


/*********** function prototye ***********/
uint8_t Select_Sysclock_Src(SYSCLK_SRC sysclock_src);
uint8_t Turn_On_PLL();
void Set_Sysclock(HCLK HCLK_frequency);

#endif