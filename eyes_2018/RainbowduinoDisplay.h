/*
 * RainbowduinoDisplay.h
 *
 *  Created on: 26 avr. 2018
 *      Author: gmo
 */

#ifndef RAINBOWDUINODISPLAY_H_
#define RAINBOWDUINODISPLAY_H_

#include "SpritePixel.h"

namespace eyes {

/*
 * Class for a 2D LCD display
 * driven by a Rainbowduino v3 card.
 */
class RainbowduinoDisplay {
public:
	RainbowduinoDisplay();
	~RainbowduinoDisplay();

	static unsigned char sizeX();
	static unsigned char sizeY();
	void init() const;
	void clear();
	void draw(SpritePixel& p);
	void transferToLED();

private:
	bool mMustTransferToLED;
	static void internalDraw(int x, int y, unsigned char red, unsigned char green, unsigned char blue);
};

} /* namespace eyes */

#endif /* RAINBOWDUINODISPLAY_H_ */
