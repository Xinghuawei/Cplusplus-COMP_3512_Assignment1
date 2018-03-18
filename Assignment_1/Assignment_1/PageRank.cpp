#include "PageRank.h"

//default constructor with size 1 and element value zero
using namespace std;
using std::swap;

Matrix::Matrix() {
	size = 1;
	matrix = new double[size*size];
	matrix[0] = 0;
}



//constructor that accepts integer which n is the size of the martix
Matrix::Matrix(int n) : size{ n } {
	matrix = new double[size*size];
	for (int i = 0; i < size*size; i++) {
		matrix[i] = 0;
	}
}



//constructor accepts an array of integers
Matrix::Matrix(double arr[], int n) {
	int s = sqrt(n);
	if (s*s == n) {
		size = sqrt(n);
		matrix = new double[size*size];

		for (int i = 0; i < size*size; i++) {
			matrix[i] = arr[i];
		}
	}
}

//set specific value for a specific location in matrix
//r is row value, c is colum value, val is value.
void Matrix::set_value(int r, int c, double value) {
	matrix[(r - 1)*size + (c - 1)] = value;
}

//get value from a specific location in matrix.
//r is row value, c is colum value
double Matrix::get_value(int r, int c) const {
	return matrix[(r - 1)*size + (c - 1)];
}

//clear the matrix and set every element in matrix to zero
void Matrix::clear() {

	for (int i = 0; i < size*size; i++) {
		matrix[i] = 0;
	}

}

//destructor for dynamic allocated memory.
Matrix::~Matrix() {
	delete[] matrix;
}

//create an overloaded insertion operator so we can print matrix
ostream& operator<<(ostream& os, const Matrix& obj) {
	for (int i = 1; i <= (obj.size)*(obj.size); i++) {
		if (i % obj.size != 0) {
			cout << setw(5) << obj.matrix[i - 1];
		}
		else {

			cout << setw(5) << obj.matrix[i - 1] << endl;
		}

	}
	return os;
}

//overload operator =
Matrix& Matrix::operator=(Matrix src) {
	swap(*this, src);
	return *this;
}

//copy & swap
Matrix::Matrix(const Matrix& m) : size{ m.size } {
	matrix = new double[size*size];
	for (int i = 0; i < size*size; i++) {
		matrix[i] = m.matrix[i];
	}
}

//copy & swap two matrixes
void swap(Matrix& first, Matrix& second) {
	first.size = second.size;
	swap(first.matrix, second.matrix);
}


Matrix& Matrix:: operator*=(const Matrix & rhs)
{
	int total{ 0 };
	Matrix c(*this);
	if (size == rhs.size) {
		for (int k = 1; k <= size; k++) {
			for (int i = 1; i <= size; i++) {
				for (int j = 1; j <= size; j++) {
					total += (get_value(k, j)*rhs.get_value(j, i));
				}
				c.set_value(k, i, total);
				total = 0;
			}

		}
		*this = c;
	}
	return *this;
}

Matrix& Matrix::operator*=(int n) {
	Matrix tmp(*this);
	for (int i = 1; i <= size; i++) {
		for (int k = 1; k <= size; k++) {
			tmp.set_value(i, k, tmp.get_value(i, k)*0.85);
		}
	}
	*this = tmp;
	return *this;
}

Matrix Matrix::operator+(const Matrix& m) {
	if (m.size == size) {
		Matrix temp(size);
		for (int i = 0; i < size*size; i++) {
			temp.matrix[i] = m.matrix[i] + matrix[i];
		}
		return temp;
	}
}