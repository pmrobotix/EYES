/*
 * SpriteMap.h
 *
 *  Created on: 8 avr. 2018
 *      Author: gmo
 */

#ifndef SPRITEMAP_H_
#define SPRITEMAP_H_

#include "SpriteIterator.h"

namespace eyes {

class SpriteMap {
public:
	SpriteMap();

	unsigned char size() const;

	SpriteIterator getSprite(unsigned char n) const;

	unsigned char sizeX(unsigned char n) const;
	unsigned char sizeY(unsigned char n) const;

};

extern SpriteMap spriteMap;

} /* namespace eyes */

#endif /* SPRITEMAP_H_ */
