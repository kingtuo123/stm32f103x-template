#include "stm32f10x.h"

void LED_Init(void){
        RCC->APB2ENR |= (uint32_t)0x01 << 3; // 使能GPIOB时钟
        GPIOB->CRL   |= (uint32_t)0x03 << 4; // 配置PB1推挽输出，50MHZ
}

void delay(__IO uint32_t i){
        while(i--);
}

int main(void){
        LED_Init();
        while(1){
                GPIOB->ODR ^= 2;
                delay(0x1FFFFF);
        }
        return 0;
}
