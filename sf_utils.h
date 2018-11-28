/*
 * st_utils.h
 *
 *  Created on: Nov 21, 2018
 *      Author: Andrey Gramakov
 */

#ifndef SF_UTILS_H_
#define SF_UTILS_H_

#include <stdint.h>
#include "main.h"

void SF_InitGpioClock(GPIO_TypeDef* gpio);
void SF_EnableClock(uint32_t* PERIPH_ADDR_BASE);
void SF_InitDelay_us();
void SF_Delay_us(uint32_t us);
uint32_t SF_GetUpTime_us();
uint32_t SF_GetUpTime_ms();

#endif /* SF_UTILS_H_ */
