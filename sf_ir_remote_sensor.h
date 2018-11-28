/*
 * ir_remote_sensor.h
 *
 *  Created on: Nov 24, 2018
 *      Author: Andrey Gramakov
 */

#ifndef SF_IR_REMOTE_SENSOR_H_
#define SF_IR_REMOTE_SENSOR_H_

#include <stdbool.h>
#include "main.h"
#include "sf_utils.h"

#define IR_CLK 38000
#define IR_PERIOD_us (1000000/IR_CLK)

typedef struct{
    uint32_t in_pin;
    GPIO_TypeDef* in_port;
    uint8_t rx_array[16];
    uint32_t rx_byte_counter;
} IrRemote_Typedef;

void SF_IrIInit(IrRemote_Typedef* ir);
uint8_t SF_IrGetByte(IrRemote_Typedef* ir);
void SF_IrWaitNGet(IrRemote_Typedef* ir);

#endif /* SF_IR_REMOTE_SENSOR_H_ */
