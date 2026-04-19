#include "sensor_reading.h"

#define SENSOR_QUEUE_SIZE 32

QueueHandle_t sensorQueue = NULL;

void setupSensorQueue() {
    sensorQueue = xQueueCreate(SENSOR_QUEUE_SIZE, sizeof(SensorReading*));
}

bool pushReading(SensorReading* reading) {
    if (xQueueSend(sensorQueue, &reading, pdMS_TO_TICKS(100) == pdTRUE)) {
        return true;
    }

    // queue full
    Serial.println("Queue full, dropping reading");
    delete reading;
    return false;
}

// TODO: add pull reading? (with default timeout value - also make that a const and unify with above)
