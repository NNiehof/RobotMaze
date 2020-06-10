/*
* matrix.cpp - Flat array class that can be manipulated
* by row and column indices like a matrix.
*/

#include "matrix.h"


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