#include "SPI.h"

Driver::SPI::SPI(std::uint32_t SPI_BASE) : base{SPI_BASE}, periph{reinterpret_cast<SPI_t>(SPI_BASE)}
{
    GPIOA->BSRR = GPIO_BSRR_BS12_Msk;
}

void Driver::SPI::enable()
{
    periph->CR1 |= SPI_CR1_SPE;
}

void Driver::SPI::disable()
{
    periph->CR1 &= ~SPI_CR1_SPE;
}

void Driver::SPI::config(std::uint32_t settings1, std::uint32_t settings2)
{
    
    /* periph->CR1 |= (0b111 << SPI_CR1_BR_Pos) |
                        SPI_CR1_BIDIMODE |
                        //SPI_CR1_LSBFIRST |
                        SPI_CR1_BIDIOE |
                        SPI_CR1_MSTR |
                        SPI_CR1_SSI |
                        SPI_CR1_DFF |
                        SPI_CR1_SSM; */
    
    periph->CR1 |= settings1;
    periph->CR2 |= settings2;
    //periph->CR1 |= SPI_CR1_SPE;
}

uint8_t Driver::SPI::receive()
{
    uint8_t value = 0;
    while(SPI1->SR & SPI_SR_BSY);
    while(!(SPI1->SR & SPI_SR_RXNE));

    value = SPI1->DR;

    return value;
}

void Driver::SPI::transmit(const uint8_t& _data)
{
    while (!(periph->SR & SPI_SR_TXE));

    periph->DR = _data;

    while(!(periph->SR & SPI_SR_TXE)); // пока SPI занят
    while (periph->SR & SPI_SR_BSY);
}
void Driver::SPI::pin_config()
{
    if (base == SPI1_BASE)
    {
        /*
        // PA12 - SPI1_CS
        GPIOA->MODER |= (0b01 << GPIO_MODER_MODE12_Pos);
        GPIOA->BSRR = GPIO_BSRR_BS12_Msk; //по умолчанию лог. 1
        // GPIOA->OSPEEDR |= (0b11 << GPIO_OSPEEDR_OSPEED15_Pos);
        // GPIOA->BSRR = GPIO_BSRR_BS15;
        */
        // PB3 - SPI1_SCK
        GPIOB->MODER |= (0b10 << GPIO_MODER_MODER3_Pos);
        GPIOB->AFR[0] |= (0b101 << GPIO_AFRL_AFSEL3_Pos);
        GPIOB->OSPEEDR |= (0b11 << GPIO_OSPEEDR_OSPEED3_Pos);

        // PB4 - SPI1_MISO
        GPIOB->MODER |= (0b10 << GPIO_MODER_MODER4_Pos);
        GPIOB->AFR[0] |= (0b101 << GPIO_AFRL_AFSEL4_Pos);
        GPIOB->OSPEEDR |= (0b11 << GPIO_OSPEEDR_OSPEED5_Pos);

        // PB5 - SPI1_MOSI
        GPIOB->MODER |= (0b10 << GPIO_MODER_MODER5_Pos);
        GPIOB->AFR[0] |= (0b101 << GPIO_AFRL_AFSEL5_Pos);
        GPIOB->OSPEEDR |= (0b11 << GPIO_OSPEEDR_OSPEED5_Pos);
    }

}
