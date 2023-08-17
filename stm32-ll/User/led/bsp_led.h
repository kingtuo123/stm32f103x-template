#ifndef __BSP_LED_H
#define __BSP_LED_H
#include "stm32f1xx_ll_gpio.h"
#include "stm32f1xx_ll_bus.h"

#define LED_GPIO        GPIOB
#define LED_Pin         LL_GPIO_PIN_0
#define LED_Toggle()	LL_GPIO_TogglePin(LED_GPIO, LED_Pin)









void LED_GPIO_Init(void);



#endif
