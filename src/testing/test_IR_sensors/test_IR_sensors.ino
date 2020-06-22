/*
 * Test the left and right infrared sensors.
 * Display 1 if the left IR detector does not detect an object,
 * or 0 if it does.
 */

void setup()
{
  // Left IR LED & Receiver
  pinMode(13, INPUT);  pinMode(12, OUTPUT);
  // Right IR LED & Receiver
  pinMode(11, INPUT);  pinMode(10, OUTPUT);

  Serial.begin(9600);
}  
 
void loop()
{
  // Check for object
  int irLeft = irDetect(12, 13, 38000);
  int irRight = irDetect(10, 11, 38000);

  // Display 1/0 no detect/detect
  Serial.print(irLeft);
  Serial.print(" ");
  Serial.print(irRight);
  Serial.println();

  delay(1000);
}

int irDetect(int irLedPin, int irReceiverPin, long frequency)
{
  /*
   * IR Object Detection
   */
   
  // IRLED 38 kHz for at least 1 ms
  tone(irLedPin, frequency, 8);
  delay(1);
  int ir = digitalRead(irReceiverPin);
  delay(1);
  // Return 1 no detect, 0 detect
  return ir;
}  
