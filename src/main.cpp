#include "../lib/SevenSeg/SevenSeg.h"

const int digitCount = 4;

const int com1 = 13;
const int com2 = 12;
const int com3 = 11;
const int com4 = 10;

int digits[digitCount] = {com1, com2, com3, com4};

const int segA = 9;
const int segB = 8;
const int segC = 7;
const int segD = 6;
const int segE = 5;
const int segF = 4;
const int segG = 3;
const int segDP = 2;

const int threshold = 512;
const int max = 99;

const int input1 = A0;
const int input2 = A1;
const int inputReset = A2;

int score1 = 0;
int score2 = 0;

bool was1Pressed = false;
bool was2Pressed = false;
bool wasResetPressed = false;

SevenSeg seg(
        segA,
        segB,
        segC,
        segD,
        segE,
        segF,
        segG
        );

bool isPressed(int pin) {
    return analogRead(pin) < threshold;
}

void setup() {
    pinMode(input1, INPUT);
    pinMode(input2, INPUT);

    Serial.begin(115200);

    seg.setCommonCathode();
    seg.setDigitPins(digitCount, digits);
    seg.setDPPin(segDP);
}

void loop() {
    bool is1Pressed = isPressed(input1);
    bool is2Pressed = isPressed(input2);
    bool isResetPressed = isPressed(inputReset);
    
    if (is1Pressed && !was1Pressed) {
        was1Pressed = true;
        if (score1 == max) score1 = 0;
        else score1++;
    } else if (!is1Pressed) {
        was1Pressed = false;
    }

    if (is2Pressed && !was2Pressed) {
        was2Pressed = true;
        if (score2 == max) score2 = 0;
        else score2++;
    } else if (!is2Pressed) {
        was2Pressed = false;
    }

    if (isResetPressed && !wasResetPressed) {
        wasResetPressed = true;
        score1 = 0;
        score2 = 0;
    } else if (!isResetPressed) {
        wasResetPressed = false;
    }

    char value[100];

    snprintf(value, 100, "%2d%2d", score1, score2);

    seg.write(value);
}
