#include <cstdio>
#include <cstdint>
#include <cstdlib>

#define n 8
#define m 8
#define maxVn 0xff
#define maxVm 0xff
#define Vn uint8_t
#define Vm uint8_t

// f array of 2^n 0-1
// Fast Mobius transform
void fastMt(uint8_t *f)
{
    // h = M / 2
    int h, x, i;
    for (h = 1; h < (1 << n); h <<= 1)
    {
        for (x = 0; x < (1 << n); x = x + (h << 1))
            for (i = x; i < x + h; i++)
                f[i + h] = f[i] ^ f[i + h];
    }
}

int sumBitVn(Vn x)
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

int XorBitVm(Vm x)
{
    int res = 0;
    for (int i = 0; i < m; i++)
    {
        res ^= (x & 1);
        x >>= 1;
    }
    return res;
}

int Degree(uint8_t *fx)
{
    int res = 0;
    Vn x;
    for (x = 0; x < maxVn; x++)
    {
        if ((fx[x] != 0) && (sumBitVn(x) > res))
            res = sumBitVn(x);
    }
    if ((fx[x] != 0) && (sumBitVn(x) > res))
        res = sumBitVn(x);
    return res;
}

int lambda(Vm *fx)
{
    int res = n;
    uint8_t f[1 << n] = {0};
    Vm b;
    Vn x;
    for (b = 1; b < maxVm; b++)
    {
        // f ^ b
        for (x = 0; x < maxVn; x++)
        {
            f[x] = XorBitVm(fx[x] & b);
        }
        // x = V_n
        f[x] = XorBitVm(fx[x] & b);

        fastMt(f);
        if (res > Degree(f))
        {
            res = Degree(f);
        }
    }
    // b = V_m
    for (x = 0; x < maxVn; x++)
    {
        f[x] = XorBitVm(fx[x] & b);
    }
    // x = V_n
    f[x] = XorBitVm(fx[x] & b);

    fastMt(f);
    if (res > Degree(f))
    {
        res = Degree(f);
    }
    return res;
}