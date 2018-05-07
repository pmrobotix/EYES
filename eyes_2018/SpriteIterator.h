/*
 * SpriteIterator.h
 *
 *  Created on: 8 avr. 2018
 *      Author: gmo
 */

#ifndef SPRITEITERATOR_H_
#define SPRITEITERATOR_H_

#include "SpritePixel.h"
#include "sprite_data.h"

namespace eyes {

/*
 * An iterator through a sprite.
 * It returns pixels with coordinates
 * that are relative to the sprite!
 * The iterator only returns non-transparent pixels.
 * Transparent pixels are simply skipped.
 */
class SpriteIterator {
public:
	SpriteData mSpriteData;

	SpriteIterator();
	void init();
	/*
	 * If no pixel is available,
	 * false is returned.
	 */
	bool hasNext() const;
	/*
	 * If no pixel is available,
	 * a pixel having only
	 * PIXEL_EXCEPTION_VALUE for each value
	 * is returned!
	 */
	SpritePixel next();
private:
	int mCurrentPosition;
	int mFinalPosition;
	const unsigned short * mPixelData;
	SpritePixel mCurrentPixel;
	bool findNextSignificantPixel();
	void incrementPixel();
};

} /* namespace eyes */

#endif /* SPRITEITERATOR_H_ */
