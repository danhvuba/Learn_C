#include "matrix.h"

// creat when NULL
Matrix::Matrix()
{
    size = 0;
    Mtr = NULL;
}

// creat matrix O n*n
Matrix::Matrix(int n)
{
    size = n;
    if (size == 0)
    {
        Mtr == NULL;
    }
    else
    {
        Mtr = new float *[size];
        for (int i = 0; i < size; i++)
        {
            Mtr[i] = new float[size]{0};
        }
    }
}

// create matrix from matrix
Matrix::Matrix(const Matrix &M)
{
    size = M.size;
    Mtr = M.Mtr;
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

// transform: row_x * n - row_y * m
void Matrix::Trans(int x, int n, int y, int m)
{
    for (int i = 0; i < size; i++)
    {
        Mtr[x][i] = Mtr[x][i] * n + Mtr[y][i] * m;
    }
}
// Det matrix
float Matrix::Det_matrix()
{
    // creat X for save matrix
    int **X = new int *[size];
    for (int i = 0; i < size; i++)
    {
        X[i] = new int[size];
    }
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            X[i][j] = Mtr[i][j];
        }
    }

    float det = 1;
    for (int i = 0; i < size; i++)
    {
        if (Mtr[i][i] == 0)
        {
            for (int j = i + 1; j < size; j++)
            {
                if (Mtr[j][i] != 0)
                {
                    for (int c = 0; c < size; c++)
                    {
                        int tmp = Mtr[i][c];
                        Mtr[i][c] = Mtr[j][c];
                        Mtr[j][c] = tmp;
                    }
                    det = -det;
                }
            }
        }
        if (Mtr[i][i] != 0)
        {
            det = det * Mtr[i][i];
            for (int j = i + 1; j < size; j++)
            {
                if (Mtr[j][i] != 0)
                {
                    Trans(j, Mtr[i][i], i, -Mtr[j][i]);
                    det = det / Mtr[i][i];
                }
            }
        }
        else
            return 0;
    }

    // return matrix
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            Mtr[i][j] = X[i][j];
        }
    }

    return det;
}

int Matrix::Algebraic_complement(int x, int y)
{
    Matrix X(size - 1);
    int pp = 0, qq = 0;
    for (int i = 0; i < size; i++)
    {
        if (i != x)
        {
            for (int j = 0; j < size; j++)
            {
                if (j != y)
                {
                    X.Mtr[pp][qq] = Mtr[i][j];
                    qq = (qq + 1) % (size - 1);
                }
            }
            pp++;
        }
    }
    float tmp = X.Det_matrix() * pow(-1, x + y);
    return tmp;
}

Matrix Matrix::Inverse_matrix()
{
    float x = 1 / Det_matrix();
    Matrix M(size);
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            M.Mtr[i][j] = Algebraic_complement(j, i) * x;
        }
    }
    return M;
}

// mul
Matrix Matrix::operator*(const Matrix &B)
{
    Matrix M2(size);
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            for (int x = 0; x < size; x++)
            {
                M2.Mtr[i][j] = (M2.Mtr[i][j] + Mtr[i][x] * B.Mtr[x][j]);
            }
        }
    }
    return M2;
}

int *Matrix::Xmatrix(int *C)
{
    int *X = new int[size]{0};
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            X[i] = (X[i] + C[j] * Mtr[j][i]);
        }
    }
    return X;
}

Matrix::~Matrix()
{
    size = 0;
    delete[] Mtr;
    Mtr = NULL;
}