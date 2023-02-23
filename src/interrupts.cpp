#include <stm32f4xx.h>
//#include "stm32_st7735.hpp"


extern "C" void TIM4_IRQHandler()
{
    if (TIM4->SR & TIM_SR_UIF_Msk)
        TIM4->SR &= ~TIM_SR_UIF_Msk;

    GPIOA->ODR ^= GPIO_ODR_OD6; 
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

        }
        else //вправо
        {

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

    }

    //CF1
    if (EXTI->PR & EXTI_PR_PR6_Msk)
    {
        EXTI->PR = EXTI_PR_PR6_Msk;

    }

    //CF2
    if (EXTI->PR & EXTI_PR_PR7_Msk)
    {
        EXTI->PR = EXTI_PR_PR7_Msk;

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

    }

    //IRQ1
    if (EXTI->PR & EXTI_PR_PR14_Msk)
    {
        EXTI->PR = EXTI_PR_PR14_Msk;

    }
}


extern uint32_t __ticks;
extern "C" void SysTick_Handler()
{
    __ticks++;
}
