

#include <MQ131.h>

#define tvocPin 3  // VOC sensor activation
int tvoc;


void setup() {
  Serial.begin(9600);

  // Init the sensor

  Serial.println("warming up");

  pinMode(tvocPin, OUTPUT);

  digitalWrite(tvocPin, HIGH);  // TVOC sensor
  delay(20 * 1000); // delay 20 seconds
  digitalWrite(tvocPin, LOW);
  // - Heater control on pin 2
  // - Sensor analog read on pin A0
  // - Model LOW_CONCENTRATION
  // - Load resistance RL of 1MOhms (1000000 Ohms)
  MQ131.begin(2, A0, LOW_CONCENTRATION, 1000000);

  Serial.println("Calibration in progress...");

  MQ131.calibrate();

  Serial.println("Calibration done!");
  Serial.print("R0 = ");
  Serial.print(MQ131.getR0());
  Serial.println(" Ohms");
  Serial.print("Time to heat = ");
  Serial.print(MQ131.getTimeToRead());
  Serial.println(" s");
}

void loop() {
  o3();
  tvoc1();
}

void o3() {
  Serial.println("Sampling...");
  MQ131.sample();
  Serial.print("o3.val=");
  Serial.print(MQ131.getO3(PPB));
    Serial.write(0xff);
    Serial.write(0xff);
    Serial.write(0xff);
}

void tvoc1(){
   // Read TVOC for 5 seconds
  digitalWrite(tvocPin, HIGH);
  delay(5000); // Blocking the programm - It would be best if the sensor heater is active all the time, we would get the most accurate values that way. The thing is that the sensers heats up quaite a lot and messes with the tempereture values. If better air circulation is provided to the case, that's the way to go.
  tvoc = analogRead(A1); // Please note that we are only reading raw data from this sensor, not ppm or ppb values. Just analog values from 0 to 1024. Higher values means there is a presence of VOC 
  digitalWrite(tvocPin, LOW);
    Serial.print("tvoc.val=");
    Serial.print(tvoc);
    Serial.write(0xff);
    Serial.write(0xff);
    Serial.write(0xff);
  }
