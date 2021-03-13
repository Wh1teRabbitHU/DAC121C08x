#include <DAC121.h>

// Change this to your address
#define DAC_I2C_ADDR      0b0001001

void setup() {
	Serial.begin(9260);

	// Just to give enough time to the DAC to boot up
	delay(100);

	DAC121_setPowerDownMode(DAC_I2C_ADDR, PDM_100K_GND);
}

void loop() {
	Serial.print("Current Power Down Mode: ");
	Serial.println(DAC121_getPowerDownMode(DAC_I2C_ADDR));

	delay(10000);
}