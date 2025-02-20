#define BLYNK_TEMPLATE_ID "TMPL38B9XUXpB"
#define BLYNK_TEMPLATE_NAME "iot"
#define BLYNK_AUTH_TOKEN "ndbF0KJFRqxGqaS0W9ukBx_J51XEZhHR"

// Include libraries
#include <WiFi.h>                 
#include <BlynkSimpleEsp32.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>
#include <Servo.h>

// Wi-Fi credentials
const char* ssid = "Prashanth";    
const char* password = "12345678901"; 

// Telegram credentials
#define BOTtoken "7588548414:AAFX1jQbQCTs0XLQpu0bd8ugeZINpO7J3PE"
#define CHAT_ID "1083232259" 

// Pins
const int waterSensorPin = 34;  // GPIO34 (Analog input for water sensor)
const int servoPin1 = 18;       // GPIO18 for Servo 1
const int servoPin2 = 19;       // GPIO19 for Servo 2
const int buzzerPin = 5;        // GPIO5 for Buzzer

// Water level thresholds
float thresholdValue1 = 40.0;
float thresholdValue2 = 40.0;
float floodThreshold = 40.0;
float ledThreshold = 40.0;

// Max tank height in cm
const float maxHeight = 100.0;

// Servo initialization
Servo gateServo1;
Servo gateServo2;

WiFiClientSecure client;
UniversalTelegramBot bot(BOTtoken, client);

unsigned long previousMillis = 0;
const long interval = 20000; 

void setup() {
  Serial.begin(115200);

  // Connect to WiFi
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi...");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println("\nConnected to WiFi!");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  // Initialize Blynk
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, password);

  // Initialize Servos
  gateServo1.attach(servoPin1);
  gateServo2.attach(servoPin2);
  gateServo1.write(0); // Close gate 1
  gateServo2.write(0); // Close gate 2

  // Buzzer setup
  pinMode(buzzerPin, OUTPUT);
  digitalWrite(buzzerPin, LOW);

  // Send startup message
  bot.sendMessage(CHAT_ID, "System has Started!", "");
}

// Control both gates via Blynk
BLYNK_WRITE(V1) {
  int gateControl = param.asInt();
  if (gateControl == 0) {
    gateServo1.write(0);
    gateServo2.write(0);
    bot.sendMessage(CHAT_ID, "Both Gates are CLOSED", "");
  } else if (gateControl == 1) {
    gateServo1.write(45);
    gateServo2.write(45);
    bot.sendMessage(CHAT_ID, "Both Gates are PARTIALLY OPEN", "");
  } else if (gateControl == 2) {
    gateServo1.write(90);
    gateServo2.write(90);
    bot.sendMessage(CHAT_ID, "Both Gates are FULLY OPEN", "");
  }
}

// Read water level
BLYNK_READ(V0) {
  int waterLevel = analogRead(waterSensorPin);
  float waterLevelPercentage = (waterLevel / 4095.0) * 100; // ESP32 uses 12-bit ADC
  Blynk.virtualWrite(V0, waterLevelPercentage);
}

void loop() {
  Blynk.run();

  // Read water level sensor
  float waterLevelPercentage = (analogRead(waterSensorPin) / 4095.0) * 100;

  // Send status to Telegram every 20 sec
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    bot.sendMessage(CHAT_ID, "Water Level: " + String(waterLevelPercentage, 2) + "%", "");
  }

  delay(1000);
}
