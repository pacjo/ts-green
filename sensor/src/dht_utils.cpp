#include "DHT.h"
#include "dht_utils.h"

DHT dht(DHT_PIN, DHT_TYPE);

DhtTask::DhtTask(int pin, int dhtType, unsigned long intervalMs, const char* label)
    : SensorTask(intervalMs, label), pin(pin), dhtType(dhtType), dht(nullptr) {}

void DhtTask::setup() {
    dht = new DHT(pin, dhtType);
    static_cast<DHT*>(dht)->begin();
}

SensorReading* DhtTask::measure() {
    auto* sensor = static_cast<DHT*>(dht);

    // TODO: figure out how to return both at the same time
    return new TemperatureReading(sensor->readTemperature(), 'C');
    // return new HumidityReading(sensor->readHumidity());
}
