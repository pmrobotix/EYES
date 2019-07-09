/*
 * EyeBlinkOne.cpp
 *
 *  Created on: 9 mai 2018
 *      Author: gmo
 */

#include "EyeBlinkOne.h"

#include <Arduino.h>

namespace eyes {

EyeBlinkOne::EyeBlinkOne() {
	mState = 0;
	mPreviousMillis = millis();
	mNextAlarm = nextAlarm();
}

EyeBlinkOne::~EyeBlinkOne() {
}

uint8_t EyeBlinkOne::generateSprites() {
	// inside the sprite buffer, the values are coded as:
	// x, y, SpriteFormNumber
	uint8_t spriteForm = mSpriteForms[mState];
	mSpriteBuffer[0] = (uint8_t) E_LEFT_EYE_POSITION_X;
	mSpriteBuffer[1] = (uint8_t) E_EYE_POSITION_Y;
	mSpriteBuffer[2] = (uint8_t)0;
	mSpriteBuffer[3] = (uint8_t) E_RIGHT_EYE_POSITION_X;
	mSpriteBuffer[4] = (uint8_t) E_EYE_POSITION_Y;
	mSpriteBuffer[5] = spriteForm;
	return (uint8_t) E_NUM_EYES;
}

uint32_t EyeBlinkOne::nextAlarm() {
	uint32_t result;
	switch(mStateDurations[(int)mState]) {
	case E_RANDOM_5_S:
		result = (uint32_t) (2500l+random(-E_RANDOM_MILLIS, E_RANDOM_MILLIS+1));
		break;
	case E_RANDOM_2_S:
		result = (uint32_t) (1000l+random(-500l, 501l));
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
}
