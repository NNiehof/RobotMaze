#ifndef ROBOT_H
#define ROBOT_H

#include <Servo.h>

class Robot {
  protected:
    Servo servo_left;
    Servo servo_right;
    
  public:
    Robot(int tau_p, int tau_i, int tau_d, int servo_left_pin, int servo_right_pin);
    Robot(int tau_p, int tau_i, int tau_d);

    int tau_p, tau_i, tau_d;
    byte pins;
    int error;
    int previous_error;
    int sum_error;

    void init();
    void go();
    byte sense();
    void move(byte pins);
    int CTE(byte pins);
};
#endif