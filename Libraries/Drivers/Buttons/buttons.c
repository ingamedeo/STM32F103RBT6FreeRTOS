/*
 * buttons.c
 *
 *  Created on: MAY 30, 2012
 *      Author: MMM
 */

#include "buttons.h"
void ButtonsInit(void) {
  //GPIO structure used to initialize Button pins
  GPIO_InitTypeDef GPIO_InitStructure;
  //Enable clock on APB2 pripheral bus where buttons are connected
  RCC_APB2PeriphClockCmd(BPORTCLK,  ENABLE);
  //select pins to initialize S2 and S3 buttons
  GPIO_InitStructure.GPIO_Pin = BS2|BS3;
  //select pull-up input mode
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
  //select GPIO speed
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(BPORT, &GPIO_InitStructure);
}

void ButtonsInitEXTI(void) {
//enable AFIO clock
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,  ENABLE);
    EXTI_InitTypeDef EXTI_InitStructure;
    //NVIC structure to set up NVIC controller
    NVIC_InitTypeDef NVIC_InitStructure;
    //GPIO structure used to initialize Button pins
    //Connect EXTI Lines to Button Pins
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOC, GPIO_PinSource0); //BS2
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOC, GPIO_PinSource1); //BS3
	
    //select EXTI line0
    EXTI_InitStructure.EXTI_Line = EXTI_Line0;
    //select interrupt mode
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
    //generate interrupt on rising edge
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
    //enable EXTI line
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;
    //send values to registers
    EXTI_Init(&EXTI_InitStructure);
    //select EXTI line13
    EXTI_InitStructure.EXTI_Line = EXTI_Line1;
    EXTI_Init(&EXTI_InitStructure);
    //disable AFIO clock
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,  DISABLE);
    //configure NVIC
    //select NVIC channel to configure
    NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;
    //set priority to lowest
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x01;
    //set subpriority to lowest
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x01;
    //enable IRQ channel
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    //update NVIC registers
    NVIC_Init(&NVIC_InitStructure);
    //select NVIC channel to configure
    NVIC_InitStructure.NVIC_IRQChannel = EXTI1_IRQn;
    NVIC_Init(&NVIC_InitStructure);
}

uint32_t ButtonRead(GPIO_TypeDef* Button_Port, uint16_t Button)
{
  return !GPIO_ReadInputDataBit(Button_Port, Button);
}
