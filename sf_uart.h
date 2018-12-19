/*
 * uart.h
 *
 *  Created on: Nov 10, 2018
 *      Author: dongr
 */

#ifndef UART_TOOLS_H
#define UART_TOOLS_H
/*                   */
#ifdef __cplusplus
extern "C"
{
#endif
/*                   */
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "main.h" // hal

typedef struct UART1_rcvStruct
{
    uint8_t single_buf;
    uint8_t array_buff[128];
    uint32_t array_buff_cur;
    uint32_t last_msg_size;
    bool rcv_complete;
} U1_rcv_Typedef;

void SF_Uart1Init(int baud);
void out(char const * str);
void out_i(int i);
void outl(char const * str);
void out_il(int i);
void out_var(char const * name, int value);

/*                   */
#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* UART_TOOLS_H */
