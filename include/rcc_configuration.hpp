#pragma once 

#include <stm32f4xx.h>

__attribute__((constructor(101))) void RCC_enable()
{

    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN |
                    RCC_AHB1ENR_GPIOBEN |
                    RCC_AHB1ENR_GPIOCEN |
                    RCC_AHB1ENR_GPIODEN |
                    RCC_AHB1ENR_GPIOEEN |
                    RCC_AHB1ENR_DMA2EN;

    RCC->APB2ENR |= RCC_APB2ENR_USART1EN |
                    RCC_APB2ENR_ADC1EN |
                    RCC_APB2ENR_SYSCFGEN;

    RCC->APB1ENR |= RCC_APB1ENR_TIM4EN;
}