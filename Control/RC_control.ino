const int CH_1_PIN = A0;
const int CH_2_PIN = A1;

const int Left_Lpwm = 5;
const int Left_Rpwm = 3;

const int Right_Lpwm = 6;
const int Right_Rpwm = 9;

const int range = 180;
const int deadzone = 20;

void setup() {
  pinMode(Left_Lpwm, OUTPUT);
  pinMode(Left_Rpwm, OUTPUT);
  pinMode(Right_Lpwm, OUTPUT);
  pinMode(Right_Rpwm, OUTPUT);

  Serial.begin(9600);
}

void loop() {
  int y = pulseToPWMy(pulseIn(CH_2_PIN, HIGH));
  int x = pulseToPWMx(pulseIn(CH_1_PIN, HIGH));

  int left = y + x;
  int right = y - x;

  drive(right, left);
}

void drive(int speed_a, int speed_b) {
  speed_a = constrain(speed_a, -range, range);
  speed_b = constrain(speed_b, -range, range);

  if (abs(speed_a) < deadzone) speed_a = 0;
  if (abs(speed_b) < deadzone) speed_b = 0;

  if (speed_a == 0) {
    analogWrite(Right_Lpwm, 0);
    analogWrite(Right_Rpwm, 0);
  } else if (speed_a > 0) {
    analogWrite(Right_Lpwm, speed_a);
    analogWrite(Right_Rpwm, 0);
  } else {
    analogWrite(Right_Lpwm, 0);
    analogWrite(Right_Rpwm, abs(speed_a));
  }

  if (speed_b == 0) {
    analogWrite(Left_Lpwm, 0);
    analogWrite(Left_Rpwm, 0);
  } else if (speed_b > 0) {
    analogWrite(Left_Lpwm, speed_b);
    analogWrite(Left_Rpwm, 0);
  } else {
    analogWrite(Left_Lpwm, 0);
    analogWrite(Left_Rpwm, abs(speed_b));
  }
}

int pulseToPWMy(int pulse) {
  if (pulse > 950) {
    pulse = map(pulse, 950, 1990, -range, range);
  } else {
    pulse = 0;
  }
  if (abs(pulse) <= deadzone) pulse = 0;
  return pulse;
}

int pulseToPWMx(int pulse) {
  if (pulse > 950) {
    pulse = map(pulse, 950, 1990, -range, range);
  } else {
    pulse = 0;
  }
  if (abs(pulse) <= deadzone) pulse = 0;
  return pulse;
}
