#pragma once

#include <cstdint>
#include <stm32f4xx.h>

namespace Driver
{
namespace SPI_Settings
{
    /* settings based on SPI->CR1 */
    enum CR1 : std::uint32_t
    {
        BIDIMODE        = SPI_CR1_BIDIMODE,
        BR_DIV_256      = (0b111 << SPI_CR1_BR_Pos),
        BR_DIV_2        = (0b000 << SPI_CR1_BR_Pos),
        BR_DIV_16       = (0b011 << SPI_CR1_BR_Pos),
        LSBFIRST        = SPI_CR1_LSBFIRST,
        BIDIOE          = SPI_CR1_BIDIOE,
        MSTR            = SPI_CR1_MSTR,
        SSI             = SPI_CR1_SSI,
        SSM             = SPI_CR1_SSM,
        DFF             = SPI_CR1_DFF
    };

    /* settings based on SPI->CR2 */
    enum CR2 : std::uint32_t
    {
        empty
    };
};

class SPI
{
public:
private:
    using SPI_t = SPI_TypeDef*;
protected:
    std::uint32_t base;
    SPI_t periph;
public:
    SPI(std::uint32_t SPI_BASE);
    
    void enable();
    void disable();

    void config(std::uint32_t settings1, std::uint32_t settings2);
    void transmit(const uint8_t&);  
    const uint8_t receive();
    void pin_config();
};
};