# Underwater-Drone
An underwater wireless drone designed for real-time environmental monitoring. Equipped with a temperature sensor and an onboard camera, it provides live POV video streaming while operating below water. Developed as a smart solution for remote aquatic observation and data collection.

## 🔧 Components Used

### 1. 🔌 Control System
- **Microcontroller:** Arduino ATmega (Uno/Nano/compatible)
- **Motor Driver:** L298N Dual H-Bridge
- **Motors:** JGB37-520 High Torque Speed Metal Gear Motors
- **Joystick:** 3-axis XYZ Analog Joystick
- **Wireless Communication:** LoRa SX1278 RF Modules (Transmitter & Receiver)
- **Power Supply:** 14.8V 2600mAh Li-ion Battery

### 2. 📷 Camera System
- **Microcontroller with Camera:** ESP32-CAM (handles POV video streaming)

### 3. 🌡 Temperature Monitoring
- **Microcontroller:** Arduino Nano
- **Sensor:** DS18B20 Waterproof Temperature Probe Sensor
