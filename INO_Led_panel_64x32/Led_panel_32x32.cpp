// Do not remove the include below
#include "Led_panel_32x32.h"

// Do not remove the include below

#include <Adafruit_GFX.h>   // Core graphics library
#include <RGBmatrixPanel.h> // Hardware-specific library

// Similar to F(), but for PROGMEM string pointers rather than literals
#define F2(progmem_ptr) (const __FlashStringHelper *)progmem_ptr

//RGBmatrixPanel *matrix = new RGBmatrixPanel(A, B, C, D, CLK, LAT, OE, false);
// Last parameter = 'true' enables double-buffering, for flicker-free,
// buttery smooth animation.  Note that NOTHING WILL SHOW ON THE DISPLAY
// until the first call to swapBuffers().  This is normal.
#define CLK 11  //8 MUST be on PORTB! (Use pin 11 on Mega)
#define OE  9
#define LAT 10
#define A   A0
#define B   A1
#define C   A2
#define D   A3
//RGBmatrixPanel matrix(A, B, C, D, CLK, LAT, OE, true); //32x32
RGBmatrixPanel matrix(A, B, C, D, CLK, LAT, OE, true, 64); //64x32

#define deltaThresh 15
#define changeWait 10000

const char str[] PROGMEM = "";

const char str2[] PROGMEM
= "PM-ROBOTIX";

int textX = matrix.width(), textMin = sizeof(str) * -8, hue = 0;
int textX2 = matrix.width(), textMin2 = sizeof(str2) * -8;

int myabs(int i) {
    if (i < 0) return -1 * i;
    else return i;
}

void setup() {
    matrix.begin();
    matrix.setTextWrap(false); // Allow text to run off right edge
    matrix.setTextSize(1);
    Serial.begin(9600);
    while (!Serial) {
    }
}

int curMusicVal;
int lastMusicVal;
int delta;
int size;
int lastBigChange = 0;
void loop() {

    curMusicVal = myabs(random(450, 650) - 512); // curMusicVal = myabs(random(450, 550) - 512);
    delta = myabs(curMusicVal - lastMusicVal);

    if (delta < deltaThresh && lastBigChange < changeWait) lastBigChange++;
    else if (delta > 50) lastBigChange = 0;

    Serial.println(lastBigChange);

    matrix.fillScreen(0);
    if (lastBigChange < 10000) {
        size = 7 + (delta / 30);
        drawHeart(&matrix, 16 - size, 11 - size, size * 2); //drawHeart(&matrix, 16 - size, 7 + 4 - size, size * 2);
    }

    lastMusicVal = curMusicVal;

    // Draw big scrolly text on top
    matrix.setTextColor(matrix.ColorHSV(hue, 255, 255, true));
    matrix.setCursor(0, 1);
    //matrix.setTextSize(1);
    matrix.print(F2(str));

    matrix.setCursor(textX2, 21); //21
    //matrix.setTextSize(1);
    matrix.print(F2(str2));

    // Move text left (w/wrap), increase hue
    if ((textX = textX - 2) < textMin) textX = matrix.width();
    hue += 7;
    if (hue >= 1536) hue -= 1536;

    if ((--textX2) < textMin2) textX2 = matrix.width();

    delay(5);	//20
    matrix.swapBuffers(false);
}

void drawHeart(RGBmatrixPanel* matrix, int x, int y, int size) {

    //Bottom left diagonal
    int j = size - 3;
    int i;
    for (i = size / 2 - 1; i > 0; i--) {
        matrix->drawPixel(x + i, y + j, heartred);
        for (int k = i + 1; k < size - i; k++)
            matrix->drawPixel(x + k, y + j, heartredlight);
        if (i == 1) matrix->drawPixel(x + i + 1, y + j, heartredhighlight);
        j--;
    }

    //Left vertical
    matrix->drawPixel(x + i, y + j, heartred);
    for (int k = i + 1; k < size - i; k++)
        matrix->drawPixel(x + k, y + j, heartredlight);
    matrix->drawPixel(x + i + 1, y + j, heartredhighlight);
    j--;
    matrix->drawPixel(x + i, y + j, heartred);
    for (int k = i + 1; k < size - i; k++)
        matrix->drawPixel(x + k, y + j, heartredlight);
    matrix->drawPixel(x + i + 1, y + j, heartredhighlight);
    j--;
    matrix->drawPixel(x + i, y + j, heartred);
    for (int k = i + 1; k < size - i; k++)
        matrix->drawPixel(x + k, y + j, heartredlight);
    matrix->drawPixel(x + i + 1, y + j, heartredhighlight);
    j--;

    //top left diagonal
    for (; j > 0; j--) {
        i++;
        matrix->drawPixel(x + i, y + j, heartred);
        matrix->drawPixel(x + i + 1, y + j, heartredhighlight);
        for (int k = i + 2; k < size - i; k++)
            matrix->drawPixel(x + k, y + j, heartredlight);
    }

    //top left horizontal
    i++;
    int top_row_size = 0;
    for (; i < size / 2 - 1; i++) {
        top_row_size++;
        matrix->drawPixel(x + i, y + j, heartred);
    }

    //top left middle
    j++;
    matrix->drawPixel(x + i, y + j, heartred);

    //Starting on the other half
    //top right middle
    i++;
    matrix->drawPixel(x + i, y + j, heartred);

    //top right horizontal
    i++;
    j--;
    for (int k = 0; k < top_row_size; k++) {
        matrix->drawPixel(x + i, y + j, heartred);
        i++;
    }

    //top right diagonal
    j++;
    for (; i < size; i++) {
        matrix->drawPixel(x + i, y + j, heartred);
        j++;
    }

    //right vertical
    i--;
    matrix->drawPixel(x + i, y + j, heartred);
    j++;
    matrix->drawPixel(x + i, y + j, heartred);

    //bottom right diagonal
    for (; i > size / 2 - 1; i--) {
        matrix->drawPixel(x + i, y + j, heartred);
        j++;
    }
}

void drawFilledHeart(RGBmatrixPanel* matrix, int x, int y, int size) {
    for (int i = 0; i < size / 2; i++) {
        drawHeart(matrix, x + i, y + i, size - i);
    }
}
