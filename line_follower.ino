#define LEFT_SENSOR A0
#define CENTER_SENSOR A1
#define RIGHT_SENSOR A2

#define ENA 5
#define IN1 8
#define IN2 9
#define ENB 6
#define IN3 10
#define IN4 7

#define THRESHOLD 500

void moveForward();
void turnLeft();
void turnRight();
void stopMotors();

class DriveCmd {
  public:
    virtual void apply() = 0;
    virtual ~DriveCmd() {}
};

class ForwardCmd : public DriveCmd { void apply() override { moveForward(); } };
class LeftCmd    : public DriveCmd { void apply() override { turnLeft(); }    };
class RightCmd   : public DriveCmd { void apply() override { turnRight(); }   };
class StopCmd    : public DriveCmd { void apply() override { stopMotors(); }  };

ForwardCmd FORWARD_CMD;
LeftCmd    LEFT_CMD;
RightCmd   RIGHT_CMD;
StopCmd    STOP_CMD;

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
  int leftValue   = analogRead(LEFT_SENSOR);
  int centerValue = analogRead(CENTER_SENSOR);
  int rightValue  = analogRead(RIGHT_SENSOR);

  Serial.print("L: "); Serial.print(leftValue);
  Serial.print(" C: "); Serial.print(centerValue);
  Serial.print(" R: "); Serial.println(rightValue);

  bool leftDetect   = leftValue   < THRESHOLD;
  bool centerDetect = centerValue < THRESHOLD;
  bool rightDetect  = rightValue  < THRESHOLD;

  DriveCmd* cmd = &FORWARD_CMD;
  if (centerDetect && !leftDetect && !rightDetect) {
    cmd = &FORWARD_CMD;
  } else if (leftDetect && !centerDetect) {
    cmd = &LEFT_CMD;
  } else if (rightDetect && !centerDetect) {
    cmd = &RIGHT_CMD;
  } else if (!leftDetect && !centerDetect && !rightDetect) {
    cmd = &STOP_CMD;
  } else {
    cmd = &FORWARD_CMD;
  }

  cmd->apply();
  delay(50);
}

void moveForward() {
  digitalWrite(IN1, HIGH); digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH); digitalWrite(IN4, LOW);
  analogWrite(ENA, 200); analogWrite(ENB, 200);
  Serial.println("Forward");
}

void turnLeft() {
  digitalWrite(IN1, LOW); digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH); digitalWrite(IN4, LOW);
  analogWrite(ENA, 150); analogWrite(ENB, 150);
  Serial.println("Turn Left");
}

void turnRight() {
  digitalWrite(IN1, HIGH); digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW); digitalWrite(IN4, HIGH);
  analogWrite(ENA, 150); analogWrite(ENB, 150);
  Serial.println("Turn Right");
}

void stopMotors() {
  digitalWrite(IN1, LOW); digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW); digitalWrite(IN4, LOW);
  analogWrite(ENA, 0); analogWrite(ENB, 0);
  Serial.println("Stop");
}
