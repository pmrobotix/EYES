// Do not remove the include below
#include "eyes_2014.h"

#include <Print.h>
#include <Rainbowduino.h>
#include <stdint.h>
#include <stdlib.h>
#include <Wire.h>

void setup() {
    Rb.init();

    Wire.begin(4);                // join i2c bus with address #4
    Wire.onReceive(receiveEvent); // register event

    startMillis = millis();  //initial start time
    period = period1;
    mode = true;

    angry = 0;
    Serial.begin(19200);
}

void loop() {

    // Clean next screen
    cleanNextScreen();

    if (MASTER == 1) {
        currentMillis = millis(); //get the current "time" (actually the number of milliseconds since the program started)
        if (currentMillis - startMillis >= period) //test whether the period has elapsed
                {
            startMillis = currentMillis; //IMPORTANT to save the start time of the current LED state.
            mode = !mode;

            if (mode) {

                doDisplayEyes();
                period = period1;
            }
            else {

                doPMX();
                period = period2;

            }
        }
        else {

        }
    }

    if (mode) {
        displayEyes();

    }
    else {
        displayPMX();
    }

    redraw();
    delay(TRANSIT_TIME);

}

void displayPMX() {
    for (int x = 0; x < 8; x++) {
        for (int y = 0; y < 8; y++) {
            setPxl(x, y, PMX[x][y]);
        }
    }
}

void cleanNextScreen() {
// Clean next screen
    for (int x = 0; x < 8; x++) {
        for (int y = 0; y < 8; y++) {
            setPxl(x, y, BLK);
        }
    }
}

void displayEyes() {

// Master asks for blinks and moves
    if (MASTER == 1) {
        // Moving
        timeSinceMove = timeSinceMove - 1;
        if (timeSinceMove < 1) {
            timeSinceMove = TIME_MOVE + random(TIME_MOVE_RANDOM);
            int randomY = random(10);
            int randomX = 1;
            if (randomY > 2 && randomY < 8) {
                randomX = random(2);
            }
            //int randomSevere = random(1); //todo a supprimer
            lookAt(randomX, randomY, angry);
        }
        // Blinking
        timeSinceBlink = timeSinceBlink - 1;
        if (timeSinceBlink < 1) {
            timeSinceBlink = TIME_BLINK + random(TIME_BLINK_RANDOM);
            doBlink();
        }
    }
    int realOpenValue = 0;
    if (blinkStatus > 1) {
        realOpenValue = convert(2 * (blinkStatus - 1), 0, 4);
        blinkStatus = blinkStatus - 0.05;
    }
    else if (blinkStatus > 0) {
        realOpenValue = convert(blinkStatus, 4, 0);
        blinkStatus = blinkStatus - 0.05;
    }
// Compute position of eye
    if (moving > 0) {
        eyeX = convert(moving, baseEyeX, targetEyeX);
        eyeY = convert(moving, baseEyeY, targetEyeY);
        moving = moving - 0.01;
    }
    else {
        eyeX = targetEyeX;
        eyeY = targetEyeY;
    }
// Draw eye
    for (int x = 0; x < 4; x++) {
        for (int y = 0; y < 4; y++) {
            if (angry == 1) {
                setPxl(x + eyeX, y + eyeY, EYE_ANGRY[x][y]);
            }
            else if (angry == 2) {
                setPxl(x + eyeX, y + eyeY, EYE_UNHAPPY[x][y]);
            }
            else if (x >= realOpenValue) {
                setPxl(x + eyeX, y + eyeY, EYE[x][y]);
            }
        }
    }
// Compute position of eyebrow

    if (angry == 0) {
        setEyeBrow(eyeBrow);
    }
    else if (angry == 1) {
        setEyeBrow(eyeBrow_angry);
    }
    else if (angry == 2) {
        setEyeBrow(eyeBrow_unhappy);
    }

// Draw Eyebrow
    for (int x = 0; x < 4; x++) {
        for (int y = 0; y < 8; y++) {
            setPxl(x, y, EYE_BROW[x][y]);
        }
    }

}

int convert(float time, int base_value, int target_value) {
// Function: cos
    float cosRatio = cos((1.0 - time) * PI);
    return base_value - cosRatio * (target_value - base_value);
}

void setNewPosition(int newX, int newY, int newSevere) {
    if (newX < 5 && newX >= 0 && newY < 5 && newY >= 0) {
        baseEyeX = eyeX;
        baseEyeY = eyeY;
        targetEyeX = newX;
        targetEyeY = newY;
        moving = 1;
    }
}

void setEyeBrow(int xx[8]) {
    for (int x = 0; x < 4; x++) {
        for (int y = 0; y < 8; y++) {
            int yy = y;
            if (MASTER == 1) {
                yy = 7 - y;
            }
            if (x < xx[yy]) {
                EYE_BROW[x][y] = BLK;
            }
            else if (x == xx[yy]) {
                EYE_BROW[x][y] = YEL;
            }
            else {
                EYE_BROW[x][y] = TRS;
            }
        }
    }
}

void setPxl(int x, int y, uint32_t color) {
    if (color != TRS && x < 8 && x >= 0 && y < 8 && y >= 0) {
        MATRIX[x][y] = color;
    }
}

void redraw() {
    for (int x = 0; x < 8; x++) {
        for (int y = 0; y < 8; y++) {
            Rb.setPixelXY(x, y, MATRIX[x][y]);
        }
    }
}

void doBlink() {
    if (MASTER == 1) {
        sendBlink();
    }
    blinkStatus = 1.5;
}

void doPMX() {
    if (MASTER == 1) {

        sendPMX();
        //angry = !angry; //on change de yeux
        angry++;
        if (angry >= 3) {
            angry = 0;
        }
        Serial.print("!angry=");
        Serial.println(angry);
    }
}

void doDisplayEyes() {
    if (MASTER == 1) {
        //to activate eyes on the slave

        int randomY = random(10);
        int randomX = 1;
        if (randomY > 2 && randomY < 8) {
            randomX = random(2);
        }
        Serial.print("send angry=");
        Serial.println(angry);
        lookAt(randomX, randomY, angry);
    }
}

void lookAt(int x, int y, int newSevere) {
    if (x >= 0 && x <= 2 && y >= 0 && y <= 10) {
        if (MASTER == 1) {
            sendLookAt(x, y, newSevere);
            // MASTER = RIGHT --> invert
            y = 10 - y;
        }

        if (y == 0) {
            setNewPosition(2 + x, 0, newSevere);
        }
        else if (y == 1) {
            setNewPosition(2 + x, 1, newSevere);
        }
        else if (y == 2) {
            setNewPosition(2 + x, 2, newSevere);
        }
        else if (y == 3) {
            setNewPosition(2 + x, 2, newSevere);
        }
        else if (y == 4) {
            setNewPosition(2 + x, 3, newSevere);
        }
        else if (y == 5) {
            setNewPosition(2 + x, 4, newSevere);
        }
        else if (y == 6) {
            setNewPosition(2 + x, 3, newSevere);
        }
        else if (y == 7) {
            setNewPosition(2 + x, 3, newSevere);
        }
        else if (y == 8) {
            setNewPosition(2 + x, 2, newSevere);
        }
        else if (y == 9) {
            setNewPosition(2 + x, 3, newSevere);
        }
        else if (y == 10) {
            setNewPosition(2 + x, 4, newSevere);
        }
    }
}

void sendLookAt(int x, int y, int newSevere) {
    Serial.print("sendLookAt=");
    Serial.println(newSevere);
    char message[4];
    message[0] = 'L';
    message[1] = x;
    message[2] = y;
    message[3] = newSevere;
    sendEvent(message, 4);
}

void sendBlink() {
    char message[1];
    message[0] = 'B';
    sendEvent(message, 1);
}

void sendPMX() {
    char message[1];
    message[0] = 'P';
    sendEvent(message, 1);
}

void sendEvent(char* dataArray, int size) {
    Wire.beginTransmission(4);
    for (int i = 0; i < size; i++) {
        Wire.write(dataArray[i]);  //data bytes are queued in local buffer
    }
    Wire.endTransmission();
}

// function that executes whenever data is received from master
// this function is registered as an event, see setup()
void receiveEvent(int howMany) {
    if (MASTER == 0) {
        char message[howMany];
        Serial.print("h=");
        Serial.print(howMany);

        for (int i = 0; i < howMany; i++) {
            message[i] = Wire.read();
        }
        if (howMany > 0) {
            char type = message[0];
            Serial.print(":");
            Serial.print(type);

            if (type == 'B') {
                mode = true;
                Serial.println();
                doBlink();
            }
            else if (type == 'L') {
                mode = true;
                int xx = message[1];
                Serial.print("-");
                Serial.print(xx);

                int yy = message[2];
                Serial.print("-");
                Serial.print(yy);

                int newSevere = message[3];
                Serial.print("-");
                Serial.print(newSevere);
                angry = newSevere;
                Serial.print("-angry=");
                Serial.print(angry);
                Serial.println();
                lookAt(xx, yy, newSevere);
            }
            else if (type == 'P') {
                mode = false;
                Serial.println();
                doPMX();
            }
        }
    }
}
