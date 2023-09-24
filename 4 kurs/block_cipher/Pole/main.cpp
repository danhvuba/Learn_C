// printf
#include <cstdio>
// uint8_t
#include <cstdint>

#define fx 0b10000111
#define u8 uint8_t
const int n = 8;
#define max 0xff

u8 Mul(u8 ax, u8 bx)
{
    u8 result = 0;
    while (ax != 0 && bx != 0)
    {
        if (bx & 1 != 0)
            result ^= ax;
        ax = (((ax >> (n - 1)) == 0) ? (ax << 1) : ((ax << 1) ^ fx))&max;
        bx = bx >> 1;
    }
    return result;
}

u8 Mul_n(u8 ax, int tmp)
{
    if (tmp == 0)
    {
        return 1;
    }

    if (ax == 0)
    {
        return 0;
    }

    // ax!=0
    u8 result = 1;
    while (tmp != 0)
    {
        if ((tmp & 1) != 0)
            result = Mul(result, ax);
        tmp = tmp >> 1;
        ax = Mul(ax, ax);
    }
    return result;
}

int main()
{
    u8 ax = 0xc6;
    printf("%02x\n", Mul_n(ax, 255));
}