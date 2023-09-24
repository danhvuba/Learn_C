#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

class Matrix
{
public:
    int size = 0;
    uint8_t *M;
    Matrix(uint8_t *Matrix, int size)
    {
        M = Matrix;
        this->size = size;
    }
    // column =size
    void PrintMatrix(int row)
    {
        for (int i = 0; i < row; i++)
        {
            for (int j = 0; j < size; j++)
            {
                printf("%d ", M[i * size + j]);
            }
            printf("\n");
        }
    }

    // m number of max_row
    int Not_0(uint8_t *Matrix, int m, int row, int column)
    {
        for (int i = row; i < m; i++)
        {
            if (Matrix[i * size + column] != 0)
            {
                return i;
            }
        }
        return 0;
    }

    // add row: j to i
    void addRow(uint8_t *Matrix, int i, int j)
    {
        for (int column = 0; column < size; column++)
        {
            Matrix[i * size + column] ^= Matrix[j * size + column];
        }
    }

    void InverseMatrix(uint8_t *Res)
    {
        // Matrix = M
        uint8_t *Matrix = (uint8_t *)malloc(size * size * sizeof(uint8_t));
        for (int i = 0; i < size; i++)
        {
            for (int j = 0; j < size; j++)
            {
                Matrix[i * size + j] = M[i * size + j];
            }
        }

        // Res = E
        for (int i = 0; i < size; i++)
        {
            for (int j = 0; j < size; j++)
            {
                Res[i * size + j] = 0;
            }
            Res[i * size + i] = 1;
        }

        /// Inverse
        int row = size;
        // --> step matrix
        int i = 0, j = 0;
        for (; i < row; i++)
        {
            // (i,j) == 0
            while (Matrix[i * size + j] == 0)
            {
                // (tmp,j) != 0
                int tmp = Not_0(Matrix, row, i + 1, j);
                // all column j = 0
                if (tmp == 0)
                {
                    // next column
                    j++;
                    // all column -> break
                    if (j == size)
                    {
                        break;
                    }
                    continue;
                }
                // add tmp to i
                addRow(Matrix, i, tmp);
                addRow(Res, i, tmp);
            }

            // all column -> break
            if (j == size)
            {
                break;
            }
            // add i to all
            for (int t = i + 1; t < row; t++)
            {
                if (Matrix[t * size + j] != 0)
                {
                    addRow(Matrix, t, i);
                    addRow(Res, t, i);
                }
            }
            // next column
            j++;
            if (j == size)
            {
                break;
            }
        }

        // special step matrix
        for (; i >= 0; i--)
        {
            // column tmp have != 0 in row i
            int tmp = 0;
            for (; tmp < size; tmp++)
            {
                if (Matrix[i * size + tmp] != 0)
                {
                    break;
                }
            }
            for (int t = i - 1; t >= 0; t--)
            {
                if (Matrix[t * size + tmp] != 0)
                {
                    addRow(Matrix, t, i);
                    addRow(Res, t, i);
                }
            }
        }
        free(Matrix);
    }

    ~Matrix()
    {
    }
};

void printMatrix(uint8_t *M, int size)
{
    for (int r = 0; r < size; r++)
    {
        for (int c = 0; c < size; c++)
        {
            printf("%d ", M[r * size + c]);
        }
        printf("\n");
    }
}

// 12,16
uint16_t mul(uint16_t x, uint8_t *C, int n)
{
    uint8_t v1[n] = {0}, v2[n] = {0}, i, j;
    // x to array v1
    for (i = 0; i < n; ++i)
    {
        v1[n - 1 - i] = x & 0x1;
        x >>= 1;
    }

    for (i = 0; i < n; ++i)
        for (j = 0; j < n; ++j)
            v2[i] ^= v1[j] & C[j * n + i];

    uint16_t y = 0;
    for (i = 0; i < n; ++i)
    {
        y <<= 1;
        y ^= v2[i];
    }
    return y;
}

// 12,16
uint8_t w(int m, uint16_t x, int n)
{
    uint8_t r = 0, i, k = n / m;
    for (i = 0; i < k; ++i)
    {
        r += ((x & ((1 << m) - 1)) == 0) ? 0 : 1;
        x >>= m;
    }
    return r;
}

void ro(int m, uint8_t *C, int n)
{
    uint16_t min = 0xffff, x_min = 0;
    uint16_t x;
    uint16_t max = (1 << n) - 1;
    for (x = 1; x < max; ++x)
    {
        if (min > (w(m, x, n) + w(m, mul(x, C, n), n)))
        {
            min = w(m, x, n) + w(m, mul(x, C, n), n);
            x_min = x;
        }
    }
    if (min > (w(m, x, n) + w(m, mul(x, C, n), n)))
    {
        min = w(m, x, n) + w(m, mul(x, C, n), n);
        x_min = x;
    }
    // printf("x_min = %d  ",x_min);
    printf("ro_%d = %d\n", m, min);
}