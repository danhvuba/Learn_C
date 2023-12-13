#include "matrix.h"

// creat when NULL
Matrix::Matrix()
{
    size = 0;
    Mtr = NULL;
    p = 0;
}

// creat matrix O n*n
Matrix::Matrix(int n, int val)
{
    size = n;
    if (size == 0)
    {
        Mtr == NULL;
    }
    else
    {
        Mtr = new int *[size];
        for (int i = 0; i < size; i++)
        {
            Mtr[i] = new int[size]{0};
        }
    }
    p = val;
}

// create matrix from matrix
Matrix::Matrix(const Matrix &M)
{
    size = M.size;
    Mtr = M.Mtr;
    p = M.p;
}

// print matrix
void Matrix::Print_matrix()
{
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            cout << setw(3) << Mtr[i][j];
        }
        cout << endl;
    }
}

// Det matrix
int Matrix::Det_matrix()
{
    int det = 0;
    if (size == 3)
    {
        det = Mtr[0][0] * Mtr[1][1] * Mtr[2][2] + Mtr[0][1] * Mtr[1][2] * Mtr[2][0] + Mtr[0][2] * Mtr[1][0] * Mtr[2][1] - Mtr[0][2] * Mtr[1][1] * Mtr[2][0] - Mtr[0][0] * Mtr[1][2] * Mtr[2][1] - Mtr[0][1] * Mtr[1][0] * Mtr[2][2];
    }
    if (size == 2)
    {
        det = Mtr[0][0] * Mtr[1][1] - Mtr[0][1] * Mtr[1][0];
    }
    return (p * p * p + det) % p;
}

int Matrix::Algebraic_complement(int x, int y)
{
    Matrix X(size - 1, p);
    int pp = 0, qq = 0;
    for (int i = 0; i < size; i++)
    {
        if (i != y)
        {
            for (int j = 0; j < size; j++)
            {
                if (j != x)
                {
                    X.Mtr[pp][qq] = Mtr[i][j];
                    qq = (qq + 1) % (size - 1);
                }
            }
            pp++;
        }
    }
    int tmp = X.Det_matrix() * (int)pow(-1, x + y);
    return (p + tmp % p) % p;
}

Matrix Matrix::Inverse_matrix()
{
    int x = Det_matrix();
    for (int i = 0; i < p; i++)
    {
        if ((i * x) % p == 1)
        {
            x = i;
            break;
        }
    }
    Matrix M(size, p);
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            M.Mtr[i][j] = (Algebraic_complement(i, j) * x) % p;
        }
    }
    return M;
}

int *Matrix::Xmatrix(int *C)
{
    int *X = new int[size]{0};
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            X[i] = (X[i] + C[j] * Mtr[j][i]) % p;
        }
    }
    return X;
}

void Matrix::SetUp()
{
    int i = 0, j = 0;
    while (true)
    {
        Mtr[i][j]++;
        if (Mtr[i][j] == p)
        {
            Mtr[i][j] = 0;
            j++;
            if (j == size)
            {
                j = 0;
                i++;
            }
        }
        else
        {
            i = 0;
            j = 0;
            break;
        }
    }
}

bool Matrix::IS()
{
    int det = this->Det_matrix();
    for (int i = 2; i < p; i++)
    {
        if ((p % i == 0) && (det % i == 0))
        {
            return false;
        }
    }
    return true;
}

Matrix::~Matrix()
{
    size = 0;
    delete[] Mtr;
    Mtr = NULL;
    p = 0;
}