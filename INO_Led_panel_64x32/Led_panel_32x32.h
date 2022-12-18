// Only modify this file to include
// - function definitions (prototypes)
// - include files
// - extern variable definitions
// In the appropriate section

#include <RGBmatrixPanel.h>

#ifndef _Led_panel_32x32_H_
#define _Led_panel_32x32_H_
#include "Arduino.h"

//add your function definitions for the project led_stella here
#define heartred           matrix->Color333(0x61,0,0)
#define heartredlight      matrix->Color333(0xff,0,0)
#define heartredhighlight  matrix->Color333(0xff,0xff,0xff)

void drawHeart(RGBmatrixPanel* matrix, int x, int y, int size);

void drawFilledHeart(RGBmatrixPanel* matrix, int x, int y, int size);

//Do not add code below this line
#endif /* _Led_panel_32x32_H_ */
