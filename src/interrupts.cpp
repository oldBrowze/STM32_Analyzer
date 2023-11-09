#include <stm32f4xx.h>
#include "analyzer.hpp"


extern Analyzer analyzer; 


extern "C" void USART1_IRQHandler()
{
    if (USART1->SR & USART_SR_RXNE_Msk)
        USART1->SR &= ~USART_SR_RXNE_Msk;

    //analyzer.debug_bus.transmit(USART1->DR);
    static char buffer[100];
    snprintf(buffer, sizeof buffer, "Receive: %c\n", static_cast<int>(USART1->DR)); // исключительно
    analyzer.debug_bus.transmit(buffer);
}

/**
 * @brief Обработчик прерывания TIM4
 * 
 */
extern "C" void TIM4_IRQHandler()
{
    if (TIM4->SR & TIM_SR_UIF_Msk)
        TIM4->SR &= ~TIM_SR_UIF_Msk;

    //GPIOB->ODR ^= GPIO_ODR_OD0;

    //static char buffer[100];
    //snprintf(buffer, sizeof buffer, "TIM4_IRQ");
    analyzer.debug_bus.transmit("TIM4_IRQ\n");
    
    //ADC1->CR2 |= ADC_CR2_SWSTART;
}

/**
 * @brief Обработчик поворота энкодера
 * 
 */
extern "C" void EXTI0_IRQHandler()
{

    if (EXTI->PR & EXTI_PR_PR0_Msk)
    {
        EXTI->PR = EXTI_PR_PR0_Msk;


        if (GPIOA->IDR & GPIO_IDR_ID1) //влево
        {
            analyzer.debug_bus.transmit("EXTI0_left\n");
            //analyzer.DSP_transmit16(0xABD, 0xAD);
        }
        else //вправо
        {
            analyzer.debug_bus.transmit("EXTI0_right\n");
            //analyzer.DSP_transmit32(0xABF, 0xAA);
        }
    }

}

/**
 * @brief Обработчик ADE_CF3
 * 
 */
extern "C" void EXTI1_IRQHandler()
{

    if (EXTI->PR & EXTI_PR_PR1_Msk)
    {
        EXTI->PR = EXTI_PR_PR1_Msk;

        analyzer.debug_bus.transmit("EXTI1\n");
    }
    
}

/**
 * @brief Обработчик нажатия на энкодер
 *
 */
extern "C" void EXTI2_IRQHandler()
{
    if (EXTI->PR & EXTI_PR_PR2_Msk)
    {
        EXTI->PR = EXTI_PR_PR2_Msk;

        analyzer.debug_bus.transmit("EXTI2\n");
        
        analyzer.DSP_transmit<uint8_t>(0xABF, 0xAB);
        _delay_ms(1);
        analyzer.DSP_transmit<uint16_t>(0xABF, 0xFADE);
        _delay_ms(1);
        analyzer.DSP_transmit<uint32_t>(0xABF, 0xFADED);
    }
}

/**
 * @brief Обработчик нажатия на KEY1
 *
 */
extern "C" void EXTI3_IRQHandler()
{
    if (EXTI->PR & EXTI_PR_PR3_Msk)
    {
        EXTI->PR = EXTI_PR_PR3_Msk;

        analyzer.debug_bus.transmit("EXTI3\n");
    }
}

/**
 * @brief Обработчик нажатия на KEY2
 *
 */
extern "C" void EXTI4_IRQHandler()
{
    if (EXTI->PR & EXTI_PR_PR4_Msk)
    {
        EXTI->PR = EXTI_PR_PR4_Msk;

        analyzer.debug_bus.transmit("EXTI4\n");
    }
}

/**
 * @brief Обработчик ADE_CF2, ADE_CF1, KEY3
 *
 */
extern "C" void EXTI9_5_IRQHandler()
{
    //KEY3
    if (EXTI->PR & EXTI_PR_PR5_Msk)
    {
        EXTI->PR = EXTI_PR_PR5_Msk;

        analyzer.debug_bus.transmit("EXTI9_5_KEY3\n");
    }

    //CF1
    if (EXTI->PR & EXTI_PR_PR6_Msk)
    {
        EXTI->PR = EXTI_PR_PR6_Msk;

        analyzer.debug_bus.transmit("EXTI9_5_CF1\n");
    }

    //CF2
    if (EXTI->PR & EXTI_PR_PR7_Msk)
    {
        EXTI->PR = EXTI_PR_PR7_Msk;

        analyzer.debug_bus.transmit("EXTI9_5_CF2\n");
    }

    //IRQ0
    if (EXTI->PR & EXTI_PR_PR8_Msk)
    {
        EXTI->PR = EXTI_PR_PR8_Msk;

        analyzer.debug_bus.transmit("EXTI9_5_IRQ0\n");
    }

    //IRQ1
    if (EXTI->PR & EXTI_PR_PR9_Msk)
    {
        EXTI->PR = EXTI_PR_PR9_Msk;

        analyzer.debug_bus.transmit("EXTI9_5_IRQ1\n");
    }
    
}

/**
 * @brief Обработчик ADE_IRQ0, ADE_IRQ1
 *
 */
extern "C" void EXTI15_10_IRQHandler()
{
    //IRQ0
    if (EXTI->PR & EXTI_PR_PR13_Msk)
    {
        EXTI->PR = EXTI_PR_PR13_Msk;

        analyzer.debug_bus.transmit("EXTI15_10_IRQ0\n");
    }

    //IRQ1
    if (EXTI->PR & EXTI_PR_PR14_Msk)
    {
        EXTI->PR = EXTI_PR_PR14_Msk;

        analyzer.debug_bus.transmit("EXTI15_10_IRQ1\n");
    }
}

/**
 * @brief Обработчик ADC_VCC_CONTROL
 * 
 */
extern "C" void ADC_IRQHandler()
{
    /*
    //if(ADC1->SR & ADC_SR_EOC)
    //    ADC1->SR &= ~ADC_SR_EOC;
    static char buffer[100];
    snprintf(buffer, sizeof buffer, "ADC1 value: %lu\n", ADC1->DR);
    analyzer.debug_bus.transmit(buffer);
    */
}

extern volatile uint32_t __ticks;
extern "C" void SysTick_Handler()
{
    __ticks++;
}
