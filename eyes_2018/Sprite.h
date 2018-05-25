/*
 * Sprite.h
 *
 *  Created on: 8 avr. 2018
 *      Author: gmo
 */

#ifndef SPRITE_H_
#define SPRITE_H_

#include "SpritePixel.h"
#include "SpriteMap.h"
#include <Arduino.h>

namespace eyes {

/*
 * Forward reference to ViewPort class.
 */
template <typename LCDDisplay>
class ViewPort;

/*
 * A sprite is a rectangular graphical object having a specific form from the SpriteMap and a specific position.
 * Its size is defined by the SpriteMap.
 */
template <typename LCDDisplay>
class Sprite {
public:
	char mX;
	char mY;
	unsigned char mSizeX;
	unsigned char mSizeY;
	unsigned char mForm;
	Sprite(char x, char y, unsigned char form) {
		mX = x;
		mY = y;
		mSizeX = spriteMap.sizeX(form);
		mSizeY = spriteMap.sizeY(form);
		mForm = form;
	}

	void draw(ViewPort<LCDDisplay>& viewPort, LCDDisplay& d) const {
		if (viewPort.isSpriteVisible(this)) {
			SpriteIterator i = spriteMap.getSprite(mForm);
			while (i.hasNext()) {
				SpritePixel p = i.next();
				SpritePixel absolutePosition = SpritePixel();
				absolutePosition.mX = mX+p.mX;
				absolutePosition.mY = mY+p.mY;
//				Serial.print("setPixel x=");
//				Serial.print(absolutePosition.mX);
//				Serial.print(" y=");
//				Serial.print(absolutePosition.mY);
//				Serial.print(" R=");
//				Serial.print(absolutePosition.mRed);
//				Serial.print(" G=");
//				Serial.print(absolutePosition.mGreen);
//				Serial.print(" B=");
//				Serial.println(absolutePosition.mBlue);
				if (viewPort.isPixelVisible(absolutePosition)) {
					absolutePosition.mX -= viewPort.mX;
					absolutePosition.mY -= viewPort.mY;
					absolutePosition.mRed = p.mRed;
					absolutePosition.mGreen = p.mGreen;
					absolutePosition.mBlue = p.mBlue;
					d.draw(absolutePosition);
				}
			}
		}
	}
};

/*
 * Within a display being dx pixels wide and dy pixels high,
 * define the visible zone.
 * It is assumed that (0,0) is in the upper left corner
 * and that the values grow towards the right resp. towards the bottom.
 */
template <typename D>
class ViewPort {
private:
	char mMaxX;
	char mMaxY;
public:
	char mX;
	char mY;
	ViewPort(char x, char y, unsigned char dx, unsigned char dy) {
		mX = x;
		mY = y;
		mMaxX = x+dx-1;
		mMaxY = y+dy-1;
	}
	ViewPort() {
		mX = 0;
		mY = 0;
		mMaxX = 0;
		mMaxY = 0;
	}

	/*
	 * Return true if and only if there is a non-empty intersection between the sprite and the ViewPort
	 */
	bool isSpriteVisible(const Sprite<D>* s) const {
		char maxX = s->mX + s->mSizeX - 1;
		char maxY = s->mY + s->mSizeY - 1;
		char x = s->mX;
		char y = s->mY;

		if (x <= mMaxX && maxX >= mX && y <= mMaxY && maxY >= mY) {
//			Serial.print("mX=");
//			Serial.print((int)mX);
//			Serial.print(" mY=");
//			Serial.print((int)mY);
//			Serial.print(" mMaxX=");
//			Serial.print((int)mMaxX);
//			Serial.print(" mMaxY=");
//			Serial.println((int)mMaxY);
//			Serial.print("x=");
//			Serial.print((int)x);
//			Serial.print(" y=");
//			Serial.print((int)y);
//			Serial.print(" maxX=");
//			Serial.print((int)maxX);
//			Serial.print(" maxY=");
//			Serial.println((int)maxY);
			return true;
		}
		return false;
	}

	/*
	 * Return true if the given pixel is in the visible area
	 */
	bool isPixelVisible(const SpritePixel& p) const {
		return (p.mX >= mX && p.mX <= mMaxX && p.mY >= mY && p.mY <= mMaxY);
	}
};

} /* namespace eyes */

#endif /* SPRITE_H_ */
