// Only modify this file to include
// - function definitions (prototypes)
// - include files
// - extern variable definitions
// In the appropriate section

#ifndef _eyes_2014_H_
#define _eyes_2014_H_
#include "Arduino.h"

#include <math.h>
#include <stdint.h>




// MASTER is right eye of the robot (on the left)
int MASTER = 1;
unsigned long period1 = 12000;  //the value is a number of milliseconds
unsigned long period2 = 2000;  //the value is a number of milliseconds





unsigned long startMillis;  //some global variables available anywhere in the program
unsigned long currentMillis;
unsigned long period = 0;
bool mode = false;


uint32_t TRS = 0x123456;
uint32_t BLK = 0x000000;
uint32_t RED = 0xFF0000;
uint32_t REL = 0xFF1010;
uint32_t YEL = 0x808000;
uint32_t WHI = 0x808080;



uint32_t EYE_BROW[4][8] = {
  {BLK, BLK, BLK, BLK, BLK, BLK, BLK, BLK},
  {BLK, BLK, BLK, BLK, BLK, BLK, BLK, BLK},
  {BLK, BLK, BLK, BLK, BLK, BLK, BLK, BLK},
  {BLK, BLK, BLK, BLK, BLK, BLK, BLK, BLK}
};

uint32_t PMX[8][8] = {
  {BLK, BLK, BLK, BLK, WHI, BLK, BLK, BLK},
  {BLK, BLK, BLK, WHI, BLK, BLK, BLK, BLK},
  {BLK, WHI, WHI, WHI, WHI, WHI, WHI, BLK},
  {WHI, BLK, BLK, BLK, BLK, BLK, BLK, WHI},
  {WHI, BLK, WHI, BLK, BLK, WHI, BLK, WHI},
  {WHI, BLK, BLK, BLK, BLK, BLK, BLK, WHI},
  {BLK, WHI, WHI, WHI, WHI, WHI, WHI, BLK},
  {BLK, BLK, BLK, BLK, BLK, BLK, BLK, BLK}
};

uint32_t MATRIX[8][8] = {
  {BLK, BLK, BLK, BLK, BLK, BLK, BLK, BLK},
  {BLK, BLK, BLK, BLK, BLK, BLK, BLK, BLK},
  {BLK, BLK, BLK, BLK, BLK, BLK, BLK, BLK},
  {BLK, BLK, BLK, BLK, BLK, BLK, BLK, BLK},
  {BLK, BLK, BLK, BLK, BLK, BLK, BLK, BLK},
  {BLK, BLK, BLK, BLK, BLK, BLK, BLK, BLK},
  {BLK, BLK, BLK, BLK, BLK, BLK, BLK, BLK},
  {BLK, BLK, BLK, BLK, BLK, BLK, BLK, BLK}
};

uint32_t EYE[4][4] = {
  {TRS, RED, RED, TRS},
  {RED, REL, REL, RED},
  {RED, REL, RED, RED},
  {TRS, RED, RED, TRS}
};

int eyeBrow[8] = { 1, 1, 0, 0, 0, 1, 1, 1 };

uint32_t EYE_ANGRY[4][4] = {
  {TRS, RED, RED, TRS},
  {RED, REL, RED, RED},
  {RED, RED, RED, RED},
  {TRS, RED, RED, TRS}
};

uint32_t EYE_UNHAPPY[4][4] = {
  {TRS, REL, REL, TRS},
  {REL, RED, REL, REL},
  {REL, REL, REL, REL},
  {TRS, REL, REL, TRS}
};

int eyeBrow_unhappy[8] = { 1, 1, 0, 0, 1, 1, 2, 3 };
int eyeBrow_angry[8] = { 3, 2, 1, 1, 0, 0, 1, 1 };

//version en croix de la pupille
//uint32_t EYE_ANGRY[4][4] = {
//  {TRS, TRS, TRS, TRS},
//  {TRS, TRS, RED, TRS},
//  {TRS, RED, REL, RED},
//  {TRS, TRS, RED, TRS}
//};




int angry = 0;
int eyeX = 2;
int eyeY = 2;
int baseEyeX = 2;
int baseEyeY = 2;
int targetEyeX = 2;
int targetEyeY = 2;


int TRANSIT_TIME = 15;//15
//int remainingGlobalTime = (1000.0 / TRANSIT_TIME) * 100;//150.0;
int remainingGlobalTime = 900;

int timeSinceBlink = 200;
float blinkStatus = 0.0;
int TIME_BLINK = 200;
int TIME_BLINK_RANDOM = 100;

int timeSinceMove = 200;
float moving = 0;
int TIME_MOVE = 100;
int TIME_MOVE_RANDOM = 300;

//add your function definitions for the project Eyes_2014_remixed here

void displayPMX();
void displayEyes();
void cleanNextScreen();

int convert(float time, int base_value, int target_value);
void setNewPosition(int newX, int newY, int newSevere);
void setEyeBrow(int xx[8]);
void setPxl(int x, int y, uint32_t color);
void redraw();
void doBlink();
void doPMX();
void doDisplayEyes();
void lookAt(int x, int y, int newSevere);
void sendLookAt(int x, int y, int newSevere);
void sendBlink();
void sendPMX();
void sendEvent(char* message, int size);

void receiveEvent(int howMany);



//Do not add code below this line
#endif /* _eyes_2014_H_ */
