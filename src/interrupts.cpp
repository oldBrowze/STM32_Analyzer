#include <stm32f4xx.h>
#include "analyzer.hpp"


extern Analyzer analyzer; 


extern "C" void TIM4_IRQHandler()
{
    if (TIM4->SR & TIM_SR_UIF_Msk)
        TIM4->SR &= ~TIM_SR_UIF_Msk;

    GPIOB->ODR ^= GPIO_ODR_OD0;
    //analyzer.debug_bus.transmit("TIM4\n");
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
        }
        else //вправо
        {
            analyzer.debug_bus.transmit("EXTI0_right\n");
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


extern uint32_t __ticks;
extern "C" void SysTick_Handler()
{
    __ticks++;
}
