#include <WiFi.h>
#include <HTTPClient.h>

const char* ssid = "klepon";
const char* password = "12345678";

// GANTI SESUAI PROJECTMU
const char* firebaseHost = "https://klimatologiot-default-rtdb.asia-southeast1.firebasedatabase.app/";
const char* firebasePath = "/anemometer/data.json";

const int pinHallEffect = 27;

volatile int pulseCount = 0;  
float K = 1.0;                 
float kecepatan = 0;

unsigned long lastTime = 0;
const unsigned long interval = 1000; // 1 detik

void IRAM_ATTR hitungPulsa() {
  pulseCount++;
}

void setup() {
  Serial.begin(115200);
  pinMode(pinHallEffect, INPUT_PULLUP);

  WiFi.begin(ssid, password);
  Serial.print("Menghubungkan ke WiFi");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nWiFi Terhubung!");
  Serial.println(WiFi.localIP());

  attachInterrupt(digitalPinToInterrupt(pinHallEffect), hitungPulsa, FALLING);

  Serial.println("Anemometer realtime + Firebase");
}

void loop() {

  if (millis() - lastTime >= interval) {

    int Rdetik = pulseCount;  
    pulseCount = 0;           

    kecepatan = 6.7824 * Rdetik * K;

    Serial.print("Kecepatan (km/h): ");
    Serial.println(kecepatan);

    // =========================
    // 🔥 KIRIM KE FIREBASE
    // =========================

    if (WiFi.status() == WL_CONNECTED) {

      HTTPClient http;

      String url = String(firebaseHost) + firebasePath;

      http.begin(url);
      http.addHeader("Content-Type", "application/json");

      // buat JSON
      String jsonData = "{";
      jsonData += "\"kecepatan\":" + String(kecepatan, 2) + ",";
      jsonData += "\"pulsa\":" + String(Rdetik);
      jsonData += "}";

      int httpResponseCode = http.POST(jsonData);

      Serial.print("HTTP Response code: ");
      Serial.println(httpResponseCode);

      http.end();
    }

    Serial.println("--------------------");

    lastTime = millis();
  }
}