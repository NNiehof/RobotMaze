#include <iostream>

class Matrix {
private:
	int rows, cols;

	int ind(int row, int col);
public:
	Matrix(int rows, int cols);
	Matrix(int dims);
	Matrix();

	int* vals;

	void zeros();
	int get(int row, int col);
	void set(int row, int col, int val);
	void incr(int row, int col);
	void decr(int row, int col);
	void print();
};

Matrix::Matrix(int rows, int cols) {
	this->rows = rows;
	this->cols = cols;

	vals = new int[rows * cols];
}

Matrix::Matrix(int dims) : Matrix(dims, dims)
{}

Matrix::Matrix() : Matrix(1, 1)
{}

int Matrix::ind(int row, int col) {
	// 2D (row, column) indices to 1D index
	return (row * cols) + col;
}

void Matrix::zeros() {
	// array with all zeros
	for (int u = 0; u < (rows * cols); u++) {
		vals[u] = 0;
	}
}

int Matrix::get(int row, int col) {
	return vals[ind(row, col)];
}

void Matrix::set(int row, int col, int val) {
	vals[ind(row, col)] = val;
}

void Matrix::incr(int row, int col) {
	// increment
	vals[ind(row, col)] ++;
}

void Matrix::decr(int row, int col) {
	// decrement
	vals[ind(row, col)] --;
}

void Matrix::print() {
	// print the values as rows and columns
	for (int r = 0; r < rows; r++) {
		for (int c = 0; c < cols; c++) {
			std::cout << vals[ind(r, c)] << '\t';
		}
		std::cout << std::endl;
	}
}

int main() {
	Matrix m(4, 5);
	m.zeros();
	m.set(2, 3, 5);
	m.incr(3, 4);
	m.decr(0, 1);
	m.print();
}