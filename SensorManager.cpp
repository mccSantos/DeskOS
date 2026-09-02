#include "SensorManager.h"

SensorManager::SensorManager(uint8_t dhtPin, unsigned long readIntervalMs)
    : dht_(dhtPin, DHT11),
      readIntervalMs_(readIntervalMs) {}

void SensorManager::begin() {
  dht_.begin();
}

void SensorManager::update() {
  if (millis() - lastRead_ < readIntervalMs_) {
    return;
  }

  lastRead_ = millis();

  const float newHumidity = dht_.readHumidity();
  const float newTemperature = dht_.readTemperature();

  if (!isnan(newHumidity)) {
    humidity_ = newHumidity;
  }

  if (!isnan(newTemperature)) {
    temperature_ = newTemperature;
  }
}

bool SensorManager::hasReading() const {
  return !isnan(temperature_) && !isnan(humidity_);
}

float SensorManager::temperatureC() const {
  return temperature_;
}

float SensorManager::humidityPercent() const {
  return humidity_;
}
