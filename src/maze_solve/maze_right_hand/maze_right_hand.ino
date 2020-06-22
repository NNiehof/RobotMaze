/*
 * Line maze resolution with the right-hand-on-the-wall rule.
 * 
 * Note: this uses direct port manipulation on the Atmega microcontroller.
 * This allows for efficient, simultaneous readout of multiple digital pins.
 * For details, see: http://playground.arduino.cc/Learning/PortManipulation
 */

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
    int mode;
    int error;
    int previous_error;
    int sum_error;
    bool goal_reached;

    void init();
    void run();
    byte sense();
    void move(byte pins);
    void CTE(byte pins);
    void follow_line();
    void turn(int control_left, int control_right);
    void turn_right();
    void turn_left();
    void search_line();
};

Robot::Robot(int tau_p, int tau_i, int tau_d, int servo_left_pin, int servo_right_pin) {
  this->tau_p = tau_p;
  this->tau_i = tau_i;
  this->tau_d = tau_d;
  
  servo_left.attach(servo_left_pin);
  servo_right.attach(servo_right_pin);

  sum_error = 0;
  goal_reached = false;
}

Robot::Robot(int tau_p, int tau_i, int tau_d) : Robot(tau_p, tau_i, tau_d, 11, 12)
{}

void Robot::init() {
  // measure initial error
  pins = sense();
  CTE(pins);
}

void Robot::run() {
  while(goal_reached == false) {
    pins = sense();
    move(pins);
  }
}

byte Robot::sense() {
  /*
   * Measure the state of port D on the ATmega168 microcontroller.
   * Port D consists of digital pins 7 to 0 on the Arduino Uno board.
   * Returns the state for pins 7 to 3, consistent with a 5-sensor array.
   * 
   * The QTI (Charge Transfer Infrared) sensor works as follows:
   * 
   * - The pin is set to HIGH to charge up the capacitor in the QTI unit.
   * - A short delay allows for the capacitor to charge.
   * - The pin is then set to LOW.
   * - A short delay allows for the charge to decay slightly.
   * - The rate at which the capacitor loses charge is then measured:
   *  the circuit is infrared-sensitive. The amount of light from the IR LED 
   *  that is reflected determines the rate of charge transfer. This
   *  measurement thus senses the reflectivity of a surface.
   */
  
  // Direction register for port D:
  // direction for digital pins 7-3 is set as OUTPUT
  DDRD |= B11111000;
  // Set level of digital pins 7-3 to HIGH to charge the QTI capacitor
  PORTD |= B11111000;
  // short delay to allow capacitor charge
  delayMicroseconds(230);

  // Set direction of pins 7-3 as INPUT (measurement)
  DDRD &= B00000111;
  // Set level of pins 7-3 to LOW
  PORTD &= B00000111;
  delayMicroseconds(230);

  // get values of digital pins 7-0
  byte pins = PIND;
  // drop bits 2-0, keeping only signal from pins 7-3
  pins >>= 3;
  return pins;
}

void Robot::move(byte pins) {
  previous_error = error;
  
  // set mode to line following
  mode = 1;
  
  // determine Cross Track Error and movement mode
  CTE(pins);

  switch(mode)
  {
    case 0:
      search_line();
      break;
    case 1:
      follow_line();
      break;
    case 2:
      turn_right();
      break;
    case 3:
      turn_left();
      break;
  }
}

void Robot::follow_line() {
  // derivative and integral error
  int diff_error = error - previous_error;
  sum_error += error;

  // PID control term
  int PID_control = (tau_p * error) + (tau_i * sum_error) + (tau_d * diff_error);

  // servo control signals
  int control_left = 1500 + 100 + PID_control;
  int control_right = 1500 - 100 + PID_control;
  
  // check whether the control signals are within limits
  control_left = max(1300, control_left);
  control_left = min(1700, control_left);
  control_right = max(1300, control_right);
  control_right = min(1700, control_right);
  
  servo_left.writeMicroseconds(control_left);
  servo_right.writeMicroseconds(control_right);

  delay(20);
}

void Robot::turn(int control_left, int control_right) {
  // drive straight until the robot is over the line
  servo_left.writeMicroseconds(1680);
  servo_right.writeMicroseconds(1300);
  delay(250);

  // turn control signal
  servo_left.writeMicroseconds(control_left);
  servo_right.writeMicroseconds(control_right);

  // turn a bit until sensors are away from line
  while(pins != B00000) {
    pins = sense();
    delay(20);
  }
  // keep turning until a line is found again
  int count = 0;
  while(pins == B00000) {
    pins = sense();
    delay(20);

    // after turning a full circle, stop
    count++;
    if (count > 104) {
      servo_left.writeMicroseconds(1500);
      servo_right.writeMicroseconds(1500);
      goal_reached = true;
    }
  }

  // reset the cumulative error for a new linepiece
  sum_error = 0;
}

void Robot::turn_right() {
  turn(1680, 1700);
}

void Robot::turn_left() {
  turn(1300, 1300);
}

void Robot::search_line() {
  // TODO: better search
  // give the stop signal
  turn(1500, 1500);
  goal_reached = true;
}

void Robot::CTE(byte pins) {
  // Cross Track Error
    switch(pins)
  {
    case B00000:
      // TODO: put search function here to find line
      mode = 0;
      error = 0;
      break;
    case B11111:
    case B01111:
    case B00111:
      // right turn mode
      mode = 2;
      error = 0;
      break;
    case B11110:
    case B11100:
      // left turn mode
      mode = 3;
      error = 0;
      break;
    case B10000:                        
      error = -4;
      break;
    case B11000:                        
      error = -3;
      break;
    case B01000:                        
      error = -2;
      break;
    case B01100:                        
      error = -1;
      break;
    case B00100:                        
      error = 0;
      break;
    case B00110:                        
      error = 1;
      break;
    case B00010:                        
      error = 2;
      break;
    case B00011:                        
      error = 3;
      break;
    case B00001:                        
      error = 4;
      break;
  }
}

// weight parameters for the P, I, D control terms
int weight_p = 50;
int weight_i = 0;
int weight_d = 10;

void setup() {
//  Serial.begin(9600);
  
  // initialise robot with servo pins
  Robot robot = Robot(weight_p, weight_i, weight_d, 11, 12);
  
  // initial measurement
  robot.init();

  // run the sense - move feedback loop
  robot.run();
}

void loop() {}
