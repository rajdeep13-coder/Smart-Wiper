# Question

Anindya was busy flexing his biceps while driving in the rain. But every time he had to stop mid-pose to switch on the wiper, his "aesthetic" was ruined. This constant interruption annoyed him badly. Design a smart wiper for Anindya using a rain sensor, servo motor, ESP8266, and a battery.

![IoT](https://img.shields.io/badge/IoT-Project-blue?style=for-the-badge)
![Hackathon](https://img.shields.io/badge/IoTricity-S2-orange?style=for-the-badge)

#  Smart Wiper System

The **Smart Wiper System** automates windshield wiping using a **two-pin HW-028 rain sensor**, an **IR obstacle avoidance sensor**, an **SG90 servo motor**, and an **ESP8266 (NodeMCU)**.  
It ensures that when it rains, the servo-powered wiper activates, and when an obstacle is detected, the system pauses — keeping the view (and Anindya’s flexing) uninterrupted.

---

##  Hardware Requirements

- **ESP8266 (NodeMCU)** → Main controller (handles sensors + servo logic)  
- **SG90 Servo Motor** → Moves the wiper arm  
  - Signal → `D1 (GPIO5)`  
  - VCC → `5V`  
  - GND → Negative rail  

- **HW-028 Rain Sensor (Two-Pin)** → Detects rain via resistance changes, linked to IR sensor  
- **IR Sensor (e.g., KY-032)** → Relays rain/obstacle detection  
  - OUT → `D3 (GPIO0)`  

- **Battery + 5V Regulator (≥1A)** → Powers the circuit  
  - ESP8266: ~100–300 mA  
  - Servo: ~100–500 mA  
  - IR Sensor: ~20–50 mA  
  - Rain Sensor: ~10–20 mA  

- Breadboard & jumper wires for prototyping  

---

## 🛠️ Wiring Diagram (Textual)

