#pragma once

#include <Arduino.h>

class TimerManager {
 public:
  explicit TimerManager(unsigned long pomodoroDurationMs);

  void update();

  // Pomodoro
  void togglePomodoro();
  void resetPomodoro();
  bool pomodoroRunning() const;
  unsigned long pomodoroRemainingMs() const;
  bool consumePomodoroFinished();

  // Stopwatch
  void toggleStopwatch();
  void resetStopwatch();
  bool stopwatchRunning() const;
  unsigned long stopwatchElapsedMs() const;

 private:
  const unsigned long pomodoroDurationMs_;

  unsigned long pomodoroRemainingMs_;
  unsigned long pomodoroLastUpdate_ = 0;
  bool pomodoroRunning_ = false;
  bool pomodoroFinishedEvent_ = false;

  unsigned long stopwatchElapsedMs_ = 0;
  unsigned long stopwatchLastUpdate_ = 0;
  bool stopwatchRunning_ = false;
};
