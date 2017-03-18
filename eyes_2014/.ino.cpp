#ifdef __IN_ECLIPSE__
//This is a automatic generated file
//Please do not modify this file
//If you touch this file your change will be overwritten during the next build
//This file has been generated on 2017-03-18 15:21:27

#include "Arduino.h"
#include "Arduino.h"
#include <Rainbowduino.h>
#include <Wire.h>
int convert(float time, int base_value, int target_value);
void setup();
void loop();
void setNewPosition(int newX, int newY, int newSevere) ;
void setEyeBrow(int xx[8]) ;
void setPxl(int x, int y, uint32_t color) ;
void redraw() ;
void doBlink() ;
void lookAt(int x, int y, int newSevere) ;
void sendLookAt(int x, int y, int newSevere) ;
void sendBlink() ;
void sendEvent(char* message) ;
void receiveEvent(int howMany) ;

#include "eyes_2014.ino"


#endif
