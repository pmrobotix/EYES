// Only modify this file to include
// - function definitions (prototypes)
// - include files
// - extern variable definitions
// In the appropriate section

#ifndef _Led_panel_64x32_H_
#define _Led_panel_64x32_H_

#include "Arduino.h"
//add your includes for the project Led_panel_64x32 here
#include <RGBmatrixPanel.h>


#define DISTANCE_ACTIVATION           210


// This could also be defined as matrix->color(255,0,0) but those defines
// are meant to work for Adafruit::GFX backends that are lacking color()
#define LED_BLACK           0

#define LED_RED_VERYLOW    (3 <<  11)
#define LED_RED_LOW        (7 <<  11)
#define LED_RED_MEDIUM     (15 << 11)
#define LED_RED_HIGH       (31 << 11)

#define LED_GREEN_VERYLOW  (1 <<  5)
#define LED_GREEN_LOW      (15 << 5)
#define LED_GREEN_MEDIUM   (31 << 5)
#define LED_GREEN_HIGH     (63 << 5)

#define LED_BLUE_VERYLOW     3
#define LED_BLUE_LOW         7
#define LED_BLUE_MEDIUM     15
#define LED_BLUE_HIGH       31

#define LED_ORANGE_VERYLOW (LED_RED_VERYLOW + LED_GREEN_VERYLOW)
#define LED_ORANGE_LOW     (LED_RED_LOW     + LED_GREEN_LOW)
#define LED_ORANGE_MEDIUM  (LED_RED_MEDIUM  + LED_GREEN_MEDIUM)
#define LED_ORANGE_HIGH    (LED_RED_HIGH    + LED_GREEN_HIGH)

#define LED_PURPLE_VERYLOW (LED_RED_VERYLOW + LED_BLUE_VERYLOW)
#define LED_PURPLE_LOW     (LED_RED_LOW     + LED_BLUE_LOW)
#define LED_PURPLE_MEDIUM  (LED_RED_MEDIUM  + LED_BLUE_MEDIUM)
#define LED_PURPLE_HIGH    (LED_RED_HIGH    + LED_BLUE_HIGH)

#define LED_CYAN_VERYLOW   (LED_GREEN_VERYLOW + LED_BLUE_VERYLOW)
#define LED_CYAN_LOW       (LED_GREEN_LOW     + LED_BLUE_LOW)
#define LED_CYAN_MEDIUM    (LED_GREEN_MEDIUM  + LED_BLUE_MEDIUM)
#define LED_CYAN_HIGH      (LED_GREEN_HIGH    + LED_BLUE_HIGH)

#define LED_WHITE_VERYLOW  (LED_RED_VERYLOW + LED_GREEN_VERYLOW + LED_BLUE_VERYLOW)
#define LED_WHITE_LOW      (LED_RED_LOW     + LED_GREEN_LOW     + LED_BLUE_LOW)
#define LED_WHITE_MEDIUM   (LED_RED_MEDIUM  + LED_GREEN_MEDIUM  + LED_BLUE_MEDIUM)
#define LED_WHITE_HIGH     (LED_RED_HIGH    + LED_GREEN_HIGH    + LED_BLUE_HIGH)


// Most of the signal pins are configurable, but the CLK pin has some
// special constraints.  On 8-bit AVR boards it must be on PORTB...
// Pin 8 works on the Arduino Uno & compatibles (e.g. Adafruit Metro),
// Pin 11 works on the Arduino Mega.  On 32-bit SAMD boards it must be
// on the same PORT as the RGB data pins (D2-D7)...
// Pin 8 works on the Adafruit Metro M0 or Arduino Zero,
// Pin A4 works on the Adafruit Metro M4 (if using the Adafruit RGB
// Matrix Shield, cut trace between CLK pads and run a wire to A4).

//#define CLK  8   // USE THIS ON ADAFRUIT METRO M0, etc.
//#define CLK A4 // USE THIS ON METRO M4 (not M0)
#define CLK 11 // USE THIS ON ARDUINO MEGA
#define OE   9
#define LAT 10
#define A   A0
#define B   A1
#define C   A2
#define D   A3

#define clear()          fillScreen(0)
#define show()           swapBuffers(true)
#define Color(x,y,z)     Color444(x/16,y/16,z/16)


//Optional interrupt and shutdown pins VL
#define SHUTDOWN_PIN0 2
#define INTERRUPT_PIN -1

//coeur rouge
#define heartred           matrix.Color333(0x61,0,0)
#define heartredlight      matrix.Color333(0xff,0,0)
#define heartredhighlight  matrix.Color333(0xff,0xff,0xff)

//coeur blue
#define heartblue           matrix.Color888(0,0,40)
#define heartbluelight      matrix.Color888(0,0,255)
#define heartbluehighlight  matrix.Color888(0xff,0xff,0xff)

//coeur yellow
#define heartyellow           matrix.Color888(20,20,0)
#define heartyellowlight      matrix.Color888(255,255,0)
#define heartyellowhighlight  matrix.Color888(0xff,0xff,0xff)


int checkDistance();

void displayPMX();

void drawHeart(RGBmatrixPanel* matrix, int x, int y, int size, uint16_t maincolor, uint16_t lightcolor, uint16_t colorHighlight);

//void drawFilledHeart(RGBmatrixPanel* matrix, int x, int y, int size);


//Do not add code below this line
#endif /* _Led_panel_64x32_H_ */
