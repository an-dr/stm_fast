/*
 * timers_tools.h
 *
 *  Created on: Nov 26, 2018
 *      Author: Andrey Gramakov
 */

#ifndef SF_TIMERS_H_
#define SF_TIMERS_H_

#include "main.h"

void SF_TimerInit_Polling(TIM_TypeDef* timer2init, uint32_t reload_val, uint32_t prescaler);
void SF_TimerInit_IT(TIM_TypeDef* timer2init, uint32_t reload_val, uint32_t prescaler);


#endif /* SF_TIMERS_H_ */
