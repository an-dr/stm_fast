/*
 * timers_tools.h
 *
 *  Created on: Nov 26, 2018
 *      Author: Andrey Gramakov
 */

#ifndef SF_TIMERS_H_
#define SF_TIMERS_H_
#ifdef __cplusplus
 extern "C" {
#endif


#include "main.h"

void SF_TIM6Init_Polling(uint32_t reload_val, uint32_t prescaler);
void SF_TIM6Init_IT(uint32_t reload_val, uint32_t prescaler);
void SF_TIM3Init_IConPB4(uint32_t reload_val, uint32_t prescaler);


#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif /* SF_TIMERS_H_ */
