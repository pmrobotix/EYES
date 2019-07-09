/*
 * RightToLeft.cpp
 *
 *  Created on: 11 mai 2018
 *      Author: gmo
 */

#include "RightToLeft.h"

#include <Arduino.h>
#include <Wire.h>

namespace eyes {

RightToLeft::RightToLeft(uint8_t sprite, char firstXPosition, char lastXPosition, char yPosition) {
	mSprite = sprite;
	mFirstXPosition = firstXPosition;
	mLastXPosition = lastXPosition;
	mYPosition = yPosition;
	mCurrentXPosition = mFirstXPosition;
	mNextAlarm = nextAlarm();
	mPreviousMillis = 0L;
}

RightToLeft::~RightToLeft() {
}

bool RightToLeft::hasFinished() {
	return mCurrentXPosition <= mLastXPosition;
}


void RightToLeft::run(unsigned long currentMillis) {
	mCurrentXPosition = mFirstXPosition;
	executeAction();
	mPreviousMillis = (uint32_t) currentMillis;
	mNextAlarm = nextAlarm();
}

void RightToLeft::update(unsigned long currentMillis) {
	uint32_t now = (uint32_t) currentMillis;
	if (now < mPreviousMillis || now >= mPreviousMillis+mNextAlarm) {
		mCurrentXPosition--;
		mNextAlarm = nextAlarm();
		mPreviousMillis = now;
		executeAction();
	}
}

void RightToLeft::executeAction() {
	uint8_t numberOfSprites = generateSprites();
	broadcastSprites(numberOfSprites);
	drawSprites(numberOfSprites);
}

uint8_t RightToLeft::generateSprites() {
	// inside the sprite buffer, the values are coded as:
	// x, y, SpriteFormNumber
	uint8_t spriteForm = mSprite;
	mSpriteBuffer[0] = (uint8_t) mCurrentXPosition;
	mSpriteBuffer[1] = (uint8_t) mYPosition;
	mSpriteBuffer[2] = spriteForm;
	return (uint8_t) 1;
}

void RightToLeft::broadcastSprites(uint8_t numberOfSprites) {
	byte result;
//	Serial.println("W");
	Wire.beginTransmission(0); // 0 = broadcast
	Wire.write(numberOfSprites);
//	Serial.println(numberOfSprites);
	int max = 3*numberOfSprites;
	for (int i=0; i<max; i++) {
		Wire.write(mSpriteBuffer[i]);
//		Serial.println(mSpriteBuffer[i]);
	}
	result = Wire.endTransmission(true);
//	switch (result) {
//	case 0:
//		Serial.println("E0");
//		break;
//	case 1:
//		Serial.println("E1");
//		break;
//	case 2:
//		Serial.println("E2");
//		break;
//	case 3:
//		Serial.println("E3");
//		break;
//	case 4:
//		Serial.println("E4");
//		break;
//	default:
//		Serial.println("E");
//	}
}

uint32_t RightToLeft::nextAlarm() {
	return RIGHTTOLEFT_SPEED;
}

void RightToLeft::drawSprites(uint8_t numberOfSprites) {

	mDisplay.clear();
	for (uint8_t i = 0; i<numberOfSprites; i++) {
		Sprite<RainbowduinoDisplay> s = Sprite<RainbowduinoDisplay>(mSpriteBuffer[i*3],
				mSpriteBuffer[i*3+1],
				mSpriteBuffer[i*3+2]);
		s.draw(mViewPort, mDisplay);
	}
	mDisplay.transferToLED();
}
} /* namespace eyes */
