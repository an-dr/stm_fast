/*
 * disco_l152.c
 *
 *  Created on: Nov 24, 2018
 *      Author: Andrey Gramakov
 */

#include <sf_disco_l152c.h>

void SF_Disco_InitLeds()
{
    __HAL_RCC_GPIOB_CLK_ENABLE()
    ;
    GPIO_InitTypeDef leds_gpio;
    uint32_t pins = GPIO_PIN_BLUE | GPIO_PIN_GREEN;
    leds_gpio.Pin = pins;
    leds_gpio.Mode = GPIO_MODE_OUTPUT_PP;
    leds_gpio.Pull = GPIO_PULLUP;
    leds_gpio.Speed = GPIO_SPEED_LOW;
    HAL_GPIO_Init(GPIOB, &leds_gpio);
    //init blinking
    HAL_GPIO_WritePin(GPIOB, pins, GPIO_PIN_SET);
    HAL_Delay(200);
    HAL_GPIO_WritePin(GPIOB, pins, GPIO_PIN_RESET);
    HAL_Delay(200);
    HAL_GPIO_WritePin(GPIOB, pins, GPIO_PIN_SET);
    HAL_Delay(200);
    HAL_GPIO_WritePin(GPIOB, pins, GPIO_PIN_RESET);
}

void Green(bool state)
{
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_GREEN, state);
}

void Blue(bool state)
{
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_BLUE, state);
}

void BlueToggle()
{
    HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_BLUE);
}

void GreenToggle()
{
    HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_GREEN);
}
