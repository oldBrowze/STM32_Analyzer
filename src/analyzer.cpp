#include "analyzer.hpp"


void Analyzer::configuration()
{
    led_configuration();
    adc_dma_configuration();
}

void Analyzer::led_configuration()
{
    TIM4->DIER |= TIM_DIER_UIE; //прерывание
    TIM4->ARR = 10000 - 1;
    TIM4->PSC = 8400 - 1;

    TIM4->EGR |= TIM_EGR_UG;
    TIM4->CR1 |= TIM_CR1_CEN;

    NVIC_EnableIRQ(TIM4_IRQn);
    NVIC_SetPriority(TIM4_IRQn, 1);

}

void Analyzer::adc_dma_configuration()
{
    /* инициализация DMA для ADC*/
    NVIC_EnableIRQ(DMA2_Stream0_IRQn);
    NVIC_SetPriority(DMA2_Stream0_IRQn, 15);
    
    /* инициализация ADC */
    
    /* конфигурация портов ADC как analog mode
    *  PA1 - ADC_IN1
    *  PA2 - ADC_IN2
    *  PA3 - ADC_IN3
    */
    GPIOA->MODER |= (0b11 << GPIO_MODER_MODE1_Pos) |
                    (0b11 << GPIO_MODER_MODE2_Pos) |
                    (0b11 << GPIO_MODER_MODE3_Pos);

    
    ADC1->CR2 |= ADC_CR2_ADON; // запуск ADC
    ADC1->CR1 |= ADC_CR1_SCAN; // режим сканирования
    ADC1->CR2 |= ADC_CR2_DDS |      // постоянная генерация DMA
                    ADC_CR2_DMA |   // DMA enable
                    ADC_CR2_CONT |  // непрерывное преобразование
                    ADC_CR2_EOCS;   // прерывание по завершению


    ADC1->SMPR2 |= (0b111 << ADC_SMPR2_SMP1_Pos) |
                    (0b111 << ADC_SMPR2_SMP2_Pos) |
                    (0b111 << ADC_SMPR2_SMP3_Pos);

    // Длина последовательности преобразований - 3
    ADC1->SQR1 |= ((0x1 - 1) << ADC_SQR1_L_Pos);


    /*
        1 преобразование - ADC_IN1
        2 преобразование - ADC_IN2
        3 преобразование - ADC_IN3
    */
    ADC1->SQR3 |= (0x1 << ADC_SQR3_SQ1_Pos) |
                    (0x2 << ADC_SQR3_SQ2_Pos) |
                    (0x3 << ADC_SQR3_SQ3_Pos);

    //NVIC_EnableIRQ(ADC_IRQn);

    DMA2_Stream0->NDTR = 1;
    DMA2_Stream0->PAR = reinterpret_cast<std::uintptr_t>(&ADC1->DR);
    DMA2_Stream0->M0AR = reinterpret_cast<std::uintptr_t>(DMA_buffer.data());

    DMA2_Stream0->CR = (0x0 << DMA_SxCR_CHSEL_Pos) |
                    (0b11 << DMA_SxCR_PL_Pos) |
                    (0b01 << DMA_SxCR_MSIZE_Pos) |
                    (0b01 << DMA_SxCR_PSIZE_Pos) |
                    (DMA_SxCR_MINC) |
                    (DMA_SxCR_CIRC) |
                    (0b00 << DMA_SxCR_DIR_Pos) |
                    DMA_SxCR_TCIE;


    /* запуск */
    ADC1->CR2 |= ADC_CR2_SWSTART;
    DMA2_Stream0->CR |= DMA_SxCR_EN;
}