# ESP32 Instrument Cluster Simulation

This project is part of my bachelor’s thesis and demonstrates how to interconnect multiple sensors and electronic modules using **two ESP32 development boards**. The setup simulates an **instrument cluster of a typical car**, displaying real-time sensor data both on a **TFT screen** and through a **web interface**.

## 🧠 Overview

The system is built around **two ESP32 boards** connected via the **ESP-NOW wireless protocol**:

- **Sender ESP32** — collects data from various sensors (e.g., temperature, humidity)  
- **Receiver ESP32** — displays the received data on a **TFT LCD screen** and hosts an **asynchronous web server** for remote monitoring  

All communication between the boards is **encrypted**, ensuring data confidentiality and integrity.

## ⚙️ Features

- 📡 **ESP-NOW communication** — secure, encrypted data transfer between the two ESP32 boards  
- 🌡️ **Real-time sensor readings** — accurate and efficient data acquisition  
- 🖥️ **TFT display integration** — live data visualization in a compact, intuitive format  
- 🌐 **Asynchronous web server** — interactive web page showing all sensor data  
- 🔄 **Unit selection module** — choose between Celsius/Fahrenheit and km/h/mph  
  - Available both via **Serial Monitor** and the **web interface**

## 🧩 Hardware Components

- 2x ESP32 development boards  
- 1x DHT11 temperature and humidity sensor  
- 1x Adafruit TFT display  
- (Optional) additional modules or sensors for extended functionality  

## 💻 Software Details

- **Programming language:** C++ (Arduino framework)  
- **Libraries used:**
  - `esp_now.h` — for wireless communication  
  - `WiFi.h` — for web server connection  
  - `Adafruit_GFX.h`, `Adafruit_TFTLCD.h` — for the display  
  - `ESPAsyncWebServer.h` — for the async web interface  

The codebase is structured modularly, with separate components for:
- Sensor reading and processing  
- ESP-NOW communication  
- Display handling  
- Web interface management  

## 🚀 How It Works

1. The **sender ESP32** reads data from the DHT11 sensor.  
2. It transmits the data to the **receiver ESP32** via the ESP-NOW protocol.  
3. The receiver displays the data on the **TFT screen** and updates the **web page** in real time.  
4. The user can switch units (temperature/speed) either from the **Serial Monitor** or directly on the **web page**.  

## 🔐 Security

ESP-NOW communication between the two ESP32 boards is **encrypted**, ensuring:
- Data confidentiality  
- Transmission integrity  
- Reliable connection between devices  

## 🧭 Conclusion

This project successfully demonstrates how ESP32 development boards can be used to **interconnect, control, and visualize sensor data** in a complex and secure setup.  
It provides a foundation for future **IoT monitoring and control systems** and highlights the potential of ESP32 in **real-time embedded applications**.

---

### 📸 Demo & Screenshots
![1](ESP32%20Sender/data/doc/IMG_20230617_003087.jpg)

![4](ESP32%20Sender/data/doc/IMG_20230617_003088.png)

![2](ESP32%20Sender/data/doc/IMG_20230617_003057.jpg)

![3](ESP32%20Sender/data/doc/IMG_20230617_003087.jpg)


![5](ESP32%20Sender/data/doc/IMG_20230617_003125.jpg)

![6](ESP32%20Sender/data/doc/IMG_20230617_003147.jpg)

![7](ESP32%20Sender/data/doc/IMG_20230617_003147.jpg)

![8](ESP32%20Sender/data/doc/IMG_20230617_003221.jpg)

![9](ESP32%20Sender/data/doc/IMG_20230617_003323.jpg)

![10](ESP32%20Sender/data/doc/IMG_20230617_003329.jpg)

![11](ESP32%20Sender/data/doc/IMG_20230617_003406.jpg)

![12](ESP32%20Sender/data/doc/IMG_20230617_003428.jpg)


---

