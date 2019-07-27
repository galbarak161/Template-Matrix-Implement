/*********************************************
Student One: Gal Barak, 204233688
Student Two: Shir Avneri, 314980517
Assignment number: 2
*********************************************/

#pragma once
#include <iostream>

typedef enum { PLUS, MULTIPLICATION, SUBTRACION, PLUS_POST, PLUS_PRE, SUB_POST, SUB_PRE} operators; // ENUM for op utilities Functions

template <int rows = 1, int cols = 1, typename T = int>
class Matrix
{
public:	
	Matrix(T value = 0) //C'tor
	{ 
		createMatrix();
		fillMatrix(value);
	}
	Matrix(const Matrix& other) //Copy C'tor
	{
		createMatrix();
		fillMatrix(other);
	}

	~Matrix() // D'tor
	{
		if (this) {
			for (int i = 0; i < rows; ++i) { // First delete all the columns
				this->_mat[i] = NULL;
				delete[] this->_mat[i];
			}
			this->_mat = NULL;
			delete[] this->_mat; // delete the main row
		}
	}
	
	Matrix& operator=(const Matrix& other) //Assignment Operator
	{
		if (this != &other) {
			this->~Matrix(); // delete the old instance
			createMatrix();
			fillMatrix(other);
		}
		return *this;
	}
	
	inline Matrix operator+(const Matrix& other) //Plus Operator between matrices
	{
		return this->mathOperators(other, PLUS);
	}

	inline Matrix operator-(const Matrix& other) //Subtracion Operator between matrices	
	{
		return this->mathOperators(other, SUBTRACION);
	}

	inline Matrix operator*(const T number) //Multiplication Operator between matrix and number
	{
		return this->mathOperators(number, MULTIPLICATION);
	}

	inline Matrix operator-() //Subtracion Unary Operator
	{
		return ((*this) * -1);
	}

	inline Matrix& operator++() //Prefix Operator	
	{
		return this->prefixOperators(PLUS_PRE);
	}

	inline const Matrix operator++(int) //Postfix Operator	
	{
		return this->postfixOperators(PLUS_POST);
	}

	inline Matrix& operator--() //Prefix Operator	
	{
		return this->prefixOperators(SUB_PRE);
	}

	inline const Matrix operator--(int) //Postfix Operator	
	{
		return this->postfixOperators(SUB_POST);
	}

	inline T& operator()(const int i, const int j) const //Brackets Operator
	{
		return this->_mat[i][j];
	}

	T* getDiag(int& number) // Function for calculating the Diag of the matrix
	{
		T* diag = NULL;

		// update the number reference for using outside the function
		if (rows == cols)
			number = rows;
		else
			number = (rows > cols) ? cols : rows;

		diag = new T[number];
		for (int i = 0; i < number; i++) // take only the diagonals items 
			diag[i] = this->_mat[i][i];

		return diag;
	}

	const T trace() // Function for calculating the trace of the matrix
	{
		int number;
		T sum = 0;
		T* diag = this->getDiag(number); // get the diag and sum all the items
		for (int i = 0; i < number; i++)
		{
			sum += diag[i];
		}
		delete[] diag;
		return sum;
	}


private:

	T** _mat; // pointer to matrix - Two-dimensional array
	
	void createMatrix() // Allocate memory to the matrix
	{
		this->_mat = new T*[rows];
		for (int i = 0; i < rows; ++i)
			this->_mat[i] = new T[cols];
	}

	void fillMatrix(T value) // Set values in the matrix from T type
	{
		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < cols; j++)
				this->_mat[i][j] = value;
		}
	}

	void fillMatrix(const Matrix& other) // Set values in the matrix from other matrix (using copy C'tor)
	{
		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < cols; j++)
				this->_mat[i][j] = other(i, j);
		}
	}

	const Matrix postfixOperators(const operators op) //Generic functions for postFix
	{
		Matrix<rows, cols, T> old = *this;
		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < cols; j++) {
				switch (op)
				{
					case PLUS_POST: ++(this->_mat[i][j]); break;
					case SUB_POST:  --(this->_mat[i][j]); break;
				}
			}
		}
		return old;
	}

	Matrix& prefixOperators(const operators op) //Generic functions for preFix
	{
		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < cols; j++) {
				switch (op)
				{
					case PLUS_PRE: ++this->_mat[i][j]; break;
					case SUB_PRE:  --this->_mat[i][j]; break;
				}
			}
		}
		return *this;
	}

	Matrix mathOperators(const Matrix<rows, cols, T>& other, const operators op) //Generic functions for math operations between matrices
	{
		Matrix<rows, cols, T> temp(*this);
		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < cols; j++) {
				switch (op)
				{
					case SUBTRACION: temp(i, j) -= other(i, j); break;
					case MULTIPLICATION: temp(i, j) *= other(i, j); break;
					case PLUS: temp(i, j) += other(i, j); break;
				}
			}
		}
		return temp;
	}

};

// Operator Overloading

template<int rows, int cols, typename T>
inline Matrix<rows, cols, T> operator+(const T number, Matrix<rows, cols, T>& mat) {
	return mat + number;
}

template<int rows, int cols, typename T>
inline Matrix<rows, cols, T> operator-(const T number, Matrix<rows, cols, T>& mat) {
	return mat - number;
}

template<int rows, int cols, typename T>
inline Matrix<rows, cols, T> operator*(const T number, Matrix<rows, cols, T>& mat) {
	return mat * number;
}

// ostream overloading
template <int rows, int cols, typename T>
std::ostream& operator<<(std::ostream& out, const Matrix<rows, cols, T>& mat) {
	
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++)
			std::cout << mat(i, j) << " ";
		std::cout << std::endl;
	}
	return out;
}
