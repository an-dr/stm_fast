/*
 * ir_remote_sensor.c
 *
 *  Created on: Nov 24, 2018
 *      Author: Andrey Gramakov
 */


#include <sf_ir_remote_sensor.h>

void SF_IrIInit(IrRemote_Typedef* ir)
{
    SF_InitDelay_us();
    SF_InitGpioClock(ir->in_port);
    //
    GPIO_InitTypeDef g;
    g.Mode = GPIO_MODE_INPUT;
    g.Pin = ir->in_pin;
    g.Pull = GPIO_PULLUP;
    g.Speed = GPIO_SPEED_FREQ_MEDIUM;
    HAL_GPIO_Init(ir->in_port, &g);
    //
    ir->rx_byte_counter = 0;
}

uint8_t SF_IrGetByte(IrRemote_Typedef* ir)
{
    uint8_t byte = 0;
    volatile bool bit = false;
    for(int b = 0; b<8; b++)
    {
        bit = HAL_GPIO_ReadPin(ir->in_port, ir->in_pin);
        byte |= ( bit << b );
        SF_Delay_us(IR_PERIOD_us);
    }
    ir->rx_array[ir->rx_byte_counter] = byte;
    return byte;
}
