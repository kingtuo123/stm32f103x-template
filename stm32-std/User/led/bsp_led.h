#ifndef __BSP_LED_H
#define __BSP_LED_H

#include "stm32f10x.h"

#define LED1_CLK     RCC_APB2Periph_GPIOB
#define LED1_GPIO    GPIOB
#define LED1_PIN     GPIO_Pin_5

#define LED1_On()    GPIO_SetBits(LED1_GPIO, LED1_PIN)
#define LED1_Off()   GPIO_ResetBits(LED1_GPIO, LED1_PIN)



void LED_Init(void);


#endif
