#pragma once

#include <Arduino.h>

enum class AppState : uint8_t {
  Home,
  Menu,
  Clock,
  Environment,
  Pomodoro,
  Timer,
  Running
};
