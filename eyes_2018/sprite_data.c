/*
 * sprite_data.c
 *
 *  Created on: 8 avr. 2018
 *      Author: gmo
 */

#include "definitions.h"
#include "sprite_data.h"
#include <avr/pgmspace.h>

#include "resources/green_closed.ino"
#include "resources/green_closing.ino"
#include "resources/green_normal.ino"

const SpriteData sprite_map[SPRITE_MAP_SIZE] PROGMEM= {
		{ (unsigned char) 8, (unsigned char) 8, &green_normal },
		{ (unsigned char) 8, (unsigned char) 8, &green_closing },
		{ (unsigned char) 8, (unsigned char) 8, &green_closed }
};
