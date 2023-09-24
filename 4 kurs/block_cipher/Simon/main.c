#include <stdio.h>
#include <stdint.h>

// 2n =32
#define n 16
#define l 64
#define r_ 32
#define j_ 0
#define Vn uint16_t

int m = l / n;
uint8_t z0[62] = {0};
uint8_t z1[62] = {0};
uint8_t z2[62] = {0};
uint8_t z3[62] = {0};
uint8_t z4[62] = {0};

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
void mul(uint8_t t, uint8_t* M)
{
    uint8_t v[5] = {0};
    for (int c = 0; c < 5; c++)
    {
        for (int r = 0; r < 5; r++)
        {
            v[c] ^= (t >> (4 - r)) & M[r * 5 + c];
        }
    }
    t = 0;
    for (int i = 0; i < 5; i++)
    {
        t <<= 1;
        t = v[i];
    }
}

void setZ()
{
    uint8_t u = 0b00001, v = 0b00001, w = 0b00001;
    for (int i = 0; i < 62; i++)
    {
        z0[i] = u & 1;           // u
        z1[i] = v & 1;           // v
        z2[i] = (u & 1 & i) & 1; // u + 0101....
        z3[i] = (v & 1 & i) & 1; // v + 0101....
        z4[i] = (w & 1 & i) & 1; // w + 0101....
        mul(u,U);
        mul(v,V);
        mul(w,W);
    }
}

int main()
{
    setZ();
}