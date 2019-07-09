/*
 * sprite_data.c
 *
 *  Created on: 8 avr. 2018
 *      Author: gmo
 */

#include "sprite_data.h"

#include "resources/ba.ino"
#include "resources/green_closed.ino"
#include "resources/green_closing.ino"
#include "resources/green_left.ino"
#include "resources/green_normal.ino"
#include "resources/green_right.ino"
#include "resources/heart.ino"
#include "resources/heart_s.ino"
#include "resources/pmr.ino"
#include "resources/robotix.ino"

const SpriteData sprite_map[SPRITE_MAP_SIZE] PROGMEM= {
		{ (unsigned char) 8, (unsigned char) 8, &green_normal },
		{ (unsigned char) 8, (unsigned char) 8, &green_closing },
		{ (unsigned char) 8, (unsigned char) 8, &green_closed },
		{ (unsigned char) 8, (unsigned char) 8, &green_left },
		{ (unsigned char) 8, (unsigned char) 8, &green_right },
		{ (unsigned char) 7, (unsigned char) 7, &heart },
		{ (unsigned char) 5, (unsigned char) 5, &heart_s },
		{ (unsigned char) 9, (unsigned char) 8, &robotix },
		{ (unsigned char) 52, (unsigned char) 7, &pmr },
		{ (unsigned char) 62, (unsigned char) 5, &ba }
};
