# IoT-Based Automated Water Gate Control System

## Overview
The **IoT-Based Automated Water Gate Control System** is designed to monitor and regulate water levels using ESP32, water level sensors, servo motors, and Blynk IoT platform. The system provides real-time updates via Telegram and allows remote control of water gates through the Blynk app.

## Features
- **Real-time water level monitoring** using an analog water level sensor.
- **Automated water gate control** based on predefined thresholds.
- **Remote control via Blynk** to manually open/close the gates.
- **Alerts and notifications** through Telegram for water level updates.
- **Buzzer alarm** for flood warnings.

## Hardware Requirements
- **ESP32 Development Board**
- **Water Level Sensor** (Analog - e.g., SEN0189)
- **Servo Motors (x2)** (for gate control)
- **Buzzer** (for alerts)
- **Jumper Wires** and necessary connections
- **Power Supply** (5V/3.3V for ESP32)

## Software Requirements
- **Arduino IDE** (with ESP32 board support installed)
- **Blynk App** (for IoT control and monitoring)
- **Telegram Bot API** (for sending notifications)
- **Required Libraries:**
  - WiFi.h
  - BlynkSimpleEsp32.h
  - WiFiClientSecure.h
  - UniversalTelegramBot.h
  - Servo.h

## Installation and Setup
### 1. Set Up ESP32
- Install the **ESP32 board package** in Arduino IDE.
- Add required libraries from the **Library Manager**.
- Connect ESP32 to your system via USB.

### 2. Configure Blynk
- Create a new **Blynk project**.
- Add a **Virtual Pin (V0) for water level** and **V1 for gate control**.
- Obtain the **Blynk Authentication Token** from the app.

### 3. Set Up Telegram Bot
- Create a Telegram bot using **BotFather**.
- Get the **BOT Token** and **CHAT ID**.

### 4. Upload Code to ESP32
- Replace **Wi-Fi credentials**, **Blynk Auth Token**, and **Telegram BOT Token** in the code.
- Compile and upload the code to the ESP32.

## How It Works
1. The **water level sensor** continuously monitors the water level.
2. The ESP32 sends updates to **Blynk and Telegram**.
3. If the level crosses **set thresholds**, the gates automatically adjust:
   - **Low level:** Gates remain closed.
   - **Medium level:** Gates open **partially**.
   - **High level:** Gates open **fully**.
4. Users can manually control the gate via **Blynk**.
5. A **buzzer** activates if water levels reach flood conditions.

## Pin Configuration 
NodeMCU (ESP8266):

Component	ESP32 Pin	Equivalent NodeMCU (ESP8266) Pin
Water Sensor	GPIO34 (A2)	A0 (Only one ADC pin available)
Servo Motor 1	GPIO18	D5 (GPIO14)
Servo Motor 2	GPIO19	D6 (GPIO12)
Buzzer	GPIO5	D1 (GPIO5)
Wi-Fi Connection	Built-in	Built-in
Blynk Virtual Pin for Water Level	V0	V0
Blynk Virtual Pin for Gate Control	V1	V1
Notes for NodeMCU (ESP8266) Adaptation:
Water Sensor: ESP8266 has only one analog input (A0) with a 10-bit ADC (0-1023), so you will need to modify the analogRead scaling accordingly:
cpp
Copy
Edit
float waterLevelPercentage = (analogRead(A0) / 1023.0) * 100;
Servo Motors: Use D5 (GPIO14) and D6 (GPIO12), as these pins support PWM.
Buzzer: Use D1 (GPIO5) as it supports digital output.
Wi-Fi and Blynk: No changes are needed, as Wi-Fi is built-in.
Telegram Bot: No changes are needed for communication, but ensure secure connections work with ESP8266.



