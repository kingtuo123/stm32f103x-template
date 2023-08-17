#ifndef __BSP_LED_H
#define __BSP_LED_H

#include "stm32f10x.h"

#define LED1_CLOCK    RCC_APB2Periph_GPIOB
#define LED1_PORT     GPIOB
#define LED1_PIN      GPIO_Pin_5
									    
#define LED2_CLOCK    RCC_APB2Periph_GPIOB
#define LED2_PORT     GPIOB
#define LED2_PIN      GPIO_Pin_0
								



#define LED1_OFF()    GPIO_SetBits(LED1_PORT, LED1_PIN)
#define LED1_ON()     GPIO_ResetBits(LED1_PORT, LED1_PIN)

#define LED2_OFF()    GPIO_SetBits(LED2_PORT, LED2_PIN)
#define LED2_ON()     GPIO_ResetBits(LED2_PORT, LED2_PIN)



void LED_Init(void);


#endif
