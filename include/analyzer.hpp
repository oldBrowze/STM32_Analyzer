#pragma once

#include <stm32f4xx.h>
#include <vector>

#include "stm32f4_usart.hpp"
#include "stm32f4_spi.hpp"

extern "C" void TIM3_IRQHandler();
extern "C" void TIM4_IRQHandler();
extern "C" void EXTI0_IRQHandler();
class Analyzer
{
private:
    static inline Driver::USART tranceiver{USART1, 115200};
    static inline char buffer_string[100];

public:
    static void configuration();
    static void debug_led_configuration();
    static void display_configuration();

    friend void ::TIM3_IRQHandler();
    friend void ::TIM4_IRQHandler();
    friend void ::EXTI0_IRQHandler();
    friend int ::main();

};