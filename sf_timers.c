/*
 * timers_tool.c
 *
 *  Created on: Nov 27, 2018
 *      Author: Andrey Gramakov
 */

#include <sf_timers.h>

TIM_HandleTypeDef tim6_handler;
int tim6_st_init_flag = false;

TIM_HandleTypeDef tim3_handler;
TIM_IC_InitTypeDef tim3_ic_handler;

void SF_TIM6Init_Polling(uint32_t reload_val, uint32_t prescaler)
{
    tim6_handler.Instance = TIM6;
    tim6_handler.Init.ClockDivision = 1;
    tim6_handler.Init.CounterMode = TIM_COUNTERMODE_UP;
    tim6_handler.Init.Period = reload_val;
    tim6_handler.Init.Prescaler = prescaler;
    SF_EnableClock((uint32_t*) tim6_handler.Instance); //enable clock
    //
    HAL_TIM_Base_Init(&tim6_handler);
    HAL_TIM_Base_Start(&tim6_handler);

}

static void EnableTimerIRQ(uint32_t* PERIPH_ADDR_BASE)
{
    switch ((uint32_t) PERIPH_ADDR_BASE)
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

void SF_TIM6Init_IT(uint32_t reload_val, uint32_t prescaler)
{
    tim6_handler.Instance = TIM6;
    tim6_handler.Init.ClockDivision = 1;
    tim6_handler.Init.CounterMode = TIM_COUNTERMODE_UP;
    tim6_handler.Init.Period = reload_val;
    tim6_handler.Init.Prescaler = prescaler;
    SF_EnableClock((uint32_t*) tim6_handler.Instance); //enable clock
    EnableTimerIRQ((uint32_t*) tim6_handler.Instance);
    //
    HAL_TIM_Base_Init(&tim6_handler);
    HAL_TIM_Base_Start_IT(&tim6_handler);
}

void SF_TIM3Init_IConPB4(uint32_t reload_val, uint32_t prescaler)
{
    // basic options
    tim3_handler.Instance = TIM3;
    tim3_handler.Init.ClockDivision = 1;
    tim3_handler.Init.CounterMode = TIM_COUNTERMODE_UP;
    tim3_handler.Init.Period = reload_val;
    tim3_handler.Init.Prescaler = prescaler;

    //ic config
    tim3_ic_handler.ICFilter = 0;
    tim3_ic_handler.ICPolarity = TIM_ICPOLARITY_FALLING;
    tim3_ic_handler.ICPrescaler = TIM_ICPSC_DIV1;
    tim3_ic_handler.ICSelection = TIM_ICSELECTION_DIRECTTI;

    // gpio config for ic
    GPIO_InitTypeDef gpio_ic;
    gpio_ic.Alternate = GPIO_AF2_TIM3;
    gpio_ic.Mode = GPIO_MODE_AF_PP;
    gpio_ic.Pin = GPIO_PIN_4;

    // clock and irq
    __HAL_RCC_GPIOB_CLK_ENABLE()
    ;
    __HAL_RCC_TIM3_CLK_ENABLE()
    ;
    NVIC_EnableIRQ(TIM3_IRQn);
//    EnableTimerIRQ((uint32_t*) tim3_handler.Instance);

    // apply configs
    HAL_GPIO_Init(GPIOB, &gpio_ic); // gpio
    HAL_TIM_IC_Init(&tim3_handler);
    HAL_TIM_IC_ConfigChannel(&tim3_handler, &tim3_ic_handler, TIM_CHANNEL_1);
    HAL_TIM_IC_Start_IT(&tim3_handler, TIM_CHANNEL_1);
    outl("TIM3 ready");
}

void TIM3_IRQHandler()
{
    HAL_TIM_IRQHandler(&tim3_handler);
}

__weak void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)
{
    GreenToggle();
//    while(1);
}

void TIM6_IRQHandler()
{
    HAL_TIM_IRQHandler(&tim6_handler);
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    BlueToggle();
}

//void
