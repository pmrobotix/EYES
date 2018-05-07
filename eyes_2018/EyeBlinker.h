/*
 * EyeBlinker.h
 *
 *  Created on: 28 avr. 2018
 *      Author: gmo
 */

#ifndef EYEBLINKER_H_
#define EYEBLINKER_H_

#include <stdint.h>
#include "Sprite.h"
#include "RainbowduinoDisplay.h"
/* 1/25 of second in milliseconds */
#define E_TWENTYFIFTH_OF_SECOND 40

#define E_NUM_STATES 3
/* Some symbolic durations */
#define E_ONE_TWENTIFIFTH 1
#define E_TWO_TWENTIFIFTH 2
#define E_RANDOM_5_S 3

#define E_RANDOM_MILLIS (1500l)

#define E_MAX_SPRITES 10

#define E_NUM_EYES 2

#define E_LEFT_EYE_POSITION_X 12
#define E_RIGHT_EYE_POSITION_X 28
#define E_EYE_POSITION_Y 8

#define E_FIRST_VISIBLE_X 8
#define E_FIRST_VISIBLE_Y 8

namespace eyes {
class EyeBlinker
{
private:
	uint8_t mState = 0;
	uint8_t mPreviousState = 0;
	uint32_t mStateDurations [E_NUM_STATES] = {E_RANDOM_5_S, E_ONE_TWENTIFIFTH, E_ONE_TWENTIFIFTH};
	unsigned char mSpriteForms[E_NUM_STATES] = {0, 1, 2};
	uint32_t mPreviousMillis;
	uint32_t mNextAlarm;
	uint8_t mSpriteBuffer[E_MAX_SPRITES];
	RainbowduinoDisplay mDisplay;
	ViewPort<RainbowduinoDisplay> mViewPort = ViewPort<RainbowduinoDisplay>(E_FIRST_VISIBLE_X, E_FIRST_VISIBLE_Y,
			mDisplay.sizeX(), mDisplay.sizeY());
	uint32_t nextAlarm();
	uint8_t generateSprites();
	void broadcastSprites(uint8_t numberOfSprites);
	void drawSprites(uint8_t numberOfSprites);
	void executeAction();
public:
	EyeBlinker();

	void update(unsigned long currentMillis);
};
}
#endif /* EYEBLINKER_H_ */
