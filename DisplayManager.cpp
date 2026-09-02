#include "DisplayManager.h"

namespace {
const char* WEEK_DAYS[] = {
    "SUN", "MON", "TUE", "WED", "THU", "FRI", "SAT"
};
}

DisplayManager::DisplayManager(uint8_t address, uint8_t columns, uint8_t rows)
    : lcd_(address, columns, rows) {}

void DisplayManager::begin() {
  lcd_.init();
  lcd_.backlight();
}

void DisplayManager::clear() {
  lcd_.clear();
}

void DisplayManager::showStartup() {
  lcd_.clear();
  lcd_.setCursor(0, 0);
  lcd_.print("DeskOS");
  lcd_.setCursor(0, 1);
  lcd_.print("Starting...");
}

void DisplayManager::showRtcError() {
  lcd_.clear();
  lcd_.setCursor(0, 0);
  lcd_.print("RTC ERROR");
  lcd_.setCursor(0, 1);
  lcd_.print("Check wiring");
}

void DisplayManager::showHome(
    const DateTime& now,
    float temperatureC,
    float humidity) {
  lcd_.setCursor(0, 0);

  lcd_.print(WEEK_DAYS[now.dayOfTheWeek()]);
  lcd_.print(" ");
  printTwoDigits(now.day());
  lcd_.print("/");
  printTwoDigits(now.month());
  lcd_.print(" ");
  printTwoDigits(now.hour());
  lcd_.print(":");
  printTwoDigits(now.minute());
  lcd_.print(" ");

  lcd_.setCursor(0, 1);

  if (!isnan(temperatureC)) {
    lcd_.print(temperatureC, 1);
    lcd_.print((char)223);
    lcd_.print("C");
  } else {
    lcd_.print("--.-C");
  }

  lcd_.print(" HUM ");

  if (!isnan(humidity)) {
    lcd_.print((int)humidity);
  } else {
    lcd_.print("--");
  }

  lcd_.print("% ");
}

void DisplayManager::showMenu(
    const char* const menuItems[],
    int index,
    int menuSize) {
  lcd_.clear();

  lcd_.setCursor(0, 0);
  lcd_.print("> ");
  lcd_.print(menuItems[index]);

  int nextItem = index + 1;
  if (nextItem >= menuSize) {
    nextItem = 0;
  }

  lcd_.setCursor(0, 1);
  lcd_.print("  ");
  lcd_.print(menuItems[nextItem]);
}

void DisplayManager::showClock(const DateTime& now) {
  lcd_.setCursor(0, 0);

  lcd_.print(WEEK_DAYS[now.dayOfTheWeek()]);
  lcd_.print(" ");
  printTwoDigits(now.day());
  lcd_.print("/");
  printTwoDigits(now.month());
  lcd_.print("/");
  lcd_.print(now.year());
  lcd_.print(" ");

  lcd_.setCursor(0, 1);
  printTwoDigits(now.hour());
  lcd_.print(":");
  printTwoDigits(now.minute());
  lcd_.print(":");
  printTwoDigits(now.second());
  lcd_.print("        ");
}

void DisplayManager::showEnvironment(
    bool hasReading,
    float temperatureC,
    float humidity) {
  if (!hasReading) {
    lcd_.setCursor(0, 0);
    lcd_.print("ENVIRONMENT     ");
    lcd_.setCursor(0, 1);
    lcd_.print("Reading...      ");
    return;
  }

  lcd_.setCursor(0, 0);
  lcd_.print("TEMP ");
  lcd_.print(temperatureC, 1);
  lcd_.print((char)223);
  lcd_.print("C     ");

  lcd_.setCursor(0, 1);
  lcd_.print("HUM  ");
  lcd_.print(humidity, 1);
  lcd_.print("%     ");
}

void DisplayManager::showPomodoro(bool running, unsigned long remainingMs) {
  const unsigned long totalSeconds = remainingMs / 1000UL;
  const int minutes = totalSeconds / 60UL;
  const int seconds = totalSeconds % 60UL;

  lcd_.setCursor(0, 0);

  if (remainingMs == 0) {
    lcd_.print("POMO FINISHED!  ");
  } else if (running) {
    lcd_.print("POMO RUNNING    ");
  } else {
    lcd_.print("POMO PAUSED     ");
  }

  lcd_.setCursor(0, 1);
  printTwoDigits(minutes);
  lcd_.print(":");
  printTwoDigits(seconds);
  lcd_.print("          ");
}

void DisplayManager::showTimer(bool running, unsigned long elapsedMs) {
  const unsigned long totalSeconds = elapsedMs / 1000UL;
  const int hours = totalSeconds / 3600UL;
  const int minutes = (totalSeconds / 60UL) % 60UL;
  const int seconds = totalSeconds % 60UL;

  lcd_.setCursor(0, 0);

  if (running) {
    lcd_.print("TIMER RUNNING   ");
  } else {
    lcd_.print("TIMER PAUSED    ");
  }

  lcd_.setCursor(0, 1);
  printTwoDigits(hours);
  lcd_.print(":");
  printTwoDigits(minutes);
  lcd_.print(":");
  printTwoDigits(seconds);
  lcd_.print("        ");
}

void DisplayManager::showRunning() {
  lcd_.setCursor(0, 0);
  lcd_.print("10K TARGET      ");
  lcd_.setCursor(0, 1);
  lcd_.print("40:00 4:00/km   ");
}

void DisplayManager::printTwoDigits(int number) {
  if (number < 10) {
    lcd_.print("0");
  }

  lcd_.print(number);
}
