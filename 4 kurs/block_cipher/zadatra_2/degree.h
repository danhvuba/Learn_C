#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#define n 4
#define m 4
#define V_n 0xf
#define V_m 0xf
#define TypeV_n uint8_t
#define TypeV_m uint8_t
// TypeM = TypeV_n + 1 size
#define TypeM uint16_t


// Fast Mobius transform
void Fast_MT(uint8_t *arr)
{
    uint32_t i, j, h = 1;
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


int sumBitV_n(TypeV_n x)
{
    int res = 0;
    for (int i = 0; i < n; i++)
    {
        if ((x & 1) != 0)
        {
            res++;
        }
        x >>= 1;
    }
    return res;
}

int XorBitV_m(TypeV_m x)
{
    int res = 0;
    for (int i = 0; i < m; i++)
    {
        res += (x & 1);
        x >>= 1;
    }
    return (res & 1);
}

int Degree(uint8_t *fx)
{
    int res = 0;
    TypeV_n x;
    for (x = 0; x < V_n; x++)
    {
        if ((fx[x] != 0) && (sumBitV_n(x) > res))
            res = sumBitV_n(x);
    }
    if ((fx[x] != 0) && (sumBitV_n(x) > res))
        res = sumBitV_n(x);
    return res;
}

int lambda(TypeV_m *fx)
{
    int res = n;
    uint8_t *f = (uint8_t *)malloc((V_n + 1) * sizeof(uint8_t));
    TypeV_m b;
    TypeV_n x;
    for (b = 1; b < V_m; b++)
    {
        // f ^ b
        for (x = 0; x < V_n; x++)
        {
            f[x] = XorBitV_m((fx[x] & b));
        }
        // x = V_n
        f[x] = XorBitV_m((fx[x] & b));

        Fast_MT(f);
        if (res > Degree(f))
        {
            res = Degree(f);
        }
    }
    // b = V_m
    for (x = 0; x < V_n; x++)
    {
        f[x] = XorBitV_m((fx[x] & b));
    }
    // x = V_n
    f[x] = XorBitV_m((fx[x] & b));

    Fast_MT(f);
    if (res > Degree(f))
    {
        res = Degree(f);
    }
    free(f);
    return res;
}
