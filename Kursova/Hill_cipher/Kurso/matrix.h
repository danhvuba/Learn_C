#include <iostream>
#include <iomanip>
#include <math.h>

using namespace std;

class Matrix
{
public:
    int size;  // size
    int **Mtr; // matrix
    int p;     // order field

    // functions
    Matrix();
    Matrix(int size, int p);
    Matrix(const Matrix &); /// co the ko can const, nhung khi Matrix(___return Matrix__) ko dung// neu dung const no se tao hang so moi va luu lai khi return vao trong
    void Print_matrix();
    int Det_matrix();
    int Algebraic_complement(int, int);
    Matrix Inverse_matrix();
    int *Xmatrix(int *); // nhan 1 hang voi ma tran
    void SetUp();
    bool IS();
    ~Matrix();
};