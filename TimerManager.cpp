#include "TimerManager.h"

TimerManager::TimerManager(unsigned long pomodoroDurationMs)
    : pomodoroDurationMs_(pomodoroDurationMs),
      pomodoroRemainingMs_(pomodoroDurationMs) {}

void TimerManager::update() {
  const unsigned long now = millis();

  if (pomodoroRunning_) {
    const unsigned long elapsed = now - pomodoroLastUpdate_;
    pomodoroLastUpdate_ = now;

    if (elapsed >= pomodoroRemainingMs_) {
      pomodoroRemainingMs_ = 0;
      pomodoroRunning_ = false;
      pomodoroFinishedEvent_ = true;
    } else {
      pomodoroRemainingMs_ -= elapsed;
    }
  }

  if (stopwatchRunning_) {
    stopwatchElapsedMs_ += now - stopwatchLastUpdate_;
    stopwatchLastUpdate_ = now;
  }
}

void TimerManager::togglePomodoro() {
  if (pomodoroRemainingMs_ == 0) {
    pomodoroRemainingMs_ = pomodoroDurationMs_;
  }

  pomodoroRunning_ = !pomodoroRunning_;
  pomodoroLastUpdate_ = millis();
}

void TimerManager::resetPomodoro() {
  pomodoroRunning_ = false;
  pomodoroRemainingMs_ = pomodoroDurationMs_;
  pomodoroFinishedEvent_ = false;
}

bool TimerManager::pomodoroRunning() const {
  return pomodoroRunning_;
}

unsigned long TimerManager::pomodoroRemainingMs() const {
  return pomodoroRemainingMs_;
}

bool TimerManager::consumePomodoroFinished() {
  if (!pomodoroFinishedEvent_) {
    return false;
  }

  pomodoroFinishedEvent_ = false;
  return true;
}

void TimerManager::toggleStopwatch() {
  stopwatchRunning_ = !stopwatchRunning_;
  stopwatchLastUpdate_ = millis();
}

void TimerManager::resetStopwatch() {
  stopwatchRunning_ = false;
  stopwatchElapsedMs_ = 0;
}

bool TimerManager::stopwatchRunning() const {
  return stopwatchRunning_;
}

unsigned long TimerManager::stopwatchElapsedMs() const {
  return stopwatchElapsedMs_;
}
