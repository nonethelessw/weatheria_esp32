#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>

#define DHTTYPE    DHT11
#define DHTPIN     5

HTTPClient http;
DHT dht(DHTPIN, DHTTYPE);
int humid = 0;
int temp = 0;

void setup() {
  Serial.begin(9600);

  WiFi.begin("Luitel 2G", "binu@123");
  Serial.println("Connecting");
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println(WiFi.localIP());
  dht.begin();
}

void send_temprature_readings(){
  http.begin("http://192.168.101.12:8080/api/add");
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");
  char parameters[1024];
  sprintf(parameters, "humidity=%d&temprature=%d", humid, temp);
  int httpResponseCode = http.POST(parameters);
  Serial.println("HTTP Response code: " + String(httpResponseCode));
  Serial.println("Response body: " + http.getString());
  http.end();
}

void read_temp(){
  humid = dht.readHumidity();
  temp = dht.readTemperature();
  if (isnan(humid) || isnan(temp) ) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }
  Serial.println(temp);
  Serial.println(humid);
}

void loop() {
  Serial.println("hello from esp32");
  // read_temp();
  // send_temprature_readings();
  delay(1000);
}