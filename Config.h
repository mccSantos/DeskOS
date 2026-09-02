#pragma once

#include <Arduino.h>

namespace Config {

// LCD
constexpr uint8_t LCD_ADDRESS = 0x3F;
constexpr uint8_t LCD_COLUMNS = 16;
constexpr uint8_t LCD_ROWS = 2;

// Rotary encoder
constexpr uint8_t ENCODER_CLK_PIN = 22;
constexpr uint8_t ENCODER_DATA_PIN = 23;
constexpr uint8_t ENCODER_SW_PIN = 24;

// DHT11
constexpr uint8_t DHT_PIN = 25;
constexpr unsigned long DHT_INTERVAL_MS = 2000UL;

// Buzzer
constexpr uint8_t BUZZER_PIN = 26;

// Input timing
constexpr unsigned long LONG_PRESS_MS = 1000UL;
constexpr unsigned long DOUBLE_CLICK_MS = 350UL;

// Display refresh
constexpr unsigned long DISPLAY_REFRESH_MS = 250UL;

// Pomodoro
constexpr unsigned long POMODORO_DURATION_MS = 25UL * 60UL * 1000UL;

// Set this to true for ONE upload if the RTC time needs to be reset
// to the sketch compile date/time. Then set it back to false.
constexpr bool FORCE_RTC_SET = false;

}  // namespace Config
