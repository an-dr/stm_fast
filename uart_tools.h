/*
 * uart.h
 *
 *  Created on: Nov 10, 2018
 *      Author: dongr
 */

#ifndef UART_TOOLS_H
#define UART_TOOLS_H
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "main.h"

typedef struct UART1_rcvStruct{
    uint8_t single_buf;
    uint8_t array_buff[128];
    uint32_t array_buff_cur;
    uint32_t last_msg_size;
    bool rcv_complete;
}U1_rcv_Typedef;

void UART_Init(int baud);
void out(char* str);
void out_i(int i);
void outl(char* str);
void out_il(int i);
void out_var(char* name, int value);


#endif /* UART_TOOLS_H */
