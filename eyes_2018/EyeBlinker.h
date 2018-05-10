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
#include "Animation.h"

#define EB_NUM_STATES 4

namespace eyes {
class EyeBlinker: public Animation
{
private:
	RainbowduinoDisplay mDisplay;
	ViewPort<RainbowduinoDisplay> mViewPort = ViewPort<RainbowduinoDisplay>(E_FIRST_VISIBLE_X, E_FIRST_VISIBLE_Y,
			mDisplay.sizeX(), mDisplay.sizeY());
	uint32_t mStateDurations [EB_NUM_STATES] = {E_RANDOM_5_S, E_ONE_TWENTIFIFTH, E_ONE_TWENTIFIFTH, E_RANDOM_5_S};
protected:
	uint8_t mState = 0;
	uint8_t mPreviousState = 0;
	uint32_t mPreviousMillis;
	uint32_t mNextAlarm;
	uint8_t mSpriteBuffer[E_MAX_SPRITES];
	unsigned char mSpriteForms[EB_NUM_STATES] = {0, 1, 2, 0};
	virtual uint8_t generateSprites();
	virtual uint32_t nextAlarm();
	virtual void broadcastSprites(uint8_t numberOfSprites);
	virtual void drawSprites(uint8_t numberOfSprites);
	virtual void executeAction();
public:
	EyeBlinker();
	virtual ~EyeBlinker();
	virtual void run(unsigned long currentMillis);
	virtual bool hasFinished();
	virtual void update(unsigned long currentMillis);
};
}
#endif /* EYEBLINKER_H_ */
