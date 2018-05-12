/*
 * RightToLeft.h
 *
 *  Created on: 11 mai 2018
 *      Author: gmo
 */

#ifndef RIGHTTOLEFT_H_
#define RIGHTTOLEFT_H_

#include "Animation.h"
#include "RainbowduinoDisplay.h"
#include "Sprite.h"
#include <stdint.h>

#define RIGHTTOLEFT_SPEED (150L)
#define RIGHTTOLEFT_SPRITE_SIZE (3)
namespace eyes {

class RightToLeft: public Animation {
private:
	uint8_t mSprite;
	char mFirstXPosition;
	char mLastXPosition;
	char mYPosition;
	char mCurrentXPosition;
	uint32_t mPreviousMillis;
	uint32_t mNextAlarm;
	uint8_t mSpriteBuffer[RIGHTTOLEFT_SPRITE_SIZE];
	RainbowduinoDisplay mDisplay;
	ViewPort<RainbowduinoDisplay> mViewPort = ViewPort<RainbowduinoDisplay>(E_FIRST_VISIBLE_X, E_FIRST_VISIBLE_Y,
			mDisplay.sizeX(), mDisplay.sizeY());
protected:
	virtual uint8_t generateSprites();
	virtual uint32_t nextAlarm();
	virtual void broadcastSprites(uint8_t numberOfSprites);
	virtual void drawSprites(uint8_t numberOfSprites);
	virtual void executeAction();
public:
	RightToLeft(uint8_t sprite, char firstXPosition, char lastXPosition, char yPosition);
	virtual ~RightToLeft();
	virtual void run(unsigned long currentMillis);
	virtual bool hasFinished();
	virtual void update(unsigned long currentMillis);
};

} /* namespace eyes */

#endif /* RIGHTTOLEFT_H_ */
