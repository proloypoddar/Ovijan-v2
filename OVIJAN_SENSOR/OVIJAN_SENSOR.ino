#include <WiFi.h>
#include <WebServer.h>
#include "DHT.h"
const char* ssid = "SHARINGAN";
const char* password = "9830020622";
#define DHTPIN 2    
#define DHTTYPE DHT11   

DHT dht(DHTPIN, DHTTYPE);
WebServer server(80);

void handleRoot() {
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  String ipAddress = WiFi.localIP().toString(); // Get the ESP32's IP address
  
  String s = "<!DOCTYPE html><html><head><meta charset='UTF-8'><meta name='viewport' content='width=device-width, initial-scale=1.0'><title>OVIJAN v2 Sensors Value</title>";
  s += "<style>body {font-family: Arial, sans-serif; text-align: center;} #data {border: 2px solid #000; padding: 20px; margin: 0 auto; max-width: 300px;}</style>";
  s += "<script>function fetchData() {var xhr = new XMLHttpRequest(); xhr.onreadystatechange = function() {if (xhr.readyState == XMLHttpRequest.DONE) {if (xhr.status == 200) {var data = JSON.parse(xhr.responseText); document.getElementById('temperature').innerHTML = 'Temperature: ' + data.temperature + ' &deg;C'; document.getElementById('humidity').innerHTML = 'Humidity: ' + data.humidity + ' %'; document.getElementById('ipAddress').innerHTML = 'IP Address: ' + data.ipAddress;} else {console.log('Error fetching data.');}}}; xhr.open('GET', '/data', true); xhr.send();} setInterval(fetchData, 2000);</script>";
  s += "</head><body><h1>OVIJAN v2 Sensors Value</h1><div id='data'><p id='temperature'>Loading...</p><p id='humidity'>Loading...</p><p id='ipAddress'>Loading...</p></div></body></html>";
  server.send(200, "text/html", s);
}

void handleData() {
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  String ipAddress = WiFi.localIP().toString(); // Get the ESP32's IP address
  
  String data = "{\"temperature\":" + String(t) + ",\"humidity\":" + String(h) + ",\"ipAddress\":\"" + ipAddress + "\"}";
  server.send(200, "application/json", data);
}

void setup() {
  Serial.begin(9600);
  delay(10);
  
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  
  dht.begin();
  
  server.on("/", HTTP_GET, handleRoot);
  server.on("/data", HTTP_GET, handleData);
  server.begin();
  Serial.println("HTTP server started");
}

void loop() {
  server.handleClient();
}
