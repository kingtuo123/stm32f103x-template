#include "bsp_led.h"


void LED_GPIO_Init(void){
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	LED_CLK_ENABLE();
	HAL_GPIO_WritePin(LED_GPIO, LED_PIN, GPIO_PIN_RESET);
	GPIO_InitStruct.Pin   = LED_PIN;
	GPIO_InitStruct.Mode  = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull  = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(LED_GPIO, &GPIO_InitStruct);
}
