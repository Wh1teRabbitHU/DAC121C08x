#include <DAC121.h>

void DAC121_initRegister(uint8_t i2cAddr, uint8_t mode, uint16_t data) {
	uint16_t maskedMode = (mode << 12) & PDM_MASK;
	uint16_t maskedData = data & DATA_MASK;

	I2C_8Bit_writeToModule(i2cAddr, maskedData | maskedMode);
}

void DAC121_setPowerDownMode(uint8_t i2cAddr, uint8_t mode) {
	uint16_t registerVal = I2C_8Bit_readFromModule(i2cAddr);

	registerVal = I2C_8Bit_setBinary(registerVal, PDM_BIT_1_POS, GET_BIT_VALUE(mode, 1));
	registerVal = I2C_8Bit_setBinary(registerVal, PDM_BIT_0_POS, GET_BIT_VALUE(mode, 0));

	I2C_8Bit_writeToModule(i2cAddr, registerVal);
}

uint8_t DAC121_getPowerDownMode(uint8_t i2cAddr) {
	uint16_t registerVal = I2C_8Bit_readFromModule(i2cAddr);

	return GET_BIT_VALUE(registerVal, PDM_BIT_1_POS) << 1 | GET_BIT_VALUE(registerVal, PDM_BIT_0_POS);
}

void DAC121_setData(uint8_t i2cAddr, uint16_t data) {
	uint16_t maskedData = data & DATA_MASK;
	uint16_t registerVal = DAC121_getData(i2cAddr) & PDM_MASK;

	I2C_8Bit_writeToModule(i2cAddr, maskedData | registerVal);
}

uint16_t DAC121_getData(uint8_t i2cAddr) {
	return I2C_8Bit_readFromModule(i2cAddr) & DATA_MASK;
}