#ifndef __BSP_LED_H
#define __BSP_LED_H
#include "stm32f1xx.h"
#include "stm32f1xx_hal.h"


#define LED_CLK_ENABLE()	__HAL_RCC_GPIOB_CLK_ENABLE()
#define LED_GPIO			GPIOB
#define LED_PIN				GPIO_PIN_0









void LED_GPIO_Init(void);



#endif
