#pragma once

#include "data/sensor_reading.h"

#define SOIL_PIN 2

/*
 * Shorthand for pinMode(SOIL_PIN, INPUT)
 */
void setupSoilMoisture();

/*
 * Take soil moisture reading.
 */
SoilMoistureReading* takeSoilMoisture();