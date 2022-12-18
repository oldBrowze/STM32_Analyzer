#pragma once

#include "stm32f4xx.h"

namespace Driver
{

    /* ST7735 defines */
    #define AO_set()            GPIOA->BSRR = GPIO_BSRR_BS10_Msk
    #define AO_reset()          GPIOA->BSRR = GPIO_BSRR_BR10_Msk
    #define RST_set()           GPIOA->BSRR = GPIO_BSRR_BS11_Msk
    #define RST_reset()         GPIOA->BSRR = GPIO_BSRR_BR11_Msk
    #define ST7735_COMMAND      static_cast<bool>(0x1)
    #define ST7735_DATA         static_cast<bool>(0x0)
    
    class SPI
    {
    private:
        volatile SPI_TypeDef *_SPI_BASE;

    public:
        SPI(volatile SPI_TypeDef *);

        void transmit(const uint8_t &, bool);
        void transmit(const uint8_t &, const uint8_t &);
    };

};