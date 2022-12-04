#pragma once

#include <stm32f4xx.h>

#include "stm32f4_usart.hpp"

extern "C" void DMA2_Stream0_IRQHandler();
extern "C" void TIM4_IRQHandler();


/*
*   I1, I2, I3, In
*   Ua Ub Uc Uab Uac Ubc
*   
*
*/
class Analyzer
{
private:
    static constexpr inline uint8_t size_buffer = 4 + 3;
    static inline Driver::USART tranceiver{USART1, 115200};
    static inline std::array<uint16_t, 3> DMA_buffer{0};
public:
    static void configuration();
    static void adc_dma_configuration();
    static void led_configuration();


    friend void ::DMA2_Stream0_IRQHandler();
    friend void ::TIM4_IRQHandler();
    friend int ::main();
};