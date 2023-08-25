#include <DHT.h>
#include <WiFiNINA.h>

char wifid[] = "iPhoneSE";
char wifpass[] = "Nishur19";
char server[] = "api.thingspeak.com";
String apiKey = "JSZ56L6B3DCNS5KZ";

#define DHTPIN 2
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);
WiFiClient client;

void setup() {
  Serial.begin(9600);
  WiFi.begin(wifid, wifpass);
  while (WiFi.status() != WL_CONNECTED) {
    delay(15000);
  }
  dht.begin();
}

void loop() {
  float temperature = dht.readTemperature();
  if (isnan(temperature){
    Serial.println("No Data is being detected");
    delay(2000);
    return;
  }
  String data = "api_key=" + apiKey + "&field1=" + String(temperature);
  
  if (client.connect(server, 80)) {
    client.print("POST /update HTTP/1.1\r\n");
    client.print("Host: " + String(server) + "\r\n");
    client.print("Content-Type: application/x-www-form-urlencoded\r\n");
    client.print("Content-Length: " + String(data.length()) + "\r\n");
    client.print("\r\n");
    client.print(data);
    Serial.println("Data is being sent");
  } else {
    Serial.println("Your Connection has been failed from the server ");
  }

  while (client.connected()) {
    if (client.available()) {
      char c = client.read();
      Serial.print(c);
    }
  }
  client.stop();
  delay(15000);
}

This code reads temperature and humidity from a DHT11 sensor and sends the data to ThingSpeak using an HTTP POST request. Make sure to replace placeholders with your actual WiFi credentials and ThingSpeak API key. The code is simplified while maintaining the core functionality.void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:

}
