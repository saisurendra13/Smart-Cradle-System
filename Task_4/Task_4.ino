#include <ESP8266WiFi.h>

const char* ssid = "YourWiFiSSID";
const char* password = "YourWiFiPassword";
const char* server = "your-server.com";

WiFiClient client;

void setup() {
  Serial.begin(115200);
  delay(10);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }
}

void loop() {
  if (WiFi.status() == WL_CONNECTED) {
    float humidity = readHumidity();
    float temperature = readTemperature();
    bool isCrying = detectCry();

    sendSensorDataToServer(humidity, temperature, isCrying);
  }
  delay(10000);
}

float readHumidity() {
  // Placeholder code to read humidity from sensor
  float humidityValue = 50.0; // Placeholder value
  return humidityValue;
}

float readTemperature() {
  // Placeholder code to read temperature from sensor
  float temperatureValue = 25.0; // Placeholder value
  return temperatureValue;
}

bool detectCry() {
  // Placeholder code to detect cry using microphone sensor
  bool isCrying = false; // Placeholder value
  return isCrying;
}

void sendSensorDataToServer(float humidity, float temperature, bool isCrying) {
  if (!client.connect(server, 80)) {
    return;
  }

  String url = "/update?humidity=" + String(humidity) + "&temperature=" + String(temperature) + "&cry=" + String(isCrying);

  client.print(String("GET ") + url + " HTTP/1.1\r\n" +
               "Host: " + server + "\r\n" +
               "Connection: close\r\n\r\n");

  delay(500);

  while (client.available()) {
    client.readStringUntil('\r');
  }

  client.stop();
}

