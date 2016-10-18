/*
 * mytasks.c
 */
#include "mytasks.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//const char * const pcUsartTaskStartMsg = "Hello STM32F103RBT6!\r\n";
//const char * const pcLCDTaskStartMsg = "   LCD task started.";

static SemaphoreHandle_t xButtonUser1Semaphore = NULL;
static SemaphoreHandle_t xButtonUser2Semaphore = NULL;
QueueHandle_t RxQueue, TxQueue;
char stringbuffer[50];

// 1 * 200ms on, 4 * 200ms off
void vLEDFlashTask( void *pvParameters ) {
  TickType_t xLastWakeTime;
  const TickType_t xFrequency = 200;
  xLastWakeTime=xTaskGetTickCount();
  int count = 0;
    for( ;; ) {
		
	  if (isLEDOn(2)) {
		  LEDOff(2);
	  } else {
		  if (count>4) {
		  	LEDOn(2);
			count = 0;
		  } else {
			  count++;
		  }
	  }
	   
	  vTaskDelayUntil(&xLastWakeTime,xFrequency);
	  }
}

void vButtonCheckTask( void *pvParameters )
{
  //for debounce
  static uint8_t count;
  TickType_t xLastWakeTime;
  const TickType_t xFrequency = 20;
  xLastWakeTime=xTaskGetTickCount();
  //create semaphores for each button
  vSemaphoreCreateBinary(xButtonUser1Semaphore);
  vSemaphoreCreateBinary(xButtonUser2Semaphore);
//check if semaphores were created successfully
  if((xButtonUser1Semaphore!=NULL)&&(xButtonUser2Semaphore!=NULL)) {
    //successfully created
    //resets initial semaphores to 0
    xSemaphoreTake(xButtonUser1Semaphore, (portTickType)0);
    xSemaphoreTake(xButtonUser2Semaphore, (portTickType)0);
  }  else {
	  //send error of failure
  }

  for (;;)
    {
      if (ButtonRead(BPORT, BS2)==pdTRUE)
        {
          count++;
          if(count==DEBOUNCECOUNTS)
            {
              xSemaphoreGive(xButtonUser1Semaphore);
              count = 0;
            }
        }
      if (ButtonRead(BPORT, BS3)==pdTRUE)
        {
          count++;
          if(count==DEBOUNCECOUNTS)
            {
              xSemaphoreGive(xButtonUser2Semaphore);
              count = 0;
            }
        }
      vTaskDelayUntil(&xLastWakeTime,xFrequency);
    }
}

void vButtonLEDsTask( void *pvParameters )
{
  TickType_t xLastWakeTime;
  const TickType_t xFrequency = 100;
  xLastWakeTime=xTaskGetTickCount();

  for( ;; )
  {
      if((xButtonUser1Semaphore!=NULL)&&(xButtonUser2Semaphore!=NULL))
      {
         if (xSemaphoreTake(xButtonUser1Semaphore, (portTickType)10)==pdTRUE) {
               LEDOn(1);
               xSemaphoreGive(xButtonUser1Semaphore);
         }
         if (xSemaphoreTake(xButtonUser2Semaphore, (portTickType)10)==pdTRUE)
             {
               LEDOff(1);
               xSemaphoreGive(xButtonUser2Semaphore);
             }
      }

    vTaskDelayUntil(&xLastWakeTime,xFrequency);
  }
}
// void vLCDTask( void *pvParameters )
// {
//   extern uint8_t Image_Table[];
//   portTickType xLastWakeTime;
//   const portTickType xFrequency = 100;
//   xLastWakeTime=xTaskGetTickCount();
//   LCD_SetDisplayWindow(00, 00, 239, 319);
//   LCD_Clear(Black);
//   LCD_DisplayStringLine(Line4,  (char*)pcLCDTaskStartMsg, White, Black);
//   for(;;)
//     {
//       if((xButtonWakeupSemaphore!=NULL)&&(xButtonTamperSemaphore!=NULL)
//        &&(xButtonUser1Semaphore!=NULL)&&(xButtonUser2Semaphore!=NULL))
//       {
//          if (xSemaphoreTake(xButtonWakeupSemaphore, (portTickType)10)==pdTRUE)
//              {
//              LCD_Clear(Blue);
//              LCD_WriteBMP_Dim(30, 30, 210, 210, Image_Table);
//              }
//          if (xSemaphoreTake(xButtonTamperSemaphore, (portTickType)10)==pdTRUE)
//              {
//              unsigned BaseType_t uxTasks;
//              uxTasks=uxTaskGetNumberOfTasks();
//              sprintf(stringbuffer, "   Tasks: %ld", uxTasks);
//              LCD_Clear(Black);
//              LCD_DisplayStringLine(Line0, "   Hello   ",White, Black);
//              LCD_DisplayStringLine(Line1, "   This is LCD DEMO  ", Black,Blue);
//              LCD_DisplayStringLine(Line2, "   Click any button  ", Black,Green);
//              LCD_DisplayStringLine(Line6, stringbuffer, Black,White);
//              }
//          if (xSemaphoreTake(xButtonUser1Semaphore, (portTickType)10)==pdTRUE)
//              {
//              LCD_Clear(White);
//              LCD_SetTextColor(Black);
//              LCD_DrawCircle(60, 60, 50);
//              LCD_SetTextColor(Green);
//              LCD_DrawCircle(100, 160, 53);
//              LCD_DrawRect(10, 300, 50, 50);
//              uint16_t i=0;
//              for(;i<320;i++)
//              {
//                      LCD_SetTextColor(i+Red);
//                      LCD_DrawLine(200, i, 30, Vertical);
//              }
//              }
//          if (xSemaphoreTake(xButtonUser2Semaphore, (portTickType)10)==pdTRUE)
//              {
//              LCD_Clear(White);
//              //LCDDrawLine(10, 10, 120, 200, Magenta);
//              //LCDDrawLine(10, 2, 220, 100, Black);
//
//              uint16_t xmax=239;
//              uint16_t ymax=319;
//
//              uint16_t x, y;
//              uint8_t prx=0;
//              uint8_t pry=0;
//              LCD_SetTextColor(Green);
//              LCD_DrawLine(0, ymax>>1, xmax, Vertical);
//              LCD_DrawLine(xmax>>1, 0, ymax, Horizontal);
//              LCD_SetTextColor(Blue);
//              for (x=0;x<xmax;x++)
//              {
//              y=(uint16_t)((ymax>>2)*sin(x*M_PI/40)+(ymax>>1));
//              if (x==0)
//                      LCD_SetPoint(x, y, Black);
//              else
//                      {
//                      LCDDrawLine(prx, pry, x, y, Black);
//                      }
//              prx=x;
//              pry=y;
//              }
//              }
//       }
//     vTaskDelayUntil(&xLastWakeTime,xFrequency);
//     }
// }

size_t count_digits(uint16_t val) {
	size_t count = 0;
	
	//If already 0 the method below won't work. we already know 0 is 1 digit long
	if (val==0) {
		return 1;
	}
	
    while(val != 0) { //Until we get to 0 (rounded since uint!)
           val /= 10;
           ++count;
       }
	   return count;
}

void from_uint16_t_to_chars(char* str, size_t len, uint32_t val) {
  uint8_t i;
  
  memset(str, 0, sizeof(str));

  for(i=1; i<=len; i++) {
	  
	  /*
	  	Example: if len=4, start from address 3 back to 0
	  */
	  
	// add '0' to convert to char
    str[len-i] = (uint8_t) ((val % 10) + '0'); //Start from last digit (right to left)
    val/=10; //Next digit
  }

  //str[i-1] = '\0'; //String termination
}

void vUSARTTask( void *pvParameters ) {

  TickType_t xLastWakeTime;
  const TickType_t xFrequency = 500;
  xLastWakeTime=xTaskGetTickCount();
  //char ch;
  // Create a queue capable of containing 128 characters.
  RxQueue = xQueueCreate( configCOM0_RX_BUFFER_LENGTH, sizeof( portCHAR ) );
  TxQueue = xQueueCreate( configCOM0_TX_BUFFER_LENGTH, sizeof( portCHAR ) );
  if(( TxQueue == 0 )||( RxQueue == 0 ))
  {
      // Failed to create the queue.
      LEDOn(1);
      LEDOn(2);
  }

  for( ;; ) {
	  
	  uint16_t light = BH1750readLightLevel();
	  
	  //USART1PutString(stringbuffer,strlen( stringbuffer ));
	  //sprintf(stringbuffer, "Light: %d lux\r\n", light);
	  
	  char* start = "Light: ";
	  strcpy( stringbuffer, start );
	  
	  char lightstr[20];
	  from_uint16_t_to_chars(lightstr, count_digits(light), light);
	  
	  strcat(stringbuffer, lightstr);
	  strcat(stringbuffer, " lux \r\n\0");
	  
	  USART1PutString(stringbuffer,strlen( stringbuffer ));
	  
      //Echo back
      //if (Usart1GetChar(&ch))
      //  {
      //    Usart1PutChar(ch);
      //  }
      vTaskDelayUntil(&xLastWakeTime,xFrequency);
  }
}

