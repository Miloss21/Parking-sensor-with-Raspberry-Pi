# Parking Sensor with Raspberry Pi

A real-time parking sensor system built with **Raspberry Pi Zero 2 WH** and written in **C++**.
The system measures distance using an HC-SR04 ultrasonic sensor, displays it on a 16x2 LCD screen,
and alerts with a buzzer that beeps faster as objects get closer.

## Hardware

| Component | Role |
|---|---|
| Raspberry Pi Zero 2 WH | Main computer |
| HC-SR04 Ultrasonic Sensor | Distance measurement (2–400 cm) |
| LCD 16x2 with I2C adapter | Real-time distance and status display |
| Active Buzzer | Proximity alert |
| 1kΩ + 2kΩ resistors | Voltage divider for ECHO pin protection |

## How It Works

The HC-SR04 sends an ultrasonic pulse and measures the time it takes to return.
Distance is calculated as: `distance = (time × 0.0343) / 2`

The buzzer has five alert zones:
- **> 100 cm** — silent
- **60–100 cm** — slow beep
- **30–60 cm** — medium beep
- **10–30 cm** — fast beep
- **< 10 cm** — continuous tone

## Project Structure
```
├── LCD.h / LCD.cpp       — LCD display class (I2C communication)
├── Sensor.h / Sensor.cpp — HC-SR04 sensor class
├── Buzzer.h / Buzzer.cpp — Buzzer control class
└── main.cpp              — Entry point
```

## Dependencies

- [WiringPi](https://github.com/WiringPi/WiringPi)
- Linux I2C drivers (`i2c-tools`, `libi2c-dev`)
