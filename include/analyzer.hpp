#pragma once

#include <stm32f4xx.h>
#include "stm32f4_usart.h"

#include "ST7735.h"
#include "SPI.h"

#include "ADE7880_config.hpp"
#include "ADE7880_register.hpp"


extern "C" void EXTI0_IRQHandler();
extern "C" void EXTI1_IRQHandler();
extern "C" void EXTI2_IRQHandler();
extern "C" void EXTI3_IRQHandler();
extern "C" void EXTI4_IRQHandler();
extern "C" void EXTI9_5_IRQHandler();
extern "C" void EXTI15_10_IRQHandler();
extern "C" void TIM4_IRQHandler();
extern "C" void USART1_IRQHandler();
extern "C" void ADC_IRQHandler();
extern void _delay_ms(const uint32_t& ms);

class Analyzer
{
private:
    enum IRQ_Priority : uint8_t
    {
        EXTI0_encoder_rotate = 1,
        EXTI2_encoder_button,
        EXTI9_5_ADE_CF,
        EXTI15_10_ADE_IRQ,
        UART_Debug = 15
    };
private:
    Driver::USART debug_bus{USART1, 115200, UART_Debug};

    Driver::SPI &HS_bus;
    Driver::ST7735 &display;
public:

    Analyzer(Driver::SPI &bus, Driver::ST7735 &display);

    /* методы конфигурирования */
    void configuration();
    void pin_configuration();
    void debug_led_configuration();
    void hs_bus_configuration();
    void display_configuration();
    void encoder_configuration();
    void adc_configuration();

    /* общение с ЦОС */
    void CS_set()           { GPIOA->BSRR = GPIO_BSRR_BR12_Msk; }
    void CS_reset()        { GPIOA->BSRR = GPIO_BSRR_BS12_Msk; }

    //uint32_t DSP_receive(const uint16_t& reg_address);

    template<class data_type>
    void DSP_transmit(const uint16_t& reg_address, const data_type& reg_value)
    {
        CS_set();
        _delay_ms(1);

        HS_bus.transmit(REG_WRITE); //нулевой бит - !разрешение на запись (0 - да, 1 - нет)

        //отправка адреса регистра
        
        HS_bus.transmit(reg_address >> 8); // выделение старшего бита
        HS_bus.transmit(reg_address && 0xFF); // младшего

        for(uint8_t i = sizeof(data_type) - 1; i >= 0; i--)
            HS_bus.transmit(reg_value >> (i * 8));    

        CS_reset();    
    }
    /* методы обработки значений */

    /* отладочные методы */
    void getInfo();
public:
    friend void EXTI0_IRQHandler();
    friend void EXTI1_IRQHandler();
    friend void EXTI2_IRQHandler();
    friend void EXTI3_IRQHandler();
    friend void EXTI4_IRQHandler();
    friend void EXTI9_5_IRQHandler();
    friend void EXTI15_10_IRQHandler();
    friend void TIM4_IRQHandler();
    friend void USART1_IRQHandler();
    friend void ADC_IRQHandler();
};