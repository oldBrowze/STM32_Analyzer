#include "stm32_st7735.hpp"

void ST7735::configuration()
{
    pin_configuration();
    /* ST7735 init */
    GPIOA->BSRR = GPIO_BSRR_BR12_Msk; //CS off

    RST_reset();
    _delay_ms(10);
    RST_set();
    _delay_ms(10); 

    transmitter.transmit(0x11, ST7735_COMMAND); // sleep out
    _delay_ms(100);

    transmitter.transmit(0x3A, ST7735_COMMAND); // pixel format
    transmitter.transmit(0b101, ST7735_DATA); // 16bit

    transmitter.transmit(0x29, ST7735_COMMAND); // display on 

    GPIOA->BSRR = GPIO_BSRR_BS12_Msk; //CS on
}

void ST7735::set_x_size(const uint16_t& x_min, const uint16_t& x_max)
{
    transmitter.transmit(0x2A, ST7735_COMMAND); // CASET - ColAdr

    transmitter.transmit((x_min & 0xFF00) >> 8, ST7735_DATA); // x_min = 0
    transmitter.transmit(x_min & 0x00FF, ST7735_DATA); 
    transmitter.transmit((x_max & 0xFF00) >> 8, ST7735_DATA); // x_min = 128
    transmitter.transmit(x_max & 0x00FF, ST7735_DATA);
}

void ST7735::set_y_size(const uint16_t& y_min, const uint16_t& y_max)
{
    transmitter.transmit(0x2B, ST7735_COMMAND); // RASET - RowAdr

    transmitter.transmit((y_min & 0xFF00) >> 8, ST7735_DATA); // x_min = 0
    transmitter.transmit(y_min & 0x00FF, ST7735_DATA); 
    transmitter.transmit((y_max & 0xFF00) >> 8, ST7735_DATA); // x_min = 128
    transmitter.transmit(y_max & 0x00FF, ST7735_DATA);
}

void ST7735::draw_rect(const uint16_t& x_min, const uint16_t& x_max, 
                        const uint16_t& y_min, const uint16_t& y_max, 
                        const uint16_t& color)
{
    GPIOA->BSRR = GPIO_BSRR_BR12_Msk; //CS off

    uint32_t size = (x_max - x_min) * (y_max - y_min);

    set_x_size(x_min, x_max - 1);
    set_y_size(y_min, y_max - 1);

    transmitter.transmit(0x2C, ST7735_COMMAND); // RAMWR

    for(auto pixel = 0ul; pixel < size; pixel++)
    {
        transmitter.transmit((color & 0xFF00) >> 8, ST7735_DATA); //полубайт
        transmitter.transmit(color & 0x00FF, ST7735_DATA); 
    }

    GPIOA->BSRR = GPIO_BSRR_BS12_Msk; //CS on
}
void ST7735::pin_configuration()
{
    // PA10 - ST7735_RESET
    GPIOA->MODER |= (0b01 << GPIO_MODER_MODE10_Pos);
    GPIOA->BSRR = GPIO_BSRR_BS10_Msk; //по умолчанию лог. 1

    // PA11 - ST7735_AO
    GPIOA->MODER |= (0b01 << GPIO_MODER_MODE11_Pos);
    GPIOA->BSRR = GPIO_BSRR_BS11_Msk; //по умолчанию лог. 1


}