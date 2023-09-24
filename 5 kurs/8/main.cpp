#include <stdio.h>
#include <stdint.h>
#include <set>
#include <math.h>
#include <vector>

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
void Encrypt(V2n &text, Vn *keyCrypt)
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
    text = x;
    text = text << 16 ^ y;
}

uint8_t F(Vn h, Vn *keyCrypt)
{
    V2n tmp = h;
    Encrypt(tmp, keyCrypt);
    return (tmp ^ (tmp >> 8) ^ (tmp >> 16)) & 0xff;
}

int main()
{

    setZ();
    Vn keyCrypt[r] = {0};
    uint64_t key = 0x1918111009080100;
    setKey(key, keyCrypt);

    // 3
    Vn h = 0;
    std::set<uint8_t> T;
    int Count[256] = {0};
    // V16 -> V32 ->V16
    // Ek: V32 -> V32
    // V16 V8 = (V32 ^ (V32 >> 8) ^ (V32 >> 16) ^ (V32 >> 24)) & 0xff;
    uint8_t tmp = F(h, keyCrypt);
    T.insert(tmp);
    Count[tmp]++;
    for (int i = 0; i < 0xffff; i++)
    {
        h++;
        tmp = F(h, keyCrypt);
        Count[tmp]++;
    }
    int sum = 0;
    for (int i = 0; i < 256; i++)
    {
        printf("%d ", Count[i]);
        sum += Count[i]*(Count[i]-1)/2;
    }
    printf("\n%d\n", sum);

    // // 3
    // Vn h = 0;
    // std::vector<uint8_t> T;
    // uint8_t Count[256] = {0};
    // // V16 -> V32 ->V16
    // // Ek: V32 -> V32
    // // V16 V8 = (V32 ^ (V32 >> 8) ^ (V32 >> 16) ^ (V32 >> 24)) & 0xff;
    // uint8_t tmp = F(h, keyCrypt);
    // T.push_back(tmp);
    // for (int i = 0; i < 0xffff; i++)
    // {
    //     h++;
    //     tmp = F(h, keyCrypt);
    //     for (std::vector<uint8_t>::iterator id = T.begin(); id < T.end(); id++)
    //         if (*id == tmp)
    //         {
    //             Count[tmp]++;
    //         }
    //         else
    //             T.push_back(tmp);
    // }
    // // for (int i = 0; i < 256; i++)
    // // {
    // //     printf("%d ", Count[i]);
    // // }
}