/*********************************************
Student One: Gal Barak, 204233688
Student Two: Shir Avneri, 314980517
Assignment number: 2
*********************************************/

#pragma once
#include "matrix.h"

template <class T>
struct matNode {
	T *mat;
	matNode<T> *next;
	matNode<T> *prev;
};

template <int rows = 1, int cols = 1, typename T = int>
class MatrixContainer
{
public:	
	MatrixContainer() //C'tor
	{
		this->_firstMat = this->_lastMat = NULL;
		this->_counter = 0;
	}

	~MatrixContainer() // D'tor
	{
		while (this->_counter)
		{
			this->removeLastMatrix(); // Delete all the list
		}
	}

	void addMatrix(Matrix<rows, cols, T> & newMatrix) // add new matrix to container
	{
		// Call private function that creats new matNode*
		this->_firstMat = createNode(newMatrix);
		this->_counter++;
	}

	void removeLastMatrix() // remove the last matrix from container
	{
		struct matNode<Matrix<rows, cols, T>> *temp;
		// Check if the container is empty
		if (!this->_lastMat) {
			std::cout << "MatrixContainer is Empty" << std::endl;
			return;
		}

		// save pointer to the prev last matrix
		temp = this->_lastMat->prev;
		
		// check if there is more then one matrix in the list
		if (temp)
			this->_lastMat = temp->next = NULL;
		else
			this->_firstMat = NULL;
		
		// delete and last matrix from the list and update the counter and the _lastMat pointer
		delete this->_lastMat;
		this->_lastMat = temp;
		this->_counter--;
	}
	
	Matrix<rows, cols, T> addMatricesAtIndexes(int index1, int index2) // mat1 + mat2
	{
		Matrix<rows, cols, T> mat1, mat2;
		struct matNode<Matrix<rows, cols, T>> *temp = this->_firstMat;

		// the loop finds the matrices and set them in the "mat1 & mat2" matrices
		for (int i = 0; temp; temp = temp->next, i++) {
			if (i == index1)
				mat1 = *temp->mat;
			if (i == index2)
				mat2 = *temp->mat;
		}
		return mat1 + mat2;
	}

	Matrix<rows, cols, T> mulMatAtIndexByScalar(int index, T scalar) // mat * scalar
	{
		Matrix<rows, cols, T> mat;
		struct matNode<Matrix<rows, cols, T>> *temp = this->_firstMat;

		// the loop finds the matrix and set it in the "mat" Matrix
		for (int i = 0; temp; temp = temp->next, i++) {
			if (i == index)
				mat = *temp->mat;
		}

		return mat * scalar;
	}
	
	int getCounter() const // getter for _counter
	{
		return this->_counter;
	}

	std::ostream& print(std::ostream& out) const
	{
		//the function moves on the linked-list and prints the matrices using Matrix oveloading to <<
		struct matNode<Matrix<rows, cols, T>> *temp = this->_firstMat;
		for (int i = 0; temp; temp = temp->next, i++) {
			Matrix<rows, cols, T> mat = *temp->mat;
			std::cout << mat << std::endl;
		}
		return out;
	}
	
private:
	
	// Private function for MatNode creation
	matNode< Matrix<rows, cols, T> >* createNode(Matrix<rows, cols, T>& matrix) {
		struct matNode<Matrix<rows, cols, T>> *node = new matNode<Matrix<rows, cols, T>>(); // allocate new memory and initialize it
		node->mat = &matrix;
		node->next = node->prev = NULL;

		// check if it's the first node in the list
		if (!this->_firstMat)
			this->_firstMat = this->_lastMat = node;

		else // If it's not the first - put it in the end
		{
			node->prev = this->_lastMat;
			this->_lastMat->next = node;
			this->_lastMat = node;
		}

		// anyway - return the first node
		return this->_firstMat;
	}

	// Pointers to handling the mat' linked-list
	matNode<Matrix<rows, cols, T>> *_firstMat; 
	matNode<Matrix<rows, cols, T>> *_lastMat;	
	int _counter;

};

// ostream overloading
template <int rows, int cols, typename T>
std::ostream& operator<<(std::ostream& out, const MatrixContainer<rows, cols, T>& container) {
	std::cout << "There are " << container.getCounter() << " matrices in the container. The matrices:" << std::endl;
	return container.print(out);
}
