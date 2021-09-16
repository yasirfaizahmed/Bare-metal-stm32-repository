#ifndef STM32F103XX_H
#define STM32F103XX_H

#include <stdint.h>


/*** Peripherals TypeDefs ***/
/** GPIO TypeDef **/
typedef struct{
    uint32_t CRL;
    uint32_t CRH;
    uint32_t IDR;
    uint32_t ODR;
    uint32_t BSRR;
    uint32_t BRR;
    uint32_t LCKR;
}GPIO_RegTypeDef;

/** RCC TypeDef **/
typedef struct{
    uint32_t CR;
    uint32_t CFGR;
    uint32_t CIR;
    uint32_t APB2RSTR;
    uint32_t APB1RSTR;
    uint32_t AHBENR;
    uint32_t APB2ENR;
    uint32_t APB1ENR;
    uint32_t BDCR;
    uint32_t CSR;
}RCC_RegTypeDef;


/*** System memories Bases ***/
#define FLASH_BASE              ((uint32_t)0x08000000)
#define SRAM_BASE               ((uint32_t)0x20000000)
#define PERIPHERAL_BASE         ((uint32_t)0x40000000)

/*** Peripherals Bases ***/
#define APB1_BASE               PERIPHERAL_BASE
#define APB2_BASE               (PERIPHERAL_BASE + 0x10000)
#define AHB_BASE                (PERIPHERAL_BASE + 0x18000)



/*** GPIOx Bases ***/
#define GPIOA_BASE              (APB2_BASE + 0x0800)
#define GPIOB_BASE              (APB2_BASE + 0x0C00)
#define GPIOC_BASE              (APB2_BASE + 0x1000)
#define GPIOD_BASE              (APB2_BASE + 0x1400)
#define GPIOE_BASE              (APB2_BASE + 0x1800)
#define GPIOF_BASE              (APB2_BASE + 0x1C00)
#define GPIOG_BASE              (APB2_BASE + 0x2000)

/*** GPIOx struct base pointers ***/
#define GPIOA               ((GPIO_RegTypeDef*) ((uint32_t)0x40010800))
#define GPIOB               ((GPIO_RegTypeDef*) ((uint32_t)0x40010C00))
#define GPIOC               ((GPIO_RegTypeDef*) ((uint32_t)0x40011000))
#define GPIOD               ((GPIO_RegTypeDef*) ((uint32_t)0x40011400))
#define GPIOE               ((GPIO_RegTypeDef*) ((uint32_t)0x40011800))
#define GPIOF               ((GPIO_RegTypeDef*) ((uint32_t)0x40011C00))
#define GPIOG               ((GPIO_RegTypeDef*) ((uint32_t)0x40012000))

/*** RCC Base ***/
#define RCC_BASE                (AHB_BASE + 0x9000)

/*** RCC struct base pointer ***/
#define RCC             ((RCC_RegTypeDef*) RCC_BASE)

#endif