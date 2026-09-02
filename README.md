# 🖥️ DeskOS

**DeskOS** is a modular Arduino-powered desktop dashboard built around an
**Arduino Mega 2560**, a **16x2 I²C LCD**, and a rotary encoder.

It started as a simple LCD experiment and evolved into a small embedded system
with a real-time clock, environmental monitoring, timers, sound feedback, and
a menu-driven user interface.


---

## ✨ Features

- 🏠 Home dashboard
- 🕒 Real date and time using a DS3231 RTC
- 🌡️ Temperature monitoring
- 💧 Humidity monitoring
- 🍅 25-minute Pomodoro timer
- ⏱️ Stopwatch
- 🏃 Running utility screen
- 🎛️ Rotary encoder navigation
- 🔊 Audio feedback and alerts
- 🔋 RTC backup support
- 🧩 Modular codebase designed for expansion

---

## 🖥️ Home screen

Example:

```text
TUE 02/09 19:30
24.3°C HUM 53%
```

Press the encoder to open the main menu.

---

## 🎛️ Controls

### General

| Action | Function |
|---|---|
| Rotate | Navigate the menu |
| Short press | Select / open |
| Long press | Go back |
| Long press in menu | Return to Home |

### Pomodoro / Stopwatch

| Action | Function |
|---|---|
| Short press | Start / pause |
| Double press | Reset |
| Long press | Return to menu |

---

## 🔩 Hardware

| Component | Purpose |
|---|---|
| Arduino Mega 2560 | Main controller |
| 16x2 LCD + I²C backpack | Display |
| DS3231 RTC | Real-time clock |
| Rotary encoder with push button | User input |
| DHT11 | Temperature + humidity |
| Buzzer | Audio feedback |

---

## 🔌 Pin map

| Function | Mega pin |
|---|---:|
| LCD + RTC SDA | 20 |
| LCD + RTC SCL | 21 |
| Encoder CLK | 22 |
| Encoder DATA | 23 |
| Encoder SW | 24 |
| DHT11 OUT | 25 |
| Buzzer | 26 |

### I²C addresses

```text
LCD     0x3F
DS3231  0x68
```

The LCD and RTC share the same I²C bus.

---

## 📚 Required Arduino libraries

Install these through the Arduino IDE Library Manager:

- **LiquidCrystal_I2C**
- **DHT sensor library by Adafruit**
- **Adafruit Unified Sensor**
- **RTClib by Adafruit**

---

## 🗂️ Project structure

```text
DeskOS/
├── README.md
├── LICENSE
├── docs/
│   └── deskos-wiring.png
├── hardware/
│   └── notes.md
└── src/
    └── DeskOS/
        ├── DeskOS.ino
        ├── Config.h
        ├── AppState.h
        ├── DisplayManager.h
        ├── DisplayManager.cpp
        ├── InputManager.h
        ├── InputManager.cpp
        ├── SensorManager.h
        ├── SensorManager.cpp
        ├── TimeManager.h
        ├── TimeManager.cpp
        ├── TimerManager.h
        ├── TimerManager.cpp
        ├── BuzzerManager.h
        └── BuzzerManager.cpp
```

The main `.ino` file now acts mainly as the application coordinator. Hardware
logic is split into small managers so that each part can evolve independently.

---

## 🧠 Architecture

```text
                 ┌───────────────┐
                 │   DeskOS.ino  │
                 │  App control  │
                 └───────┬───────┘
                         │
       ┌─────────────────┼─────────────────┐
       │                 │                 │
       ▼                 ▼                 ▼
┌─────────────┐   ┌─────────────┐   ┌─────────────┐
│   Display   │   │    Input    │   │   Timers    │
│   Manager   │   │   Manager   │   │   Manager   │
└─────────────┘   └─────────────┘   └─────────────┘
       │                                   │
       ▼                                   ▼
     LCD                              Pomodoro /
                                      Stopwatch

       ┌─────────────────┬─────────────────┐
       │                 │                 │
       ▼                 ▼                 ▼
┌─────────────┐   ┌─────────────┐   ┌─────────────┐
│   Sensors   │   │     Time    │   │   Buzzer    │
│   Manager   │   │   Manager   │   │   Manager   │
└─────────────┘   └─────────────┘   └─────────────┘
       │                 │
       ▼                 ▼
     DHT11            DS3231
```

---

## 🚀 Uploading

1. Open `DeskOS.ino` in Arduino IDE.
2. Select **Arduino Mega or Mega 2560**.
3. Select the correct COM port.
4. Install the required libraries.
5. Compile and upload.

If the RTC needs to be reset to your computer's compile time, temporarily
change:

```cpp
constexpr bool FORCE_RTC_SET = false;
```

to:

```cpp
constexpr bool FORCE_RTC_SET = true;
```

Upload once, then change it back to `false` and upload again.

---

## 🧩 Current applications

### Clock

Displays the real date and time from the DS3231.

```text
TUE 02/09/2026
19:30:42
```

### Environment

```text
TEMP 24.3°C
HUM  53.0%
```

### Pomodoro

```text
POMO RUNNING
24:38
```

The buzzer sounds when the countdown reaches zero.

### Stopwatch

```text
TIMER RUNNING
00:12:43
```

### Running

Currently a simple target display:

```text
10K TARGET
40:00 4:00/km
```

This module is intended to become a configurable pace / race calculator.

---

## 🔊 Audio feedback

DeskOS currently provides sounds for:

- startup
- selection
- reset
- back navigation
- Pomodoro completion
- RTC error

---

## 🛣️ Roadmap

- [ ] PIR presence detection
- [ ] Automatic LCD sleep / wake
- [ ] LDR ambient light sensing
- [ ] Automatic backlight behaviour
- [ ] Configurable Pomodoro duration
- [ ] Persistent settings
- [ ] Configurable running targets
- [ ] Pace / split calculator
- [ ] Prototype Shield V3 migration
- [ ] Cleaner connectors and wiring
- [ ] Custom 3D-printed enclosure
- [ ] USB PC monitoring mode
- [ ] CPU / RAM / temperature display
- [ ] Refine input debouncing
- [ ] Non-blocking buzzer sound engine

---

## 🔮 Planned hardware layout

The breadboard / jumper-wire prototype will eventually be migrated to a
**Prototype Shield V3**, which will act as the internal DeskOS motherboard.

Modules such as the display, RTC, encoder, and sensors can remain removable by
using pin headers rather than soldering them permanently.

---

## ⚠️ DS3231 battery note

Some **ZS-042 / HW-84 DS3231** boards contain a battery charging circuit.

A normal **CR2032 is not rechargeable**, so verify the board's charging circuit
before using a CR2032 in a permanently powered build.

---

## 🎯 Why build DeskOS?

The project is an ongoing playground for learning and experimenting with:

- Embedded C++
- Arduino
- I²C communication
- Sensors
- State machines
- Hardware abstraction
- Human-machine interfaces
- Electronics prototyping
- 3D-printed enclosures

---

## 📄 License

MIT License. See [`LICENSE`](LICENSE).
