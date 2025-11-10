// ------------------------------------------------------
// Line Follower Robot using Arduino + L298N + 3 IR Sensors
// Author: Shushrutha N Gowda
// Description: A simple robot that follows a black line using
// three IR sensors and controls movement via L298N motor driver.
// ------------------------------------------------------

#define LEFT_SENSOR   A0
#define CENTER_SENSOR A1
#define RIGHT_SENSOR  A2

// Motor driver pins
#define ENA 5
#define IN1 8
#define IN2 9
#define ENB 6
#define IN3 10
#define IN4 7

// Threshold for sensor detection
#define THRESHOLD 500  // Adjust based on calibration (0–1023)

void setup() {
  pinMode(LEFT_SENSOR, INPUT);
  pinMode(CENTER_SENSOR, INPUT);
  pinMode(RIGHT_SENSOR, INPUT);

  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  Serial.begin(9600);
  Serial.println("Line Follower Bot Initialized");
}

void loop() {
  int leftValue = analogRead(LEFT_SENSOR);
  int centerValue = analogRead(CENTER_SENSOR);
  int rightValue = analogRead(RIGHT_SENSOR);

  Serial.print("L: "); Serial.print(leftValue);
  Serial.print("  C: "); Serial.print(centerValue);
  Serial.print("  R: "); Serial.println(rightValue);

  bool leftDetect = leftValue < THRESHOLD;
  bool centerDetect = centerValue < THRESHOLD;
  bool rightDetect = rightValue < THRESHOLD;

  // Basic logic for line following:
  if (centerDetect && !leftDetect && !rightDetect) {
    moveForward();         // Line is centered
  } 
  else if (leftDetect && !centerDetect) {
    turnLeft();            // Line is on the left
  } 
  else if (rightDetect && !centerDetect) {
    turnRight();           // Line is on the right
  } 
  else if (!leftDetect && !centerDetect && !rightDetect) {
    stopMotors();          // Line lost
  } 
  else {
    moveForward();         // Default
  }

  delay(50);
}

// ------------------- Movement Functions -------------------

void moveForward() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(ENA, 200);
  analogWrite(ENB, 200);
  Serial.println("Forward");
}

void turnLeft() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(ENA, 150);
  analogWrite(ENB, 150);
  Serial.println("Turn Left");
}

void turnRight() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  analogWrite(ENA, 150);
  analogWrite(ENB, 150);
  Serial.println("Turn Right");
}

void stopMotors() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  analogWrite(ENA, 0);
  analogWrite(ENB, 0);
  Serial.println("Stop");
}
