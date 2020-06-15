#include <Servo.h>

// declare servo signals
Servo servoLeft;
Servo servoRight;

void setup() {
  // attach to digital pins
  servoLeft.attach(11);
  servoRight.attach(12);

  // values needed for straight path
  // servoLeft.writeMicroseconds(1680);
  // servoRight.writeMicroseconds(1300);

  // values needed for standing still
//  servoLeft.writeMicroseconds(1490);
//  servoRight.writeMicroseconds(1490);

  // values needed for driving backwards
  servoLeft.writeMicroseconds(1490);
  servoRight.writeMicroseconds(1490);
  delay(10000);

  servoLeft.detach();
  servoRight.detach();
}

void loop() {}
