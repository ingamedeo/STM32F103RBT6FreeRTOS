/*
 * bh1750.h
 *
 * @author Amedeo <ingamedeo[at]gmail[dot]com
 * @date 08/10/2016
 *
 * This is a driver for the BH1750FVI Digital Light Sensor
 * breakout board.
 * The board uses I2C for communication. 2 pins are required to
 * interface to the device.
 * Datasheet:
 * http://rohmfs.rohm.com/en/products/databook/datasheet/ic/sensor/light/bh1750fvi-e.pdf
 *
 */

#ifndef BH1750_H_
#define BH1750_H_
#include "STM32f10x.h"
#include "delay.h"
#include "i2c1_remap.h"

#define BH1750_I2CADDR 0x23

// No active state
#define BH1750_POWER_DOWN 0x00

// Wating for measurment command
#define BH1750_POWER_ON 0x01

// Reset data register value - not accepted in POWER_DOWN mode
#define BH1750_RESET 0x07

// Start measurement at 1lx resolution. Measurement time is approx 120ms.
#define BH1750_CONTINUOUS_HIGH_RES_MODE  0x10

// Start measurement at 0.5lx resolution. Measurement time is approx 120ms.
#define BH1750_CONTINUOUS_HIGH_RES_MODE_2  0x11

// Start measurement at 4lx resolution. Measurement time is approx 16ms.
#define BH1750_CONTINUOUS_LOW_RES_MODE  0x13

// Start measurement at 1lx resolution. Measurement time is approx 120ms.
// Device is automatically set to Power Down after measurement.
#define BH1750_ONE_TIME_HIGH_RES_MODE  0x20

// Start measurement at 0.5lx resolution. Measurement time is approx 120ms.
// Device is automatically set to Power Down after measurement.
#define BH1750_ONE_TIME_HIGH_RES_MODE_2  0x21

// Start measurement at 1lx resolution. Measurement time is approx 120ms.
// Device is automatically set to Power Down after measurement.
#define BH1750_ONE_TIME_LOW_RES_MODE  0x23


void BH1750Init(uint8_t mode);
void BH1750configure(uint8_t mode);
uint16_t BH1750readLightLevel(void);

//SPI write command
void write8(uint8_t data);

//void ButtonsInit(void);
//uint32_t ButtonRead(GPIO_TypeDef* Button_Port, uint16_t Button);
#endif /* BH1750_H_ */
