/**
 ******************************************************************************
 * @file	i2c1_remap.h
 * @author	Hampus Sandberg
 * @version	0.1
 * @date	2014-02-18
 * @brief	Manage I2C1
 ******************************************************************************
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef RF_I2C1_H_
#define RF_I2C1_H_

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"
#include "stm32f10x_i2c.h"

/* Defines -------------------------------------------------------------------*/

#define I2C_TIMEOUT                 100000

/* Typedefs ------------------------------------------------------------------*/
/* Function prototypes -------------------------------------------------------*/
void I2C1_Init(void);

ErrorStatus I2C1_BeginTransmission(uint8_t Address);
void I2C1_EndTransmission(void);
ErrorStatus I2C1_Write(uint8_t Data);
ErrorStatus I2C1_RequestFrom(uint8_t Address, uint8_t* Storage, uint16_t NumByteToRead);

uint8_t I2C1_SlaveAtAddress(const uint8_t Address);

#endif /* RF_I2C1_H_ */
