#include <stdio.h>  // c std input, output: printf ...
#include <stdint.h> // uint8_t ...

#define Vx uint32_t
// size matrix = n
#define n 32
// 1...1 -- n
#define maxVx 0xfffff/// bo 3xf-12 bit

Vx mul(Vx x, uint8_t *C)
{
    uint8_t arrX[n] = {0}, arr[n] = {0}, r, c;
    // x to arr
    for (r = 0; r < n; r++)
        arrX[n - 1 - r] = (x >> r) & 1;
    // mul C
    for (c = 0; c < n; c++)
        for (r = 0; r < n; r++)
            arr[c] ^= arrX[r] & C[r * n + c];
    /// arr to Vx
    Vx res = 0;
    for (r = 0; r < n; r++)
    {
        res <<= 1;
        res ^= arr[r];
    }
    return res;
}

int w(Vx x, int m)
{
    int k = n / m, i, res = 0;
    for (i = 0; i < k; i++)
    {
        res += ((x & ((1 << m) - 1)) == 0) ? 0 : 1;
        x >>= m;
    }
    return res;
}

int ro(uint8_t *C, int m)
{
    Vx x;
    // 2 <= weight <= n/m +1
    int weight = n + 2;
    for (x = 1; x < maxVx; x++)
    {
        if ((w(x, m) + w(mul(x, C), m)) < weight)
        {
            weight = w(x, m) + w(mul(x, C), m);
        }
    }
    if ((w(x, m) + w(mul(x, C), m)) < weight)
    {
        weight = w(x, m) + w(mul(x, C), m);
    }
    return weight;
}