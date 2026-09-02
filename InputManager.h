#pragma once

#include <Arduino.h>

enum class InputEvent : uint8_t {
  None,
  RotateLeft,
  RotateRight,
  ShortPress,
  DoublePress,
  LongPress
};

class InputManager {
 public:
  InputManager(
      uint8_t clkPin,
      uint8_t dataPin,
      uint8_t switchPin,
      unsigned long longPressMs,
      unsigned long doubleClickMs);

  void begin();

  // When allowDoubleClick is false, a short press is emitted immediately.
  // When true, the first click is held briefly to detect a possible double click.
  InputEvent update(bool allowDoubleClick);

 private:
  uint8_t clkPin_;
  uint8_t dataPin_;
  uint8_t switchPin_;

  unsigned long longPressMs_;
  unsigned long doubleClickMs_;

  int lastClk_ = HIGH;

  bool buttonWasPressed_ = false;
  unsigned long buttonPressedAt_ = 0;

  bool waitingForSecondClick_ = false;
  unsigned long lastShortPress_ = 0;
};
