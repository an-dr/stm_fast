/*
 * sf_utils_time.h
 *
 *  Created on: Dec 3, 2018
 *      Author: Andrey Gramakov
 */

#ifndef SF_UTILS_TIME_H_
#define SF_UTILS_TIME_H_
/*                   */
#ifdef __cplusplus
 extern "C" {
#endif
/*                   */
#include <stdint.h>
#include "main.h"



void SF_InitDelay_us();
void SF_Delay_us_blocking(uint32_t us);
uint32_t SF_TS_GetInterpVal(TimePoint_Typedef timescale[], uint32_t ts_size, uint32_t time);
uint32_t SF_GetUpTime_us();
uint32_t SF_GetUpTime_ms();
/*                   */
#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* SF_UTILS_TIME_H_ */
