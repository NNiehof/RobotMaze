/*
* matrix_test.cpp - Child class of Matrix that adds printing
* functionality. This allows for building and testing in
* pure C++ for easier debugging than on Arduino.
* The iostream functions are kept out of the Matrix class
* as this does not work on an Arduino.
*/

#include <iostream>
#include "../libraries/matrix/matrix.h"

class MatrixTest : public Matrix {
public:
	MatrixTest(int rows, int cols) : Matrix(rows, cols) {};
	MatrixTest(int dims) : Matrix(dims) {};
	MatrixTest() : Matrix() {};

	void print();
};

void MatrixTest::print() {
	// print the values as rows and columns
	for (int r = 0; r < rows; r++) {
		for (int c = 0; c < cols; c++) {
			std::cout << vals[ind(r, c)] << '\t';
		}
		std::cout << std::endl;
	}
}

int main() {
	MatrixTest m = MatrixTest(4, 5);
	m.zeros();
	m.set(1, 3, 7);
	m.incr(3, 4);
	m.decr(0, 1);
	m.print();
}