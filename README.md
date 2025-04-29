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

# 🤖 Underwater Wireless Drone

A wireless underwater drone designed for real-time environmental monitoring. Equipped with a temperature sensor and onboard ESP32-CAM, it streams POV video and captures live temperature data via LoRa communication.

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

---

## 🛠 Setup Instructions

### 1. **Hardware Setup**
Follow these steps to assemble your underwater drone:
1. Connect the **Arduino ATmega** to the **L298N motor driver** and **JGB37-520 motors** using jumper wires.
2. Attach the **3-axis joystick** to the **Arduino** for control input.
3. Connect the **LoRa SX1278 modules** to the **Arduino** for wireless communication.
4. Install the **ESP32-CAM** and wire it for real-time video streaming.
5. Attach the **DS18B20** temperature sensor to the **Arduino Nano**.
6. Power the system with the **14.8V 2600mAh battery** (ensure the battery is securely housed in a waterproof casing).

### 2. **Software Setup**
1. Install the **Arduino IDE** if you haven't already (download from [here](https://www.arduino.cc/en/software)).
2. Clone the repository or download the Arduino code from the **`src/`** folder.
3. Open the Arduino IDE and load the appropriate sketch:
   - For controlling motors, ESP32-CAM, and LoRa communication, use the **control sketch** (e.g., `drone_control.ino`).
   - For reading temperature data, use the **temperature sensor sketch** (e.g., `temperature_monitor.ino`).
4. Configure your LoRa settings (frequency, baud rate, etc.) as required.
5. Upload the sketches to the respective boards (Arduino Uno, Nano, ESP32).

---

## ⚙️ Usage

Once setup is complete, power on the drone and follow these steps to operate:

1. Use the **3-axis joystick** to control the drone's movement.
2. The **ESP32-CAM** streams live video, which can be viewed on a connected device (using an app or direct connection via the cloud).
3. The **LoRa** modules handle communication between the drone and the base station.
4. The **temperature sensor** sends real-time temperature readings to the cloud via Arduino Cloud.

---

## 📷 Circuit Diagram

![Circuit Diagram](diagrams/underwater_drone_wiring.png)

---

## 🤝 Contributing

If you'd like to contribute to this project, please follow these steps:
1. Fork the repository.
2. Create a branch for your feature (`git checkout -b feature-name`).
3. Commit your changes (`git commit -m 'Add feature'`).
4. Push to the branch (`git push origin feature-name`).
5. Create a pull request.

