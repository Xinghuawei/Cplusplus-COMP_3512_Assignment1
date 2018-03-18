#pragma onece

#include<iostream>
#include<stdexcept>
#include<math.h>
#include <iomanip>
#include <vector>

using namespace std;
class Matrix {
private:
	//size of the matrix
	int size;

	//create dynamic memory matrix array 
	double* matrix;

	//double* matrixRank;
public:
	//default constructor
	Matrix();


	//constructor that accepts integer which is the size of the martix
	Matrix(int);

	//Matrix(int, int);
	//constructor accepts an array of integers
	Matrix(double[], int);

	//set specific value for a specific location in matrix
	void set_value(int, int, double);

	//get value from a specific location in matrix.
	double get_value(int, int) const;

	//clear the matrix and set every element in matrix to zero
	void clear();

	//destructor
	~Matrix();

	//create an overloaded insertion operator so we can print matrix
	friend ostream& operator<<(std::ostream& os, const Matrix& obj);


	//overload operator =
	Matrix& operator=(Matrix);

	//copy & swap
	Matrix(const Matrix&);

	//copy & swap
	friend void swap(Matrix&, Matrix&);

	//matrix multiplication with another matrix.
	Matrix& operator*=(const Matrix & rhs);

	//matrix multiplication with another double value.
	Matrix& operator*=(double);

	//overload operator +
	Matrix operator+(const Matrix&);
};







