/*
 * st_utils.c
 *
 *  Created on: Nov 21, 2018
 *      Author: Andrey Gramakov
 */

#include <sf_utils.h>

// TODO: remove this
/***
 * \brief
 * @param gpio
 */
void SF_InitGpioClock(GPIO_TypeDef* gpio)
{
    switch ((uint32_t)gpio)
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

/**
 * @author     Andrey Gramakov
 * @brief      Using base address pointer trying to execute matched HAL macros to enable clock. Currently GPIO and TIM are implemented.
 *
 * @param      PERIPH_ADDR_BASE  The periph addr base
 */
void SF_EnableClock(uint32_t* PERIPH_ADDR_BASE)
{
    switch ((uint32_t)PERIPH_ADDR_BASE)
    {
//
// GPIO
//
#       ifdef GPIOA_BASE
        case GPIOA_BASE:
            __HAL_RCC_GPIOA_CLK_ENABLE()
                                ;
            return;
#       endif

#       ifdef GPIOB_BASE
        case GPIOB_BASE:
            __HAL_RCC_GPIOB_CLK_ENABLE()
                                ;
            return;
#       endif

#       ifdef GPIOC_BASE
        case GPIOC_BASE:
            __HAL_RCC_GPIOC_CLK_ENABLE()
                                ;
            return;
#       endif

#       ifdef GPIOD_BASE
        case GPIOD_BASE:
            __HAL_RCC_GPIOD_CLK_ENABLE()
                                ;
            return;
#       endif

#       ifdef GPIOE_BASE
        case GPIOE_BASE:
            __HAL_RCC_GPIOE_CLK_ENABLE()
                                ;
            return;
#      endif

#       ifdef GPIOF_BASE
            case GPIOF_BASE:
            __HAL_RCC_GPIOF_CLK_ENABLE()
            ;
            return;
#      endif

#       ifdef GPIOG_BASE
            case GPIOG_BASE:
            __HAL_RCC_GPIOG_CLK_ENABLE()
            ;
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
            __HAL_RCC_TIM2_CLK_ENABLE()
                                ;
            return;
#       endif

#       ifdef TIM3_BASE
        case TIM3_BASE:
            __HAL_RCC_TIM3_CLK_ENABLE()
                                ;
            return;
#       endif

#       ifdef TIM4_BASE
        case TIM4_BASE:
            __HAL_RCC_TIM4_CLK_ENABLE()
                                ;
            return;
#       endif

#       ifdef TIM5_BASE
        case TIM5_BASE:
            __HAL_RCC_TIM5_CLK_ENABLE()
                                ;
            return;
#       endif

#       ifdef TIM6_BASE
        case TIM6_BASE:
            __HAL_RCC_TIM6_CLK_ENABLE()
                                ;
            return;
#       endif

#       ifdef TIM7_BASE
        case TIM7_BASE:
            __HAL_RCC_TIM7_CLK_ENABLE()
                                ;
            return;
#       endif

#       ifdef TIM8_BASE
            case TIM8_BASE:
            __HAL_RCC_TIM8_CLK_ENABLE();
            return;
#      endif

#       ifdef TIM9_BASE
        case TIM9_BASE:
            __HAL_RCC_TIM9_CLK_ENABLE()
                                ;
            return;
#       endif

#       ifdef TIM10_BASE
        case TIM10_BASE:
            __HAL_RCC_TIM10_CLK_ENABLE()
                                ;
            return;
#       endif

#       ifdef TIM11_BASE
        case TIM11_BASE:
            __HAL_RCC_TIM11_CLK_ENABLE()
                                ;
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


uint32_t SF_GetArrAverage(uint32_t* array, uint32_t arr_size)
{
    uint32_t sum = 0;
    for (int i = 0; i < arr_size; i++)
    {
        sum += array[i];
    }
    return (sum / arr_size);
}

uint32_t SF_LinInterp(uint32_t x, uint32_t x0, uint32_t y0, uint32_t x1, uint32_t y1)
{
    /*(y - y0) / (x - x0) = (y1 - y0) / (x1 - x0)
     * v
     * y = y0 + (x - x0) * (y1 - y0) / (x1 - x0)
     * */
    return ( y0 + (x - x0) * (y1 - y0) / (x1 - x0) );
}
