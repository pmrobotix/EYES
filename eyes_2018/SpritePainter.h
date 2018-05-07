/*
 * SpritePainter.h
 *
 *  Created on: 3 mai 2018
 *      Author: gmo
 */

#ifndef SPRITEPAINTER_H_
#define SPRITEPAINTER_H_

#include "Sprite.h"
#include "RainbowduinoDisplay.h"

#define SP_FIRST_Y 8

namespace eyes {

class SpritePainter {
public:
	SpritePainter(int myAddress);

	void drawAll(int numberOfSprites, uint8_t spriteArray[]);

private:
	RainbowduinoDisplay mDisplay;
	ViewPort<RainbowduinoDisplay> mViewPort;
	unsigned char mViewportStartsX[6] = { 0, 0, 8, 16, 24, 32 };
};

} /* namespace eyes */

#endif /* SPRITEPAINTER_H_ */
