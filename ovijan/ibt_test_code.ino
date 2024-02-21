// Motor 1
int RPWM1 = 5;
int LPWM1 = 6;
int R_EN1 = 9;
int L_EN1 = 10;

// Motor 2
int RPWM2 = 7;
int LPWM2 = 8;
int R_EN2 = 11;
int L_EN2 = 12;

void setup() {
  // Set up pins as outputs
  for (int i = 5; i < 13; i++) {
    pinMode(i, OUTPUT);
  }
  // Set all outputs LOW initially
  for (int i = 5; i < 13; i++) {
    digitalWrite(i, LOW);
  }
  delay(1000);
  Serial.begin(9600); // Initialize serial communication
}

void loop() {
  Serial.println("EN High");
  digitalWrite(R_EN1, HIGH); // Enable motor driver channels
  digitalWrite(L_EN1, HIGH);
  digitalWrite(R_EN2, HIGH);
  digitalWrite(L_EN2, HIGH);
  delay(1000);

  // Increase speed gradually for motor 1
  for (int i = 0; i <= 100; i++) {
    int mappedSpeed = map(i, 0, 100, 0, 255);
    analogWrite(RPWM1, mappedSpeed);
    if(mappedSpeed >= 100) break; // Ensure it doesn't exceed 100
    delay(100);
  }
  delay(500);

  // Decrease speed gradually for motor 1
  for (int i = 100; i >= 0; i--) {
    int mappedSpeed = map(i, 0, 100, 0, 255);
    analogWrite(RPWM1, mappedSpeed);
    delay(100);
  }
  delay(500);

  // Increase speed gradually for motor 2
  for (int i = 0; i <= 100; i++) {
    int mappedSpeed = map(i, 0, 100, 0, 255);
    analogWrite(RPWM2, mappedSpeed);
    if(mappedSpeed >= 100) break; // Ensure it doesn't exceed 100
    delay(100);
  }
  delay(500);

  // Decrease speed gradually for motor 2
  for (int i = 100; i >= 0; i--) {
    int mappedSpeed = map(i, 0, 100, 0, 255);
    analogWrite(RPWM2, mappedSpeed);
    delay(100);
  }
  delay(500);

  Serial.println("EN LOW");
  digitalWrite(R_EN1, LOW); // Disable motor driver channels for motor 1
  digitalWrite(L_EN1, LOW);
  digitalWrite(R_EN2, LOW); // Disable motor driver channels for motor 2
  digitalWrite(L_EN2, LOW);
  delay(1000);
}
