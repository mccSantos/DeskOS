#pragma once

#include <Arduino.h>
#include <DHT.h>

class SensorManager {
 public:
  SensorManager(uint8_t dhtPin, unsigned long readIntervalMs);

  void begin();
  void update();

  bool hasReading() const;
  float temperatureC() const;
  float humidityPercent() const;

 private:
  DHT dht_;
  unsigned long readIntervalMs_;
  unsigned long lastRead_ = 0;

  float temperature_ = NAN;
  float humidity_ = NAN;
};
