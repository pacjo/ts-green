#pragma once

#include <Arduino.h>

// TODO: document what does this do
class SensorReading {
public:
    unsigned long timestamp;
    const char* label = "";

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
            "{\"sensor\":\"temperature\",\"value\":%.2f,\"scale\":\"%c\",\"id\":\"%s\",\"ts\":%lu}",
            value, scale, label, timestamp
        );
    }
};

class PressureReading final : public SensorReading {
public:
    float value;
    const char* unit;

    PressureReading(float value, const char* unit = "hPa") : value(value), unit(unit) {}

    const char* sensorName() const override { return "pressure"; }

    int toJson(char* buf, size_t len) const override {
        return snprintf(
            buf, len,
            "{\"sensor\":\"pressure\",\"value\":%.2f,\"unit\":\"%s\",\"id\":\"%s\",\"ts\":%lu}",
            value, unit, label, timestamp
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
            "{\"sensor\":\"humidity\",\"value\":%.2f,\"id\":\"%s\",\"ts\":%lu}",
            value, label, timestamp
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
            "{\"sensor\":\"light\",\"value\":%.2f,\"id\":\"%s\",\"ts\":%lu}",
            value, label, timestamp
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
            "{\"sensor\":\"soil_moisture\",\"value\":%.2f,\"id\":\"%s\",\"ts\":%lu}",
            value, label, timestamp
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
