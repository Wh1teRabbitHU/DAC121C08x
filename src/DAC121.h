#ifndef DAC121
#define DAC121

#include <I2C.h>

#define DATA_MASK       0b111111111111
#define PDM_MASK		0b11 << 12
#define PDM_BIT_1_POS	13
#define PDM_BIT_0_POS	12

#define PDM_NORMAL		0b00
#define PDM_2_5K_GND	0b01
#define PDM_100K_GND	0b10
#define PDM_HIGH_IMP	0b11

void DAC121_initRegister(uint8_t i2cAddr, uint8_t mode, uint16_t data);

void DAC121_setPowerDownMode(uint8_t i2cAddr, uint8_t mode);
uint8_t DAC121_getPowerDownMode(uint8_t i2cAddr);

void DAC121_setData(uint8_t i2cAddr, uint16_t data);
uint16_t DAC121_getData(uint8_t i2cAddr);

#endif