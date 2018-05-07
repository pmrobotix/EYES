// Wire Master Writer
// by Nicholas Zambetti <http://www.zambetti.com>

// Demonstrates use of the Wire library
// Writes data to an I2C/TWI slave device
// Refer to the "Wire Slave Receiver" example for use with this

// Created 29 March 2006

// This example code is in the public domain.


#include <Wire.h>
#include <Arduino.h>
#include "Rainbowduino.h"
#include "EyeBlinker.h"
#include "SpritePainter.h"
//#include "SpritePainter.h"

//#define BROADCAST_ADDRESS 0
#define MY_ADDRESS 2
#define IS_MASTER 1
eyes::EyeBlinker eyeBlinker = eyes::EyeBlinker();

static int receivedBytes = 0;
static uint8_t spriteBuffer[3*E_MAX_SPRITES];
static uint8_t spritesToReceive = 0;
static int bytesToReceive = 0;

void receiveEvent(int numberOfBytes) {
//	Serial.println("Event received.");
	if (numberOfBytes > 0) {
		if (bytesToReceive==0) {
			if (Wire.available()) {
				spritesToReceive = Wire.read();
//				Serial.println(spritesToReceive);
			}
			else {
//				Serial.println("No data");
				return;
			}
			numberOfBytes--;
			bytesToReceive = spritesToReceive*3;
		}
		while(Wire.available() && numberOfBytes>0 && bytesToReceive>0) {
			spriteBuffer[receivedBytes] = Wire.read();
//			Serial.println(spriteBuffer[receivedBytes]);
			receivedBytes++;
			numberOfBytes--;
			bytesToReceive--;
		}
		if (bytesToReceive<=0) {
			// throw away any garbage
			while (Wire.available() > 0) {
				Wire.read();
			}
			// display the result!
//			Serial.println("print sprites...");
			eyes::SpritePainter sp = eyes::SpritePainter(MY_ADDRESS);
			sp.drawAll(spritesToReceive, spriteBuffer);
			// reset the data
			receivedBytes=0;
			bytesToReceive = 0;
			spritesToReceive = 0;
		}
	}
}
void setup() {
	Rb.init();
#if IS_MASTER==1
	//	cli(); // Stop interrupts
	// Timer0 is already used for millis() - we'll just interrupt somewhere
	// in the middle and call the "Compare A" function below
	//	OCR0A = 0xAF;
	//	TIMSK0 |= _BV(OCIE0A);
	//	sei(); // Enable interrupts
	Wire.begin(MY_ADDRESS); // join i2c bus
	TWAR = (MY_ADDRESS << 1) | 1;  // enable broadcasts to be received
	Serial.begin(9600);
	Serial.println(F("Master configured"));
#else
	Wire.begin(MY_ADDRESS); // join i2c bus
	TWAR = (MY_ADDRESS << 1) | 1;  // enable broadcasts to be received
	Wire.onReceive(receiveEvent);  // set up receive handler
	Serial.begin (9600);
	Serial.print(F("Display "));
	Serial.print(MY_ADDRESS);
	Serial.println(F(" ready"));
#endif // IS_MASTER
}

//#ifdef IS_MASTER
//ISR(TIMER0_COMPA_vect, ISR_NOBLOCK)
//{
//	unsigned long currentMillis = millis();
//	eyeBlinker.update(currentMillis);
//	Serial.println("A");
//}
//#endif

void loop() {
#if IS_MASTER==1
	while (true) {
		eyeBlinker.update(millis());
		delay(20);
	}
#endif
}
