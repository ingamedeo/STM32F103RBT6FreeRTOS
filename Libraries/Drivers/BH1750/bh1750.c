/*
 * bh1750.c
 *
 * @author Amedeo <ingamedeo[at]gmail[dot]com
 * @date 08/10/2016
 *
 */

#include "bh1750.h"

void BH1750Init(uint8_t mode) {
  I2C1_Init();
  BH1750configure(mode);
}

void BH1750configure(uint8_t mode) {

    switch (mode) {
        case BH1750_CONTINUOUS_HIGH_RES_MODE:
        case BH1750_CONTINUOUS_HIGH_RES_MODE_2:
        case BH1750_CONTINUOUS_LOW_RES_MODE:
        case BH1750_ONE_TIME_HIGH_RES_MODE:
        case BH1750_ONE_TIME_HIGH_RES_MODE_2:
        case BH1750_ONE_TIME_LOW_RES_MODE:
            // apply a valid mode change
            write8(mode);
            //delay_ms(10);
            break;
        default:
            // Invalid measurement mode
            break;
    }
}

uint16_t BH1750readLightLevel(void) {
	
  uint8_t dataRecv[2];
  uint16_t level;
  
  //I2C1_BeginTransmission(BH1750_I2CADDR);
  /*
  NOTE: Calling I2C1_BeginTransmission here locks up the bus!
  I2C1_RequestFrom inits the bus already! (Generates START req)
   */
  I2C1_RequestFrom(BH1750_I2CADDR, dataRecv, 2);

  level = dataRecv[0];
  level <<= 8;
  level |= dataRecv[1];

  I2C1_EndTransmission();

  level = level/1.2; // convert to lux

  return level;
}


/*********************************************************************/


void write8(uint8_t d) {
  I2C1_BeginTransmission(BH1750_I2CADDR);
  I2C1_Write(d);
  I2C1_EndTransmission();
}

// void ButtonsInit(void)
// {
//   //GPIO structure used to initialize Button pins
//   GPIO_InitTypeDef GPIO_InitStructure;
//   //Enable clock on APB2 pripheral bus where buttons are connected
//   RCC_APB2PeriphClockCmd(BPORTCLK,  ENABLE);
//   //select pins to initialize S2 and S3 buttons
//   GPIO_InitStructure.GPIO_Pin = BS2|BS3;
//   //select pull-up input mode
//   GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
//   //select GPIO speed
//   GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//   GPIO_Init(BPORT, &GPIO_InitStructure);
// }
// uint32_t ButtonRead(GPIO_TypeDef* Button_Port, uint16_t Button)
// {
//   return !GPIO_ReadInputDataBit(Button_Port, Button);
// }
