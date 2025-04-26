// Motor driver pin definitions
#define MOTOR_A_IN1 14
#define MOTOR_A_IN2 27
#define PWM_A       12

#define MOTOR_B_IN1 26
#define MOTOR_B_IN2 25
#define PWM_B       33

// RC receiver input pins
#define CH3_PIN     36  // VP
#define CH4_PIN     39  // VN

// Motor control constants
const int PWM_MAX = 255;
const int PULSE_MIN = 1000;
const int PULSE_MAX = 2000;

void setup() {
  // Motor pins as output
  pinMode(MOTOR_A_IN1, OUTPUT);
  pinMode(MOTOR_A_IN2, OUTPUT);
  pinMode(PWM_A, OUTPUT);
  pinMode(MOTOR_B_IN1, OUTPUT);
  pinMode(MOTOR_B_IN2, OUTPUT);
  pinMode(PWM_B, OUTPUT);

  // RC pins as input
  pinMode(CH3_PIN, INPUT);
  pinMode(CH4_PIN, INPUT);

  Serial.begin(115200);
}

void loop() {
  // Read PWM values from RC receiver
  int ch3_value = pulseIn(CH3_PIN, HIGH, 25000); // throttle
  int ch4_value = pulseIn(CH4_PIN, HIGH, 25000); // steering

  // Jika tidak ada sinyal (timeout)
  if (ch3_value == 0 || ch4_value == 0) {
    stopMotors();
    return;
  }

  // --- THROTTLE HANDLING ---
  int throttle_input = map(ch3_value, PULSE_MIN, PULSE_MAX, -225, 283);
  throttle_input = constrain(throttle_input, -225, 283);
  int throttle_pwm = map(throttle_input, -225, 283, 0, 255);

  // --- STEERING HANDLING ---
  int steering = map(ch4_value, PULSE_MIN, PULSE_MAX, -PWM_MAX, PWM_MAX);

  // Mixing throttle dan steering
  int motorA_speed = throttle_pwm + steering;
  int motorB_speed = throttle_pwm - steering;

  // Batasi supaya tidak melebihi 0-255
  motorA_speed = constrain(motorA_speed, 0, PWM_MAX);
  motorB_speed = constrain(motorB_speed, 0, PWM_MAX);

  // Gerakkan motor
  driveMotor(MOTOR_A_IN1, MOTOR_A_IN2, PWM_A, motorA_speed);
  driveMotor(MOTOR_B_IN1, MOTOR_B_IN2, PWM_B, motorB_speed);

  // Debugging output
  Serial.print("Throttle PWM: "); Serial.print(throttle_pwm);
  Serial.print(" | Steering: "); Serial.print(steering);
  Serial.print(" | MotorA: "); Serial.print(motorA_speed);
  Serial.print(" | MotorB: "); Serial.println(motorB_speed);

  delay(20); // loop delay
}

void driveMotor(int pin1, int pin2, int pwmPin, int speed) {
  if (speed > 0) {
    digitalWrite(pin1, HIGH);
    digitalWrite(pin2, LOW);
    analogWrite(pwmPin, speed);
  } else {
    digitalWrite(pin1, LOW);
    digitalWrite(pin2, LOW);
    analogWrite(pwmPin, 0);
  }
}

void stopMotors() {
  digitalWrite(MOTOR_A_IN1, LOW);
  digitalWrite(MOTOR_A_IN2, LOW);
  analogWrite(PWM_A, 0);

  digitalWrite(MOTOR_B_IN1, LOW);
  digitalWrite(MOTOR_B_IN2, LOW);
  analogWrite(PWM_B, 0);
}
