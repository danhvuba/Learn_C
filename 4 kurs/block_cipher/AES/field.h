#include <cstdio>
#include <cstdint>

#define mx 0b00011011

uint8_t MulF_2_8(uint8_t ax, uint8_t bx)
{
    uint8_t result = 0;
    while (ax != 0 && bx != 0)
    {
        if (bx & 1 != 0)
            result ^= ax;
        // & 0xff -- 8 bit
        ax = ((ax >> (8 - 1)) == 0) ? ((ax << 1) & 0xff) : (((ax << 1) ^ mx) & 0xff);
        bx = bx >> 1;
    }
    return result;
}

uint8_t MulF_2_8_n(uint8_t ax, int tmp)
{
    if (ax == 0)
    {
        return 0;
    }

    // ax!=0
    uint8_t result = 1;
    while (tmp != 0)
    {
        if ((tmp & 1) != 0)
            result = MulF_2_8(result, ax);
        tmp = tmp >> 1;
        ax = MulF_2_8(ax, ax);
    }
    return result;
}

// x != 0
uint8_t InverseF_2_8(uint8_t x)
{
    for (uint8_t i = 0xff; i > 0; i--)
    {
        if (MulF_2_8(x, i) == 1)
        {
            return i;
        }
    }
    return 1;
}

int OrdOfF[8] = {1, 3, 5, 17, 15, 51, 85, 255};
// 255 = 3x5x17
uint8_t OrdF_2_8(uint8_t x)
{
    for (int i = 0; i < 8; i++)
    {
        if (MulF_2_8_n(x, OrdOfF[i]) == 1)
        {
            return OrdOfF[i];
        }
    }
    return 0;
}

////////////////////////////
///////////////////////////
// F 2^8 / x^4 +1
// -> 0-0-0-0-1 (x^4) = 1-0-0-0 (1)
// array of 4 element
// (a0,a1,a2,a3)

// result in a
void addF(uint8_t *a, uint8_t *b)
{
    for (int i = 0; i < 4; i++)
    {
        a[i] ^= b[i];
    }
}

// result in a
void mulF(uint8_t *a, uint8_t *b)
{
    uint8_t tmp[4] = {0};
    // when a*a need
    uint8_t ib[4] = {b[0], b[1], b[2], b[3]};
    for (int i = 0; i < 4; i++)
    {
        if (ib[i] != 0)
            addF(tmp, a);
        // shift a
        // x^4 +1 -> simple shift
        uint8_t id = a[3];
        a[3] = a[2];
        a[2] = a[1];
        a[1] = a[0];
        a[0] = id;
    }
    for (int i = 0; i < 4; i++)
    {
        a[i] = tmp[i];
    }
}

// result in x
void mulF_n(uint8_t *x, int tmp)
{
    uint8_t res[4] = {1, 0, 0, 0};
    while (tmp != 0)
    {
        if ((tmp & 1) != 0)
            mulF(res, x);
        tmp = tmp >> 1;
        mulF(x, x);
    }
    x[0] = res[0];
    x[1] = res[1];
    x[2] = res[2];
    x[3] = res[3];
}

void PrintF(uint8_t *x)
{
    for (int i = 0; i < 4; i++)
    {
        printf("%02x ", x[i]);
    }
    printf("\n");
}

bool IsE(uint8_t *x)
{
    if ((x[0] == 0) && (x[1] == 1) && (x[2] == 0) && x[3] == 0)
    {
        return true;
    }
    return false;
}

#define size 4

// column =size
void PrintMatrix(uint8_t *M, int row)
{
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < size; j++)
        {
            printf("%02x ", M[i * size + j]);
        }
        printf("\n");
    }
    printf("\n");
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

// make row: j to i and M[i][col]=0
// M[j][col]=e
void makeRow(uint8_t *Matrix, int i, int j, int col)
{
    uint8_t tmp = Matrix[i * size + col];
    for (int column = col; column < size; column++)
    {
        Matrix[i * size + column] ^= MulF_2_8(Matrix[j * size + column], tmp);
    }
}

// column = size
void SpecialStepMatrix(uint8_t *Matrix, int row, uint8_t *Y)
{
    // --> step matrix
    int i = 0, j = 0;
    /////////////////////////////////
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
            Y[i] ^= Y[tmp];
        }

        // (i,j) !=0
        // make [i][j] = e
        uint8_t val = InverseF_2_8(Matrix[i * size + j]);
        for (int t = j; t < size; t++)
            Matrix[i * size + t] = MulF_2_8(Matrix[i * size + t], val);
        Y[i] = MulF_2_8(Y[i], val);

        // all column -> break
        if (j == size)
        {
            break;
        }
        // add i to all (all to 0 )
        for (int t = i + 1; t < row; t++)
        {
            if (Matrix[t * size + j] != 0)
            {
                Y[t] = Y[t] ^ MulF_2_8(Y[i], Matrix[t * size + j]);
                makeRow(Matrix, t, i, j);
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
                Y[t] = Y[t] ^ MulF_2_8(Y[i], Matrix[t * size + tmp]);
                makeRow(Matrix, t, i, tmp);
            }
        }
    }
}

void inverseF(uint8_t *x)
{
    uint8_t E[4] = {0x01, 0, 0, 0};
    uint8_t M[16] = {0};
    // 0 3 2 1
    // 1 0 3 2
    // 2 1 0 3
    // 3 2 1 0
    for (int r = 0; r < 4; r++)
    {
        for (int c = 0; c < 4; c++)
        {
            M[r + c * 4] = x[(4 + c - r) % 4];
        }
    }
    SpecialStepMatrix(M, 4, E);
    for (int i = 0; i < 4; i++)
    {
        x[i] = E[i];
    }
}
