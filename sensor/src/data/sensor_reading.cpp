#include "sensor_reading.h"
#include "logger.h"

#define SENSOR_QUEUE_SIZE 32

QueueHandle_t sensorQueue = NULL;

void setupSensorQueue() {
    sensorQueue = xQueueCreate(SENSOR_QUEUE_SIZE, sizeof(SensorReading*));
    LOG_INFO("queue", "created, size=%d", SENSOR_QUEUE_SIZE);
}

bool pushReading(SensorReading* reading) {
    if (xQueueSend(sensorQueue, &reading, pdMS_TO_TICKS(100)) == pdTRUE) {
        LOG_DEBUG("queue", "push ok  (%d/%d used)", uxQueueMessagesWaiting(sensorQueue), SENSOR_QUEUE_SIZE);
        return true;
    }

    LOG_WARN("queue", "full! dropping \"%s\" (id=\"%s\")  (%d/%d used)", reading->sensorName(), reading->label, uxQueueMessagesWaiting(sensorQueue), SENSOR_QUEUE_SIZE);
    delete reading;
    return false;
}

// TODO: add pull reading? (with default timeout value - also make that a const and unify with above)
