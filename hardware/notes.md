# Hardware Notes

## Current pin map

| Function | Arduino Mega 2560 |
|---|---:|
| I²C SDA — LCD + DS3231 | 20 |
| I²C SCL — LCD + DS3231 | 21 |
| Rotary encoder CLK | 22 |
| Rotary encoder DATA | 23 |
| Rotary encoder SW | 24 |
| DHT11 OUT | 25 |
| Buzzer + | 26 |

All modules share the Arduino's 5V and GND rails as appropriate.

## I²C devices

| Device | Address |
|---|---|
| LCD 16x2 backpack | `0x3F` |
| DS3231 RTC | `0x68` |

## DS3231 battery note

Some ZS-042 / HW-84 DS3231 boards include a charging circuit intended for
rechargeable cells. A standard CR2032 is not rechargeable. Verify or modify
the charging circuit before leaving a CR2032 installed in a permanently
powered build.
