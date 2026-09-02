#include "BuzzerManager.h"

BuzzerManager::BuzzerManager(uint8_t pin) : pin_(pin) {}

void BuzzerManager::begin() {
  pinMode(pin_, OUTPUT);
}

void BuzzerManager::click() {
  tone(pin_, 1800, 45);
}

void BuzzerManager::reset() {
  tone(pin_, 1400, 70);
  delay(100);
  tone(pin_, 1800, 70);
}

void BuzzerManager::back() {
  tone(pin_, 700, 100);
}

void BuzzerManager::startup() {
  tone(pin_, 1000, 70);
  delay(100);
  tone(pin_, 1500, 70);
  delay(100);
  tone(pin_, 2000, 100);
}

void BuzzerManager::pomodoroFinished() {
  for (uint8_t i = 0; i < 3; ++i) {
    tone(pin_, 2000, 180);
    delay(300);
  }
}

void BuzzerManager::error() {
  tone(pin_, 400, 500);
}
