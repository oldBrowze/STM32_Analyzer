#include <stm32f4xx.h>
#include <stm32f4_usart.hpp>
#include <array>
#include <string>
#include <cstdlib>
#include <cmath>
#include "pll_configuration.hpp"
#include "rcc_configuration.hpp"
#include "analyzer.hpp"
#include <arm_math.h>

int main()
{
    Clock::enable_PLL();
    __enable_irq();
    Analyzer::configuration();
    while(true)
    {
        
    #if defined __debug__
        for(int i = 0; i < 3; i++)
        {
            Analyzer::tranceiver.transmit(std::string_view{"Value: "});
            Analyzer::tranceiver.transmit(std::to_string(Analyzer::DMA_buffer[i]));
            Analyzer::tranceiver.transmit(std::string_view{"\n"});
        }
    //Analyzer::tranceiver.transmit(std::string_view{"=========\n"});
    #endif

    }
}