/*
 * ir_remote_sensor.h
 *
 *  Created on: Nov 24, 2018
 *      Author: Andrey Gramakov
 */

#ifndef IR_REMOTE_SENSOR_H_
#define IR_REMOTE_SENSOR_H_

#include "main.h"
#include <stdbool.h>
#include "st_utils.h"

#define IR_CLK 38000
#define IR_PERIOD_us (1000000/IR_CLK)

typedef struct{
    uint32_t in_pin;
    GPIO_TypeDef* in_port;
    uint8_t rx_array[16];
    uint32_t rx_byte_counter;
} IrRemote_Typedef;

void IR_Init(IrRemote_Typedef* ir);
uint8_t IR_GetByte(IrRemote_Typedef* ir);
void IR_WaitNGet(IrRemote_Typedef* ir);

#endif /* IR_REMOTE_SENSOR_H_ */
