#pragma once

#include "data/sensor_reading.h"

#define DHT_PIN 5
#define DHT_TYPE DHT22

/*
 * Shorthand for dht.begin()
 */
void setupDht();

/*
 * Take humidity reading.
 */
HumidityReading* takeHumidity();

/*
 * Take temperature reading.
 */
TemperatureReading* takeTemperature();
