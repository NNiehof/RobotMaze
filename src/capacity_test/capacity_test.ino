#include <matrix.h>

int val = 0;

// matrix dimensions
int rows = 16;
int cols = 16;

// create matrix objects
Matrix flag = Matrix(rows, cols);
Matrix mark = Matrix(rows, cols);
Matrix count = Matrix(rows, cols);

void print_mat(Matrix m, int rows, int cols) {
  // send the values over the serial port one by one
  for (int r = 0; r < rows; r++) {
    for (int c = 0; c < cols; c++) {
      val = m.get(r, c);
      Serial.print(val);
      Serial.print("\t");
    }
    Serial.print("\n");
  }
  Serial.print("\n");
}

void setup() {
  Serial.begin(9600);

  // set all values to zero
  flag.zeros();
  mark.zeros();
  count.zeros();
  
  // change some values
  flag.set(0, 0, 1);
  mark.set(1, 2, 5);
  count.set(3, 6, 8);
}

void loop() {
  print_mat(flag, rows, cols);
  delay(1000);

  print_mat(mark, rows, cols);
  delay(1000);

  print_mat(count, rows, cols);
  delay(1000);
}
