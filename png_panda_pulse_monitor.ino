#include <WiFi.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <ESP_Mail_Client.h>

// OLED display config
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// Pulse sensor configuration
#define PULSE_PIN 34            // Analog input pin from pulse sensor
int threshold = 550;            // Raw signal threshold to detect a heartbeat
bool pulseDetected = false;
unsigned long lastBeat = 0;
int bpmReadings[5];             // To store 5 BPM values
int count = 0;                  // Reading count

// ======== 🔁 CHANGE THESE TO YOUR CONFIGURATION ========

// WiFi Credentials
const char* ssid = "Nothing";              // 🔁 Your WiFi SSID
const char* password = "66666666";         // 🔁 Your WiFi password

// SMTP2GO Server
#define SMTP_HOST "mail.smtp2go.com"
#define SMTP_PORT 587                      // ✅ 587 recommended for TLS (can also use 2525 or 8025)

// SMTP Login
#define AUTHOR_EMAIL "AeroBay"             // 🔁 SMTP2GO Username (not your email)
#define AUTHOR_PASSWORD "AeroBay@2025"     // 🔁 SMTP2GO Password for the SMTP user

// Sender Details
#define SENDER_NAME "Pulse Monitor"
#define SENDER_EMAIL "gaurav.pratapsingh@aerobay.in" // ✅ Must be verified on SMTP2GO

// Recipient Details
#define RECIPIENT_NAME "Gaurav". ////change accordingly
#define RECIPIENT_EMAIL "gauravpratap2631@gmail.com" // 🔁 Receiver of the alert email

// Mail session
SMTPSession smtp;

void sendEmailAlert(int avgBPM) {
  SMTP_Message message;
  Session_Config config;

  // SMTP Server settings
  config.server.host_name = SMTP_HOST;
  config.server.port = SMTP_PORT;
  config.login.email = AUTHOR_EMAIL;            // SMTP2GO Username
  config.login.password = AUTHOR_PASSWORD;      // SMTP2GO Password
  config.login.user_domain = "";                // Leave blank for SMTP2GO
  config.time.ntp_server = "pool.ntp.org";      // NTP server for correct time

  // Compose Email
  message.sender.name = SENDER_NAME;
  message.sender.email = SENDER_EMAIL;
  message.subject = "⚠️ PNG Panda Alert: Abnormal BPM Detected";
  message.addRecipient(RECIPIENT_NAME, RECIPIENT_EMAIL);
  message.text.content = "Average BPM recorded: " + String(avgBPM) + 
                         "\nWarning: This is outside the normal range (60–100).";

  // Debugging + callback
  smtp.debug(1);
  smtp.callback([](SMTP_Status status) {
    Serial.println(status.info());
  });

  // Connect and send
  if (!smtp.connect(&config)) {
    Serial.println("❌ SMTP connection failed: " + smtp.errorReason());
    return;
  }

  if (!MailClient.sendMail(&smtp, &message)) {
    Serial.println("❌ Email send failed: " + smtp.errorReason());
  }

  smtp.closeSession();
}

void setup() {
  Serial.begin(115200);
  pinMode(PULSE_PIN, INPUT);

  // OLED Initialization
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.print("PNG Panda Starting...");
  display.display();

  // WiFi Connection
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\n✅ WiFi Connected!");
  display.clearDisplay();
  display.setCursor(0, 0);
  display.print("WiFi Connected!");
  display.display();
  delay(1000);
}

void loop() {
  int raw = analogRead(PULSE_PIN);
  unsigned long currentTime = millis();

  // Detect heartbeat
  if (raw > threshold && !pulseDetected) {
    pulseDetected = true;

    if (lastBeat > 0) {
      int duration = currentTime - lastBeat;
      int bpm = 60000 / duration;

      if (bpm >= 40 && bpm <= 200) { // Valid BPM range
        bpmReadings[count] = bpm;
        count++;

        Serial.print("✔ BPM ");
        Serial.print(count);
        Serial.print(": ");
        Serial.println(bpm);

        display.clearDisplay();
        display.setCursor(0, 10);
        display.print("BPM ");
        display.print(count);
        display.print(": ");
        display.print(bpm);
        display.display();

        // After 5 readings, calculate average
        if (count >= 5) {
          int sum = 0;
          for (int i = 0; i < 5; i++) sum += bpmReadings[i];
          int avg = sum / 5;

          Serial.print("📊 Avg BPM: ");
          Serial.println(avg);

          display.clearDisplay();
          display.setCursor(0, 20);
          display.print("Avg BPM: ");
          display.print(avg);
          display.display();

          // If abnormal, send alert
          if (avg < 60 || avg > 100) {
            sendEmailAlert(avg);
          }

          count = 0;  // Reset for next round
        }
      }
    }

    lastBeat = currentTime;
  }

  if (raw < threshold) {
    pulseDetected = false;
  }

  delay(10); // Smoothing delay
}
#include <WiFi.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <ESP_Mail_Client.h>

// OLED display config
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// Pulse sensor configuration
#define PULSE_PIN 34            // Analog input pin from pulse sensor
int threshold = 550;            // Raw signal threshold to detect a heartbeat
bool pulseDetected = false;
unsigned long lastBeat = 0;
int bpmReadings[5];             // To store 5 BPM values
int count = 0;                  // Reading count

// ======== 🔁 CHANGE THESE TO YOUR CONFIGURATION ========

// WiFi Credentials
const char* ssid = "Nothing";              // 🔁 Your WiFi SSID
const char* password = "66666666";         // 🔁 Your WiFi password

// SMTP2GO Server
#define SMTP_HOST "mail.smtp2go.com"
#define SMTP_PORT 587                      // ✅ 587 recommended for TLS (can also use 2525 or 8025)

// SMTP Login
#define AUTHOR_EMAIL "AeroBay"             // 🔁 SMTP2GO Username (not your email)
#define AUTHOR_PASSWORD "AeroBay@2025"     // 🔁 SMTP2GO Password for the SMTP user

// Sender Details
#define SENDER_NAME "Pulse Monitor"
#define SENDER_EMAIL "gaurav.pratapsingh@aerobay.in" // ✅ Must be verified on SMTP2GO

// Recipient Details
#define RECIPIENT_NAME "Gaurav". ////change accordingly
#define RECIPIENT_EMAIL "gauravpratap2631@gmail.com" // 🔁 Receiver of the alert email

// Mail session
SMTPSession smtp;

void sendEmailAlert(int avgBPM) {
  SMTP_Message message;
  Session_Config config;

  // SMTP Server settings
  config.server.host_name = SMTP_HOST;
  config.server.port = SMTP_PORT;
  config.login.email = AUTHOR_EMAIL;            // SMTP2GO Username
  config.login.password = AUTHOR_PASSWORD;      // SMTP2GO Password
  config.login.user_domain = "";                // Leave blank for SMTP2GO
  config.time.ntp_server = "pool.ntp.org";      // NTP server for correct time

  // Compose Email
  message.sender.name = SENDER_NAME;
  message.sender.email = SENDER_EMAIL;
  message.subject = "⚠️ PNG Panda Alert: Abnormal BPM Detected";
  message.addRecipient(RECIPIENT_NAME, RECIPIENT_EMAIL);
  message.text.content = "Average BPM recorded: " + String(avgBPM) + 
                         "\nWarning: This is outside the normal range (60–100).";

  // Debugging + callback
  smtp.debug(1);
  smtp.callback([](SMTP_Status status) {
    Serial.println(status.info());
  });

  // Connect and send
  if (!smtp.connect(&config)) {
    Serial.println("❌ SMTP connection failed: " + smtp.errorReason());
    return;
  }

  if (!MailClient.sendMail(&smtp, &message)) {
    Serial.println("❌ Email send failed: " + smtp.errorReason());
  }

  smtp.closeSession();
}

void setup() {
  Serial.begin(115200);
  pinMode(PULSE_PIN, INPUT);

  // OLED Initialization
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.print("PNG Panda Starting...");
  display.display();

  // WiFi Connection
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\n✅ WiFi Connected!");
  display.clearDisplay();
  display.setCursor(0, 0);
  display.print("WiFi Connected!");
  display.display();
  delay(1000);
}

void loop() {
  int raw = analogRead(PULSE_PIN);
  unsigned long currentTime = millis();

  // Detect heartbeat
  if (raw > threshold && !pulseDetected) {
    pulseDetected = true;

    if (lastBeat > 0) {
      int duration = currentTime - lastBeat;
      int bpm = 60000 / duration;

      if (bpm >= 40 && bpm <= 200) { // Valid BPM range
        bpmReadings[count] = bpm;
        count++;

        Serial.print("✔ BPM ");
        Serial.print(count);
        Serial.print(": ");
        Serial.println(bpm);

        display.clearDisplay();
        display.setCursor(0, 10);
        display.print("BPM ");
        display.print(count);
        display.print(": ");
        display.print(bpm);
        display.display();

        // After 5 readings, calculate average
        if (count >= 5) {
          int sum = 0;
          for (int i = 0; i < 5; i++) sum += bpmReadings[i];
          int avg = sum / 5;

          Serial.print("📊 Avg BPM: ");
          Serial.println(avg);

          display.clearDisplay();
          display.setCursor(0, 20);
          display.print("Avg BPM: ");
          display.print(avg);
          display.display();

          // If abnormal, send alert
          if (avg < 60 || avg > 100) {
            sendEmailAlert(avg);
          }

          count = 0;  // Reset for next round
        }
      }
    }

    lastBeat = currentTime;
  }

  if (raw < threshold) {
    pulseDetected = false;
  }

  delay(10); // Smoothing delay
}
