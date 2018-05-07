// Wire Master Writer
// by Nicholas Zambetti <http://www.zambetti.com>

// Demonstrates use of the Wire library
// Writes data to an I2C/TWI slave device
// Refer to the "Wire Slave Receiver" example for use with this

// Created 29 March 2006

// This example code is in the public domain.


#include <Wire.h>
#include "EyeBlinker.h"
#define MY_ADDRESS 1
eyes::EyeBlinker eyeBlinker = eyes::EyeBlinker();
//void setup() {
//	Wire.begin(/*MY_ADDRESS*/); // join i2c bus (address optional for master)
//	Serial.begin(9600);
//	Serial.println("Arduino master OK");
//}


//void loop() {
//	while (true) {
//		eyeBlinker.update(millis());
//		delay(20);
//	}
//}
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
	Wire.begin(MY_ADDRESS);
	Serial.begin(9600);
//	Serial.println("Master OK");
}

// the loop function runs over and over again forever
void loop() {
	while (true) {
		eyeBlinker.update(millis());
		delay(20);
	}
}
