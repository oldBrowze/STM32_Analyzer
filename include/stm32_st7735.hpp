#pragma once
#include <stm32f4xx.h>

#include "stm32f4_spi.hpp"

extern "C" void SysTick_Handler();
extern "C" void TIM4_IRQHandler();

class ST7735
{
private:
    static inline uint8_t
        x_max = 128,
        x_min = 0,
        y_max = 160,
        y_min = 0;
private:
    static inline Driver::SPI transmitter{SPI1};
    static volatile inline uint32_t __ticks = 0;

public:

    static void configuration();
    static void pin_configuration();
    
    static void set_x_size(const uint16_t&, const uint16_t&);
    static void set_y_size(const uint16_t&, const uint16_t&);
    static void draw_rect(const uint16_t&, const uint16_t&, const uint16_t&, const uint16_t&, const uint16_t&);

    static inline void _delay_ms(const uint32_t& ms)
    {
        uint32_t current = __ticks;
        while((__ticks - current) <= ms);
    }

public:
    friend void ::SysTick_Handler();
    friend void ::TIM4_IRQHandler();
};