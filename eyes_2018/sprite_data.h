/*
 * data.h
 *
 *  Created on: 8 avr. 2018
 *      Author: gmo
 */

#ifndef SPRITE_DATA_H_
#define SPRITE_DATA_H_
#include "avr/pgmspace.h"

#include "definitions.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct SpriteData {
	#pragma pack(push, 1)
	unsigned char sizeX;
	unsigned char sizeY;
	const unsigned short (*spritePixels)[];
	#pragma pack(pop)
} SpriteData;

extern const SpriteData sprite_map[SPRITE_MAP_SIZE];

#ifdef __cplusplus
}
#endif

#endif /* SPRITE_DATA_H_ */
