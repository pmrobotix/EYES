/*
 * RainbowduinoDisplay.cpp
 *
 *  Created on: 26 avr. 2018
 *      Author: gmo
 */

#include "RainbowduinoDisplay.h"

#include <Rainbowduino.h>

#define DISPLAY_SIZE_X 8
#define DISPLAY_SIZE_Y 8

namespace eyes {


static const unsigned char BLK = (unsigned char) 0;
static unsigned char MATRIX_RED[DISPLAY_SIZE_X][DISPLAY_SIZE_Y] = {
		{BLK, BLK, BLK, BLK, BLK, BLK, BLK, BLK},
		{BLK, BLK, BLK, BLK, BLK, BLK, BLK, BLK},
		{BLK, BLK, BLK, BLK, BLK, BLK, BLK, BLK},
		{BLK, BLK, BLK, BLK, BLK, BLK, BLK, BLK},
		{BLK, BLK, BLK, BLK, BLK, BLK, BLK, BLK},
		{BLK, BLK, BLK, BLK, BLK, BLK, BLK, BLK},
		{BLK, BLK, BLK, BLK, BLK, BLK, BLK, BLK},
		{BLK, BLK, BLK, BLK, BLK, BLK, BLK, BLK}
};

static unsigned char MATRIX_GREEN[DISPLAY_SIZE_X][DISPLAY_SIZE_Y] = {
		{BLK, BLK, BLK, BLK, BLK, BLK, BLK, BLK},
		{BLK, BLK, BLK, BLK, BLK, BLK, BLK, BLK},
		{BLK, BLK, BLK, BLK, BLK, BLK, BLK, BLK},
		{BLK, BLK, BLK, BLK, BLK, BLK, BLK, BLK},
		{BLK, BLK, BLK, BLK, BLK, BLK, BLK, BLK},
		{BLK, BLK, BLK, BLK, BLK, BLK, BLK, BLK},
		{BLK, BLK, BLK, BLK, BLK, BLK, BLK, BLK},
		{BLK, BLK, BLK, BLK, BLK, BLK, BLK, BLK}
};

static unsigned char MATRIX_BLUE[DISPLAY_SIZE_X][DISPLAY_SIZE_Y] = {
		{BLK, BLK, BLK, BLK, BLK, BLK, BLK, BLK},
		{BLK, BLK, BLK, BLK, BLK, BLK, BLK, BLK},
		{BLK, BLK, BLK, BLK, BLK, BLK, BLK, BLK},
		{BLK, BLK, BLK, BLK, BLK, BLK, BLK, BLK},
		{BLK, BLK, BLK, BLK, BLK, BLK, BLK, BLK},
		{BLK, BLK, BLK, BLK, BLK, BLK, BLK, BLK},
		{BLK, BLK, BLK, BLK, BLK, BLK, BLK, BLK},
		{BLK, BLK, BLK, BLK, BLK, BLK, BLK, BLK}
};

RainbowduinoDisplay::RainbowduinoDisplay() {
	mMustTransferToLED = false;
}

RainbowduinoDisplay::~RainbowduinoDisplay() {
}

unsigned char RainbowduinoDisplay::sizeX() {
	return ((unsigned char) DISPLAY_SIZE_X);
}
unsigned char RainbowduinoDisplay::sizeY() {
	return ((unsigned char) DISPLAY_SIZE_Y);
}
void RainbowduinoDisplay::init() const {
	Rb.init();
}

void RainbowduinoDisplay::clear() {
	for (int x = 0; x<DISPLAY_SIZE_X; x++) {
		for (int y = 0; y<DISPLAY_SIZE_Y; y++) {
			internalDraw(x, y, BLK, BLK, BLK);
		}
	}
}
void RainbowduinoDisplay::draw(SpritePixel& p) {
	int x = (int) (p.mX);
	int y = (int) (p.mY);
	//	Serial.print("x=");
	//	Serial.print(p.mX);
	//	Serial.print(" y=");
	//	Serial.print(p.mY);
	//	Serial.print(" red=");
	//	Serial.print(p.mRed);
	//	Serial.print(" green=");
	//	Serial.print(p.mGreen);
	//	Serial.print(" blue=");
	//	Serial.println(p.mBlue);
	internalDraw(y, x, p.mRed, p.mGreen, p.mBlue);
}

void RainbowduinoDisplay::transferToLED() {
	for (int y = 0; y<DISPLAY_SIZE_Y; y++) {
		for (int x = 0; x<DISPLAY_SIZE_X; x++) {
			Rb.setPixelXY(x, y, MATRIX_RED[x][y], MATRIX_GREEN[x][y], MATRIX_BLUE[x][y]);
		}
	}
}

void RainbowduinoDisplay::internalDraw(int x, int y, unsigned char red, unsigned char green, unsigned char blue) {
	MATRIX_RED[x][y] = red;
	MATRIX_GREEN[x][y] = green;
	MATRIX_BLUE[x][y] = blue;
}

} /* namespace eyes */
