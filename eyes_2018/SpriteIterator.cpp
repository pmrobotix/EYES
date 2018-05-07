/*
 * SpriteIterator.cpp
 *
 *  Created on: 8 avr. 2018
 *      Author: gmo
 */

#include "SpriteIterator.h"
#include "avr/pgmspace.h"
#include "definitions.h"
#include "sprite_data.h"
#include <Arduino.h>

namespace eyes {

SpriteIterator::SpriteIterator() {
	mCurrentPosition = -1;
	mFinalPosition = 0;
	mCurrentPixel = SpritePixel(0, 0, 0, 0, 0);
	mPixelData = NULL;
}

bool SpriteIterator::hasNext() const {
	if (mCurrentPosition>=mFinalPosition) {
		return false;
	}
	else {
		return true;
	}
}

void SpriteIterator::init() {
	mCurrentPosition = -1;
	mFinalPosition = (int)mSpriteData.sizeX * (int)mSpriteData.sizeY;
	mPixelData = *(mSpriteData.spritePixels);
	SpriteIterator::findNextSignificantPixel();
}

SpritePixel SpriteIterator::next() {
	SpritePixel p = mCurrentPixel;
	SpriteIterator::findNextSignificantPixel();
	return p;
}

void SpriteIterator::incrementPixel() {

	mCurrentPosition++;
	if (mCurrentPosition==0) {
		mCurrentPixel.mX = mCurrentPixel.mY = 0;
	}
	else {
		mCurrentPixel.mX++;
		if (mCurrentPixel.mX>=mSpriteData.sizeX) {
			mCurrentPixel.mX = 0;
			mCurrentPixel.mY++;
		}
	}
//	Serial.print("Current position=");
//	Serial.println(mCurrentPosition);
}

bool SpriteIterator::findNextSignificantPixel() {
	unsigned short candidatePixel = 0;
	incrementPixel();
	if (mCurrentPosition<mFinalPosition) {
		candidatePixel = pgm_read_word_near(mPixelData+mCurrentPosition);
		while (candidatePixel==TRANSPARENT&&mCurrentPosition<mFinalPosition) {
			incrementPixel();
			if (mCurrentPosition<mFinalPosition) {
				candidatePixel = pgm_read_word_near(mPixelData+mCurrentPosition);
			}
		}
	}
	if (mCurrentPosition<mFinalPosition) {
		mCurrentPixel.setColour(candidatePixel);
//		Serial.print("Found position=");
//		Serial.println(mCurrentPosition);
//		Serial.print(mCurrentPixel.mX);
//		Serial.print(", ");
//		Serial.print(mCurrentPixel.mY);
//		Serial.print(", ");
//		Serial.print(mCurrentPixel.mRed);
//		Serial.print(", ");
//		Serial.print(mCurrentPixel.mGreen);
//		Serial.print(", ");
//		Serial.println(mCurrentPixel.mBlue);
		return true;
	}
	mCurrentPixel.mX = (unsigned char) PIXEL_EXCEPTION_VALUE;
	mCurrentPixel.mY = (unsigned char) PIXEL_EXCEPTION_VALUE;
	mCurrentPixel.mRed = (unsigned char) PIXEL_EXCEPTION_VALUE;
	mCurrentPixel.mGreen = (unsigned char) PIXEL_EXCEPTION_VALUE;
	mCurrentPixel.mBlue = (unsigned char) PIXEL_EXCEPTION_VALUE;
//	Serial.println("No position found.");
	return false;
}

} /* namespace eyes */
