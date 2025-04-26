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

  // Mapping PWM input ke range -255 s/d 255
  int throttle = map(ch3_value, PULSE_MIN, PULSE_MAX, -PWM_MAX, PWM_MAX);
  int steering = map(ch4_value, PULSE_MIN, PULSE_MAX, -PWM_MAX, PWM_MAX);

  // Mixing throttle dan steering
  int motorA_speed = throttle + steering;
  int motorB_speed = throttle - steering;

  // Batasi nilai agar tidak melebihi PWM
  motorA_speed = constrain(motorA_speed, -PWM_MAX, PWM_MAX);
  motorB_speed = constrain(motorB_speed, -PWM_MAX, PWM_MAX);

  // Gerakkan motor
  driveMotor(MOTOR_A_IN1, MOTOR_A_IN2, PWM_A, motorA_speed);
  driveMotor(MOTOR_B_IN1, MOTOR_B_IN2, PWM_B, motorB_speed);

  // Debug
  Serial.print("Throttle: "); Serial.print(throttle);
  Serial.print(" | Steering: "); Serial.print(steering);
  Serial.print(" | MotorA: "); Serial.print(motorA_speed);
  Serial.print(" | MotorB: "); Serial.println(motorB_speed);

  delay(20); // loop delay
}

void driveMotor(int pin1, int pin2, int pwmPin, int speed) {
  int dir = (speed > 0) - (speed < 0); // 1: maju, -1: mundur, 0: diam
  int pwm = abs(speed);

  if (dir > 0) {
    digitalWrite(pin1, HIGH);
    digitalWrite(pin2, LOW);
  } else if (dir < 0) {
    digitalWrite(pin1, LOW);
    digitalWrite(pin2, HIGH);
  } else {
    digitalWrite(pin1, LOW);
    digitalWrite(pin2, LOW);
  }

  analogWrite(pwmPin, pwm);
}

void stopMotors() {
  digitalWrite(MOTOR_A_IN1, LOW);
  digitalWrite(MOTOR_A_IN2, LOW);
  analogWrite(PWM_A, 0);

  digitalWrite(MOTOR_B_IN1, LOW);
  digitalWrite(MOTOR_B_IN2, LOW);
  analogWrite(PWM_B, 0);
}
