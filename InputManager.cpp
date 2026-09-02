#include "InputManager.h"

InputManager::InputManager(
    uint8_t clkPin,
    uint8_t dataPin,
    uint8_t switchPin,
    unsigned long longPressMs,
    unsigned long doubleClickMs)
    : clkPin_(clkPin),
      dataPin_(dataPin),
      switchPin_(switchPin),
      longPressMs_(longPressMs),
      doubleClickMs_(doubleClickMs) {}

void InputManager::begin() {
  pinMode(clkPin_, INPUT);
  pinMode(dataPin_, INPUT);
  pinMode(switchPin_, INPUT_PULLUP);

  lastClk_ = digitalRead(clkPin_);
}

InputEvent InputManager::update(bool allowDoubleClick) {
  const int currentClk = digitalRead(clkPin_);

  if (currentClk != lastClk_ && currentClk == LOW) {
    lastClk_ = currentClk;

    if (digitalRead(dataPin_) != currentClk) {
      return InputEvent::RotateRight;
    }

    return InputEvent::RotateLeft;
  }

  lastClk_ = currentClk;

  const bool pressed = digitalRead(switchPin_) == LOW;

  if (pressed && !buttonWasPressed_) {
    buttonWasPressed_ = true;
    buttonPressedAt_ = millis();
  }

  if (!pressed && buttonWasPressed_) {
    const unsigned long pressDuration = millis() - buttonPressedAt_;
    buttonWasPressed_ = false;

    if (pressDuration >= longPressMs_) {
      waitingForSecondClick_ = false;
      return InputEvent::LongPress;
    }

    if (!allowDoubleClick) {
      waitingForSecondClick_ = false;
      return InputEvent::ShortPress;
    }

    if (waitingForSecondClick_ &&
        millis() - lastShortPress_ <= doubleClickMs_) {
      waitingForSecondClick_ = false;
      return InputEvent::DoublePress;
    }

    waitingForSecondClick_ = true;
    lastShortPress_ = millis();
  }

  if (waitingForSecondClick_ &&
      millis() - lastShortPress_ > doubleClickMs_) {
    waitingForSecondClick_ = false;
    return InputEvent::ShortPress;
  }

  return InputEvent::None;
}
