#include <Arduino.h>
#include "photodiode_utils.h"

// by experimentation - TODO: determine actual values
int LIGHT_MIN = 0;
int LIGHT_MAX = 4095;

void setupPhotodiode() {
    pinMode(PHOTODIODE_PIN, INPUT);
}

float readPhotodiode() {
    return analogRead(PHOTODIODE_PIN) / (float) LIGHT_MAX;
}

LightReading* takeLight() {
    float value = readPhotodiode();
    return new LightReading(value);
}