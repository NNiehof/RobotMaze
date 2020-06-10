/*
* matrix.h
*/

#ifndef MATRIX_H
#define MATRIX_H

class Matrix {
protected:
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
};
#endif