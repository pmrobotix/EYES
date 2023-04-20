// Do not remove the include below
#include "INO_Led_Panel_64x32_2023.h"

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

int myabs(int i)
{
    if (i < 0)
        return -1 * i;
    else
        return i;
}

/**Table of Optical Centers**
 *
 * 128,136,144,152,160,168,176,184,  192,200,208,216,224,232,240,248
 * 129,137,145,153,161,169,177,185,  193,201,209,217,225,233,241,249
 * 130,138,146,154,162,170,178,186,  194,202,210,218,226,234,242,250
 * 131,139,147,155,163,171,179,187,  195,203,211,219,227,235,243,251
 * 132,140,148,156,164,172,180,188,  196,204,212,220,228,236,244,252
 * 133,141,149,157,165,173,181,189,  197,205,213,221,229,237,245,253
 * 134,142,150,158,166,174,182,190,  198,206,214,222,230,238,246,254
 * 135,143,151,159,167,175,183,191,  199,207,215,223,231,239,247,255

 * 127,119,111,103, 95, 87, 79, 71,  63, 55, 47, 39, 31, 23, 15, 7
 * 126,118,110,102, 94, 86, 78, 70,  62, 54, 46, 38, 30, 22, 14, 6
 * 125,117,109,101, 93, 85, 77, 69,  61, 53, 45, 37, 29, 21, 13, 5
 * 124,116,108,100, 92, 84, 76, 68,  60, 52, 44, 36, 28, 20, 12, 4
 * 123,115,107, 99, 91, 83, 75, 67,  59, 51, 43, 35, 27, 19, 11, 3
 * 122,114,106, 98, 90, 82, 74, 66,  58, 50, 42, 34, 26, 18, 10, 2
 * 121,113,105, 97, 89, 81, 73, 65,  57, 49, 41, 33, 25, 17, 9, 1
 * 120,112,104, 96, 88, 80, 72, 64,  56, 48, 40, 32, 24, 16, 8, 0 Pin 1
 *
 * To set the center, set the pad that is to the right and above the exact center of the region you'd like to measure as your opticalCenter*/

void setup(void)
{
    delay(1000); //delay pour voir afficher sur la console minicom et voir l'initialisation

    // initialize the digital pin as an output.
    pinMode(ledpin, OUTPUT);

    Serial.begin(115200); //921600
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
    } else {
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
    distanceSensor.setIntermeasurementPeriod(22);
    distanceSensor.setTimingBudgetInMs(20);
    distanceSensor.setDistanceModeShort();
    distanceSensor.setROICenter(4, 16, center[8]);

}

int ensure = 0;
void loop(void)
{

    checkDistCenterMulti();
    /*
     int dist = 999;
     int dist1 = 999;
     int dist2 = 999;
     int dist3 = 999;
     int dist4 = 999;
     while (1) {
     //135,143,151,159, 167,175,183,191,  199,207,215,223, 231,239,247,255
     //dist = checkDistance();
     dist1 = checkDistCenter(151);
     delay(22);
     dist2 = checkDistCenter(183);
     delay(22);
     dist3 = checkDistCenter(215);
     delay(22);
     dist4 = checkDistCenter(247);
     if (led) {
     digitalWrite(ledpin, HIGH);   // turn the LED on (HIGH is the voltage level)
     led = false;
     } else {
     digitalWrite(ledpin, LOW);    // turn the LED off by making the voltage LOW
     led = true;
     }

     Serial.print("mm1: ");
     Serial.print(dist1);
     Serial.print(" ");
     Serial.print(dist2);
     Serial.print(" ");
     Serial.print(dist3);
     Serial.print(" ");
     Serial.print(dist4);
     Serial.println();

     delay(30);
     }
     */
}

int checkDistCenterMulti()
{
    int ball_count = 0;
    int ball_count_zone = 0;
    bool ready = 0;
    int dist[4] = { 0 };
    int status[4] = { 0 };
    int zone = 0;
    distanceSensor.setIntermeasurementPeriod(17);
    distanceSensor.setTimingBudgetInMs(15);
    distanceSensor.setDistanceModeShort();

    //135,143,151,159, 167,175,183,191,  199,207,215,223, 231,239,247,255
    int _center[4] = { 151, 183, 215, 247 };
    distanceSensor.setROICenter(4, 8, _center[zone]);
    distanceSensor.startRanging();

    while (1) {
        while (ready == 0) {
            ready = distanceSensor.checkForDataReady();
            delay(1);
        }
        ready = 0;
        status[zone] = distanceSensor.getRangeStatus();
        dist[zone] = distanceSensor.getDistance();
        /*
         int roix = distanceSensor.getROIX();
         int roiy = distanceSensor.getROIY();
         Serial.print(_center[zone]);
         Serial.print(" ROI x: ");
         Serial.print(roix);
         Serial.print(" y: ");
         Serial.print(roiy); */
        /*
         Serial.print(" s: ");
         Serial.print(status);
         Serial.print(" mm: ");
         Serial.print(dist);
         Serial.println();
         */

        distanceSensor.clearInterrupt();

        zone++;

        if (zone == 4) {

            //print
            Serial.print(" mm: ");
            for (int i = 0; i < 4; i++) {
                if (dist[i] < 100) //moins de 100mm
                {
                    ball_count_zone++;
                }
                Serial.print(dist[i]);
//                Serial.print(" (");
//                Serial.print(status[i]);
//                Serial.print(") ");
                Serial.print(" ");

            }
            if (ball_count_zone>0)
            {
                ball_count++;
            }
            Serial.print("  ");
            Serial.print(ball_count_zone);
                            Serial.print("   ");
                            Serial.print(ball_count);
            Serial.println();

            ball_count_zone = 0;
            zone = 0;
            //delay(400);
        }
        distanceSensor.setROICenter(4, 8, _center[zone]);
        delay(15);
    }
}

int checkDistCenter(int center)
{
    int status = 0;
    int dist = 0;
    int ambient = 0;
    int signal = 0;
    distanceSensor.setROICenter(4, 8, center);
    /*
     int roix = distanceSensor.getROIX();
     int roiy = distanceSensor.getROIY();

     Serial.print(center);
     Serial.print(" ROI x: ");
     Serial.print(roix);
     Serial.print(" y: ");
     Serial.print(roiy);
     Serial.print(" ");
     */
    distanceSensor.startRanging(); //Write configuration bytes to initiate measurement

    //Attente de la donnée
//    while (!distanceSensor.checkForDataReady()) {
//        delay(1);
//    }

//    status = distanceSensor.getRangeStatus();
//    ambient = distanceSensor.getAmbientRate();
//    signal = distanceSensor.getSignalRate();
    dist = distanceSensor.getDistance();

    delay(5);
    distanceSensor.clearInterrupt();
    distanceSensor.stopRanging();
    /*
     Serial.print("D(mm): ");
     Serial.print(dist);
     Serial.print(" Status: ");
     Serial.print(status);
     Serial.print(" Ambient: ");
     Serial.print(ambient);
     Serial.print(" Peak_signal: ");
     Serial.print(signal);
     Serial.println();
     */
    return dist;
}

int checkDistance()
{
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

void displayPMX()
{

    curMusicVal = myabs(random(450, 650) - 512); // curMusicVal = myabs(random(450, 550) - 512);
    delta = myabs(curMusicVal - lastMusicVal);

    if (delta < deltaThresh && lastBigChange < changeWait)
        lastBigChange++;
    else if (delta > 50)
        lastBigChange = 0;

    //Serial.println(lastBigChange);

    matrix.fillScreen(0);

    //line blue yellow
    matrix.drawLine(0, 19, 64, 19, LED_BLUE_HIGH);
    matrix.drawLine(0, 29, 64, 29, heartyellowlight);

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
    if ((textX = textX - 2) < textMin)
        textX = matrix.width();
    hue += 7;
    if (hue >= 1536)
        hue -= 1536;

    if ((--textX2) < textMin2)
        textX2 = matrix.width();

    delay(5);       //20
    matrix.swapBuffers(false);

}

void drawHeart(RGBmatrixPanel *matrix, int x, int y, int size, uint16_t maincolor, uint16_t lightcolor,
        uint16_t colorHighlight)
{

    //Bottom left diagonal
    int j = size - 3;
    int i;
    for (i = size / 2 - 1; i > 0; i--) {
        matrix->drawPixel(x + i, y + j, maincolor);
        for (int k = i + 1; k < size - i; k++)
            matrix->drawPixel(x + k, y + j, lightcolor);
        if (i == 1)
            matrix->drawPixel(x + i + 1, y + j, colorHighlight);
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

