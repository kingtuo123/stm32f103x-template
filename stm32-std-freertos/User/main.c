#include "stm32f10x.h"
#include "bsp_led.h"
#include "FreeRTOS.h"
#include "task.h"


void SetSysClockTo72(void);
void task0(void *param);
void task1(void *param);


int main(void){
	SetSysClockTo72();
	LED_Init();

	xTaskCreate(task0, "task0", 128, NULL, 1, NULL);
	xTaskCreate(task1, "task1", 128, NULL, 1, NULL);
	vTaskStartScheduler();

	while(1){
	}
}


void task0(void *param){
	while(1){
		LED1_ON();
		vTaskDelay(1000);
		LED1_OFF();
		vTaskDelay(1000);
	}
}


void task1(void *param){
	while(1){
		LED2_OFF();
		vTaskDelay(1000);
		LED2_ON();
		vTaskDelay(1000);
	}
}


void SetSysClockTo72(void){
	// RCC system reset(for debug purpose)
	RCC_DeInit();
	// Enable HSE
	RCC_HSEConfig(RCC_HSE_ON);
	// Wait till HSE is ready
	if (RCC_WaitForHSEStartUp() == SUCCESS){
		// Enable Prefetch Buffer
		FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable);
		// Flash 2 wait state
		FLASH_SetLatency(FLASH_Latency_2);
		// HCLK = SYSCLK
		RCC_HCLKConfig(RCC_SYSCLK_Div1); 
		// PCLK2 = HCLK
		RCC_PCLK2Config(RCC_HCLK_Div1); 
		// PCLK1 = HCLK/2
		RCC_PCLK1Config(RCC_HCLK_Div2);
		// PLLCLK = 8MHz * 9 = 72 MHz
		RCC_PLLConfig(RCC_PLLSource_HSE_Div1, RCC_PLLMul_9);
		// Enable PLL
		RCC_PLLCmd(ENABLE);
		// Wait till PLL is ready
		while (RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET);
		// Select PLL as system clock source
		RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);
		// Wait till PLL is used as system clock source
		while(RCC_GetSYSCLKSource() != 0x08);
	}else{ 
		while (1);
	}
}

