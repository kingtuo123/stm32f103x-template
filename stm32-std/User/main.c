#include "stm32f10x.h"
#include "bsp_led.h"


void Delay_ms(__IO uint32_t ms);
void SetSysClockTo72(void);


int main(void){
	SetSysClockTo72();
	LED_Init();
	while(1){
		LED1_On();
		Delay_ms(1000);
		LED1_Off();
		Delay_ms(1000);
	}
}


void Delay_ms(__IO uint32_t ms){
	SysTick->LOAD  = 72000;             // 计数器重装载值，1ms 中断一次(系统时钟72MHZ)
	SCB->SHP[11]  |= (uint8_t)0xF0;     // 配置 SysTick 中断优先级
	SysTick->VAL   = (uint32_t)0x00;    // 计数器初始值
	SysTick->CTRL |= (uint32_t)0x07;    // 选择AHB时钟源，使能 SysTick 中断，使能 SysTick
	while(ms-- > 0){
		// 当计数器的值减小到 0 的时候，CRTL 寄存器的位 16 会置 1
		while(!((SysTick->CTRL) & ((uint32_t)0x01 << 16)));
	}
	SysTick->CTRL &= ~(uint32_t)0x01;   //关闭 SysTick
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

