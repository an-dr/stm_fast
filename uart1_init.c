/*
 * uart1_init.c
 *
 *  Created on: Nov 11, 2018
 *      Author: Andrey Gramakov
 */

#include "uart1_init.h"

UART_HandleTypeDef uart1;

// todo: make a structure
uint8_t uart1_single_buf;
uint32_t uart1_array_buff_cur;
uint32_t uart1_last_msg_size;
uint8_t uart1_array_buff[128];
bool uart1_rcv_complete = true;

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

    uart1_array_buff_cur = 0;
    HAL_UART_Receive_IT(&uart1, &uart1_single_buf, 1); // HAL_UART_RxCpltCallback will called every byte

    char* hello = "Hello, my developer!\n";
    HAL_UART_Transmit(&uart1, (uint8_t*) hello, strlen(hello), 1000);

}

void USART1_IRQHandler(void)
{
//    char* msg = "IRQ!";
//    HAL_UART_Transmit(&uart1, (uint8_t*)msg, strlen(msg), 1000);
    HAL_UART_IRQHandler(&uart1); // check what's going on

}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
    char* msg = "HAL_UART_RxCpltCallback!";
    HAL_UART_Transmit(&uart1, (uint8_t*)msg, strlen(msg), 1000);
    if (uart1_single_buf == '\r')
    {
        uart1_array_buff[uart1_array_buff_cur++] = '\r';
        // ending
        uart1_last_msg_size = uart1_array_buff_cur;
        uart1_rcv_complete = true;
        uart1_array_buff_cur = 0;
        // action
        UART1_ActionAfterReceiving();
    }
    else
    {
        uart1_array_buff[uart1_array_buff_cur++] = uart1_single_buf;
    }
    HAL_UART_Receive_IT(&uart1, &uart1_single_buf, 1); // reenable
}

void UART1_ActionAfterReceiving()
{
    char* msg = "Rcvd: ";
    HAL_UART_Transmit(&uart1, (uint8_t*)msg, strlen(msg), 1000);
    HAL_UART_Transmit(&uart1,uart1_array_buff,uart1_last_msg_size, 1000);
}
