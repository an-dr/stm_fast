/*
 * st_utils_time.c
 *
 *  Created on: Dec 3, 2018
 *      Author: Andrey Gramakov
 */

#include "sf_utils_time.h"

/**
 * @author     Andrey Gramakov
 * @brief      Unitialization of Debug block to provide cycle counting for precise delay
 */
void SF_InitDelay_us()
{
    CoreDebug->DEMCR = CoreDebug_DEMCR_TRCENA_Msk; // enable tracing
    DWT->CYCCNT = 0; // reset
    DWT->CTRL |= DWT_CTRL_CYCCNTENA_Msk; //enable counter
}

/**
 * @author     Andrey Gramakov
 * @brief      Delay in us. Call @ref SF_InitDelay_us before
 *
 * @param[in]  us    { parameter_description }
 */
void SF_Delay_us_blocking(uint32_t us)
{
    uint32_t t0 = DWT->CYCCNT;
    SystemCoreClockUpdate();
    uint32_t us_count_tic = us * (SystemCoreClock / 1000000);
    while ((DWT->CYCCNT) < us_count_tic + t0)
        ;
}

static uint32_t SearchPoint1(TimePoint_Typedef timescale[], uint32_t ts_size, uint32_t time)
{
    //search a points
    uint32_t point_0 = 0; // first
    while (point_0 < ts_size)
    {
        if (timescale[point_0].t > time)
        {
            return (point_0 + 1); // got point_b
        }
        ++point_0;
    }
    return point_0;
}

uint32_t SF_TS_GetInterpVal(TimePoint_Typedef timescale[], uint32_t ts_size, uint32_t time)
{

    uint32_t point_1 = SearchPoint1(timescale, ts_size, time);
    if (point_1 < ts_size)
    {
        uint32_t point_0 = point_1 - 1;
        return SF_LinInterp(time,
                            timescale[point_0].t,
                            timescale[point_0].val,
                            timescale[point_1].t,
                            timescale[point_1].val);
    }
    else
    {
        return -1; // timescale exceeded
    }

}

uint32_t SF_GetUpTime_ms()
{
    return (DWT->CYCCNT / (SystemCoreClock / 1000));
}

uint32_t SF_GetUpTime_us()
{
    return (DWT->CYCCNT / (SystemCoreClock / 1000000));
}
