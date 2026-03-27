#pragma once

#include "DHT.h"

#define DHT_PIN 5
#define DHT_TYPE DHT22

extern DHT dht;

/*
 * Shorthand for dht.begin()
 */
void setupDht();

// TODO: add wrapers for humidity and temperature
// TODO: remove extern
