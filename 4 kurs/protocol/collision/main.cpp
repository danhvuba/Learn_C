#include <cstdio>
#include <cstdint>
// #include <cstdlib>

// uint32_t shift 3
#define Shift(x) ((x >> (32 - 3) & 0b111) ^ (x << 3))
#define m(b, c, d) (b & c ^ b & d ^ c & d)

void Print(uint32_t *x)
{
    for (int i = 0; i < 4; i++)
    {
        printf("%x ", x[i]);
    }
    printf("\n");
}


// x : 3 2 1 0
//     a b c d
void f(uint32_t *x)
{
    uint32_t tmp = x[0];
    x[0] = x[3] + Shift(m(x[2], x[1], x[0]));
    x[3] = x[2];
    x[2] = x[1];
    x[1] = tmp;
}

void H(uint32_t *res, uint32_t x[4])
{
    for (int i = 0; i < 4; i++)
    {
        res[i] = x[i];
    }
    for (int i = 0; i < 48; i++)
    {
        f(x);
    }
    
    for (int i = 0; i < 4; i++)
    {
        res[i] ^= x[i];
    }
}

int main()
{
    uint32_t res[4] = {0};
    uint32_t x[4] = {4, 0, 0, 0};
    H(res, x);
    Print(x);
    Print(res);
}