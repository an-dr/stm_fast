/*
 * uart.h
 *
 *  Created on: Nov 10, 2018
 *      Author: dongr
 */

#ifndef UART1_INIT_H_
#define UART1_INIT_H_
#include "stm32l1xx_hal.h"
#include <string.h>


//void HAL_UART_MspInit(UART_HandleTypeDef *huart);
void UART_Init(int baud);
void UART1_ActionAfterReceiving();


#endif /* UART1_INIT_H_ */
