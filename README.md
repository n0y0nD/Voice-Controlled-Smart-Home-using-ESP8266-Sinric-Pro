# Smart Home Automation using ESP8266, Alexa & Google Assistant

An IoT-based smart home automation system powered by the NodeMCU ESP8266.  
The system enables users to control up to four electrical appliances via voice commands using Amazon Alexa and Google Assistant, along with physical manual switches.  

It provides real-time bidirectional state synchronization using the Sinric Pro cloud.

---

## 📌 Key Highlights
✔ Voice control via Alexa & Google Assistant  
✔ Manual wall-switch/button control  
✔ Real-time feedback & synchronization  
✔ WiFi-enabled remote operation  
✔ Scalable and low-cost implementation  
✔ Designed for reliability and easy deployment  

---

## 🧠 System Overview
The ESP8266 connects to the local WiFi network and maintains a persistent connection with Sinric Pro cloud services.  
Voice commands issued through smart assistants are transmitted to the cloud and relayed to the device, which toggles the appropriate relay channel.

If a manual switch is pressed, the device updates the cloud instantly, ensuring the mobile app and assistants always display the correct state.

---

## 🏗 Architecture
Voice Assistant → Sinric Pro Cloud → ESP8266 → Relay → Appliance  
Manual Switch → ESP8266 → Sinric Pro Cloud → Updated everywhere

---

## 🛠 Hardware Requirements
- NodeMCU ESP8266 (ESP-12E)
- 4-Channel Relay Module
- Push Buttons / Toggle Switches
- AC Appliances / Loads
- Power Supply & connectors

---

## 💻 Software Stack
- Arduino IDE
- Embedded C/C++
- ESP8266 WiFi libraries
- Sinric Pro SDK / APIs

---

## ⚙️ Board Settings
In Arduino IDE select:

Board: **NodeMCU 1.0 (ESP-12E Module)**

---

## 🔧 Installation & Setup
1. Install ESP8266 board package in Arduino IDE.
2. Install necessary libraries.
3. Insert your WiFi SSID and password.
4. Configure Sinric Pro credentials and device IDs.
5. Upload the firmware to the board.
6. Link devices with Alexa / Google Home.

---

## 📡 Supported Functionalities
- Turn ON/OFF appliances remotely
- Control devices via routines & automation
- Maintain sync between manual & voice actions
- Expandable to additional devices

---

## 🔒 Security Note
Keep your WiFi credentials and API keys private.  
Avoid committing secrets to public repositories.

---

## 👨‍💻 Author
**NAYANYJYOTI DAS**

---

## 📄 License
This project is intended for academic and learning purposes.
