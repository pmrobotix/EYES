/*
 * AnimationSelector.cpp
 *
 *  Created on: 9 mai 2018
 *      Author: gmo
 */

#include "AnimationSelector.h"

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
	else {
		animation = &eyeBlinker;
	}
	return animation;
}

} /* namespace eyes */
