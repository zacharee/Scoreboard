#include "../lib/SevenSeg/SevenSeg.h"

const unsigned char digitCount = 4;

const unsigned char com1 = 5;
const unsigned char com2 = 4;
const unsigned char com3 = 3;
const unsigned char com4 = 2;

unsigned char digits[digitCount] = {com1, com2, com3, com4};

const unsigned char segA = 13;
const unsigned char segB = 12;
const unsigned char segC = 11;
const unsigned char segD = 10;
const unsigned char segE = 9;
const unsigned char segF = 8;
const unsigned char segG = 7;
const unsigned char segDP = 6;

const unsigned int threshold = 512;
const unsigned char max = 99;

const unsigned char input1 = A0;
const unsigned char input2 = A1;
const unsigned char inputReset = A2;

unsigned char score1 = 0;
unsigned char score2 = 0;

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

bool isPressed(char pin) {
    return analogRead(pin) < threshold;
}

void setup() {
    seg.setCommonAnode();
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

    char value[4];

    snprintf(value, 4, "%2d%2d", score1, score2);

    seg.write(value);
}
