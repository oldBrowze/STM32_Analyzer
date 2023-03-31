#include "stm32f4_usart.h"

namespace Driver
{
    
    USART::USART(volatile USART_TypeDef* uart_base, const uint32_t& baudrate, const uint8_t& interrupt_priority) : _base{uart_base}, _baudrate{baudrate}
    {
        uart_base->CR1 = USART_CR1_UE_Msk;
        uart_base->BRR = 84'000'000 / baudrate;
        uart_base->CR1 |= USART_CR1_TE_Msk | USART_CR1_RE_Msk | USART_CR1_RXNEIE_Msk;

        NVIC_EnableIRQ(USART1_IRQn);
        NVIC_SetPriority(USART1_IRQn, interrupt_priority);
        pin_configuration();
    }
    
    inline void USART::pin_configuration()
    {
        //TODO:на каждый uart свой пин сделать

        //PA9 - Tx,  PA10 - Rx
        
        GPIOA->MODER |= (0b10 << GPIO_MODER_MODER9_Pos) | (0b10 << GPIO_MODER_MODER10_Pos);
        GPIOA->AFR[1] |= (0b111 << GPIO_AFRH_AFSEL9_Pos) | (0b111 << GPIO_AFRH_AFSEL10_Pos);
/*
        // PB6 - Tx 

        GPIOB->MODER |= (0b10 << GPIO_MODER_MODER6_Pos);
        GPIOB->AFR[0] |= (0b111 << GPIO_AFRL_AFSEL6_Pos);
*/
    }
    
    void USART::transmit(const uint8_t& message)
    {
        _base->DR = static_cast<uint8_t>(message);
        while((_base->SR & USART_SR_TXE) == false);
    }

    void USART::transmit(const std::string_view message)
    {
        for(const auto &i : message)
        {
            _base->DR = static_cast<uint8_t>(i);
            while((_base->SR & USART_SR_TXE) == false);
        }
    }
    
    template<uint8_t size> 
    void USART::transmit(const std::array<uint8_t, size>& message)
    {
        for(const auto &i : message)
        {
            _base->DR = static_cast<uint8_t>(i);
            while((_base->SR & USART_SR_TXE) == false);
        }
    }
}