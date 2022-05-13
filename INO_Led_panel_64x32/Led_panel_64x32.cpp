// Do not remove the include below
#include "Led_panel_64x32.h"

#include <ComponentObject.h>
#include <RangeSensor.h>
#include <SparkFun_VL53L1X.h>
#include <vl53l1x_class.h>
#include <vl53l1_error_codes.h>

#include <Adafruit_GFX.h>   // Core graphics library
#include <RGBmatrixPanel.h> // Hardware-specific library

#include <Wire.h>

SFEVL53L1X distanceSensor(Wire, SHUTDOWN_PIN0, INTERRUPT_PIN);
int center[16] = { 135, 143, 151, 159, 167, 175, 183, 191, 199, 207, 215, 223, 231, 239, 247, 255 };

int ledpin = 13;
bool led;

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
int curMusicVal;
int lastMusicVal;
int delta;
int size;
int lastBigChange = 0;

int myabs(int i) {
    if (i < 0) return -1 * i;
    else return i;
}

void setup(void) {
    delay(1000); //delay pour voir afficher sur la console minicom et voir l'initialisation

    // initialize the digital pin as an output.
    pinMode(ledpin, OUTPUT);

    Serial.begin(921600); //921600
    Serial.println("Go");

    Wire.begin();
    Wire.setClock(400000); // use 400 kHz I2C

    matrix.begin();
    matrix.setTextWrap(false); // Allow text to run off right edge
    matrix.setTextSize(1);

    pinMode(SHUTDOWN_PIN0, OUTPUT);
    digitalWrite(SHUTDOWN_PIN0, LOW);
    //digitalWrite(SHUTDOWN_PIN0, HIGH);
    pinMode(SHUTDOWN_PIN0, INPUT);

    delay(10);
    while (!distanceSensor.checkBootState()) {
        //Serial.println("NO checkBootState...");
    }
    //Begin returns 0 on a good init
    if (distanceSensor.begin() == 0) {
        Serial.println("distanceSensor online! ");
        distanceSensor.setI2CAddress((uint8_t) (21 << 1));
    }
    else {
        Serial.println("pb begin() distanceSensor ! ");
    }

    Serial.println("I2C scanner. Scanning Wire...");
    byte count = 0;

    for (byte i = 1; i < 120; i++) {

        Wire.beginTransmission(i);
        if (Wire.endTransmission() == 0) {
            Serial.print("Found address: ");
            Serial.print(i, DEC);
            Serial.print(" (0x");
            Serial.print(i, HEX);
            Serial.println(")");
            count++;
            delay(1);
        }
    }
    Serial.println("Done.");
    Serial.print("Found ");
    Serial.print(count, DEC);
    Serial.println(" device(s).");

    // Intermeasurement period must be >= timing budget. Default = 100 ms.
    distanceSensor.setIntermeasurementPeriod(510);
    distanceSensor.setTimingBudgetInMs(500);
    distanceSensor.setDistanceModeShort();
    distanceSensor.setROICenter(16, 16, center[8]);

}

int ensure = 0;
void loop(void) {
    int dist = 999;
    int i = 0;
    if (led) {
        digitalWrite(ledpin, HIGH);   // turn the LED on (HIGH is the voltage level)
        led = false;
    }
    else {
        digitalWrite(ledpin, LOW);    // turn the LED off by making the voltage LOW
        led = true;
    }

    dist = checkDistance();

    if (dist < DISTANCE_ACTIVATION) {
        ensure ++;
    }
    if (ensure > 5) {
        ensure = 0;
        while (1) {

            if (led) {
                digitalWrite(ledpin, HIGH);   // turn the LED on (HIGH is the voltage level)
                led = false;
            }
            else {
                digitalWrite(ledpin, LOW);    // turn the LED off by making the voltage LOW
                led = true;
            }

            displayPMX();

            //i pour ne pas gener l'affichage avec une pause supplémentaire
            i++;
            if (i > 10) {
                dist = checkDistance();
                if (dist > DISTANCE_ACTIVATION) {
                    ensure++;
                }
                if (ensure > 5)
                {
                    ensure = 0;
                    matrix.clear();
                    matrix.show();
                    i = 0;
                    break;
                }
            }
        }
    }
    delay(500);

}

int checkDistance() {
    int status = 0;
    int dist = 0;
    int ambient = 0;
    int signal = 0;
    distanceSensor.startRanging(); //Write configuration bytes to initiate measurement

    //Attente de la donnée
//    while (!distanceSensor.checkForDataReady()) {
//        delay(1);
//    }

    status = distanceSensor.getRangeStatus();
    ambient = distanceSensor.getAmbientRate();
    signal = distanceSensor.getSignalRate();
    dist = distanceSensor.getDistance();

    delay(5);
    distanceSensor.clearInterrupt();
    distanceSensor.stopRanging();

    Serial.print("D(mm): ");
    Serial.print(dist);
    Serial.print(" Status: ");
    Serial.print(status);
    Serial.print(" Ambient: ");
    Serial.print(ambient);
    Serial.print(" Peak_signal: ");
    Serial.print(signal);
    Serial.println();

    return dist;
}

void displayPMX() {

    curMusicVal = myabs(random(450, 650) - 512); // curMusicVal = myabs(random(450, 550) - 512);
    delta = myabs(curMusicVal - lastMusicVal);

    if (delta < deltaThresh && lastBigChange < changeWait) lastBigChange++;
    else if (delta > 50) lastBigChange = 0;

    //Serial.println(lastBigChange);

    matrix.fillScreen(0);

    //line blue yellow
    matrix.drawLine(0,19, 64, 19, LED_BLUE_HIGH);
    matrix.drawLine(0,29, 64, 29, heartyellowlight);


    if (lastBigChange < 10000) {
        size = 7 + (delta / 30);
        drawHeart(&matrix, 16 - size, 11 - size, size * 2, heartblue, heartbluelight, heartbluehighlight);
        drawHeart(&matrix, 48 - size, 11 - size, size * 2, heartyellow, heartyellowlight, heartyellowhighlight);
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

    delay(5);       //20
    matrix.swapBuffers(false);

}

void drawHeart(RGBmatrixPanel* matrix, int x, int y, int size, uint16_t maincolor, uint16_t lightcolor, uint16_t colorHighlight) {

    //Bottom left diagonal
    int j = size - 3;
    int i;
    for (i = size / 2 - 1; i > 0; i--) {
        matrix->drawPixel(x + i, y + j, maincolor);
        for (int k = i + 1; k < size - i; k++)
            matrix->drawPixel(x + k, y + j, lightcolor);
        if (i == 1) matrix->drawPixel(x + i + 1, y + j, colorHighlight);
        j--;
    }

    //Left vertical
    matrix->drawPixel(x + i, y + j, maincolor);
    for (int k = i + 1; k < size - i; k++)
        matrix->drawPixel(x + k, y + j, lightcolor);
    matrix->drawPixel(x + i + 1, y + j, colorHighlight);
    j--;
    matrix->drawPixel(x + i, y + j, maincolor);
    for (int k = i + 1; k < size - i; k++)
        matrix->drawPixel(x + k, y + j, lightcolor);
    matrix->drawPixel(x + i + 1, y + j, colorHighlight);
    j--;
    matrix->drawPixel(x + i, y + j, maincolor);
    for (int k = i + 1; k < size - i; k++)
        matrix->drawPixel(x + k, y + j, lightcolor);
    matrix->drawPixel(x + i + 1, y + j, colorHighlight);
    j--;

    //top left diagonal
    for (; j > 0; j--) {
        i++;
        matrix->drawPixel(x + i, y + j, maincolor);
        matrix->drawPixel(x + i + 1, y + j, colorHighlight);
        for (int k = i + 2; k < size - i; k++)
            matrix->drawPixel(x + k, y + j, lightcolor);
    }

    //top left horizontal
    i++;
    int top_row_size = 0;
    for (; i < size / 2 - 1; i++) {
        top_row_size++;
        matrix->drawPixel(x + i, y + j, maincolor);
    }

    //top left middle
    j++;
    matrix->drawPixel(x + i, y + j, maincolor);

    //Starting on the other half
    //top right middle
    i++;
    matrix->drawPixel(x + i, y + j, maincolor);

    //top right horizontal
    i++;
    j--;
    for (int k = 0; k < top_row_size; k++) {
        matrix->drawPixel(x + i, y + j, maincolor);
        i++;
    }

    //top right diagonal
    j++;
    for (; i < size; i++) {
        matrix->drawPixel(x + i, y + j, maincolor);
        j++;
    }

    //right vertical
    i--;
    matrix->drawPixel(x + i, y + j, maincolor);
    j++;
    matrix->drawPixel(x + i, y + j, maincolor);

    //bottom right diagonal
    for (; i > size / 2 - 1; i--) {
        matrix->drawPixel(x + i, y + j, maincolor);
        j++;
    }
}

//void drawFilledHeart(RGBmatrixPanel* matrix, int x, int y, int size) {
//    for (int i = 0; i < size / 2; i++) {
//        drawHeart(matrix, x + i, y + i, size - i);
//    }
//}

