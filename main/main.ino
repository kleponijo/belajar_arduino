#include <WiFi.h>

// Tipe data di arduino

int ledPin; // bilangan bulat 2 byte -32.768 sampai 32.768
char text = "Hello World!"; // char bisa digunakan untuk string
bool nilai = 0, 1, false, true; // itu adalah binnary atau binner
long nilai1 = -2.146.483.648; // long bilangan bulat 4 byte -2.146.483.648 sampai -2.146.483.647 
float nilai2 = -3,4028235; // float bilangan real -3,4028235 x 10^38 sampai 3,-3,4028235 x 10^38
double nilai3 = 1.123.123; // double bilangan real yang buanyaaakkk
unsigned int nilai4 = 65.535; // bilangan bulat 2 byte 0 sampai 65.535

const char SSID = "DIDIET CH";
const char PASSWORD = "didietch";

void setup() {
  Serial.begin(115200);
  println(Text);
  println("Connecting to Wifi");
  WiFi.begin(SSID, PASSWORD);
   while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nConnected, IP address: ");
  Serial.println(WiFi.localIP());

}

void loop() {


}