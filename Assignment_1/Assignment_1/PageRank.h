#pragma once
#include<iostream>
#include<stdexcept>
#include<math.h>
#include <iomanip>


using namespace std;
class Matrix {
private:
	//size of the matrix
	int size;

	//create dynamic memory matrix array 
	int* matrix;

public:
	//default constructor
	Matrix();

	//constructor that accepts integer which is the size of the martix
	Matrix(int);

	//constructor accepts an array of integers
	Matrix(int[], int);

	//set specific value for a specific location in matrix
	void set_value(int, int, int);

	//get value from a specific location in matrix.
	int get_value(int, int) const;

	//clear the matrix and set every element in matrix to zero
	void clear();

	//return a same matrix.
	Matrix identity();

	//destructor
	~Matrix();

	//create an overloaded insertion operator so we can print matrix
	friend ostream& operator<<(std::ostream& os, const Matrix& obj);

	//overload comparison operator ==
	bool operator==(const Matrix&);

	//overload comparison operator !=
	bool operator!=(const Matrix&);

	//overload comparison operator <
	bool operator<(const Matrix&);

	//overload comparison operator >
	bool operator>(const Matrix&);

	//overload comparison operator <=
	bool operator<=(const Matrix&);

	//overload comparison operator >=
	bool operator>=(const Matrix&);

	//overload unary prefix operator ++
	Matrix& operator++();

	//overload unary postfix operator ++
	Matrix operator++(int);

	//overload unary prefix operator --
	Matrix& operator--();

	//overload unary postfix operator --
	Matrix operator--(int);

	//over load binary operators +=
	Matrix& operator+=(const Matrix&);

	//over load binary operators -=
	Matrix& operator-=(const Matrix&);

	//over load binary operators +
	Matrix operator+(const Matrix&);

	//over load binary operators -
	Matrix operator-(const Matrix&);

	//overload operator =
	Matrix& operator=(Matrix);

	//copy & swap
	Matrix(const Matrix&);

	//copy & swap
	friend void swap(Matrix&, Matrix&);


};
