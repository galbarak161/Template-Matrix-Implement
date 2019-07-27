#include "matrix.h"

template <int row, int col, typename T>
void printDiag(Matrix<row, col, T>& mat) {
	int number;
	T* diag = mat.getDiag(number);
	for (int i = 0; i<number; i++)
	{
		std::cout << diag[i] << " ";
	}
    std::cout << std::endl;
	delete[] diag;
}

int main() {

	//freopen("output_matrix.txt", "w", stdout);

	
    Matrix<4, 4> mat;
    std::cout << mat << std::endl;

    Matrix<4, 4> identity(1);
    std::cout << identity << std::endl;

    Matrix<4, 4> res = (identity + 2) * 3;
    std::cout << res << std::endl;

    Matrix<3, 4> mat1(9);
    Matrix<3, 4> mat2(4);

    std::cout << (mat1 - 4) << std::endl;

    mat2(2, 1) = 0;

    const int cell = (2 + mat1 - 1)(1, 2);

    std::cout << "The value of cell 1, 2 is: " << cell << std::endl;

    std::cout << (1 + mat2) << std::endl;

    std::cout << ++mat1 << std::endl;
    std::cout << --mat2 << std::endl;

    std::cout << "Values of mat1 and mat2, before..." << std::endl;
    std::cout << mat1++ << std::endl;
    std::cout << mat2++ << std::endl;

    std::cout << "Values of mat1 and mat2, after..." << std::endl;
    std::cout << mat1 << std::endl;
    std::cout << mat2 << std::endl;

    mat2(0,0) = 13;

    /*
     * Matrix diagonal is:
     * 1. In case of nxn matrix it's simple all (i, i) cell for all
     * i between 0 and n - 1.
     * 2. In case of nxm matrix it's all cells (i, i) cells for all
     * i between 0 and min(n,m).
     */
    std::cout << "Printing main diagonal of mat2" << std::endl;
    printDiag(mat2);

    /*
     *
     * Trace of any given Matrix nxm is the sum of main
     * diagonal entries.
     *
     * */
    std::cout << "trace(mat2) = " << mat2.trace() << std::endl;
    std::cout << std::endl;

    Matrix<3, 2, double> m1, m2;

    m1(0,0)=1;  m1(0,1) = -1;   //  1 -1
    m1(1,0)=3;  m1(1,1) = 7;    //  3  7
    m1(2,0)=-5; m1(2,1) = 0;    // -5  0

    std::cout << "Matrix m1: " << std::endl;
    std::cout << m1 << std::endl;
    std::cout << "Printing main diagonal of m1" << std::endl;
    printDiag(m1);
    std::cout << "trace(m1) = " << m1.trace() << std::endl;
    std::cout << std::endl;

    m2(0,0)=3;      m2(0,1) = 1;   //  3  1
    m2(1,0)=-1;     m2(1,1) = 2;   // -1  2
    m2(2,0)=0;      m2(2,1) = 6;   //  0  6

    std::cout << "Matrix m2: " << std::endl;
    std::cout << m2 << std::endl;
    std::cout << "Printing main diagonal of m2" << std::endl;
    printDiag(m2);
    std::cout << "trace(m2) = " << m2.trace() << std::endl;
    std::cout << std::endl;

    Matrix<3, 2, double> m3 = m1 + m2;

    std::cout << "Matrix m3 = m1 + m2: " << std::endl;
    std::cout << m3 << std::endl;
    std::cout << "Printing main diagonal of m3" << std::endl;
    printDiag(m3);
    std::cout << "trace(m3) = " << m3.trace() << std::endl;
    std::cout << std::endl;

    Matrix<3, 2, double> m4 = m3 + 1 - m2*2 + m1;
    ++m4;
    ++m4;

    std::cout << "Matrix m4 = m3 + 1 - 2*m2 + m1" << std::endl;
    std::cout << "++m4" << std::endl;
    std::cout << "m4:" << std::endl;
    std::cout << m4 << std::endl;
    std::cout << "Printing main diagonal of m4" << std::endl;
    printDiag(m4);
    std::cout << "trace(m4) = " << m4.trace() << std::endl;
    std::cout << std::endl;


    Matrix<2, 4, float> mf1(2.5f);

    mf1(0,0) += 3; mf1(0, 3) -= 0.5f;
    mf1(1,1) = 0; mf1(1, 2) = 0;
    ++mf1;
    mf1 = (-mf1 + 1.7f) + mf1*0.25f - 1;
    std::cout << "Matrix mf1:" << std::endl;
    std::cout << mf1 << std::endl;
    std::cout << "Printing main diagonal of mf1" << std::endl;
    printDiag(mf1);
    std::cout << "trace(mf1) = " << mf1.trace() << std::endl;
    std::cout << std::endl;

    return 0;
}
