#include <Servo.h>

// declare servo signals
Servo servoLeft;
Servo servoRight;

void setup() {
  // attach to digital pins
  servoLeft.attach(11);
  servoRight.attach(12);

  // values needed for straight path
   servoLeft.writeMicroseconds(1680);
   servoRight.writeMicroseconds(1300);

  // values needed for standing still
  servoLeft.writeMicroseconds(1500);
  servoRight.writeMicroseconds(1500);

  // values needed for driving backwards
  servoLeft.writeMicroseconds(1380);
  servoRight.writeMicroseconds(1700);

  // values needed for right 90 deg turn
  servoLeft.writeMicroseconds(1680);
  servoRight.writeMicroseconds(1700);
  delay(520);

  // values needed for left 90 deg turn
  servoLeft.writeMicroseconds(1300);
  servoRight.writeMicroseconds(1300);
  delay(520);

  servoLeft.detach();
  servoRight.detach();
}

void loop() {}
