#include "DHT.h"
#include "dht_utils.h"

DHT dht(DHT_PIN, DHT_TYPE);

DhtTask::DhtTask(int pin, int dhtType, unsigned long intervalMs, const char* label)
    : SensorTask(intervalMs, label), pin(pin), dhtType(dhtType), dht(nullptr) {}

void DhtTask::setup() {
    dht = new DHT(pin, dhtType);
    static_cast<DHT*>(dht)->begin();
}

std::vector<SensorReading*> DhtTask::measure() {
    auto* sensor = static_cast<DHT*>(dht);

    SensorReading* temperature = new TemperatureReading(sensor->readTemperature(), 'C');
    SensorReading* humidity = new HumidityReading(sensor->readHumidity());

    return {temperature, humidity};
}
