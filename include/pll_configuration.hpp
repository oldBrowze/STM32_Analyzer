#include <stm32f4xx.h>

#define HSE_VALUE 8000000UL
#define HSI_VALUE 16000000UL

namespace Clock
{
    constexpr uint32_t
        PLL_M = 25, 
        PLL_N = 168, 
        PLL_P = 2,
        PLL_Q = 4;
    /**
     * @brief 
     * Установка тактирования от PLL(HSE) с заданными коэффициентами
     */


    __attribute__((constructor(101))) void enable_PLL()
    {
        /* Запускаем HSE */
        RCC->CR |= RCC_CR_HSEON;
        while(!(RCC->CR & RCC_CR_HSERDY));

        RCC->CFGR |= RCC_CFGR_HPRE_DIV1 |   // делитель шины AHB 
                    RCC_CFGR_PPRE1_DIV2 |   // делитель шины APB1
                    RCC_CFGR_PPRE2_DIV1;    // делитель шины APB2

        /* Определяем коэффициенты и устанавливаем источник PLL - HSE */
        RCC->PLLCFGR = (PLL_M << RCC_PLLCFGR_PLLM_Pos) | 
                    (PLL_N << RCC_PLLCFGR_PLLN_Pos) |
                    (((PLL_P >> 1) - 1) << RCC_PLLCFGR_PLLP_Pos) |
                    RCC_PLLCFGR_PLLSRC_HSE |
                    (PLL_Q << RCC_PLLCFGR_PLLQ_Pos);

        /* Активируем PLL */
        RCC->CR |= RCC_CR_PLLON;
        while ((RCC->CR & RCC_CR_PLLRDY) == 0);

         /* Настраиваем FLASH - 2 WS */
        FLASH->ACR |= FLASH_ACR_PRFTEN | FLASH_ACR_ICEN | FLASH_ACR_DCEN | FLASH_ACR_LATENCY_2WS;

        /* Переключаемся на PLL */
        RCC->CFGR &= ~RCC_CFGR_SW;
        RCC->CFGR |= RCC_CFGR_SW_PLL;
        while (!(RCC->CFGR & RCC_CFGR_SWS));


        SystemCoreClockUpdate();
    }
}