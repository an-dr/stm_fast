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
    Hello();
}

Uart1::Uart1(const uint32_t & spec_baudrate)
            : baudrate(spec_baudrate), rx_buff_p(NULL)
{
    Pre_Init();
    Init();
    Hello();
}

/**
 *
 * @param baudrate
 */
void Uart1::SetBaudRate(uint32_t new_br)
{
    baudrate = new_br;
    float fck = HAL_RCC_GetSysClockFreq();
    uint32_t over8 = (USART1->CR1 >> USART_CR1_OVER8_Pos) & 1;
    uint32_t new_brr = 0;
    // BRR for STM32L1
#   if defined( __STM32L1xx_H )
    float uart_div, uart_div_Fraction, uart_div_Mantissa;
    uint32_t DIV, DIV_Fraction, DIV_Mantissa;
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
    new_brr = DIV;
    // BRR for STM32F0
#   elif defined( __STM32F0xx_H )
    uint32_t usart_div;
    if (over8) // set OVER8 bit
    {
        usart_div = (2 * fck) / baudrate;
        new_brr = ((usart_div >> 1) & 0x7) // BRR[2:0] = USARTDIV[3:0] shifted 1 bit to the right.
                  //BRR[3] must be kept cleared
                  | (usart_div & 0xFFFFFFF0); //BRR[15:4] = USARTDIV[15:4]
    }
    else
    {
        usart_div = fck / baudrate;
        new_brr = usart_div;
    }
#   endif
    USART1->BRR = new_brr;

}

bool sf::Uart1::Hello()
{
    int n = 1;
    this->Send("\n\rHello...\n\r");
    this->printf("... my developer!!%d\n\r", n);
    return true;
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

    USART1->CR1 = (1 << USART_CR1_RE_Pos) // RE: Receiver enable
                  | (1 << USART_CR1_TE_Pos) // TE: Transmitter enable
                  | (1 << USART_CR1_OVER8_Pos); // over8
    SetBaudRate(baudrate);
    USART1->CR1 |= (1 << USART_CR1_UE_Pos); //UE: USART enable
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
#   if defined( __STM32L1xx_H )
        USART1->DR = s;
        while (!(USART1->SR >> 7 & 1))
        ; // while not TXE: Transmit data register empty
#   elif defined( __STM32F0xx_H )
        USART1->TDR = s;
        while (!(USART1->ISR >> USART_ISR_TXE_Pos & 1))
            ; // while not TXE: Transmit data register empty
#   else
#       warning "Not defined UART registers"
#   endif
    }
    return true;
}

bool Uart1::Send(const uint8_t & tx)
{
#   if defined( __STM32L1xx_H )
    USART1->DR = tx;
    while (!(USART1->SR >> 7 & 1))
    ; // while not TXE: Transmit data register empty
#   elif defined( __STM32F0xx_H )
    USART1->TDR = tx;
    while (!(USART1->ISR >> USART_ISR_TXE_Pos & 1))
        ; // while not TXE: Transmit data register empty
#   else
#       warning "Not defined UART registers"
#   endif
    return true;
}

void Uart1::Receive(string * rx_str)
{
    
}

bool sf::Uart1::Pre_Init()
{
    __HAL_RCC_USART1_CLK_ENABLE()
                ;
    __HAL_RCC_GPIOA_CLK_ENABLE()
                ;
    GPIO_InitTypeDef u1_pins;
    u1_pins.Pin = GPIO_PIN_9 | GPIO_PIN_10;
    u1_pins.Mode = GPIO_MODE_AF_PP;
    u1_pins.Pull = GPIO_PULLUP;
    u1_pins.Speed = GPIO_SPEED_FREQ_MEDIUM;
#   if defined( __STM32L1xx_H )
    u1_pins.Alternate = GPIO_AF7_USART1;
#   warning "USED PA9/PA10 for UART1"
#   elif defined( __STM32F0xx_H )
    u1_pins.Alternate = GPIO_AF1_USART1;
#   warning "USED PA9/PA10 for UART1"
#   endif
    HAL_GPIO_Init(GPIOA, &u1_pins);
    HAL_NVIC_EnableIRQ(USART1_IRQn);
    HAL_NVIC_SetPriority(USART1_IRQn, 15, 0);
    return true;
}

int sf::Uart1::printf(const char* format, ...)
{
    char str[128];
    char *s = str; // pointer for the buffer
    int ch_count = 0;

    va_list args; // holds args
    va_start(args, format); // format - last defined param name
    vsprintf(str, format, args); // formatting

    while (*s)
    {
#       if defined( __STM32L1xx_H )
        USART1->DR = *s;
        while (!(USART1->SR >> 7 & 1))
        ; // while not TXE: Transmit data register empty
#       elif defined( __STM32F0xx_H )
        USART1->TDR = *s;
        while (!(USART1->ISR >> USART_ISR_TXE_Pos & 1))
            ; // while not TXE: Transmit data register empty
#       else
#           warning "Not defined UART registers"
#       endif
        s++;
        ch_count++;
    }
    va_end(args);
    return ch_count;
}
