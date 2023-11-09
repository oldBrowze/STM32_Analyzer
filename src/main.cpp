//CMSIS-based
#include <stm32f4xx.h>

//Hardware init
#include "pll_configuration.hpp"
#include "rcc_configuration.hpp"

volatile uint32_t __ticks = 0;
void _delay_ms(const uint32_t& ms)
{
    uint32_t current = __ticks;
    while((__ticks - current) <= ms);
}

void systick_enable()
{
    NVIC_EnableIRQ(SysTick_IRQn);
    SysTick_Config(84'000'000ul / 1000); // 1 ms
}

//drivers
#include "SPI.h"
#include "ST7735.h"
#include "analyzer.hpp"

/*  global objects */
Driver::SPI data_bus{SPI1_BASE}; //todo: на тестирование
Driver::ST7735 display{data_bus, 128, 160};
Analyzer analyzer{data_bus, display};

/// @brief debug only
void led_debug_enable()
{
    NVIC_EnableIRQ(TIM4_IRQn);
    NVIC_SetPriority(TIM4_IRQn, 15);

    TIM4->DIER |= TIM_DIER_UIE; //прерывание
    TIM4->ARR = 20000 - 1;
    TIM4->PSC = 8400 - 1;

    TIM4->EGR |= TIM_EGR_UG;
    TIM4->CR1 |= TIM_CR1_CEN;

    //GPIOB->MODER |= 0b01 << GPIO_MODER_MODE0_Pos;
    //GPIOB->OTYPER |= 0b1 << GPIO_OTYPER_OT0_Pos;
    //GPIOA->PUPDR |= 0b01 << GPIO_PUPDR_PUPD6_Pos;
}

int main()
{
    //using namespace Driver;
    //using namespace SPI_Settings;
    RCC_enable();
    __enable_irq();

    systick_enable();
    analyzer.configuration();
    display.pin_configuration();
 
    /*
    data_bus.draw_rect(0, 128, 0, 160, ST7735::color::BLACK);
    _delay_ms(300);

    data_bus.draw_char('F', 160 / 2, 128 / 2, ST7735::color::GREEN, ST7735::color::BLACK);
    */

    while(true)
    {
        /* analyzer.DSP_transmit<uint8_t>(0xABF, 0xAB);
        _delay_ms(10);
        analyzer.DSP_transmit<uint16_t>(0xABF, 0xFADE);
        _delay_ms(10);
        analyzer.DSP_transmit<uint32_t>(0xABF, 0xFADED); */
    }
    return 0;
}