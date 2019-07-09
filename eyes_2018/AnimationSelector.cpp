/*
 * AnimationSelector.cpp
 *
 *  Created on: 9 mai 2018
 *      Author: gmo
 */

#include "AnimationSelector.h"

#include <Arduino.h>

namespace eyes {

AnimationSelector::AnimationSelector() {
	animation = &eyeBlinker;
	randomSeed(analogRead(0));
}

AnimationSelector::~AnimationSelector() {
	animation = NULL;
}

Animation* AnimationSelector::selectNext() {
	long p = random(100);
	if (p>=90l) {
		animation = &eyeBlinkOne;
	}
	else if (p>=85) {
		animation = &ufo;
	}
	else if (p>=80) {
		animation = &pmRobotix;
	}
	else if (p>=75) {
		animation = &ba;
	}
	else {
		animation = &eyeBlinker;
	}
	return animation;
}

} /* namespace eyes */
