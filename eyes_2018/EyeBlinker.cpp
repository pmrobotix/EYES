/*
 * EyeBlinker.cpp
 *
 *  Created on: 28 avr. 2018
 *      Author: gmo
 */

#include "EyeBlinker.h"
#include <Arduino.h>
#include <Wire.h>

namespace eyes {

EyeBlinker::EyeBlinker() {
	mState = 0;
	mPreviousMillis = millis();
	mNextAlarm = nextAlarm();
}

void EyeBlinker::update(unsigned long currentMillis) {
	uint32_t now = (uint32_t) currentMillis;
//	Serial.println("A0");
	if (now < mPreviousMillis || now >= mPreviousMillis+mNextAlarm) {
		mPreviousState = mState;
		mState++;
		mState = mState % E_NUM_STATES;
		mNextAlarm = nextAlarm();
		mPreviousMillis = now;
//		Serial.println("A1");
		executeAction();
	}
}

void EyeBlinker::executeAction() {
	uint8_t numberOfSprites = generateSprites();
	broadcastSprites(numberOfSprites);
	drawSprites(numberOfSprites);
}

uint8_t EyeBlinker::generateSprites() {
	// inside the sprite buffer, the values are coded as:
	// x, y, SpriteFormNumber
	uint8_t spriteForm = mSpriteForms[mState];
	mSpriteBuffer[0] = (uint8_t) E_LEFT_EYE_POSITION_X;
	mSpriteBuffer[1] = (uint8_t) E_EYE_POSITION_Y;
	mSpriteBuffer[2] = spriteForm;
	mSpriteBuffer[3] = (uint8_t) E_RIGHT_EYE_POSITION_X;
	mSpriteBuffer[4] = (uint8_t) E_EYE_POSITION_Y;
	mSpriteBuffer[5] = spriteForm;
	return (uint8_t) E_NUM_EYES;
}

void EyeBlinker::broadcastSprites(uint8_t numberOfSprites) {
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

uint32_t EyeBlinker::nextAlarm() {
	uint32_t result;
	switch(mStateDurations[(int)mState]) {
	case E_RANDOM_5_S:
		result = (uint32_t) (5000l+random(-E_RANDOM_MILLIS, E_RANDOM_MILLIS+1));
		break;
	case E_ONE_TWENTIFIFTH:
		result = (uint32_t) 40l;
		break;
	case E_TWO_TWENTIFIFTH:
		result = (uint32_t) 80l;
		break;
	default:
		result = (uint32_t) 1000l;
	}
	return result;
}

void EyeBlinker::drawSprites(uint8_t numberOfSprites) {
	using namespace eyes;

	mDisplay.clear();
	for (uint8_t i = 0; i<numberOfSprites; i++) {
		Sprite<RainbowduinoDisplay> s = Sprite<RainbowduinoDisplay>(mSpriteBuffer[i*3],
				mSpriteBuffer[i*3+1],
				mSpriteBuffer[i*3+2]);
		s.draw(mViewPort, mDisplay);
	}
	mDisplay.transferToLCD();
}
} /* namespace eyes */
