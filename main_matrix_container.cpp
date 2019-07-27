#include "MatrixContainer.h"

int main()
{

	//freopen("output_matrix_container.txt", "w", stdout);

	Matrix<4, 4> mat1(1);
	Matrix<4, 4> mat2(2);
	Matrix<4, 4> mat3(5);
	std::cout << "mat1:" << std::endl << mat1 << std::endl;
	std::cout << "mat2:" << std::endl << mat2 << std::endl;
	std::cout << "mat3:" << std::endl << mat3 << std::endl;

	MatrixContainer<4, 4> container; //you may assume that all the matrices in the container have the same template parameters
	container.addMatrix(mat1);
	container.addMatrix(mat2);
	container.addMatrix(mat3);
	container.addMatrix(mat1);


	std::cout << container;
	container.removeLastMatrix();
	std::cout << container;

	std::cout << std::endl;
	std::cout << std::endl;

	std::cout << "The result of the addition of the matrix in the index 1 and the matrix in index 2 is:" << std::endl;
	std::cout << container.addMatricesAtIndexes(1, 2); //you may assume correct input

	std::cout << std::endl;
	std::cout << std::endl;

	std::cout << "The result of the multiplication of the matrix in the index 2 with the scalar 2 is:" << std::endl;
	std::cout << container.mulMatAtIndexByScalar(2, 2); //you may assume correct input
	return 0;
}