/*
 * Line following robot class with five QTI sensors.
 * 
 * Note: this uses direct port manipulation on the Atmega microcontroller.
 * This allows for efficient, simultaneous readout of multiple digital pins.
 * For details, see: http://playground.arduino.cc/Learning/PortManipulation
 */

#include "robot.h"

Robot::Robot(int tau_p, int tau_i, int tau_d, int servo_left_pin, int servo_right_pin) {
  this->tau_p = tau_p;
  this->tau_i = tau_i;
  this->tau_d = tau_d;
  
  servo_left.attach(servo_left_pin);
  servo_right.attach(servo_right_pin);

  sum_error = 0;
}

Robot::Robot(int tau_p, int tau_i, int tau_d) : Robot(tau_p, tau_i, tau_d, 11, 12)
{}

void Robot::init() {
  // measure initial error
  pins = sense();
  error = CTE(pins);
}

void Robot::go() {
  while(true) {
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

  // cross track error
  error = CTE(pins);

  // derivative and integral error
  int diff_error = error - previous_error;
  sum_error += error;

  // PID control term
  int PID_control = (tau_p * error) + (tau_i * sum_error) + (tau_d * diff_error);
  
  servo_left.writeMicroseconds(1500 + 100 - PID_control);
  servo_right.writeMicroseconds(1500 - 100 - PID_control);
  
  delay(50);
}

int Robot::CTE(byte pins) {
  // Cross Track Error
    switch(pins)
  {
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
    case B00000:
      // TODO: put search function here to find line
      error = 10;
      break;
  }
  return error;
}