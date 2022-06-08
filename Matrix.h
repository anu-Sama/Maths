#pragma once
#include <iostream>
class Matrix
{
public:
	Matrix();
	Matrix(int, int);
	Matrix(const Matrix&);
	Matrix(float**, int, int);
	~Matrix();
	Matrix& operator=(const Matrix&);

	Matrix operator+=(Matrix& m);
	Matrix operator-=(Matrix& m);
	Matrix operator*=(const Matrix& m);
	Matrix operator*=(const float f);
	Matrix operator/=(const float f);
	Matrix operator^(int);
	float* operator[](int k);

	// Input Output Operator
	friend std::ostream& operator<<(std::ostream&, Matrix& m);
	friend std::istream& operator>>(std::istream&, Matrix& m);

	float Dot(Matrix& m, Matrix& n);

	// Functions for matrices
	void Identity(int k);
	void Null(int rows, int cols);
	Matrix Transpose();
	Matrix Inverse();
	Matrix Adjoint();
	Matrix Cofactor(int p, int q);

	float Determinant(int);


	int rows();
	int cols();

private:
	int _rows=0, _cols=0;
	float** mat = nullptr;

	void allocSpace();

};

// Utility Function
Matrix operator+(Matrix& a, Matrix& b);
Matrix operator-(Matrix& a, Matrix& b);
Matrix operator*(Matrix& a, Matrix& b);
Matrix operator*(Matrix& a, float f);
Matrix operator*(float f, Matrix& m);
Matrix operator/(Matrix& m, float f);

