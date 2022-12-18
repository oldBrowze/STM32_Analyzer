#include <stm32f4xx.h>
#include <stm32f4_usart.hpp>

#include "pll_configuration.hpp"
#include "rcc_configuration.hpp"
#include "analyzer.hpp"
#include "stm32_st7735.hpp"

int main()
{
    __enable_irq();

    /* SysTick delay init */
    NVIC_EnableIRQ(SysTick_IRQn);
    SysTick_Config(SystemCoreClock / 1000); // 1 ms

    Analyzer::configuration();
    ST7735::configuration();

    while(true)
    {
        ST7735::draw_rect(0, 128, 0, 160, 0xF800);
        ST7735::_delay_ms(100);

        ST7735::draw_rect(0, 128, 0, 160, 0x07E0);
        ST7735::_delay_ms(100);

        ST7735::draw_rect(0, 128, 0, 160, 0x001F);
        ST7735::_delay_ms(100);

        ST7735::draw_rect(0, 128, 0, 160, 0xFFE0);
        ST7735::_delay_ms(100);

        ST7735::draw_rect(0, 128, 0, 160, 0xFFFF);
        ST7735::_delay_ms(100);

        ST7735::draw_rect(0, 128, 0, 160, 0x0000);
        ST7735::_delay_ms(100);

        ST7735::draw_rect(0, 128, 0, 160, 0xFA20);
        ST7735::_delay_ms(100);
    }
}