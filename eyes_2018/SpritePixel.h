/*
 * SpritePixel.h
 *
 *  Created on: 8 avr. 2018
 *      Author: gmo
 */

#ifndef SPRITEPIXEL_H_
#define SPRITEPIXEL_H_

namespace eyes {

class SpritePixel {
public:
	unsigned char mX;
	unsigned char mY;
	unsigned char mRed;
	unsigned char mGreen;
	unsigned char mBlue;
	SpritePixel(unsigned char x, unsigned char y, unsigned char red, unsigned char green, unsigned char blue);
	SpritePixel();
	void setColour(unsigned short rgb565);
};

} /* namespace eyes */

#endif /* SPRITEPIXEL_H_ */
