#include "DHT.h"
#include <MQ131.h>

// DHT11 sensor
#define DHTPIN 6     // Digital pin connected to the DHT sensor
#define DHTTYPE DHT11   // DHT 11
DHT dht(DHTPIN, DHTTYPE);

// MQ131 sensor
#define HEATER_PIN 2
#define SENSOR_PIN A0
#define LOAD_RESISTANCE 1000000 // 1 MOhm
#define SENSOR_TYPE LOW_CONCENTRATION

// MP135 sensor
#define MP135_PIN A4

// MQ2 sensor
#define MQ2_PIN A7

bool mq131_calibrated = false;

void setup() {
  Serial.begin(9600);

  // Initialize DHT11 sensor
  dht.begin();
  
  // Initialize MQ131 sensor
  MQ131.begin(HEATER_PIN, SENSOR_PIN, SENSOR_TYPE, LOAD_RESISTANCE);
}

void loop() {
  // Read temperature and humidity from DHT11 sensor
  float humidity = dht.readHumidity();
  float temperatureC = dht.readTemperature();
  float temperatureF = dht.readTemperature(true);
  
  if (isnan(humidity) || isnan(temperatureC) || isnan(temperatureF)) {
    Serial.println("Failed to read from DHT sensor!");
  } else {
    Serial.print("Humidity: ");
    Serial.print(humidity);
    Serial.print(" %, Temperature: ");
    Serial.print(temperatureC);
    Serial.print(" C / ");
    Serial.print(temperatureF);
    Serial.println(" F");
  }

  // Calibrate and read ozone concentration from MQ131 sensor
  if (!mq131_calibrated) {
    MQ131.sample();
    float o3_ppm = MQ131.getO3(PPM);
    if (!isnan(o3_ppm)) {
      mq131_calibrated = true;
    }
  }

  if (mq131_calibrated) {
    float o3_ppm = MQ131.getO3(PPM);
    float o3_ppb = MQ131.getO3(PPB);
    float o3_mg_m3 = MQ131.getO3(MG_M3);
    float o3_ug_m3 = MQ131.getO3(UG_M3);
    
    Serial.print("O3 (PPM): ");
    Serial.print((isnan(o3_ppm) ? 0 : o3_ppm)); // Handle NaN value
    Serial.print(", O3 (PPB): ");
    Serial.print((isnan(o3_ppb) ? 0 : o3_ppb)); // Handle NaN value
    Serial.print(", O3 (mg/m3): ");
    Serial.print(o3_mg_m3);
    Serial.print(", O3 (ug/m3): ");
    Serial.println(o3_ug_m3);
  }

  // Read MP135 sensor value
  int mp135_value = analogRead(MP135_PIN);
  String airQuality;
  if (mp135_value < 200) {
    airQuality = "Good";
  } else if (mp135_value < 400) {
    airQuality = "Moderate";
  } else if (mp135_value < 600) {
    airQuality = "Unhealthy for Sensitive Groups";
  } else if (mp135_value < 800) {
    airQuality = "Unhealthy";
  } else {
    airQuality = "Very Unhealthy";
  }
  
  Serial.print("Air Quality: ");
  Serial.print(airQuality);
  Serial.print(", MP135 Value: ");
  Serial.println(mp135_value);

  // Read MQ2 sensor value and identify gases
  int mq2_value = analogRead(MQ2_PIN);
  String detectedGas;
  if (mq2_value < 200) {
    detectedGas = "Clean Air";
  } else if (mq2_value < 400) {
    detectedGas = "LPG";
  } else if (mq2_value < 600) {
    detectedGas = "CO";
  } else {
    detectedGas = "Smoke";
  }
  
  Serial.print("MQ2 Value: ");
  Serial.print(mq2_value);
  Serial.print(", Detected Gas: ");
  Serial.println(detectedGas);

  // Wait 10 seconds before next measurement
  delay(10000);
}