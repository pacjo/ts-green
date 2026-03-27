#pragma once

#include <Arduino.h>

// TODO: document what does this do
class SensorReading {
public:
    unsigned long timestamp;

    SensorReading() : timestamp(millis()) {}
    virtual ~SensorReading() = default;

    virtual const char* sensorName() const = 0;
    virtual int toJson(char* buf, size_t len) const = 0;

    SensorReading(const SensorReading&) = delete;
    SensorReading& operator=(const SensorReading&) = delete;
};

class TemperatureReading final : public SensorReading {
public:
    float value;
    char scale;

    TemperatureReading(float value, char scale = 'C') : value(value), scale(scale) {}

    const char* sensorName() const override { return "temperature"; }
    int toJson(char* buf, size_t len) const override {
        return snprintf(
            buf, len,
            "{\"sensor\":\"temperature\",\"value\":%.2f,\"scale\":\"%c\",\"ts\":%lu}",
            value, scale, timestamp
        );
    }
};

class HumidityReading final : public SensorReading {
public:
    float value;

    HumidityReading(float value) : value(value) {}

    const char* sensorName() const override { return "humidity"; }
    int toJson(char* buf, size_t len) const override {
        return snprintf(
            buf, len,
            "{\"sensor\":\"humidity\",\"value\":%.2f,\"ts\":%lu}",
            value, timestamp
        );
    }
};

class LightReading final : public SensorReading {
public:
    float value;

    LightReading(float value) : value(value) {}

    const char* sensorName() const override { return "light"; }
    int toJson(char* buf, size_t len) const override {
        return snprintf(
            buf, len,
            "{\"sensor\":\"light\",\"value\":%.2f,\"ts\":%lu}",
            value, timestamp
        );
    }
};

class SoilMoistureReading final : public SensorReading {
public:
    float value;

    SoilMoistureReading(float value) : value(value) {}

    const char* sensorName() const override { return "soil_moisture"; }
    int toJson(char* buf, size_t len) const override {
        return snprintf(
            buf, len,
            "{\"sensor\":\"soil_moisture\",\"value\":%.2f,\"ts\":%lu}",
            value, timestamp
        );
    }
};

extern QueueHandle_t sensorQueue;

/*
 * Create the shared queue.  Must be called before any sensor task starts.
 */
void setupSensorQueue();

/*
 * Push a heap-allocated reading onto the queue.
 * Takes ownership: deletes the reading if the queue is full.
 * Returns true on success.
 *
 * Usage: pushReading(new TemperatureReading(23.5f));
 */
bool pushReading(SensorReading* reading);
