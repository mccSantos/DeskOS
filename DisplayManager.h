#pragma once

#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
#include <RTClib.h>

class DisplayManager {
 public:
  DisplayManager(uint8_t address, uint8_t columns, uint8_t rows);

  void begin();
  void clear();

  void showStartup();
  void showRtcError();

  void showHome(const DateTime& now, float temperatureC, float humidity);
  void showMenu(const char* const menuItems[], int index, int menuSize);
  void showClock(const DateTime& now);
  void showEnvironment(bool hasReading, float temperatureC, float humidity);
  void showPomodoro(bool running, unsigned long remainingMs);
  void showTimer(bool running, unsigned long elapsedMs);
  void showRunning();

 private:
  LiquidCrystal_I2C lcd_;

  void printTwoDigits(int number);
};
