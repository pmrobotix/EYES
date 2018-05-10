/*
 * Animation.h
 *
 *  Created on: 9 mai 2018
 *      Author: gmo
 */

#ifndef ANIMATION_H_
#define ANIMATION_H_

namespace eyes {

class Animation {
public:
	virtual ~Animation() {}
	virtual void run(unsigned long currentMillis) = 0;
	virtual bool hasFinished() = 0;
	virtual void update(unsigned long currentMillis) = 0;
};

} /* namespace eyes */

#endif /* ANIMATION_H_ */
