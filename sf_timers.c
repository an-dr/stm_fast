/*
 * timers_tool.c
 *
 *  Created on: Nov 27, 2018
 *      Author: Andrey Gramakov
 */

#include <sf_timers.h>

TIM_HandleTypeDef tim_handler;

void SF_TimerInit_Polling(TIM_TypeDef* timer2init, uint32_t reload_val,
                            uint32_t prescaler)
{
    tim_handler.Instance = timer2init;
    tim_handler.Init.ClockDivision = 1;
    tim_handler.Init.CounterMode = TIM_COUNTERMODE_UP;
    tim_handler.Init.Period = reload_val;
    tim_handler.Init.Prescaler = prescaler;
    SF_EnableClock((uint32_t*) tim_handler.Instance); //enable clock
    //
    HAL_TIM_Base_Init(&tim_handler);
    HAL_TIM_Base_Start(&tim_handler);

}

static void EnableTimerIRQ(uint32_t* PERIPH_ADDR_BASE)
{
    switch ((uint32_t)PERIPH_ADDR_BASE)
    {
#       ifdef TIM0_BASE
        case TIM0_BASE:
        HAL_NVIC_EnableIRQ(TIM0_IRQn);
        return;
#       endif

#       ifdef TIM1_BASE
        case TIM1_BASE:
        HAL_NVIC_EnableIRQ(TIM1_IRQn);
        return;
#       endif

#       ifdef TIM2_BASE
        case TIM2_BASE:
            HAL_NVIC_EnableIRQ(TIM2_IRQn);
            return;
#       endif

#       ifdef TIM3_BASE
        case TIM3_BASE:
            HAL_NVIC_EnableIRQ(TIM3_IRQn);
            return;
#       endif

#       ifdef TIM4_BASE
        case TIM4_BASE:
            HAL_NVIC_EnableIRQ(TIM4_IRQn);
            return;
#       endif

#       ifdef TIM5_BASE
        case TIM5_BASE:
            HAL_NVIC_EnableIRQ(TIM5_IRQn);
            return;
#       endif

#       ifdef TIM6_BASE
        case TIM6_BASE:
            HAL_NVIC_EnableIRQ(TIM6_IRQn);
            return;
#       endif

#       ifdef TIM7_BASE
        case TIM7_BASE:
            HAL_NVIC_EnableIRQ(TIM7_IRQn);
            return;
#       endif

#       ifdef TIM8_BASE
            case TIM8_BASE:
            HAL_NVIC_EnableIRQ(TIM8_IRQn);
            return;
#      endif

#       ifdef TIM9_BASE
        case TIM9_BASE:
            HAL_NVIC_EnableIRQ(TIM9_IRQn);
            return;
#       endif

#       ifdef TIM10_BASE
        case TIM10_BASE:
            HAL_NVIC_EnableIRQ(TIM10_IRQn);
            return;
#       endif

#       ifdef TIM11_BASE
        case TIM11_BASE:
            HAL_NVIC_EnableIRQ(TIM11_IRQn);
            return;
#       endif

#       ifdef TIM12_BASE
            case TIM12_BASE:
            HAL_NVIC_EnableIRQ(TIM12_IRQn);
            return;
#       endif

#       ifdef TIM13_BASE
            case TIM13_BASE:
            HAL_NVIC_EnableIRQ(TIM13_IRQn);
            return;
#       endif

#       ifdef TIM14_BASE
            case TIM14_BASE:
            HAL_NVIC_EnableIRQ(TIM14_IRQn);
            return;
#       endif

        default:
            return;
    }
}

void SF_TimerInit_IT(TIM_TypeDef* timer2init, uint32_t reload_val,
                       uint32_t prescaler)
{
    tim_handler.Instance = timer2init;
    tim_handler.Init.ClockDivision = 1;
    tim_handler.Init.CounterMode = TIM_COUNTERMODE_UP;
    tim_handler.Init.Period = reload_val;
    tim_handler.Init.Prescaler = prescaler;
    SF_EnableClock((uint32_t*) tim_handler.Instance); //enable clock
    EnableTimerIRQ((uint32_t*)tim_handler.Instance);
    //
    HAL_TIM_Base_Init(&tim_handler);
    HAL_TIM_Base_Start_IT(&tim_handler);
}

void TIM6_IRQHandler()
{
    HAL_TIM_IRQHandler(&tim_handler);
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    BlueToggle();
}

//void
