/*
 * st_utils.c
 *
 *  Created on: Nov 21, 2018
 *      Author: Andrey Gramakov
 */

#include "st_utils.h"


void Util_InitGpioClock(GPIO_TypeDef* gpio)
{
    switch ((uint32_t) gpio)
    {
        case (uint32_t) GPIOA:
            __GPIOA_CLK_ENABLE()
                                ;
            return;
        case (uint32_t) GPIOB:
            __GPIOB_CLK_ENABLE()
                                ;
            return;
        case (uint32_t) GPIOC:
            __GPIOC_CLK_ENABLE()
                                ;
            return;
        case (uint32_t) GPIOD:
            __GPIOD_CLK_ENABLE()
                                ;
            return;
        default:
            return;
    }
}
void Util_InitTicksCounter()
{
    CoreDebug->DEMCR = CoreDebug_DEMCR_TRCENA_Msk; // enable tracing
    DWT->CYCCNT = 0; // reset
    DWT->CTRL |= DWT_CTRL_CYCCNTENA_Msk; //enable counter
}

void Util_Delay_us(uint32_t us)
{
    uint32_t t0 = DWT->CYCCNT;
    SystemCoreClockUpdate();
    uint32_t us_count_tic = us * (SystemCoreClock / 1000000);
    while ((DWT->CYCCNT) < us_count_tic + t0 )
        ;
}

uint32_t Util_GetUpTime_ms()
{
    return (DWT->CYCCNT / (SystemCoreClock / 1000));
}

uint32_t Util_GetUpTime_us()
{
    return (DWT->CYCCNT / (SystemCoreClock / 1000000));
}

