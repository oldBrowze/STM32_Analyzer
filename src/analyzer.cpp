#include "analyzer.hpp"


Analyzer::Analyzer(Driver::SPI &bus, Driver::ST7735 &display) : HS_bus{bus}, display{display}
{

}

void Analyzer::configuration()
{
    //debug_led_configuration();
    hs_bus_configuration();
    //display_configuration();
    pin_configuration();
    //adc_configuration();
}

void Analyzer::pin_configuration()
{
    /* входы */

    /* 
    *  конфигурация ног для чтения энкодера(входы)
    *  PA0 - ENC_A | PA1 - ENC_B | PA2 - ENC_KEY
    */
    GPIOA->MODER |= (0b00 << GPIO_MODER_MODE0_Pos) | (0b00 << GPIO_MODER_MODE1_Pos) | (0b00 << GPIO_MODER_MODE2_Pos);
    GPIOA->PUPDR |= (0b01 << GPIO_PUPDR_PUPD0_Pos) | (0b01 << GPIO_PUPDR_PUPD1_Pos) | (0b01 << GPIO_PUPDR_PUPD2_Pos);

    /* 
    *  конфигурация ног для чтения энкодера(входы)
    *  PA3 - KEY1 | PA4 - KEY2 | PA5 - KEY3
    */
    //GPIOA->MODER |= (0b00 << GPIO_MODER_MODE3_Pos) | (0b00 << GPIO_MODER_MODE4_Pos) | (0b00 << GPIO_MODER_MODE5_Pos);
    //GPIOA->PUPDR |= (0b01 << GPIO_PUPDR_PUPD3_Pos) | (0b01 << GPIO_PUPDR_PUPD4_Pos) | (0b01 << GPIO_PUPDR_PUPD5_Pos);
    //EXTI->IMR |= EXTI_IMR_MR3_Msk | EXTI_IMR_MR4_Msk | EXTI_IMR_MR5_Msk;
    //EXTI->RTSR |= EXTI_RTSR_TR3_Msk | EXTI_RTSR_TR4_Msk | EXTI_RTSR_TR5_Msk;
    
    
    //ADE: IRQ0, IRQ1, CF1, CF2, CF3

    //CF3 - PB1, IRQ0 - PB8, IRQ1 - PB9
    GPIOB->MODER |= (0b00 << GPIO_MODER_MODE1_Pos) | (0b00 << GPIO_MODER_MODE8_Pos) | (0b00 << GPIO_MODER_MODE9_Pos);
    GPIOB->PUPDR |= (0b01 << GPIO_PUPDR_PUPD1_Pos) | (0b01 << GPIO_PUPDR_PUPD8_Pos) | (0b01 << GPIO_PUPDR_PUPD9_Pos);
    //CF1 - PA6, CF2 - PA7
    GPIOA->MODER |= (0b00 << GPIO_MODER_MODE6_Pos) | (0b00 << GPIO_MODER_MODE7_Pos);
    GPIOA->PUPDR |= (0b01 << GPIO_PUPDR_PUPD6_Pos) | (0b01 << GPIO_PUPDR_PUPD7_Pos);

    //подтяжка кнопок +пит
    GPIOA->PUPDR |= (0b01 << GPIO_PUPDR_PUPD0_Pos) | (0b01 << GPIO_PUPDR_PUPD1_Pos) |\
                    (0b01 << GPIO_PUPDR_PUPD2_Pos) | (0b01 << GPIO_PUPDR_PUPD5_Pos) |\
                    (0b10 << GPIO_PUPDR_PUPD8_Pos) | (0b10 << GPIO_PUPDR_PUPD9_Pos);

    EXTI->IMR |= EXTI_IMR_MR0_Msk | EXTI_IMR_MR1_Msk | EXTI_IMR_MR2_Msk | EXTI_IMR_MR6_Msk | 
                    EXTI_IMR_MR7_Msk | EXTI_IMR_MR8_Msk | EXTI_IMR_MR9_Msk;
    EXTI->FTSR |= EXTI_FTSR_TR0_Msk | EXTI_FTSR_TR1_Msk | EXTI_FTSR_TR2_Msk | EXTI_FTSR_TR6_Msk | EXTI_FTSR_TR7_Msk;
    EXTI->RTSR |= EXTI_FTSR_TR8_Msk | EXTI_RTSR_TR9_Msk;

    NVIC_EnableIRQ(EXTI0_IRQn);
    NVIC_EnableIRQ(EXTI1_IRQn);
    NVIC_EnableIRQ(EXTI2_IRQn);
    //NVIC_EnableIRQ(EXTI3_IRQn);
    //NVIC_EnableIRQ(EXTI4_IRQn);
    NVIC_EnableIRQ(EXTI9_5_IRQn);
    //NVIC_EnableIRQ(EXTI15_10_IRQn);

    NVIC_SetPriority(EXTI0_IRQn, IRQ_Priority::EXTI0_encoder_rotate);
    NVIC_SetPriority(EXTI1_IRQn, IRQ_Priority::EXTI9_5_ADE_CF);
    NVIC_SetPriority(EXTI2_IRQn, IRQ_Priority::EXTI2_encoder_button);
    NVIC_SetPriority(EXTI9_5_IRQn, IRQ_Priority::EXTI9_5_ADE_CF);
    //VIC_SetPriority(EXTI15_10_IRQn, IRQ_Priority::EXTI15_10_ADE_IRQ);

    SYSCFG->EXTICR[0] |= SYSCFG_EXTICR1_EXTI0_PA | SYSCFG_EXTICR1_EXTI1_PB | SYSCFG_EXTICR1_EXTI2_PA | SYSCFG_EXTICR1_EXTI3_PA;
    SYSCFG->EXTICR[1] |= SYSCFG_EXTICR2_EXTI4_PA | SYSCFG_EXTICR2_EXTI5_PA | SYSCFG_EXTICR2_EXTI6_PA | SYSCFG_EXTICR2_EXTI7_PA;
    SYSCFG->EXTICR[2] |= SYSCFG_EXTICR3_EXTI8_PB | SYSCFG_EXTICR3_EXTI9_PB;

    /* выходы */

    /*
        DISPLAY_CS - PA12
        FLASH_CS - PB6
        ADE_RESET - PB10
        FLASH_WP - PB14
        FLASH_HOLD - PB15
    */
    GPIOB->MODER |= (0b01 << GPIO_MODER_MODE6_Pos) | (0b01 << GPIO_MODER_MODE10_Pos) | (0b01 << GPIO_MODER_MODE14_Pos) | (0b01 << GPIO_MODER_MODE15_Pos);
    GPIOB->BSRR = (0b01 << GPIO_MODER_MODE6_Pos) | GPIO_BSRR_BS10_Msk | GPIO_BSRR_BS14_Msk | GPIO_BSRR_BS15_Msk; //по умолчанию лог. 1


}

void Analyzer::hs_bus_configuration()
{
    using namespace Driver;
    using namespace SPI_Settings;

    HS_bus.pin_config();
    HS_bus.config(CR1::BR_DIV_16 | CR1::BIDIMODE | 
                        CR1::BIDIOE | CR1::MSTR |
                        CR1::SSI | CR1::SSM, 0x0);
    
    HS_bus.enable();
}

void Analyzer::display_configuration()
{
    display.configuration();
}

void Analyzer::debug_led_configuration()
{

    //NVIC_EnableIRQ(TIM3_IRQn);
    //NVIC_SetPriority(TIM3_IRQn, 15);

    NVIC_EnableIRQ(TIM4_IRQn);
    NVIC_SetPriority(TIM4_IRQn, 5);

    //TIM4->DIER |= TIM_DIER_UIE; //прерывание 1 кгЦ
    //TIM4->ARR = 84 - 1;
    //TIM4->PSC = 10 - 1;

    //TIM4->CR2 |= (0b010) << TIM_CR2_MMS_Pos;
    //TIM4->EGR |= TIM_EGR_UG;
    //TIM4->CR1 |= TIM_CR1_CEN;


    TIM4->DIER |= TIM_DIER_UIE; //прерывание
    TIM4->ARR = 10000 - 1;
    TIM4->PSC = 8400 - 1;

    TIM4->EGR |= TIM_EGR_UG;
    TIM4->CR1 |= TIM_CR1_CEN;

    GPIOA->MODER |= 0b01 << GPIO_MODER_MODE6_Pos;
    GPIOA->PUPDR |= 0b10 << GPIO_PUPDR_PUPD6_Pos;
}

void Analyzer::adc_configuration()
{
    NVIC_EnableIRQ(ADC_IRQn);

    ADC1->CR2 = ADC_CR2_ADON;
    ADC1->CR1 = ADC_CR1_EOCIE;
    ADC1->SMPR2 = (0b111 << ADC_SMPR2_SMP8_Pos); //PB0 480 cycles
    ADC1->SQR3 = (8 << ADC_SQR3_SQ1_Pos);

    GPIOB->MODER |= (0b11 << GPIO_MODER_MODE0_Pos); //PB0 as analog
    //ADC1->CR2 = ADC_CR2_SWSTART;
}

void Analyzer::getInfo()
{
    static char buffer[1000];
    snprintf(buffer, sizeof buffer, "Voltage A: %lu\n \
                                    Voltage B: %lu\n \
                                    Voltage C: %lu\n \
                                    Current A: %lu\n \
                                    Current B: %lu\n \
                                    Current C: %lu\n \
                                    aPower A: %lu\n \
                                    aPower B: %lu\n \
                                    aPower C: %lu\n ", 1UL, 1UL, 1UL, 1UL, 1UL, 1UL, 1UL, 1UL, 1UL);
    debug_bus.transmit(buffer);
}

/*
uint32_t Analyzer::DSP_receive(const uint16_t& reg_address)
{
    HS_bus.transmit(0x1); //чтение
    
    HS_bus.transmit(reg_address >> 8); 
    HS_bus.transmit(reg_address && 0xFF);

    Прием в  регистр
    return value
}
*/