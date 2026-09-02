#include "AppState.h"
#include "BuzzerManager.h"
#include "Config.h"
#include "DisplayManager.h"
#include "InputManager.h"
#include "SensorManager.h"
#include "TimeManager.h"
#include "TimerManager.h"

DisplayManager display(
    Config::LCD_ADDRESS,
    Config::LCD_COLUMNS,
    Config::LCD_ROWS);

InputManager input(
    Config::ENCODER_CLK_PIN,
    Config::ENCODER_DATA_PIN,
    Config::ENCODER_SW_PIN,
    Config::LONG_PRESS_MS,
    Config::DOUBLE_CLICK_MS);

SensorManager sensors(
    Config::DHT_PIN,
    Config::DHT_INTERVAL_MS);

TimeManager clockManager;

TimerManager timers(
    Config::POMODORO_DURATION_MS);

BuzzerManager buzzer(
    Config::BUZZER_PIN);

AppState currentState = AppState::Home;

const char* MENU_ITEMS[] = {
    "Clock",
    "Environment",
    "Pomodoro",
    "Timer",
    "Running"
};

constexpr int MENU_SIZE =
    sizeof(MENU_ITEMS) / sizeof(MENU_ITEMS[0]);

int menuIndex = 0;

unsigned long lastDisplayRefresh = 0;

void setup() {
  input.begin();
  buzzer.begin();

  display.begin();
  display.showStartup();

  buzzer.startup();

  sensors.begin();

  if (!clockManager.begin(Config::FORCE_RTC_SET)) {
    display.showRtcError();
    buzzer.error();

    while (true) {
      // RTC is required for the current DeskOS build.
    }
  }

  delay(900);

  display.clear();
}

void loop() {
  const bool allowDoubleClick =
      currentState == AppState::Pomodoro ||
      currentState == AppState::Timer;

  const InputEvent event =
      input.update(allowDoubleClick);

  handleInput(event);

  timers.update();

  if (timers.consumePomodoroFinished()) {
    buzzer.pomodoroFinished();
  }

  sensors.update();

  if (millis() - lastDisplayRefresh >=
      Config::DISPLAY_REFRESH_MS) {
    lastDisplayRefresh = millis();
    refreshDisplay();
  }
}

void handleInput(InputEvent event) {
  if (event == InputEvent::None) {
    return;
  }

  if (event == InputEvent::RotateRight &&
      currentState == AppState::Menu) {
    menuIndex++;

    if (menuIndex >= MENU_SIZE) {
      menuIndex = 0;
    }

    display.showMenu(
        MENU_ITEMS,
        menuIndex,
        MENU_SIZE);

    return;
  }

  if (event == InputEvent::RotateLeft &&
      currentState == AppState::Menu) {
    menuIndex--;

    if (menuIndex < 0) {
      menuIndex = MENU_SIZE - 1;
    }

    display.showMenu(
        MENU_ITEMS,
        menuIndex,
        MENU_SIZE);

    return;
  }

  if (event == InputEvent::ShortPress) {
    handleShortPress();
    return;
  }

  if (event == InputEvent::DoublePress) {
    handleDoublePress();
    return;
  }

  if (event == InputEvent::LongPress) {
    handleLongPress();
  }
}

void handleShortPress() {
  buzzer.click();

  if (currentState == AppState::Home) {
    currentState = AppState::Menu;

    display.showMenu(
        MENU_ITEMS,
        menuIndex,
        MENU_SIZE);

    return;
  }

  if (currentState == AppState::Menu) {
    openSelectedApp();
    return;
  }

  if (currentState == AppState::Pomodoro) {
    timers.togglePomodoro();
    return;
  }

  if (currentState == AppState::Timer) {
    timers.toggleStopwatch();
  }
}

void handleDoublePress() {
  if (currentState == AppState::Pomodoro) {
    timers.resetPomodoro();
    buzzer.reset();
    return;
  }

  if (currentState == AppState::Timer) {
    timers.resetStopwatch();
    buzzer.reset();
  }
}

void handleLongPress() {
  if (currentState == AppState::Menu) {
    buzzer.back();
    currentState = AppState::Home;
    display.clear();
    return;
  }

  if (currentState != AppState::Home) {
    buzzer.back();
    currentState = AppState::Menu;

    display.showMenu(
        MENU_ITEMS,
        menuIndex,
        MENU_SIZE);
  }
}

void openSelectedApp() {
  switch (menuIndex) {
    case 0:
      currentState = AppState::Clock;
      break;

    case 1:
      currentState = AppState::Environment;
      break;

    case 2:
      currentState = AppState::Pomodoro;
      break;

    case 3:
      currentState = AppState::Timer;
      break;

    case 4:
      currentState = AppState::Running;
      break;
  }

  display.clear();
}

void refreshDisplay() {
  const DateTime now =
      clockManager.now();

  switch (currentState) {
    case AppState::Home:
      display.showHome(
          now,
          sensors.temperatureC(),
          sensors.humidityPercent());
      break;

    case AppState::Menu:
      // Menu is redrawn only when navigation changes.
      break;

    case AppState::Clock:
      display.showClock(now);
      break;

    case AppState::Environment:
      display.showEnvironment(
          sensors.hasReading(),
          sensors.temperatureC(),
          sensors.humidityPercent());
      break;

    case AppState::Pomodoro:
      display.showPomodoro(
          timers.pomodoroRunning(),
          timers.pomodoroRemainingMs());
      break;

    case AppState::Timer:
      display.showTimer(
          timers.stopwatchRunning(),
          timers.stopwatchElapsedMs());
      break;

    case AppState::Running:
      display.showRunning();
      break;
  }
}
