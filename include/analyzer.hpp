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
extern "C" void SysTick_Handler();
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

    uint8_t encoder;
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
    void DSP_configuration();

    /* общение с ЦОС */
    void CS_set() noexcept      { GPIOA->BSRR = GPIO_BSRR_BR8_Msk; }
    void CS_reset() noexcept    { GPIOA->BSRR = GPIO_BSRR_BS8_Msk; }

    /// @brief low - именно на ADE7880
    void RST_low()      { GPIOB->BSRR = GPIO_BSRR_BS10_Msk; }
    /// @brief high - именно на ADE7880
    void RST_high()    { GPIOB->BSRR = GPIO_BSRR_BR10_Msk; }
    void SPI_choose()
    {
        for(uint8_t i = 0; i < 3; i++)
        {
            CS_set();
            _delay_ms(10);
            CS_reset();
            _delay_ms(10);
        }
    }

    template<class data_type>
    uint8_t DSP_receive_8(const data_type& reg_address)
    {
        uint8_t value = 0;
        Analyzer::CS_set();
        GPIOA->BSRR = GPIO_BSRR_BR12_Msk;

        HS_bus.transmit(REG_WRITE); //нулевой бит - !разрешение на запись (0 - да, 1 - нет)

        //отправка адреса регистра
        HS_bus.transmit(reg_address >> 8); // выделение старшего бита
        HS_bus.transmit(reg_address & 0xFF); // младшего

        value = HS_bus.receive(); // прием 8 битного значения


        Analyzer::CS_reset();
        GPIOA->BSRR = GPIO_BSRR_BS12_Msk; 

        return value;
    }

    template<class data_type>
    uint16_t DSP_receive_16(const data_type& reg_address)
    {
        uint8_t 
            value1 = 0,
            value2 = 0;
        Analyzer::CS_set();
        GPIOA->BSRR = GPIO_BSRR_BR12_Msk;

        HS_bus.transmit(REG_WRITE); //нулевой бит - !разрешение на запись (0 - да, 1 - нет)

        //отправка адреса регистра
        HS_bus.transmit(reg_address >> 8); // выделение старшего бита
        HS_bus.transmit(reg_address & 0xFF); // младшего

        value1 = HS_bus.receive(); // прием 8 битного значения
        value2 = HS_bus.receive();

        Analyzer::CS_reset();
        GPIOA->BSRR = GPIO_BSRR_BS12_Msk; 

        return ((value1 << 8) | value2);
    }

    template<class data_type>
    uint32_t DSP_receive_32(const data_type& reg_address)
    {
        uint8_t 
            value1 = 0,
            value2 = 0,
            value3 = 0,
            value4 = 0;
        Analyzer::CS_set();
        GPIOA->BSRR = GPIO_BSRR_BR12_Msk;

        HS_bus.transmit(REG_WRITE); //нулевой бит - !разрешение на запись (0 - да, 1 - нет)

        //отправка адреса регистра
        HS_bus.transmit(reg_address >> 8); // выделение старшего бита
        HS_bus.transmit(reg_address & 0xFF); // младшего

        value1 = HS_bus.receive(); // прием 8 битного значения
        value2 = HS_bus.receive();
        value3 = HS_bus.receive();
        value4 = HS_bus.receive();


        Analyzer::CS_reset();
        GPIOA->BSRR = GPIO_BSRR_BS12_Msk; 

        return ((value1 << 24) | (value2 << 16) | (value3 << 8) | value4);
    }

    template<class data_type>
    void DSP_transmit(const uint16_t& reg_address, const data_type& reg_value)
    {
        Analyzer::CS_set();
        GPIOA->BSRR = GPIO_BSRR_BR12_Msk;

        HS_bus.transmit(REG_WRITE); //нулевой бит - !разрешение на запись (0 - да, 1 - нет)

        //отправка адреса регистра

        HS_bus.transmit(reg_address >> 8); // выделение старшего бита
        HS_bus.transmit(reg_address & 0xFF); // младшего

        for(int8_t i = sizeof(data_type) - 1; i >= 0; i--)
            HS_bus.transmit(reg_value >> (i * 8));    
        
        Analyzer::CS_reset();
        GPIOA->BSRR = GPIO_BSRR_BS12_Msk; 
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
    friend void SysTick_Handler();
    friend int main();
};