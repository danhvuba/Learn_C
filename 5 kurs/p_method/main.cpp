// SIMON

#include <stdio.h>
#include <stdint.h>
#include <math.h>

// 2n = 32 - size block
#define n 16
#define l 64 // size key l = m * n
#define r 32 // number of rounds
#define j 0
#define c 0xfffc // const c = 2^n -4

// size of x = n
#define R_Right(x, i) ((x >> i) ^ (x << (n - i)))

// size of x = n
#define R_left(x, i) ((x << i) ^ (x >> (n - i)))
#define Vn uint16_t
#define V2n uint32_t
#define Vl uint64_t
const int m = l / n;

uint8_t z[5][62] = {0};
uint8_t U[25] = {0, 1, 0, 0, 0,
                 0, 0, 1, 0, 0,
                 1, 0, 0, 1, 0,
                 0, 0, 0, 0, 1,
                 1, 0, 0, 0, 1};
uint8_t V[25] = {0, 1, 1, 0, 0,
                 0, 0, 1, 0, 0,
                 1, 0, 0, 1, 0,
                 0, 0, 0, 0, 1,
                 1, 0, 0, 0, 0};
uint8_t W[25] = {0, 1, 0, 0, 0,
                 0, 0, 1, 0, 0,
                 1, 0, 0, 1, 0,
                 0, 0, 0, 0, 1,
                 1, 0, 0, 0, 0};

// t - 5 bit
// result t = t * M
void mul(uint8_t &t, uint8_t *M)
{
    uint8_t v[5] = {0};
    for (int column = 0; column < 5; column++)
    {
        for (int row = 0; row < 5; row++)
        {
            v[column] ^= (t >> (4 - row)) & M[row * 5 + column];
        }
    }

    t = 0;
    for (int i = 0; i < 5; i++)
    {
        t <<= 1;
        t ^= v[i];
    }
}

void setZ()
{
    uint8_t u = 0b00001, v = 0b00001, w = 0b00001;
    for (int i = 0; i < 62; i++)
    {
        z[0][i] = u & 1;             // u
        z[1][i] = v & 1;             // v
        z[2][i] = (u & 1) ^ (i & 1); // u + 0101....
        z[3][i] = (v & 1) ^ (i & 1); // v + 0101....
        z[4][i] = (w & 1) ^ (i & 1); // w + 0101....
        mul(u, U);
        mul(v, V);
        mul(w, W);
    }
}

void setKey(Vl key, Vn *keyCrypt)
{
    for (int i = 0; i < m; i++)
    {
        keyCrypt[i] = key & 0xffff;
        key >>= 16;
    }
    for (int i = 0; i < (r - m); i++)
    {
        if (m == 2)
        {
            printf("The code hasn't been written yet\n");
        }
        if (m == 3)
        {
            printf("The code hasn't been written yet\n");
        }
        if (m == 4)
        {
            keyCrypt[i + m] = c ^ z[j][i] ^ keyCrypt[i] ^ keyCrypt[i + 1] ^
                              R_Right(keyCrypt[i + 1], 1) ^
                              R_Right(keyCrypt[i + 3], 3) ^
                              R_Right(keyCrypt[i + 3], 4);
        }
    }
}

// Vn * pt = x y
V2n Encrypt(V2n text, Vn *keyCrypt)
{

    // text = x-y
    Vn x, y;
    y = text & 0xffff;
    x = text >> 16;
    for (int i = 0; i < r; i++)
    {
        Vn tmp = x;
        x = y ^ ((R_left(x, 1) & R_left(x, 8)) ^ R_left(x, 2)) ^ keyCrypt[i];
        y = tmp;
        // printf("%x%x\n", x,y);
    }
    V2n res;
    res = x;
    res = res << 16 ^ y;
    return res;
}

int main()
{
    setZ();
    Vn keyCrypt[r] = {0};
    uint64_t key = 0x1918111009080100;
    setKey(key, keyCrypt);

    ////////////////////////////////////////////////////////////////////
    int N = 1000;
    printf("computing x..... in %d\n", N);
    uint32_t x[N];
    bool flag = false;
    int i, count = 0;
    while (!flag)
    {
        count++;
        x[0] = rand();
        x[0] = (x[0] << 16) ^ rand();
        i = 1;
        while (i < N)
        {
            x[i] = Encrypt(x[i - 1], keyCrypt)^ x[i - 1];
            if ((i % 2 == 0) && (x[i] == x[i / 2]))
            {
                i = i / 2;
                flag = true;
                break;
            }
            i++;
        }
    }
    printf("number of round = %d\n", count);
    printf("i= %d\n", i);
    printf("x[%d] = %08x, x[%d] = %08x\n", i, x[i], (2 * i), x[2 * i]);

    /////
    printf("\nfind collisions....\n");
    int l_0 = -1, l_1 = i;
    int j_;
    while (l_1 != (l_0 + 1))
    {

        j_ = (l_0 + l_1) / 2;
        if (x[j_] == x[j_ + i])
            l_1 = j_;
        else
            l_0 = j_;
    }

    ////////
    if (l_0 == -1)
    {
        printf("no\n");
        return -1;
    }
    printf("x[%d] = %08x, x[%d] = %08x\n", l_0, x[l_0], l_0 + i, x[l_0 + i]);
    printf("H: %x,  %x\n", x[l_0 + 1], x[l_0 + i + 1]);
}