/*
 * EyeBlinker.h
 *
 *  Created on: 28 avr. 2018
 *      Author: gmo
 */

#ifndef EYEBLINK_ONE_H_
#define EYEBLINK_ONE_H_

#include <stdint.h>

#include "definitions.h"
#include "EyeBlinker.h"

namespace eyes {
class EyeBlinkOne: public EyeBlinker
{
private:
	uint32_t mStateDurations [EB_NUM_STATES] = {E_RANDOM_5_S, E_ONE_TWENTIFIFTH, E_RANDOM_2_S, E_RANDOM_5_S};
protected:
	uint8_t generateSprites();
	uint32_t nextAlarm();
public:
	EyeBlinkOne();
	virtual ~EyeBlinkOne();
};
}
#endif /* EYEBLINK_ONE_H_ */
