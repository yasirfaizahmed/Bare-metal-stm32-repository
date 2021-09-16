

#ifndef STM32F103XX_GPIO_DRIVER_H
#define STM32F103XX_GPIO_DRIVER_H

#include <stdint.h>
#include "../../inc/stm32f103xx.h"


/*
 *GPIO_TypeDef 
 */
typedef struct{
    GPIO_RegTypeDef* GPIOx;
    uint8_t PinNumber;
    uint8_t Mode;
	uint8_t Conf;
    uint8_t Speed;
}GPIO_HandleTypeDef;

/*
 * GPIO CRL/CRH bit/s definitions
 */
#define ANALOG_INPUT                ((uint8_t) 0x00)
#define FlOATING_INPUT              ((uint8_t) 0x04)
#define PUPD_INPUT                  ((uint8_t) 0x08)

#define GP_PUPD_OUTPUT              ((uint8_t) 0x00)
#define GP_OD_OUTPUT                ((uint8_t) 0x01)
#define AF_PUPD_OUTPUT              ((uint8_t) 0x02)
#define AF_OD_OUTPUT                ((uint8_t) 0x03)

#define SPEED_10MHZ                 ((uint8_t) 0x01)
#define SPEED_2MHZ                  ((uint8_t) 0x02)
#define SPEED_50MHZ                 ((uint8_t) 0x03)

#define GPIO_CLEAR_MASK				((uint8_t)0x0F)

/*
 *RCC APB2ENR bit/s definitions
 */
#define AFIOEN              ((uint32_t) 0x00000001)
#define IOPAEN              ((uint32_t) 0x00000004)
#define IOPBEN              ((uint32_t) 0x00000008)
#define IOPCEN              ((uint32_t) 0x00000010)
#define IOPDEN              ((uint32_t) 0x00000020)
#define IOPEEN              ((uint32_t) 0x00000040)
#define IOPFEN              ((uint32_t) 0x00000080)
#define IOPGEN              ((uint32_t) 0x00000100)
/*
 * Some handy bit/s definitions
 */
typedef enum{
    HIGH = 1,
    LOW  = 0 
}PIN_STATE;

/*
 * Function prototyping
 */
/**
 *  \brief Initilizes the GPIO pin
 *  
 *  \param [in] GPIO_instance GPIO_Instance
 *  \return nothing
 *  
 *  \details 
 */
void GPIO_Init(GPIO_HandleTypeDef* GPIO_instance);

/**
 *  \brief De-Initilizes the GPIO pin
 *  
 *  \param [in] GPIO_Instance GPIO_Instance
 *  \return nothing
 *  
 *  \details 
 */
void GPIO_DeInit(GPIO_HandleTypeDef* GPIO_instance);

/**
 *  \brief Writes 16bit value to the port
 *  
 *  \param [in] GPIO_Instance GPIO_Instance
 *  \param [in] value 16bit value
 *  \return nothing
 *  
 *  \details 
 */
void GPIO_WriteToPort(GPIO_HandleTypeDef* GPIO_instance, uint16_t value);

/**
 *  \brief Writes bit either HIGH or LOW
 *  
 *  \param [in] GPIO_Instance GPIO_Ins
 *  \param [in] state HIGH/LOW
 *  \return nothing
 *  
 *  \details 
 */
void GPIO_WriteToPin(GPIO_HandleTypeDef* GPIO_instance, PIN_STATE state);

/**
 *  \brief Reads 16bit value from the port
 *  
 *  \param [in] GPIO_Instance GPIO_Ins
 *  \return the 16 value from the port
 *  
 *  \details 
 */
uint16_t GPIO_ReadFromPort(GPIO_HandleTypeDef* GPIO_instance);

/**
 *  \brief Reads bit value from the port
 *  
 *  \param [in] GPIO_Instance GPIO_Ins
 *  \return bit value HIGH/LOW
 *  
 *  \details 
 */
PIN_STATE GPIO_ReadFromPin(GPIO_HandleTypeDef* GPIO_instance);
#endif
