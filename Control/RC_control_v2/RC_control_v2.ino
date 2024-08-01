// Define dead zone threshold
const int DEAD_ZONE_THRESHOLD = 20; // Adjust as needed

// Motor pins
int RPWM1 = 5;
int LPWM1 = 6;
int R_EN1 = 9;
int L_EN1 = 10;

int RPWM2 = 7;
int LPWM2 = 8;
int R_EN2 = 11;
int L_EN2 = 12;

// Receiver pins
int receiverChannel1 = A0; // Connect the receiver channel 1 to analog pin A0
int receiverChannel2 = A1; // Connect the receiver channel 2 to analog pin A1

void setup() {
  // Set motor pins as outputs
  pinMode(RPWM1, OUTPUT);
  pinMode(LPWM1, OUTPUT);
  pinMode(R_EN1, OUTPUT);
  pinMode(L_EN1, OUTPUT);
  pinMode(RPWM2, OUTPUT);
  pinMode(LPWM2, OUTPUT);
  pinMode(R_EN2, OUTPUT);
  pinMode(L_EN2, OUTPUT);

  // Initialize EN pins to low (motors disabled)
  digitalWrite(R_EN1, LOW);
  digitalWrite(L_EN1, LOW);
  digitalWrite(R_EN2, LOW);
  digitalWrite(L_EN2, LOW);

  // Initialize Serial communication
  Serial.begin(9600);
}

void loop() {
  // Read remote control signals
  int throttle = analogRead(receiverChannel1); // Read throttle from channel 1
  int steering = analogRead(receiverChannel2); // Read steering from channel 2

  // Apply dead zone to throttle and steering signals
  if (abs(throttle - 512) < DEAD_ZONE_THRESHOLD) {
    throttle = 512; // Set throttle to neutral position
  }
  if (abs(steering - 512) < DEAD_ZONE_THRESHOLD) {
    steering = 512; // Set steering to neutral position
  }

  // Map the remote control signals to motor speeds
  int motorSpeed1 = map(throttle, 0, 1023, -255, 255); // Map throttle to motor speed (-255 to 255)
  int motorSpeed2 = map(steering, 0, 1023, -255, 255); // Map steering to motor speed (-255 to 255)

  // Apply motor speeds
  if (motorSpeed1 > 0) {
    digitalWrite(R_EN1, HIGH); // Enable motor 1
    analogWrite(RPWM1, motorSpeed1);
    analogWrite(LPWM1, 0);
  } else {
    digitalWrite(R_EN1, LOW); // Disable motor 1
    analogWrite(RPWM1, 0);
    analogWrite(LPWM1, -motorSpeed1);
  }

  if (motorSpeed2 > 0) {
    digitalWrite(R_EN2, HIGH); // Enable motor 2
    analogWrite(RPWM2, motorSpeed2);
    analogWrite(LPWM2, 0);
  } else {
    digitalWrite(R_EN2, LOW); // Disable motor 2
    analogWrite(RPWM2, 0);
    analogWrite(LPWM2, -motorSpeed2);
  }

  // Print motor speeds for debugging
  Serial.print("Motor 1 Speed: ");
  Serial.print(motorSpeed1);
  Serial.print(", Motor 2 Speed: ");
  Serial.println(motorSpeed2);

  // Add some delay if needed
  delay(100);
}
