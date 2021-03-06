/*
 * AnimationSelector.h
 *
 *  Created on: 9 mai 2018
 *      Author: gmo
 */

#ifndef ANIMATIONSELECTOR_H_
#define ANIMATIONSELECTOR_H_

#include <stdlib.h>

#include "EyeBlinkOne.h"
#include "RightToLeft.h"

namespace eyes {

class AnimationSelector {
private:
	Animation* animation = NULL;
	EyeBlinker eyeBlinker;
	EyeBlinkOne eyeBlinkOne;
	RightToLeft pmRobotix = RightToLeft(8, 40, -46, 8);
	RightToLeft ufo = RightToLeft(7, 40, -1, 8);
	RightToLeft ba = RightToLeft(9, 40, -56, 9);
public:
	AnimationSelector();
	~AnimationSelector();

	Animation* selectNext();
};

} /* namespace eyes */

#endif /* ANIMATIONSELECTOR_H_ */
