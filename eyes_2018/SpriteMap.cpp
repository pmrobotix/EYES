/*
 * SpriteMap.cpp
 *
 *  Created on: 8 avr. 2018
 *      Author: gmo
 */

#include "SpriteMap.h"

#include <avr/pgmspace.h>

#include "definitions.h"
#include "sprite_data.h"

namespace eyes {

SpriteMap::SpriteMap() {
}

unsigned char SpriteMap::size() const {
	return (unsigned char) SPRITE_MAP_SIZE;
}

SpriteIterator SpriteMap::getSprite(unsigned char n) const {
	SpriteIterator si = SpriteIterator(); // dummy value with no pixels!!!
	if (n<(unsigned char) SPRITE_MAP_SIZE) {
		memcpy_P(&(si.mSpriteData), &(sprite_map[n]), sizeof(SpriteData));
		si.init();
	}
	return si;
}

unsigned char SpriteMap::sizeX(unsigned char n) const {
	SpriteData sd;
	memcpy_P(&sd, &(sprite_map[n]), sizeof(SpriteData));
	return sd.sizeX;
}

unsigned char SpriteMap::sizeY(unsigned char n) const {
	SpriteData sd;
	memcpy_P(&sd, &(sprite_map[n]), sizeof(SpriteData));
	return sd.sizeY;
}

} /* namespace eyes */
