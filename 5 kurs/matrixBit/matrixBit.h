#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#define size 64

// column =size
void PrintMatrix(uint8_t *M, int row)
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

// column = size
void StepMatrix(uint8_t *Matrix, int row)
{
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
    // for (; i >= 0; i--)
    // {
    //     int tmp = 0;
    //     for (; tmp < n; tmp++)
    //     {
    //         if (El(Matrix[i], tmp) != 0)
    //         {
    //             break;
    //         }
    //     }
    //     for (int t = i - 1; t >= 0; t--)
    //     {
    //         if (El(Matrix[t], tmp) != 0)
    //         {
    //             Matrix[t] = Matrix[t] ^ Matrix[i];
    //         }
    //     }
    // }
}

// column = size
void SpecialStepMatrix(uint8_t *Matrix, int row)
{
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
            }
        }
    }
}

void InverseMatrix(uint8_t *Res, uint8_t *Source)
{
    // Matrix = Source
    uint8_t *Matrix = (uint8_t *)malloc(size * size * sizeof(uint8_t));
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            Matrix[i * size + j] = Source[i * size + j];
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

int rank(uint8_t *Matrix, int row)
{
    uint8_t *M = (uint8_t *)malloc((row * size + size) * sizeof(uint8_t));
    memcpy(M, Matrix, (row * size + size));
    SpecialStepMatrix(M,row);
    if (M[0]==0)
    {
        return 0;
    }
    
    for (int i = 1; i < row; i++)
    {
        if (M[i*size+i]==0)
        {
            return i;
        }
        
        if (i==(size-1))
        {
            return i+1;
        }
        
    }
    return 0;
}

// result in A matrix*matrix
void MulMatrix(uint8_t *A, uint8_t *B)
{
    // M,N for when A = B
    // M = A
    uint8_t *M = (uint8_t *)malloc(size * size * sizeof(uint8_t));
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            M[i * size + j] = A[i * size + j];
        }
    }

    // N = B
    uint8_t *N = (uint8_t *)malloc(size * size * sizeof(uint8_t));
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            N[i * size + j] = B[i * size + j];
        }
    }

    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            // = M row i * N column j
            A[i * size + j] = 0;
            for (int t = 0; t < size; t++)
            {
                A[i * size + j] ^= M[i * size + t] & N[t * size + j];
            }
        }
    }
    free(M);
    free(N);
}
