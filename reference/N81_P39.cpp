#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define u8      unsigned char
#define u32     unsigned int

#define n   4
#define m   4

static const u8 f[(1 << n)] = {0x0, 0xd, 0x1, 0xb, 0x6, 0x4, 0x8, 0x7, 0x9, 0x2, 0x5, 0xe, 0xc, 0x3, 0xf, 0xa};

static u8 rf[(1 << n)];

u8 F(u8 x)
{
    return f[x];
}

u8 F1(u8 x)
{
    return rf[x];
}

/*  Построить матрицу L     */

u8 dot_product(u8 a, u8 b)
{
    u8 ab = a & b, d = 0;
    for (u8 i = 0; i < m; ++i)
    {
        if (ab & 1)
            ++d;
        ab >>= 1;
    }
    return d;
}

/*
    Коэффициент Уольша-Адамара
*/
void Fast_WHT(int *arr)
{
    u32 i, j, h = 1;
    while (h < (1 << n))
    {
        for (i = 0; i < (1 << n); i += h << 1)
            for (j = i; j < i + h; ++j)
            {
                int x = arr[j];
                int y = arr[j + h];
                arr[j] = x + y;
                arr[j + h] = x - y;
            }
        h <<= 1;
    }
}

void delta(u8 (*phi)(u8), int L[1 << n][1 << m], u8 b)
{
    u8 i;
    int W[1 << n] = {0};
    for (i = 0; i < (1 << n); ++i)
        W[i] = (dot_product(phi(i), b) & 0x1) ? -1 : 1;

    Fast_WHT(W);

    for (i = 0; i < (1 << n); ++i)
        L[i][b] = W[i];
}

u32 _abs(int a)
{
    return (a < 0)? (-a) : a;
}

/*
    Линейная аппроксимационная матрица
*/
u8 construct_L(int L[1 << n][1 << m], u8 (*phi)(u8))
{
    u8 i, j, max = 0;
    for (j = 0; j < (1 << m); ++j)
        delta(phi, L, j);

    for (i = 0; i < (1 << n); ++i)
        for (j = 0; j < (1 << m); ++j)
            if (max < abs(L[i][j]) && j != 0)
                max = (u8)_abs(L[i][j]);
    return max;
}

/*  Построить матрицу D     */

u8 p(u8 (*phi)(u8), u8 a, u8 b)
{
    u8 x, cnt = 0;
    for (x = 0; x < (1 << n); ++x)
        if ((phi(x) ^ phi(x ^ a)) == b)
            ++cnt;
    return cnt;
}

/*
    Матрица распределения разностей
*/
u8 construct_D(u8 D[1 << n][1 << m], u8 (*phi)(u8))
{
    u8 i, j, max = 0;
    for (i = 0; i < (1 << n); ++i)
        for (j = 0; j < (1 << m); ++j)
        {
            D[i][j] = p(phi, i, j);
            if (max < D[i][j] && i != 0)
                max = D[i][j];
        }
    return max;
}

template <typename T>
void printMat(T M[1 << n][1 << m])
{
    u8 i, j;

    printf("  |");
    for (i = 0; i < (1 << m); ++i)
        printf(" %3x", i);
    printf("\n---------------------------\n");

    for (i = 0; i < (1 << n); ++i)
    {
        printf("%x | ", i);
        for (j = 0; j < (1 << m); ++j)
            printf("%3d ", M[i][j]);
        printf("\n");
    }
}

/*
    Степень нелинейности отображения Phi: V_n --> V_m
*/
// Fast Mobius transform
void Fast_MT(int *arr)
{
    u32 i, j, h = 1;
    while (h < (1 << n))
    {
        for (i = 0; i < (1 << n); i += h << 1)
            for (j = i; j < i + h; ++j)
            {
                arr[j + h] ^= arr[j];
            }
        h <<= 1;
    }
}

// dem so bit trong byte
u8 count_ones(u8 byte)
{
    static const u8 NIBBLE_LOOKUP[16] =
        {
            0, 1, 1, 2, 1, 2, 2, 3,
            1, 2, 2, 3, 2, 3, 3, 4};

    return NIBBLE_LOOKUP[byte & 0x0F] + NIBBLE_LOOKUP[byte >> 4];
}

u8 algebraic_degree(u8 (*phi)(u8))
{
    int f[1 << n] = {0};
    bool flag = false;
    u8 lamda = 0;
    for (u8 alpha = 1; alpha < (1 << m); ++alpha)
    {
        for (u8 x = 0; x < (1 << n); ++x)
            f[x] = dot_product(alpha, phi(x)) & 0x1;

        Fast_MT(f);

        u8 deg_f = 0;
        for (u8 i = 0; i < (1 << n); ++i)
            if ((f[i] & 0x1) && (deg_f < count_ones(i)))
                deg_f = count_ones(i);

        if (!flag || deg_f < lamda)
        {
            if (!flag)
                flag = true;
            lamda = deg_f;
            // printf("alpha = %d, lamda = %d\n", alpha, lamda);
        }
    }
    return lamda;
}


int main()
{
    assert(m <= n && n < 8);

    u8 i, j, r;

    for (i = 0; i < (1 << n); ++i)
        rf[f[i]] = i;

    printf("F = ");
    for (i = 0; i < (1 << n); ++i)
    {
        r = F(i);
        printf("%x", r);
    }
    printf("\n");

    printf("rF = ");
    for (i = 0; i < (1 << n); ++i)
    {
        r = F1(i);
        printf("%x", r);
    }
    printf("\n");

    u8 D[1 << n][1 << m], pF;

    printf("\n-----\n\tMATRIX (16 * D(F))\n\n");
    pF = construct_D(D, F);
    printMat(D);
    printf("\n16 * p(F) = %d\n", pF);

    printf("\n-----\n\tMATRIX (16 * D(rF))\n\n");
    pF = construct_D(D, F1);
    printMat(D);
    printf("\n16 * p(F1) = %d\n", pF);

    int L[1 << n][1 << m], dF;

    printf("\n-----\n\tMATRIX (16 * L(F))\n\n");
    dF = construct_L(L, F);
    printMat(L);
    printf("\n16 * delta(F) = %d\n", dF);

    printf("\n-----\n\tMATRIX (16 * L(rF))\n\n");
    dF = construct_L(L, F1);
    printMat(L);
    printf("\n16 * delta(F1) = %d\n", dF);

    u8 lamda;

    lamda = algebraic_degree(F);
    printf("\n-----\nlamda(F ) = %d\n", lamda);

    lamda = algebraic_degree(F1);
    printf("lamda(rF) = %d\n", lamda);

    return 0;
}
