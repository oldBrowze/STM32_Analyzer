#include "analyzer.hpp"


void Analyzer::configuration()
{
    debug_led_configuration();
}


void Analyzer::debug_led_configuration()
{

    //NVIC_EnableIRQ(TIM3_IRQn);
    //NVIC_SetPriority(TIM3_IRQn, 15);

    NVIC_EnableIRQ(TIM4_IRQn);
    NVIC_SetPriority(TIM4_IRQn, 5);

    //TIM4->DIER |= TIM_DIER_UIE; //прерывание 1 кгЦ
    //TIM4->ARR = 84 - 1;
    //TIM4->PSC = 10 - 1;

    //TIM4->CR2 |= (0b010) << TIM_CR2_MMS_Pos;
    //TIM4->EGR |= TIM_EGR_UG;
    //TIM4->CR1 |= TIM_CR1_CEN;


    TIM4->DIER |= TIM_DIER_UIE; //прерывание
    TIM4->ARR = 10000 - 1;
    TIM4->PSC = 8400 - 1;

    TIM4->EGR |= TIM_EGR_UG;
    TIM4->CR1 |= TIM_CR1_CEN;

    GPIOA->MODER |= 0b01 << GPIO_MODER_MODE6_Pos;
    GPIOA->PUPDR |= 0b10 << GPIO_PUPDR_PUPD6_Pos;
}

