/*
 * st_utils.c
 *
 *  Created on: Nov 21, 2018
 *      Author: Andrey Gramakov
 */

#include <sf_utils.h>

void SF_InitGpioClock(GPIO_TypeDef* gpio)
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

void SF_EnableClock(uint32_t* PERIPH_ADDR_BASE)
{
    switch ((uint32_t)PERIPH_ADDR_BASE)
    {
//
// GPIO
//
#       ifdef GPIOA_BASE
        case GPIOA_BASE:
            __HAL_RCC_GPIOA_CLK_ENABLE();
            return;
#       endif

#       ifdef GPIOB_BASE
        case GPIOB_BASE:
            __HAL_RCC_GPIOB_CLK_ENABLE();
            return;
#       endif

#       ifdef GPIOC_BASE
        case GPIOC_BASE:
            __HAL_RCC_GPIOC_CLK_ENABLE();
            return;
#       endif

#       ifdef GPIOD_BASE
        case GPIOD_BASE:
            __HAL_RCC_GPIOD_CLK_ENABLE();
            return;
#       endif

#       ifdef GPIOE_BASE
        case GPIOE_BASE:
            __HAL_RCC_GPIOE_CLK_ENABLE();
            return;
#      endif
//
// Timers
//
#       ifdef TIM0_BASE
        case TIM0_BASE:
            __HAL_RCC_TIM0_CLK_ENABLE();
            return;
#       endif

#       ifdef TIM1_BASE
        case TIM1_BASE:
            __HAL_RCC_TIM1_CLK_ENABLE();
            return;
#       endif

#       ifdef TIM2_BASE
        case TIM2_BASE:
            __HAL_RCC_TIM2_CLK_ENABLE();
            return;
#       endif

#       ifdef TIM3_BASE
        case TIM3_BASE:
            __HAL_RCC_TIM3_CLK_ENABLE();
            return;
#       endif

#       ifdef TIM4_BASE
        case TIM4_BASE:
            __HAL_RCC_TIM4_CLK_ENABLE();
            return;
#       endif

#       ifdef TIM5_BASE
        case TIM5_BASE:
            __HAL_RCC_TIM5_CLK_ENABLE();
            return;
#       endif

#       ifdef TIM6_BASE
        case TIM6_BASE:
            __HAL_RCC_TIM6_CLK_ENABLE();
            return;
#       endif

#       ifdef TIM7_BASE
        case TIM7_BASE:
            __HAL_RCC_TIM7_CLK_ENABLE();
            return;
#       endif

#       ifdef TIM8_BASE
        case TIM8_BASE:
            __HAL_RCC_TIM8_CLK_ENABLE();
            return;
#      endif

#       ifdef TIM9_BASE
        case TIM9_BASE:
            __HAL_RCC_TIM9_CLK_ENABLE();
            return;
#       endif

#       ifdef TIM10_BASE
        case TIM10_BASE:
            __HAL_RCC_TIM10_CLK_ENABLE();
            return;
#       endif

#       ifdef TIM11_BASE
        case TIM11_BASE:
            __HAL_RCC_TIM11_CLK_ENABLE();
            return;
#       endif

#       ifdef TIM12_BASE
        case TIM12_BASE:
            __HAL_RCC_TIM12_CLK_ENABLE();
            return;
#       endif

#       ifdef TIM13_BASE
        case TIM13_BASE:
            __HAL_RCC_TIM13_CLK_ENABLE();
            return;
#       endif

#       ifdef TIM14_BASE
        case TIM14_BASE:
            __HAL_RCC_TIM14_CLK_ENABLE();
            return;
#       endif

        default:
            return;
    }
}

void SF_InitDelay_us()
{
    CoreDebug->DEMCR = CoreDebug_DEMCR_TRCENA_Msk; // enable tracing
    DWT->CYCCNT = 0; // reset
    DWT->CTRL |= DWT_CTRL_CYCCNTENA_Msk; //enable counter
}

void SF_Delay_us(uint32_t us)
{
    uint32_t t0 = DWT->CYCCNT;
    SystemCoreClockUpdate();
    uint32_t us_count_tic = us * (SystemCoreClock / 1000000);
    while ((DWT->CYCCNT) < us_count_tic + t0)
        ;
}

uint32_t SF_GetUpTime_ms()
{
    return (DWT->CYCCNT / (SystemCoreClock / 1000));
}

uint32_t SF_GetUpTime_us()
{
    return (DWT->CYCCNT / (SystemCoreClock / 1000000));
}

