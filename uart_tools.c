/*
 * uart1_init.c
 *
 *  Created on: Nov 11, 2018
 *      Author: Andrey Gramakov
 */

#include "uart_tools.h"

UART_HandleTypeDef uart1;

U1_rcv_Typedef u1r;

// 4printf:

/* We need to implement own __FILE struct */
/* FILE struct is used from __FILE */
//struct __FILE {
//    int dummy;
//};
/* You need this if you want use printf */
/* Struct FILE is implemented in stdio.h */
//FILE __stdout;
//int fputc(int ch, FILE *f) {
//    /* Do your stuff here */
//    /* Send your custom byte */
//    uint8_t c = ch;
////    c[0] = ch & 0x00FF;
//    HAL_UART_Transmit(&uart1, &c, 1, 10);
//
//    /* If everything is OK, you have to return character written */
//    return ch;
//    /* If character is not correct, you can return EOF (-1) to stop writing */
//    //return -1;
//}
//int __io_putchar(int ch)
//{
//    uint8_t c[1];
//    c[0] = ch & 0x00FF;
//    HAL_UART_Transmit(&uart1, &*c, 1, 10);
//    return ch;
//}
//
//int _write(int file, char *ptr, int len)
//{
//    int DataIdx;
//    for (DataIdx = 0; DataIdx < len; DataIdx++)
//    {
//        __io_putchar(*ptr++);
//    }
//    return len;
//}

// .4printf

static void UART1_ActionAfterReceiving()
{
    char* msg = "\rRcvd: ";
    HAL_UART_Transmit(&uart1, (uint8_t*) msg, strlen(msg), 1000);
    HAL_UART_Transmit(&uart1, u1r.array_buff, u1r.last_msg_size, 1000);
//    HAL_UART_Transmit(&uart1, &'\r', 1, 1000);
}

static void UART1_ActionOnGettingAByte()
{
#   ifdef UART1_DBG_OUT
    char* msg = "HAL_UART_RxCpltCallback!";
    HAL_UART_Transmit(&uart1, (uint8_t*)msg, strlen(msg), 1000);
#   endif
    if (u1r.single_buf == '\r')
    {
        u1r.array_buff[u1r.array_buff_cur++] = '\r';
        // ending
        u1r.last_msg_size = u1r.array_buff_cur;
        u1r.rcv_complete = true;
        u1r.array_buff_cur = 0;
        // action
        UART1_ActionAfterReceiving();
    }
    else
    {
        u1r.array_buff[u1r.array_buff_cur++] = u1r.single_buf;
    }

}

void UART_Init(int baud)
{
    __HAL_RCC_USART1_CLK_ENABLE()
                ;
    __HAL_RCC_GPIOA_CLK_ENABLE()
                ;

    GPIO_InitTypeDef u1_pins;
    u1_pins.Pin = GPIO_PIN_9 | GPIO_PIN_10;
    u1_pins.Mode = GPIO_MODE_AF_PP;
    u1_pins.Pull = GPIO_PULLUP;
    u1_pins.Speed = GPIO_SPEED_MEDIUM;
    u1_pins.Alternate = GPIO_AF7_USART1;
    HAL_GPIO_Init(GPIOA, &u1_pins);
    HAL_NVIC_EnableIRQ(USART1_IRQn);
    HAL_NVIC_SetPriority(USART1_IRQn, 15, 0);

    uart1.Instance = USART1;
    uart1.Init.BaudRate = baud;
    uart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
    uart1.Init.Mode = UART_MODE_TX_RX;
    uart1.Init.OverSampling = UART_OVERSAMPLING_8;
    uart1.Init.Parity = UART_PARITY_NONE;
    uart1.Init.StopBits = UART_STOPBITS_1;
    uart1.Init.WordLength = UART_WORDLENGTH_8B;
    HAL_UART_Init(&uart1);

    u1r.array_buff_cur = 0;
    HAL_UART_Receive_IT(&uart1, &u1r.single_buf, 1); // HAL_UART_RxCpltCallback will called every byte

    char* hello = "Hello, my developer!\n\r";
    HAL_UART_Transmit(&uart1, (uint8_t*) hello, strlen(hello), 1000);
//    printf("Hello from printf");

}

void USART1_IRQHandler(void)
{
#   ifdef UART1_DBG_OUT
    char* msg = "IRQ!";
    HAL_UART_Transmit(&uart1, (uint8_t*)msg, strlen(msg), 1000);
#   endif
    HAL_UART_IRQHandler(&uart1); // check what's going on

}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
    UART1_ActionOnGettingAByte();
    HAL_UART_Receive_IT(&uart1, &u1r.single_buf, 1); // reenable
}

static void out_newlinechar()
{
    HAL_UART_Transmit(&uart1, (uint8_t*)"\n\r", strlen("\n\r"), 1000);
}

void out(char* str)
{
    HAL_UART_Transmit(&uart1, (uint8_t*) str, strlen(str), 1000);
}

void outl(char* str)
{
    HAL_UART_Transmit(&uart1, (uint8_t*) str, strlen(str), 1000);
    out_newlinechar();
}

void out_i(int i)
{
    char str_buff[128];
    HAL_UART_Transmit(&uart1, (uint8_t*) itoa(i, str_buff, 10),
                      strlen(str_buff), 1000);
}

void out_il(int i)
{
    char str_buff[128];
    HAL_UART_Transmit(&uart1, (uint8_t*) itoa(i, str_buff, 10),
                      strlen(str_buff), 1000);
    out_newlinechar();
}

void out_var(char* name, int value)
{
    out(name);
    out(": ");
    out_il(value);
}

