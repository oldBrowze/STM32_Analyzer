#pragma once

#include <stm32f4xx.h>
#include "stm32f4_usart.h"

#include "ST7735.h"
#include "SPI.h"


class Analyzer
{
private:
    enum IRQ_Priority : uint8_t
    {
        EXTI0_encoder_rotate,
        EXTI2_encoder_button,
        EXTI9_5_ADE_CF,
        EXTI15_10_ADE_IRQ
    };
private:
    Driver::USART tranceiver{USART1, 115200};

    Driver::SPI &HS_bus;
    Driver::ST7735 &display;
public:

    Analyzer(Driver::SPI &bus, Driver::ST7735 &display);

    void configuration();
    void pin_configuration();
    void debug_led_configuration();
    void hs_bus_configuration();
    void display_configuration();
    void encoder_configuration();
};