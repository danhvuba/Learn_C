#include <iostream>

using namespace std;

const int n = 8;
#define u8 uint8_t
#define El(x, i) ((x >> (n - 1 - i)) & 1)

void Print_bit(u8 x)
{
    for (int i = 0; i < n; i++)
    {
        cout << El(x, i) << " ";
    }
}

int Not_0(u8 *Matrix, int m, int row, int column)
{
    for (int i = row; i < m; i++)
    {
        if (El(Matrix[i], column) != 0)
        {
            return i;
        }
    }
    return 0;
}

// matrix to E
void Function(u8 *Matrix, int m)
{
    int i = 0, j = 0;
    for (; i < m; i++)
    {
        // (i,j) == 0
        while (El(Matrix[i], j) == 0)
        {
            // (tmp,j) != 0
            int tmp = Not_0(Matrix, m, i + 1, j);
            // next column
            if (tmp == 0)
            {
                j++;
                if (j == n)
                {
                    break;
                }
                continue;
            }
            // add tmp to i
            Matrix[i] = Matrix[i] ^ Matrix[tmp];
        }

        // end 1
        if (j == n)
        {
            break;
        }
        // add i to all
        for (int t = i + 1; t < m; t++)
        {
            if (El(Matrix[t], j) != 0)
            {
                Matrix[t] = Matrix[t] ^ Matrix[i];
            }
        }
        j++;
        if (j == n)
        {
            break;
        }
    }

    // E
    for (; i >= 0; i--)
    {
        int tmp = 0;
        for (; tmp < n; tmp++)
        {
            if (El(Matrix[i], tmp) != 0)
            {
                break;
            }
        }
        for (int t = i - 1; t >= 0; t--)
        {
            if (El(Matrix[t], tmp) != 0)
            {
                Matrix[t] = Matrix[t] ^ Matrix[i];
            }
        }
    }
}

void Function(u8 *Matrix, u8 *Matrix_2, int m)
{
    int i = 0, j = 0;
    for (; i < m; i++)
    {
        // (i,j) == 0
        while (El(Matrix[i], j) == 0)
        {
            // (tmp,j) != 0
            int tmp = Not_0(Matrix, m, i + 1, j);
            // next column
            if (tmp == 0)
            {
                j++;
                if (j == n)
                {
                    break;
                }
                continue;
            }
            // add tmp to i
            Matrix[i] = Matrix[i] ^ Matrix[tmp];
            Matrix_2[i] = Matrix_2[i] ^ Matrix_2[tmp];
        }

        // end 1
        if (j == n)
        {
            break;
        }
        // add i to all
        for (int t = i + 1; t < m; t++)
        {
            if (El(Matrix[t], j) != 0)
            {
                Matrix[t] = Matrix[t] ^ Matrix[i];
                Matrix_2[t] = Matrix_2[t] ^ Matrix_2[i];
            }
        }
        j++;
        if (j == n)
        {
            break;
        }
    }
    // E
    for (; i >= 0; i--)
    {
        int tmp = 0;
        for (; tmp < n; tmp++)
        {
            if (El(Matrix[i], tmp) != 0)
            {
                break;
            }
        }
        for (int t = i - 1; t >= 0; t--)
        {
            if (El(Matrix[t], tmp) != 0)
            {
                Matrix[t] = Matrix[t] ^ Matrix[i];
                Matrix_2[t] = Matrix_2[t] ^ Matrix_2[i];
            }
        }
    }
}

u8 Mul(u8 x, u8 *Matrix)
{
    u8 result = 0;
    for (int i = 0; i < n; i++)
    {
        int tmp = 0;
        for (int j = 0; j < n; j++)
        {
            tmp = tmp ^ (El(x,j) * El(Matrix[j], i));
        }
        result = result ^ (tmp << (n - 1 - i));
    }
    return result;
}