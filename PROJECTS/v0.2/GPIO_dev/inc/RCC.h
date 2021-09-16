#ifndef RCC_H
#define RCC_H

#include <stdint.h>


#define RCC_BASE        (uint32_t) 0x40021000U


#define GPIOC_BASE      (uint32_t) 0x40011000U



#define RCC_CR          *(uint32_t*) ((RCC_BASE) + (0x00U))
#define RCC_CFGR        *(uint32_t*) ((RCC_BASE) + (0x04U))
#define RCC_CIR         *(uint32_t*) ((RCC_BASE) + (0x08U))
#define RCC_APB2RSTR    *(uint32_t*) ((RCC_BASE) + (0x0CU))
#define RCC_APB1RSTR    *(uint32_t*) ((RCC_BASE) + (0x10U))
#define RCC_AHBENR      *(uint32_t*) ((RCC_BASE) + (0x14U))
#define RCC_APB2ENR     *(uint32_t*) ((RCC_BASE) + (0x18U))
#define RCC_APB1ENR     *(uint32_t*) ((RCC_BASE) + (0x1CU))
#define RCC_BDCR        *(uint32_t*) ((RCC_BASE) + (0x20U))
#define RCC_CSR         *(uint32_t*) ((RCC_BASE) + (0x24U))



#define GPIOC_CRH 	    *(uint32_t*) (GPIOC_BASE + 0x04)
#define GPIOC_ODR		*(uint32_t*) (GPIOC_BASE + 0x0c)


#endif