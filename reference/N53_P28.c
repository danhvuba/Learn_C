#include <stdio.h>
#include <string.h>

#define n 32

typedef unsigned char u8;
typedef unsigned int u32;

void gen_mat(u8 *A, u32 fr)
{
    u8 i, j;
    for (i = 0; i < n; ++i)
    {
        A[n - 1 - i] = fr & 0x1;
        fr >>= 1;
    }

    for (i = 1; i < n; ++i)
        for (j = 0; j < n; ++j)
        {
            A[n * i + j] = A[(j - i + n) % n];
        }
}

void row_swap(u8 *r1, u8 *r2)
{
    u8 buf[2 * n];
    memcpy(buf, r1, 2 * n * sizeof(u8));
    memcpy(r1, r2, 2 * n * sizeof(u8));
    memcpy(r2, buf, 2 * n * sizeof(u8));
}

void row_add(u8 *r1, u8 *r2)
{
    u8 i;
    for (i = 0; i < 2 * n; ++i)
        r1[i] ^= r2[i];
}

void inverse(u8 *rA, u8 *A)
{
    u8 AI[n * 2 * n] = {0};
    int i, j, k;

    for (i = 0; i < n; ++i)
    {
        memcpy(AI + 2 * n * i, A + n * i, n * sizeof(u8));
        AI[2 * n * i + n + i] = 1;
    }

    for (i = 0; i < n; ++i)
    {
        if (AI[2 * n * i + i] != 1)
            for (j = i + 1; j < n; ++j)
                if (AI[2 * n * j + i] == 1)
                {
                    row_swap(AI + 2 * n * i, AI + 2 * n * j);
                    break;
                }

        for (j = i + 1; j < n; ++j)
            if (AI[2 * n * j + i] == 1)
                row_add(AI + 2 * n * j, AI + 2 * n * i);
    }

    for (i = n - 1; i >= 0; --i)
    {
        for (j = i - 1; j >= 0; --j)
            if (AI[2 * n * j + i] == 1)
                row_add(AI + 2 * n * j, AI + 2 * n * i);
    }

    for (i = 0; i < n; ++i)
        memcpy(rA + n * i, AI + 2 * n * i + n, n * sizeof(u8));
}

u32 mul(u32 x, u8 *C)
{
    u8 v1[n] = {0}, v2[n] = {0}, i, j;
    for (i = 0; i < n; ++i)
    {
        v1[n - 1 - i] = x & 0x1;
        x >>= 1;
    }

    for (i = 0; i < n; ++i)
        for (j = 0; j < n; ++j)
            v2[i] ^= v1[j] & C[j * n + i];

    u32 y = 0;
    for (i = 0; i < n; ++i)
    {
        y <<= 1;
        y ^= v2[i];
    }

    return y;
}

u32 w(u8 m, u32 x)
{
    u32 r = 0, i, k = n / m;
    for (i = 0; i < k; ++i)
    {
        r += ((x & ((1 << m) - 1)) == 0) ? 0 : 1;
        x >>= m;
    }
    return r;
}

u32 ro(u8 m, u8 *C)
{
    u32 min = 0xfffffff, x_min = 0;
    unsigned long long int x, lim = (unsigned long long int)1 << (n-12);

    for (x = 1; x < lim; ++x)
    {
        if (min > (w(m, x) + w(m, mul(x, C))))
        {
            min = w(m, x) + w(m, mul(x, C));
            x_min = x;
        }
    }
    printf("min = %d, x_min = %d\n", min, x_min);
    return min;
}

int main()
{
    // A: 1000 0000 1000 0010 0000 0010 0000 0010
    // B: 1000 0000 0100 0000 0001 0000 0000 0000
    u32 frA = 0x80401000;
    u8 A[n * n] = {0}, i, j;
    gen_mat(A, frA);
    // for (i = 0; i < n; ++i)
    // {
    //     for (j = 0; j < n; ++j)
    //         printf("%x ", A[n * i + j]);
    //     printf("\n");
    // }

    u8 rA[n * n] = {0};
    inverse(rA, A);

    // for (i = 0; i < n; ++i)
    // {
    //     for (j = 0; j < n; ++j)
    //         printf("%x ", rA[n * i + j]);
    //     printf("\n");
    // }

    printf("First row of  A: ");
    for (i = 0; i < n; ++i)
        printf("%X", A[i]);
    printf("\n");

    printf("First row of rA: ");
    for (i = 0; i < n; ++i)
        printf("%X", rA[i]);
    printf("\n");

    u8 m = 8;
    printf("ro(%d, A) = %d\n", m, ro(m, A));

    return 0;
}