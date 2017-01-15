//STM32F103ZET6 FreeRTOS Test
#include "stm32f10x.h"
//#include "stm32f10x_it.h"
#include "mytasks.h"

//#include "ssd1306.h"

//task priorities
#define mainLED_TASK_PRIORITY			( tskIDLE_PRIORITY )
#define mainButton_TASK_PRIORITY                   ( tskIDLE_PRIORITY )
#define mainButtonLEDs_TASK_PRIORITY                   ( tskIDLE_PRIORITY + 1 )
#define mainUSART_TASK_PRIORITY                   ( tskIDLE_PRIORITY )
#define mainUSART_TASK_STACK_SIZE configMINIMAL_STACK_SIZE+100

void DelayAAA(__IO uint32_t nCount)
{
  for(; nCount > 0; nCount--);
}

int main(void)
{
  //init hardware
  LEDsInit();
  Usart1Init();    
  ButtonsInitEXTI();
  BH1750Init(BH1750_CONTINUOUS_HIGH_RES_MODE);
  
  xTaskCreate( vLEDFlashTask, ( const char * ) "LED", configMINIMAL_STACK_SIZE, NULL, mainLED_TASK_PRIORITY, NULL );
  //xTaskCreate( vButtonCheckTask, ( const char * ) "Button", configMINIMAL_STACK_SIZE, NULL, mainButton_TASK_PRIORITY, NULL );
  //xTaskCreate( vButtonLEDsTask, ( const char * ) "ButtonLED", configMINIMAL_STACK_SIZE, NULL, mainButtonLEDs_TASK_PRIORITY, NULL );
  //xTaskCreate( vLCDTask, ( signed char * ) "LCD", mainLCD_TASK_STACK_SIZE, NULL, mainLCD_TASK_PRIORITY, NULL );
  xTaskCreate( vUSARTTask, ( const char * ) "USART", mainUSART_TASK_STACK_SIZE, NULL, mainUSART_TASK_PRIORITY, NULL );
  //start scheduler
  vTaskStartScheduler();
  //you should never get here
  while(1)
	{
	}
}
void vApplicationStackOverflowHook( TaskHandle_t *pxTask, signed portCHAR *pcTaskName )
{
  //indicate stack overflow
  LEDOn(1);
  LEDOn(2);
  for( ;; );
}

//Interrupts
void EXTI0_IRQHandler(void)
{
 
    //Check if EXTI_Line0 is asserted
    if(EXTI_GetITStatus(EXTI_Line0) != RESET)
    {
        LEDOn(1);
    }
    //we need to clear line pending bit manually
    EXTI_ClearITPendingBit(EXTI_Line0);
}

void EXTI1_IRQHandler(void)
{
 
    //Check if EXTI_Line0 is asserted
    if(EXTI_GetITStatus(EXTI_Line1) != RESET)
    {
        LEDOff(1);
    }
    //we need to clear line pending bit manually
    EXTI_ClearITPendingBit(EXTI_Line1);
}