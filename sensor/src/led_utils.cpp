#include <Arduino.h>
#include "led_utils.h"

// https://gist.github.com/fairlight1337/4935ae72bcbcc1ba5c72
/*
 * Converts a given set of HSV values `h', `s', `v' into RGB
 * coordinates. The output RGB values are in the range [0, 1], and
 * the input HSV values are in the ranges h = [0, 360], and s, v =
 * [0, 1], respectively.
 */
void HSVtoRGB(float& fR, float& fG, float& fB, float& fH, float& fS, float& fV) {
    float fC = fV * fS; // chroma
    float fHPrime = fmod(fH / 60.0, 6);
    float fX = fC * (1 - fabs(fmod(fHPrime, 2) - 1));
    float fM = fV - fC;

    if (0 <= fHPrime && fHPrime < 1) {
        fR = fC;
        fG = fX;
        fB = 0;
    } else if (1 <= fHPrime && fHPrime < 2) {
        fR = fX;
        fG = fC;
        fB = 0;
    } else if (2 <= fHPrime && fHPrime < 3) {
        fR = 0;
        fG = fC;
        fB = fX;
    } else if (3 <= fHPrime && fHPrime < 4) {
        fR = 0;
        fG = fX;
        fB = fC;
    } else if (4 <= fHPrime && fHPrime < 5) {
        fR = fX;
        fG = 0;
        fB = fC;
    } else if (5 <= fHPrime && fHPrime < 6) {
        fR = fC;
        fG = 0;
        fB = fX;
    } else {
        fR = 0;
        fG = 0;
        fB = 0;
    }

    fR += fM;
    fG += fM;
    fB += fM;
}

BlinkLedBuiltinTask::BlinkLedBuiltinTask(unsigned long intervalMs)
    : PeriodicTask(intervalMs) {}

void BlinkLedBuiltinTask::setup() {
    pinMode(LED_BUILTIN, OUTPUT);
}

void BlinkLedBuiltinTask::tick() {
    digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
}

ColorWheelRgbTask::ColorWheelRgbTask(unsigned long intervalMs)
    : PeriodicTask(intervalMs) {}

void ColorWheelRgbTask::setup() {
    pinMode(LED_R, OUTPUT);
    pinMode(LED_G, OUTPUT);
    pinMode(LED_B, OUTPUT);
}

void ColorWheelRgbTask::tick() {
    HSVtoRGB(fR, fG, fB, fH, fS, fV);
    fH = fmod(fH + 0.01f, 360.0f);

    analogWrite(LED_R, fR);
    analogWrite(LED_G, fG);
    analogWrite(LED_B, fB);
}
