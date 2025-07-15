# 🐼 PING Panda Pulse Monitor

A DIY smartwatch-style project using ESP32, OLED, and a pulse sensor that monitors the user's heart rate and sends an **email alert** via SMTP2GO when the BPM (beats per minute) is **abnormally low or high** (outside 60–100 BPM).

---

## 📦 Features

- ⏱️ Reads heart rate using analog pulse sensor  
- 📺 Displays live BPM on OLED screen  
- 🧠 Calculates average BPM from 5 readings  
- 📩 Sends alert email via **SMTP2GO** if average BPM is abnormal  
- 🌐 WiFi connected – no GSM module needed  
- ⚡ Powered via USB/laptop (no battery required)

---

## 🛠️ Hardware Required

| Component            | Details                             |
|----------------------|-------------------------------------|
| ESP32 Dev Module     | Any ESP32 board                     |
| OLED Display         | 128x64 I2C (SSD1306)                |
| Pulse Sensor         | KY-039 or similar analog sensor     |
| Jumper Wires         | Male-to-female                      |
| Breadboard           | Optional                            |

---

## 🔌 Circuit Connections

### OLED Display (SSD1306)

| OLED Pin | ESP32 Pin   |
|----------|-------------|
| VCC      | 3.3V        |
| GND      | GND         |
| SCL      | GPIO 22     |
| SDA      | GPIO 21     |

### Pulse Sensor

| Sensor Pin | ESP32 Pin |
|------------|-----------|
| Signal     | GPIO 34   |
| VCC        | 3.3V      |
| GND        | GND       |

---

## 📲 Email Alert Setup (SMTP2GO)

1. 🔗 Create a free account at [SMTP2GO](https://www.smtp2go.com)
2. ➕ Go to **Settings → SMTP Users** → create a new SMTP user
3. ✅ Verify your sender email (e.g., `yourname@yourdomain.com`)
4. ✍️ In the code, set:
   ```cpp
   #define AUTHOR_EMAIL "your_smtp_username"     // NOT your email — use SMTP username
   #define AUTHOR_PASSWORD "your_smtp_password"
   #define SENDER_EMAIL "your_verified_email"
   #define RECIPIENT_EMAIL "receiver@email.com"
   ```
5. 📤 Use port `587` (recommended), or try `2525` or `8025` if blocked

---

## 📚 Required Arduino Libraries

Install these libraries from the **Library Manager** (`Sketch > Include Library > Manage Libraries`):

- [ESP Mail Client](https://github.com/mobizt/ESP-Mail-Client) by Mobizt
- Adafruit GFX Library
- Adafruit SSD1306
- WiFi (included with ESP32 board)

---

## 🚀 Uploading

1. Select board: `ESP32 Dev Module` under `Tools > Board`
2. Connect ESP32 via USB
3. Paste and upload the code from `main.ino` (or your final sketch)
4. Open Serial Monitor @ 115200 baud to view logs

---

## 📊 BPM Logic

- Reads analog value from pulse sensor
- On each pulse detection:
  - Calculates BPM using time between beats
  - Stores 5 valid readings
- If average BPM < 60 or > 100:
  - Triggers an email alert

---

## 📬 Sample Alert Email

**Subject:** ⚠️ PNG Panda Alert: Abnormal BPM Detected  
**Body:**
```
Average BPM recorded: 122  
Warning: This is outside the safe range (60–100).
```

---

## 📸 Screenshots

_Add screenshots of:_
- OLED display showing BPM
- Serial Monitor output
- Example email alert in inbox

---

## 📘 License

MIT License – Free to use, modify, and share.
