/*
 * st_utils.h
 *
 *  Created on: Nov 21, 2018
 *      Author: Andrey Gramakov
 */

#ifndef ST_UTILS_H_
#define ST_UTILS_H_

#include <stdint.h>
#include "main.h"
//#include <string.h>

void Util_InitGpioClock(GPIO_TypeDef* gpio);
void Util_InitTicksCounter();
void Util_Delay_us(uint32_t us);
uint32_t Util_GetUpTime_us();
uint32_t Util_GetUpTime_ms();

#endif /* ST_UTILS_H_ */
