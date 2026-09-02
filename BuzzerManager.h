#pragma once

#include <Arduino.h>

class BuzzerManager {
 public:
  explicit BuzzerManager(uint8_t pin);

  void begin();

  void click();
  void reset();
  void back();
  void startup();
  void pomodoroFinished();
  void error();

 private:
  uint8_t pin_;
};
