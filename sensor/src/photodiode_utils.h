#pragma once

#include "data/sensor_reading.h"

#define PHOTODIODE_PIN 6

void setupPhotodiode();

/*
 * Take light level reading.
 */
LightReading* takeLight();
