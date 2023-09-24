#include <iostream>
#include <iomanip>
#include <math.h>

using namespace std;

class Matrix
{
public:
    // size and matrix
    int size;
    int **Mtr;
    int p;

    // functions
    Matrix();
    Matrix(int, int);
    Matrix(const Matrix &);
    void Set_matrix();
    void Print_matrix();
    void Trans(int, int, int, int);
    int Det_matrix();
    int Algebraic_complement(int, int);
    Matrix Inverse_matrix();
    Matrix operator*(const Matrix &);
    ~Matrix();
};