/*
 * st_utils.h
 *
 *  Created on: Nov 21, 2018
 *      Author: Andrey Gramakov
 */

#ifndef SF_UTILS_H_
#define SF_UTILS_H_

#ifdef __cplusplus
 extern "C" {
#endif

#include <stdint.h>
#include "main.h"


void SF_InitGpioClock(GPIO_TypeDef* gpio); // TODO: remove this
void SF_EnableClock(uint32_t* PERIPH_ADDR_BASE);
uint32_t SF_GetArrAverage(uint32_t* array, uint32_t arr_size);
uint32_t SF_LinInterp(uint32_t x, uint32_t x0, uint32_t y0, uint32_t x1, uint32_t y1);
#endif /* SF_UTILS_H_ */

#ifdef __cplusplus
}
#endif /* __cplusplus */
