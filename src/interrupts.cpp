#include <stm32f4xx.h>
#include "analyzer.hpp"
#include "stm32_st7735.hpp"


extern "C" void TIM4_IRQHandler()
{
    if (TIM4->SR & TIM_SR_UIF_Msk)
        TIM4->SR &= ~TIM_SR_UIF_Msk;

    GPIOA->ODR ^= GPIO_ODR_OD6; 
}


extern "C" void EXTI0_IRQHandler()
{
    if (EXTI->PR & EXTI_PR_PR0_Msk)
    {
        EXTI->PR = EXTI_PR_PR0_Msk;
    }
}

extern "C" void SysTick_Handler()
{
    ST7735::__ticks++; 
}