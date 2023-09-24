#include <iostream>
#include <iomanip>
#include <math.h>

using namespace std;

class Matrix
{
public:
    int size;  // size
    float **Mtr; // matrix

    // functions
    Matrix();
    Matrix(int size);
    Matrix(const Matrix &); /// co the ko can const, nhung khi Matrix(___return Matrix__) ko dung// neu dung const no se tao hang so moi va luu lai khi return vao trong
    void Print_matrix();
    void Trans(int, int, int, int);
    float Det_matrix();
    int Algebraic_complement(int, int);
    Matrix Inverse_matrix();
    Matrix operator*(const Matrix &);
    int *Xmatrix(int *); // nhan 1 hang voi ma tran
    ~Matrix();
};