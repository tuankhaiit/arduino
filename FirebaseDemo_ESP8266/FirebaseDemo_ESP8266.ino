#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>
#include <DHT.h>

//Set Firebase
#define FIREBASE_HOST "pivotal-layout-160702.firebaseio.com"
#define FIREBASE_AUTH "Bm9FbNXw9jcx0HP1ueC2SeaP9s5kqA2TAXnTHvc8"
#define WIFI_SSID "Syslytic Working"
#define WIFI_PASSWORD "welovesyslytic"
//#define WIFI_SSID "102"
//#define WIFI_PASSWORD "123456789"

//Set Sensor
#define DHTPIN 13              // what pin we're connected to
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE, 15);

void setup() {
  Serial.begin(115200);

  dht.begin();

  // connect to wifi.
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("connecting");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.print("connected: ");
  Serial.println(WiFi.localIP());

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
}

int n = 0;

void loop() {
  float h = dht.readHumidity();
  float t = dht.readTemperature();

  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    delay(100);
  } else {
    // set value
    Firebase.setFloat("/sensor/temperature", t);
    if (Firebase.failed()) {
      Serial.print("Set temp failed:");
      Serial.println(Firebase.error());
    }
    Firebase.setFloat("/sensor/humidity", h);
    if (Firebase.failed()) {
      Serial.print("Set hum failed:");
      Serial.println(Firebase.error());
    }
    Firebase.setFloat("/sensor/log", n++);
    // get value
    Serial.print("n = ");
    Serial.println(t);
    Serial.print("temp: ");
    Serial.println(t);
    Serial.print("hum: ");
    Serial.println(h);
    Serial.println();
    delay(4000);
  }
}
