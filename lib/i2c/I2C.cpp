#include <I2C.h>

uint16_t I2C_readFromModule(uint8_t i2cAddr) {
	uint8_t byteCount = 2;

	Wire.beginTransmission(i2cAddr);
	Wire.endTransmission();
	Wire.requestFrom(i2cAddr, byteCount);

	if (Wire.available()) {
		uint8_t firstuint8_t = Wire.read();
		uint8_t seconduint8_t = Wire.read();

		return (firstuint8_t << 8) + seconduint8_t;
	}

	return 0;
}

uint16_t I2C_readFromModule(uint8_t i2cAddr, uint8_t registerAddr) {
	uint8_t byteCount = 2;

	Wire.beginTransmission(i2cAddr);
	Wire.write(registerAddr);
	Wire.endTransmission();
	Wire.requestFrom(i2cAddr, byteCount);

	if (Wire.available()) {
		uint8_t firstuint8_t = Wire.read();
		uint8_t seconduint8_t = Wire.read();

		return (firstuint8_t << 8) + seconduint8_t;
	}

	return 0;
}

void I2C_writeToModule(uint8_t i2cAddr, uint16_t data) {
	uint8_t hByte = data >> 8;
	uint8_t lByte = data & 255;

	Wire.beginTransmission(i2cAddr);
	Wire.write(hByte);
	Wire.write(lByte);
	Wire.endTransmission();
}

void I2C_writeToModule(uint8_t i2cAddr, uint8_t registerAddr, uint16_t data) {
	uint8_t hByte = data >> 8;
	uint8_t lByte = data & 255;

	Wire.beginTransmission(i2cAddr);
	Wire.write(registerAddr);
	Wire.write(hByte);
	Wire.write(lByte);
	Wire.endTransmission();
}

uint8_t I2C_readFlag(uint8_t i2cAddr, uint8_t pos) {
	uint16_t registerValue = I2C_readFromModule(i2cAddr);

	return GET_BIT_VALUE(registerValue, pos);
}

uint8_t I2C_readFlag(uint8_t i2cAddr, uint8_t registerAddr, uint8_t pos) {
	uint16_t registerValue = I2C_readFromModule(i2cAddr, registerAddr);

	return GET_BIT_VALUE(registerValue, pos);
}

void I2C_writeFlag(uint8_t i2cAddr, uint8_t pos, uint8_t value) {
	uint16_t registerValue = I2C_readFromModule(i2cAddr);
	registerValue = I2C_setBinary(registerValue, pos, value);
	I2C_writeToModule(i2cAddr, registerValue);
}

void I2C_writeFlag(uint8_t i2cAddr, uint8_t registerAddr, uint8_t pos, uint8_t value) {
	uint16_t registerValue = I2C_readFromModule(i2cAddr, registerAddr);
	registerValue = I2C_setBinary(registerValue, pos, value);
	I2C_writeToModule(i2cAddr, registerAddr, registerValue);
}

uint16_t I2C_setBinary(uint16_t binary, uint8_t pos, uint8_t flagVal) {
	if (flagVal == 1) {
		return binary | (1 << pos);
	}

	return binary & (~(1 << pos));
}