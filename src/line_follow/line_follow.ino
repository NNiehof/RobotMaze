/*
 * Line following with five QTI sensors.
 * 
 * Note: this uses direct port manipulation on the Atmega microcontroller.
 * This allows for efficient, simultaneous readout of multiple digital pins.
 * For details, see: http://playground.arduino.cc/Learning/PortManipulation
 */

#include <Servo.h>

Servo servoL;
Servo servoR;

void setup() {
  servoL.attach(11);
  servoR.attach(12);
}

void loop() {
  // Direction register for port D:
  // direction for digital pins 3-7 is set as OUTPUT (infrared LED)
  DDRD |= B11111000;
  // Set level of digital pins 3-7 to HIGH (LEDs on)
  PORTD |= B11111000;
  // short delay to allow capacitor charge in QTI module
  delayMicroseconds(230);

  // Set direction of pins 3-7 as INPUT (measurement)
  DDRD &= B00000111;
  // Set level of pins 3-7 to LOW (LEDs off)
  PORTD &= B00000111;
  delayMicroseconds(230);

  // get values of digital pins 0-7
  int pins = PIND;
  // drop bits 0-2, keeping only signal from pins 3-7
  pins >>= 3;

  // Determine how to steer based on state of the five QTI sensors
  int vL, vR;
  switch(pins)
  {
    case B10000:                        
      vL = -100;
      vR = 100;
      break;
    case B11000:                        
      vL = 0;
      vR = 100;
      break;
    case B01000:                        
      vL = 50;
      vR = 100;
      break;
    case B01100:                        
      vL = 120;
      vR = 100;
      break;
    case B00100:                        
      vL = 100;
      vR = 100;
      break;
    case B00110:                        
      vL = 100;
      vR = 50;
      break;
    case B00010:                        
      vL = 100;
      vR = 0;
      break;
    case B00011:                        
      vL = 100;
      vR = -100;
      break;
    case B00001:                        
      vL = 100;
      vR = -100;
      break;
    case B00000:
      // TODO: put search function here to find line
      vL = 100;
      vR = -100;
      break;
  }
  
  servoL.writeMicroseconds(1500 + vL);
  servoR.writeMicroseconds(1500 - vR);
  
  delay(50);
}
