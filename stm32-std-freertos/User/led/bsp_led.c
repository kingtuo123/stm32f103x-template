#include "bsp_led.h"


void LED_Init(void){
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(LED1_CLOCK|LED2_CLOCK, ENABLE);
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Pin   = LED1_PIN;
	GPIO_Init(LED1_PORT, &GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin   = LED2_PIN;
	GPIO_Init(LED2_PORT, &GPIO_InitStructure);
	LED1_OFF();
	LED2_OFF();
}
