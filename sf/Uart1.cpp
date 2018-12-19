/*
 * Uart1.cpp
 *
 *  Created on: Dec 16, 2018
 *      Author: Andrey Gramakov
 */

#include "sf/Uart1.h"
using namespace std;
using namespace sf;

Uart1::Uart1()
{
    rx_buff_p = NULL;
    baudrate = 0;
    Pre_Init();
    Init();
    Send("Hello");
}

Uart1::Uart1(const uint32_t & spec_baudrate)
{
    rx_buff_p = NULL;
    baudrate = spec_baudrate;
    Pre_Init();
    Init();
    Send("Hello");
}

/**
 *
 * @param baudrate
 */
void Uart1::SetBaudRate(uint32_t new_br)
{
    baudrate = new_br;
    float uart_div, uart_div_Fraction, uart_div_Mantissa;
    uint32_t DIV, DIV_Fraction, DIV_Mantissa;
    uint32_t over8 = (USART1->CR1 >> 15) & 1;
    float fck = HAL_RCC_GetSysClockFreq();
    if (over8) // set OVER8 bit
    {
        uart_div = (fck / baudrate) / (8 * (2 - over8));
    }
    else
    {
        uart_div = (fck / baudrate) / (16);
    }
    uart_div_Fraction = modf(uart_div, &uart_div_Mantissa);
    DIV_Fraction = (uart_div_Fraction * 16);
    DIV_Mantissa = (uint32_t)uart_div_Mantissa << 4;
    DIV = DIV_Mantissa + DIV_Fraction;
    USART1->BRR = DIV;

}

Uart1::~Uart1()
{
    Deinit();
    __HAL_RCC_USART1_CLK_DISABLE();
}

bool Uart1::Init()
{

    if (baudrate == 0)
    {
        baudrate = 115200;
    }

    USART1->CR1 = (1 << 2) // RE: Receiver enable
                  | (1 << 3) // TE: Transmitter enable
                  | (1 << 15); // over8
    SetBaudRate(baudrate);
    USART1->CR1 |= (1 << 13); //UE: USART enable
    return true;
}

bool Uart1::Deinit()
{
    USART1->BRR = 0;
    USART1->CR1 = 0;
    return true;
}

void Uart1::IRQ(bool rx, bool tx)
{
}

bool Uart1::Send(const string & tx_str)
{
    for (uint8_t s : tx_str)
    {
        USART1->DR = s;
        while (!(USART1->SR >> 7 & 1))
            ; // while not TXE: Transmit data register empty
    }
    return true;
}

bool Uart1::Send(const uint8_t & tx)
{
    USART1->DR = tx;
    while (!(USART1->SR >> 7 & 1))
        ; // while not TXE: Transmit data register empty
    return true;
}

void Uart1::Receive(string * rx_str)
{

    
}

bool sf::Uart1::Pre_Init()
{
    __HAL_RCC_USART1_CLK_ENABLE();
    __HAL_RCC_GPIOA_CLK_ENABLE();
    GPIO_InitTypeDef u1_pins;
    u1_pins.Pin = GPIO_PIN_9 | GPIO_PIN_10;
    u1_pins.Mode = GPIO_MODE_AF_PP;
    u1_pins.Pull = GPIO_PULLUP;
    u1_pins.Speed = GPIO_SPEED_MEDIUM;
    u1_pins.Alternate = GPIO_AF7_USART1;
    HAL_GPIO_Init(GPIOA, &u1_pins);
    HAL_NVIC_EnableIRQ(USART1_IRQn);
    HAL_NVIC_SetPriority(USART1_IRQn, 15, 0);
    return true;
}

sf::Uart1::Uart1(const uint32_t& spec_baudrate, const uint8_t* rx_buf, const uint32_t& buf_size)
{
}
