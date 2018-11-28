/*
 * disco_l152c.h
 *
 *  Created on: Nov 24, 2018
 *      Author: Andrey Gramakov
 */

#ifndef SF_DISCO_L152C_H_
#define SF_DISCO_L152C_H_

#include "main.h"
#include <stdbool.h>

#define GPIO_PIN_BLUE GPIO_PIN_6
#define GPIO_PIN_GREEN GPIO_PIN_7


void SF_Disco_InitLeds();
void Green(bool state);
void GreenToggle();
void Blue(bool state);
void BlueToggle();

#endif /* SF_DISCO_L152C_H_ */
