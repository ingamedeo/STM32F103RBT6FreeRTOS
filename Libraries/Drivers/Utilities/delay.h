/*
 * delay.h
 *
 *  Created on: Nov 19, 2011
 *      Author: MMM
 */

#ifndef DELAY_H_
#define DELAY_H_
#include "stm32f10x.h"
#include "FreeRTOS.h"
#include "task.h"
void Delay(__IO uint32_t nCount);
void delay_ms(uint32_t ms);

#endif /* DELAY_H_ */
