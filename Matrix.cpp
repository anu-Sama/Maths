#include <iostream>
#include <iomanip>
#include "Matrix.h"
#include "Functions.h"

Matrix::Matrix() {
	allocSpace();
};

Matrix::Matrix(int rows, int cols) {
	_rows = rows, _cols = cols;
	allocSpace();

}

Matrix::Matrix(float **a,int rows, int cols) {
	_rows = rows, _cols = cols;
	allocSpace();
	for (int i = 0; i < _rows; i++) {
		for (int j = 0; j < _cols; j++) {
			mat[i][j] = a[i][j];
		}
	}

}

Matrix::Matrix(const Matrix& a) {
	_rows = a._rows, _cols = a._cols;
	allocSpace();

	for (int i = 0; i < _rows; i++) {
		for (int j = 0; j < _cols; j++) {
			mat[i][j] = a.mat[i][j];
		}
	}
}

Matrix::~Matrix() {

	for (int i = 0; i < _rows; i++) {
		delete[] mat[i];
	}

	delete[] mat;

}

Matrix& Matrix::operator=(const Matrix& m) {

	if (this == &m)
		return *this;

	if (_rows != m._rows || _cols != m._cols) {

		for (int i = 0; i < _rows; i++) {
			delete[] mat[i];
		}

		delete[] mat;

		_rows = m._rows;
		_cols = m._cols;

		allocSpace();
	}

	for (int i = 0; i < m._rows; i++) {
		for (int j = 0; j < m._cols; j++) {
			mat[i][j] = m.mat[i][j];
		}
	}

	return (*this);
}

Matrix Matrix::operator+=(Matrix& m) {
	for (int i = 0; i < _rows; i++) {
		for (int j = 0; j < _cols; j++) {
			mat[i][j] += m[i][j];
		}
	}

	return (*this);
}

Matrix Matrix::operator-=(Matrix& m) {
	for (int i = 0; i < m._rows; i++) {
		for (int j = 0; j < _cols; j++) {
			mat[i][j] -= m[i][j];
		}
	}

	return (*this);
}

Matrix Matrix::operator*=(const float f) {
	for (int i = 0; i < _rows; i++) {
		for (int j = 0; j < _cols; j++) {
			mat[i][j] *= f;
		}
	}

	return (*this);
}

Matrix Matrix::operator/=(const float f) {
	for (int i = 0; i < _rows; i++) {
		for (int j = 0; j < _cols; j++) {
			mat[i][j] *= 1/f;
		}
	}

	return (*this);
}

Matrix Matrix::operator*=(const Matrix& m) {
	Matrix n(m._rows, m._cols);
	for (int i = 0; i < n._rows; i++) {
		for (int j = 0; j < n._cols; j++) {
			for (int k = 0; k < _cols; k++)
				n.mat[i][j] += (*this).mat[j][k] * m.mat[k][j];
		}
	}
	return (*this = n);
}

Matrix Matrix::operator^(int k) {
	Matrix n(*this);
	for (int i = 0; i < k; i++) {
		n *= (*this);
	}

	return n;
}

float* Matrix::operator[](int k) {

	return mat[k];

}

void Matrix::Identity(int size) {
	Matrix m(size, size);
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			if (i == j) {
				m.mat[i][j] = 1;
			}
			else m.mat[i][j] = 0;
		}
	}

	(*this) = m;
}

void Matrix::Null(int rows, int cols ){
	Matrix m(rows, cols);
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			m.mat[i][j] = 0;
		}
	}

	(*this) = m;
}

Matrix Matrix::Transpose() {
	int rows = (*this)._rows, cols = (*this)._cols;
	Matrix m(rows, cols);

	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			m[i][j] = (*this).mat[j][i];
		}
	}

	return m;
}

float Matrix::Dot(Matrix& m, Matrix& n) {
	float sum = 0;
	for (int i = 0; i < m._rows; i++) {
		sum += (m.mat[i][0] + n.mat[i][0]);
	}
	return sum;
}


float Matrix::Determinant(int size) {
	float det = 0;
	if (size == 2) {
		det = (mat[0][0] * mat[1][1]) - (mat[0][1] * mat[1][0]);
		return det;
	}

	Matrix submat(size-1, size-1);

	for (int x = 0; x < size; x++) {
		int subi = 0;
		for (int i = 1; i < size; i++) {
			int subj = 0;
			for (int j = 0; j < size; j++) {
				if (j == x)
					continue;
				submat[subi][subj] = mat[i][j];
				subj++;
			}
			subi++;
		}
		det += power(-1, x) * mat[0][x] * submat.Determinant(size - 1);
	}

	return det;
}

Matrix Matrix::Adjoint() {
	int size = (*this)._rows;

	Matrix adj(size, size);

	if (size == 1)
	{
		adj[0][0] = 1;
		return adj;
	}

	int sign = 1;
	Matrix temp(size, size);

	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			
			temp = (*this).Cofactor(i, j);
			
			sign = ((i + j) % 2 == 0) ? 1 : -1;

			
			adj[j][i] = (sign) * (temp.Determinant(size - 1));
		}
	}

	return adj;
}

Matrix Matrix::Cofactor(int p, int q) {
	int size = (*this)._rows;

	Matrix a(size, size), temp(size, size);
	a = (*this);

	int i = 0, j = 0;

	for (int rows = 0; rows < size; rows++) {
		for (int cols = 0; cols < size; cols++) {
			if (rows != p && cols != q) {
				temp[i][j++] = a[rows][cols];

				if (j == size - 1) {
					j = 0;
					i++;
				}
			}
		}
	}

	return temp;
}

Matrix Matrix::Inverse() {
	
	int size = (*this)._rows;
	int determinant = (*this).Determinant(size);
	Matrix adj(size, size);
	adj = (*this).Adjoint();

	Matrix Inverse(size, size);

	Inverse = adj;

	if (adj.Determinant(size) != 0)
		Inverse = adj / determinant;
	else std::cerr << "Inverse does not exist, It is a singular matrix\n";

	return Inverse;
}


void Matrix::allocSpace() {
	
	mat = new float*[_rows];
	for (int i = 0; i < _cols; i++)
		mat[i] = new float[_cols];

}

int Matrix::rows() {
	return _rows;
}

int Matrix::cols() {
	return _cols;
}

// Input Output Function

std::ostream& operator<<(std::ostream& o, Matrix& m) {
	for (int i = 0; i < m.rows(); i++) {
		o << m[i][0];
		for (int j = 1; j < m.cols(); j++) {
			o <<std::setw(6) << " " << m[i][j];
		}
		o << "\n";
	}

	return o;
}

std::istream& operator>>(std::istream& is, Matrix& m) {
	for (int i = 0; i < m.rows(); i++) {
		for (int j = 0; j < m.cols(); j++) {
			is >> m[i][j];
		}
	}

	return is;
}


// Utility Functions

Matrix operator+(Matrix& a, Matrix &b) {
	
	Matrix temp(a);

	return (temp += b);
}

Matrix operator-(Matrix& a, Matrix& b) {

	Matrix temp(a);

	return (temp -= b);
}

Matrix operator*(Matrix& a, Matrix& b) {
	Matrix temp(a);

	return (temp *= b);
}

Matrix operator*(Matrix& a, float f) {
	Matrix temp(a);

	return (temp *= f);
}

Matrix operator*(float f, Matrix& a) {
	Matrix temp(a);

	return (temp *= f);
}

Matrix operator/(Matrix& a, float f) {
	Matrix temp(a);

	return (temp /= f);
}
