// Do not remove the include below

#include "eyes_2017.h"

#include <Wire.h>
#include <Adafruit_GFX.h>
#include "Adafruit_LEDBackpack.h"

Adafruit_8x16minimatrix matrix = Adafruit_8x16minimatrix();
Adafruit_8x16minimatrix matrixLeft = Adafruit_8x16minimatrix();

void setup() {
	//while (!Serial);
	Serial.begin(9600);
	Serial.println("16x8 LED Mini Matrix Test");

	matrix.begin(0x70);  // pass in the address
	matrixLeft.begin(0x71);
	matrix.setBrightness(4);
	matrixLeft.setBrightness(1);
}

static const uint8_t PROGMEM
eye_g_test001_bmp[] = {
B11111111,
B11111111,
B11110001,
B11100001,
B11100001,
B11100001,
B11111111,
B11111111 }, smile_bmp[] = { B00111100,
B01000010,
B10100101,
B10000001,
B10100101,
B10011001,
B01000010,
B00111100 }, neutral_bmp[] = { B00111100,
B01000010,
B10100101,
B10000001,
B10111101,
B10000001,
B01000010,
B00111100 }, frown_bmp[] = { B00111100,
B01000010,
B10100101,
B10000001,
B10011001,
B10100101,
B01000010,
B00111100 };

void loop() {

	matrix.clear();
	matrix.drawBitmap(0, 0, eye_g_test001_bmp, 8, 8, LED_ON);
	matrix.writeDisplay();
	matrixLeft.clear();
	matrixLeft.drawBitmap(0, 0, eye_g_test001_bmp, 8, 8, LED_ON);
	matrixLeft.writeDisplay();

	delay(500);

	matrix.clear();
	matrix.drawBitmap(0, 0, smile_bmp, 8, 8, LED_ON);
	matrix.writeDisplay();
	matrixLeft.clear();
	matrixLeft.drawBitmap(0, 0, smile_bmp, 8, 8, LED_ON);
	matrixLeft.writeDisplay();

	delay(500);

	matrix.clear();
	matrix.drawBitmap(0, 8, neutral_bmp, 8, 8, LED_ON);
	matrix.writeDisplay();
	matrixLeft.clear();
	matrixLeft.drawBitmap(0, 8, neutral_bmp, 8, 8, LED_ON);
	matrixLeft.writeDisplay();
	delay(500);

	matrix.clear();
	matrix.drawBitmap(0, 0, frown_bmp, 8, 8, LED_ON);
	matrix.writeDisplay();
	matrixLeft.clear();
	matrixLeft.drawBitmap(0, 0, frown_bmp, 8, 8, LED_ON);
	matrixLeft.writeDisplay();
	delay(500);

	matrix.drawPixel(0, 0, LED_ON);
	matrix.writeDisplay();  // write the changes we just made to the display
	matrixLeft.drawPixel(0, 0, LED_ON);
	matrixLeft.writeDisplay();  // write the changes we just made to the display
	delay(500);

	matrix.clear();
	matrix.drawLine(0, 0, 7, 15, LED_ON);
	matrix.writeDisplay();  // write the changes we just made to the display
	matrixLeft.clear();
	matrixLeft.drawLine(0, 0, 7, 15, LED_ON);
	matrixLeft.writeDisplay();  // write the changes we just made to the display
	delay(500);

	matrix.clear();
	matrix.drawRect(0, 0, 8, 16, LED_ON);
	matrix.fillRect(2, 2, 4, 12, LED_ON);
	matrix.writeDisplay();  // write the changes we just made to the display
	matrixLeft.clear();
	matrixLeft.drawRect(0, 0, 8, 16, LED_ON);
	matrixLeft.fillRect(2, 2, 4, 12, LED_ON);
	matrixLeft.writeDisplay();  // write the changes we just made to the display
	delay(500);

	matrix.clear();
	matrix.drawCircle(3, 8, 3, LED_ON);
	matrix.writeDisplay();  // write the changes we just made to the display
	matrixLeft.clear();
	matrixLeft.drawCircle(3, 8, 3, LED_ON);
	matrixLeft.writeDisplay();  // write the changes we just made to the display
	delay(500);

	matrix.setTextSize(2);
	matrix.setTextWrap(false); // we dont want text to wrap so it scrolls nicely
	matrix.setTextColor(LED_ON);
	matrixLeft.setTextSize(2);
	matrixLeft.setTextWrap(false); // we dont want text to wrap so it scrolls nicely
	matrixLeft.setTextColor(LED_ON);
	for (int8_t x = 0; x >= -64; x--) {
		matrix.clear();
		matrixLeft.clear();
		matrix.setCursor(x, 0);
		matrix.print("PMX");

		matrixLeft.setCursor(x, 0);
		matrixLeft.print("PMX");

		matrix.writeDisplay();
		matrixLeft.writeDisplay();
		delay(100);
	}

	matrix.setTextSize(1);
	matrix.setTextWrap(false); // we dont want text to wrap so it scrolls nicely
	matrix.setTextColor(LED_ON);
	matrix.setRotation(1);
	matrixLeft.setTextSize(1);
	matrixLeft.setTextWrap(false); // we dont want text to wrap so it scrolls nicely
	matrixLeft.setTextColor(LED_ON);
	matrixLeft.setRotation(1);
	for (int8_t x = 7; x >= -36; x--) {
		matrix.clear();
		matrix.setCursor(x, 0);
		matrix.print("PM-ROBOTIX");
		matrix.writeDisplay();
		matrixLeft.clear();
		matrixLeft.setCursor(x, 0);
		matrixLeft.print("PM-ROBOTIX");
		matrixLeft.writeDisplay();
		delay(100);
	}
	matrix.setRotation(1);
	matrixLeft.setRotation(1);
}
