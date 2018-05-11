/*
 * SpritePainter.cpp
 *
 *  Created on: 3 mai 2018
 *      Author: gmo
 */

#include "SpritePainter.h"
#include "Sprite.h"

namespace eyes {

SpritePainter::SpritePainter(int myAddress) {
	mViewPort = ViewPort<RainbowduinoDisplay>(mViewportStartsX[myAddress], SP_FIRST_Y,
			mDisplay.sizeX(), mDisplay.sizeY());
}

void SpritePainter::drawAll(int numberOfSprites, uint8_t spriteArray[]) {
	mDisplay.clear();
	for (int i = 0; i<numberOfSprites; i++) {
		Sprite<RainbowduinoDisplay> s = Sprite<RainbowduinoDisplay>(spriteArray[i*3],
				spriteArray[i*3+1],
				spriteArray[i*3+2]);
		s.draw(mViewPort, mDisplay);
	}
	mDisplay.transferToLED();
}

} /* namespace eyes */
