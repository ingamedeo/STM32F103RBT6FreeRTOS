/*
 * mytasks.h
 */

#ifndef MYTASKS_H_
#define MYTASKS_H_
#include "STM32f10x.h"
#include "FreeRTOS.h"
//#include "printf-stdarg.h"
#include "delay.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"
#include "leds.h"
#include "buttons.h"
//#include "lcd.h"
#include "usart.h"
#include "i2c1_remap.h"
#include "bh1750.h"

#define DEBOUNCECOUNTS 10
extern QueueHandle_t RxQueue, TxQueue;
void vLEDFlashTask( void *pvParameters );
void vButtonCheckTask( void *pvParameters );
void vButtonLEDsTask( void *pvParameters );
//void vLCDTask( void *pvParameters );
void vUSARTTask( void *pvParameters );
#endif /* MYTASKS_H_ */
