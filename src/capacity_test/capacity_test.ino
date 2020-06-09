#include <Matrix.h>

int val = 0;

// matrix dimensions
int rows = 2;
int cols = 3;

// create matrix obj
Matrix m = Matrix(rows, cols);

void setup() {
  Serial.begin(9600);

  // set all values to zero
  m.zeros();
  // change some values
  m.incr(1, 2);
  m.set(0, 0, 6);
}

void loop() {
  // send the values over the serial port one by one
  for (int r = 0; r < rows; r++) {
    for (int c = 0; c < cols; c++) {
      val = m.get(r, c);
      Serial.print(val);
      Serial.print("\t");
      delay(500);
    }
    Serial.print("\n");
  }
  Serial.print("\n");
  delay(1000);
}
