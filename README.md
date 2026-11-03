# SPI-Based RFID Access Control and Intrusion Detection System with BLE Connectivity

## 📌 Project Overview

This project is an ESP32-based smart security system that combines RFID-based access control, IR sensor-based intrusion detection, and Bluetooth Low Energy (BLE) connectivity.

The system uses an RC522 RFID reader to authenticate users through their unique card UID. Access status is displayed on a 16×2 I2C LCD, while red and green LEDs indicate access status.

An IR sensor detects unauthorized intrusion, and the ESP32 sends real-time security notifications to a smartphone using BLE.

## 🎯 Project Objectives

* Implement RFID-based access control using SPI communication.
* Interface the RC522 RFID reader with ESP32.
* Display access status using an I2C LCD.
* Detect intrusion using an IR sensor.
* Send security alerts to a smartphone through BLE.
* Understand SPI, I2C, and BLE communication protocols.

## 🛠️ Hardware Components

| Component            | Description                          |
| -------------------- | ------------------------------------ |
| ESP32 DevKit         | Main microcontroller                 |
| RC522 RFID Reader    | RFID card authentication             |
| RFID Card / Keychain | User identification                  |
| 16×2 LCD with I2C    | Status display                       |
| IR Sensor            | Intrusion detection                  |
| Red LED              | Access denied / intrusion indication |
| Green LED            | Access granted indication            |
| Resistors            | LED current limiting                 |
| Breadboard           | Circuit assembly                     |
| Jumper Wires         | Hardware connections                 |

## 🔌 Pin Configuration

### 1. RFID Reader – SPI Communication

| RC522 Pin | ESP32 GPIO |
| --------- | ---------- |
| SDA / SS  | GPIO 5     |
| SCK       | GPIO 18    |
| MOSI      | GPIO 23    |
| MISO      | GPIO 19    |
| RST       | GPIO 4     |
| VCC       | 3.3V       |
| GND       | GND        |

### 2. LCD – I2C Communication

| LCD Pin | ESP32 GPIO |
| ------- | ---------- |
| SDA     | GPIO 21    |
| SCL     | GPIO 22    |
| VCC     | 3.3V       |
| GND     | GND        |

### 3. IR Sensor and LEDs

| Component     | ESP32 GPIO |
| ------------- | ---------- |
| IR Sensor OUT | GPIO 27    |
| Green LED     | GPIO 25    |
| Red LED       | GPIO 26    |

## ⚙️ Communication Protocols

### SPI (Serial Peripheral Interface)

SPI is used for communication between the ESP32 and RC522 RFID reader to retrieve the RFID card UID.

### I2C (Inter-Integrated Circuit)

I2C is used to interface the 16×2 LCD with the ESP32 using SDA and SCL lines.

### BLE (Bluetooth Low Energy)

BLE enables wireless communication between the ESP32 and a smartphone. It sends security status notifications to the mobile device.

## 💻 Software and Development Tools

* Visual Studio Code
* PlatformIO IDE
* Arduino Framework
* Embedded C/C++
* nRF Connect for Mobile
* Git and GitHub

## 📚 Libraries Used

* MFRC522
* LiquidCrystal_I2C
* Wire
* SPI
* ESP32 BLE Libraries

## 🔄 Working Principle

1. ESP32 initializes the RFID reader, LCD, IR sensor, and BLE.
2. The RC522 RFID reader scans the card and retrieves its unique UID.
3. ESP32 compares the scanned UID with the authorized UID stored in the program.
4. If the UID matches, the LCD displays **ACCESS GRANTED**, and the green LED turns ON.
5. If the UID does not match, the LCD displays **ACCESS DENIED**, and the red LED turns ON.
6. The IR sensor detects an object or intrusion within its detection range.
7. When intrusion is detected, the system activates the red LED and displays an intrusion alert.
8. BLE sends security notifications to the connected smartphone.

## 📱 BLE Notifications

The system sends the following notifications to the smartphone through BLE:

* ACCESS GRANTED
* ACCESS DENIED
* INTRUSION DETECTED
* SYSTEM READY

**Mobile Application:** nRF Connect for Mobile

## 🧪 Testing and Results

* Successfully tested RFID card detection.
* Verified authorized card authentication.
* Verified unauthorized card detection.
* Tested LCD status display.
* Successfully connected ESP32 to a smartphone using BLE.
* Verified BLE notification functionality.
* Tested IR sensor-based intrusion detection.

## 🚀 Skills and Concepts Learned

* ESP32 Microcontroller Programming
* Embedded C/C++
* SPI Communication
* I2C Communication
* BLE Communication
* RFID Interfacing
* IR Sensor Interfacing
* Hardware and Software Integration
* Embedded System Debugging
* PlatformIO Development Environment

## 🔮 Future Enhancements

* Develop a web-based security monitoring dashboard.
* Store access logs with date and time.
* Develop a dedicated mobile application.
* Integrate cloud-based security monitoring.
* Add additional security sensors.

## Project Demo
[Watch Project Demo on You Tube]
https://youtube.com/shorts/IuRDZ2gRIuM?si=yo4rXm8XuHtOI19P

## 👨‍💻 Author

**Bala Krishnan M.**

BE – Electrical and Electronics Engineering

**Project Domain:** Embedded Systems / Firmware Development

---

⭐ If you find this project useful, feel free to star this repository!
