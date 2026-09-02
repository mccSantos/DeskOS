#pragma once

#include <RTClib.h>

class TimeManager {
 public:
  bool begin(bool forceSet);
  DateTime now();

 private:
  RTC_DS3231 rtc_;
};
