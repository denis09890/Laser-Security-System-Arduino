# 🚨 Intelligent Laser Motion Detection Alarm System

[![Language-C++](https://img.shields.io/badge/Language-C%2B%2B-blue.svg)](https://img.shields.io/badge/Language-C%2B%2B-blue.svg)
[![Platform-Arduino](https://img.shields.io/badge/Platform-Arduino-00979D.svg)](https://img.shields.io/badge/Platform-Arduino-00979D.svg)
[![Hardware-Atmega328P](https://img.shields.io/badge/Hardware-ATmega328P-red.svg)](https://img.shields.io/badge/Hardware-ATmega328P-red.svg)

## 📖 Project Overview
This project focuses on the development of a cost-effective and efficient security alert system based on the physical principle of interrupting a laser beam to detect intrusions. Developed for the **Arduino UNO R3** platform, the system provides an unmistakable notification through a distinctive sound melody and a visual LED indicator.



## 🛠️ System Architecture
The system is designed with a modular approach, integrating several key electronic components:

* **Processing Unit**: Arduino UNO R3 (ATmega328P) acting as the central "brain".
* **Detection Unit**: A **KY-008 Laser Module** (transmitter) and an **LDR Light Sensor** (receiver).
* **Alert Unit**: A passive buzzer for distinct acoustic signals and a 5mm LED for visual feedback.
* **Power Supply**: Powered via a 7.4V Li-ion rechargeable battery or a standard USB connection.



## 🌟 Key Features
* ✅ **Non-blocking Logic**: Implemented using the `millis()` function to ensure a smooth execution loop without using `delay()`.
* ✅ **Automatic Hold Time**: The alarm remains active for **5 seconds** after the laser beam is restored to ensure user notification.
* ✅ **Real-time Monitoring**: Continuous digital acquisition of LDR signals to detect status changes instantly.
* ✅ **Distinctive Alerts**: High-frequency alarm sound (1000 Hz) with patterned beeps.

## 📊 Logic States
The software manages the alarm through three main logic states:
1. **IDLE (State 0)**: System is armed, the laser is hitting the LDR, and outputs are OFF.
2. **ACTIVE (State 1)**: Beam is interrupted; the buzzer and LED are activated immediately.
3. **HOLD (State 2)**: Beam is restored, but the alarm stays ON for a 5000ms countdown.



## 📂 Project Structure
* **`src/`**: Contains the Arduino source code (`laser.ino`).
* **`docs/`**: Technical documentation (MES Documentation), circuit schematics, and component lists.

## 🚀 Getting Started
1. **Hardware Setup**: Assemble the components on a breadboard using Dupont wires as specified in the schematics.
2. **Software Installation**: Open `src/laser.ino` in **Arduino IDE**.
3. **Calibration**: Adjust the laser alignment to ensure it directly hits the LDR sensor.
4. **Deploy**: Upload the code to your Arduino UNO R3 and test the intrusion detection.
