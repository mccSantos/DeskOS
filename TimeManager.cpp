#include "TimeManager.h"

bool TimeManager::begin(bool forceSet) {
  if (!rtc_.begin()) {
    return false;
  }

  if (rtc_.lostPower() || forceSet) {
    rtc_.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }

  return true;
}

DateTime TimeManager::now() {
  return rtc_.now();
}
