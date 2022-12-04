#include <stm32f4xx.h>
#include <string>
#include "analyzer.hpp"


extern "C" void DMA2_Stream0_IRQHandler()
{
    if (DMA2->LISR & DMA_LISR_TCIF0)
        DMA2->LISR = ~DMA_LISR_TCIF0;

    Analyzer::tranceiver.transmit(std::string_view{"Value: "});
    Analyzer::tranceiver.transmit(std::to_string(ADC1->DR));
    Analyzer::tranceiver.transmit(std::string_view{"\n=========\n"});
}

extern "C" void TIM4_IRQHandler()
{
    if (TIM4->SR & TIM_SR_UIF_Msk)
        TIM4->SR &= ~TIM_SR_UIF_Msk;

    GPIOA->ODR ^= GPIO_ODR_OD6_Msk;
}