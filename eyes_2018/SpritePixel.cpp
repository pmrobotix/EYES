/*
 * SpritePixel.cpp
 *
 *  Created on: 8 avr. 2018
 *      Author: gmo
 */

#include "SpritePixel.h"
#include "definitions.h"
#include <Arduino.h>

namespace eyes {

SpritePixel::SpritePixel(char x, char y, unsigned char red, unsigned char green, unsigned char blue) {
	mX = x;
	mY = y;
	mRed = red;
	mGreen = green;
	mBlue = blue;
}

SpritePixel::SpritePixel() {
	mX = PIXEL_EXCEPTION_VALUE;
	mY = PIXEL_EXCEPTION_VALUE;
	mRed = PIXEL_EXCEPTION_VALUE;
	mGreen = PIXEL_EXCEPTION_VALUE;
	mBlue = PIXEL_EXCEPTION_VALUE;
}

void SpritePixel::setColour(unsigned short rgb565) {
//	Serial.print("Input=");
//	Serial.println(rgb565);
	mRed = (((rgb565 >> 11) << 3)+((rgb565&0x8000)!=0?(unsigned short)7:(unsigned short)0));
	mGreen = (((rgb565&0x07E0) >> 5) << 2)+((rgb565&0x0400)!=0?(unsigned short)3:(unsigned short)0);
	mBlue = ((rgb565&0x001F) << 3)+((rgb565&0x0010)!=0?(unsigned short)7:(unsigned short)0);
//	Serial.print(" red=");
//	Serial.print(mRed);
//	Serial.print(" green=");
//	Serial.print(mGreen);
//	Serial.print(" blue=");
//	Serial.println(mBlue);
}

} /* namespace eyes */
