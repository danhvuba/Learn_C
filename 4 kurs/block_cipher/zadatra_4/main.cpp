#include <cstdio>
#include <cstdint>
#include <ctime>
#include "function.h"

using namespace std;

// block 16-bit
// key : k0,..,kr = (r+1)*16

uint8_t pi[16] = {5, 2, 6, 8, 1, 0xd, 7, 0xe, 4, 0xf, 0xc, 0xa, 0xb, 3, 0, 9};
// uint8_t pi[16] = {0xe, 4, 0xd, 1, 2, 0xf, 0xb, 8, 3, 0xa, 6, 0xc, 5, 9, 0, 7};
//  const
uint8_t p[16] = {0, 4, 8, 12, 1, 5, 9, 13, 2, 6, 10, 14, 3, 7, 11, 15};

/// x0 x1 x2 x3
void X(uint8_t *x, uint16_t k)
{
    for (int i = 0; i < 4; i++)
    {
        x[i] ^= (k >> ((3 - i) * 4)) & 0xf;
    }
}

void S(uint8_t *x)
{
    for (int i = 0; i < 4; i++)
    {
        x[i] = pi[x[i]];
    }
}

#define bit(x, n) ((x >> n) & 1)
void P(uint8_t *x)
{
    uint8_t v[16], i, j;
    for (i = 0; i < 4; i++)
        for (j = 0; j < 4; j++)
        {
            v[15 - i * 4 - j] = x[3 - i] & 1;
            x[3 - i] >>= 1;
        }
    for (i = 0; i < 4; i++)
        for (j = 0; j < 4; j++)
        {
            x[i] <<= 1;
            x[i] ^= v[p[i * 4 + j]];
        }
}

// k0 ... kr
void encryptTOYr(uint8_t *pt, uint16_t *key)
{
    // // pt = S_[P_[S_[P_[S_[pt ^ *key0]] ^ *key1]] ^ *key2] ^ *key3;
    for (int i = 0; i < (3 - 1); i++)
    {
        X(pt, key[i]);
        S(pt);
        P(pt);
    }
    X(pt, key[3 - 1]);
    S(pt);
    X(pt, key[3]);
}

void printMatrix_16(uint8_t *x)
{
    for (int rr = 0; rr < 16; rr++)
    {
        for (int c = 0; c < 16; c++)
        {
            printf("%2d ", x[16 * rr + c]);
        }
        printf("\n");
    }
}

void assign(uint8_t *res, uint8_t *source)
{
    for (int i = 0; i < 4; i++)
    {
        res[i] = source[i];
    }
}

void Random(uint8_t *x)
{
    for (int i = 0; i < 4; i++)
    {
        x[i] = rand() % 16;
    }
}

int main()
{
    /////////////////////////////////////////////////////////
    Function<uint8_t, uint8_t> PI(4, 4, pi);
    printf("\nD_phi:\n");
    uint8_t D_phi[256] = {0};
    for (int r = 0; r < 16; r++)
    {
        for (int c = 0; c < 16; c++)
        {
            D_phi[16 * r + c] = (int)(16 * PI.p[r][c]);
        }
    }
    printMatrix_16(D_phi);

    ////////////////////////////////////////////
    uint8_t a1[4] = {0, 0, 0, 0};
    uint8_t b1[4] = {0, 0, 0, 0};
    uint8_t a2[4];
    uint8_t b2[4] = {0, 0, 0, 0};
    uint8_t a3[4];
    uint8_t b3[4] = {0, 0, 0, 0};
    uint8_t a4[4];
    for (a1[0] = 0; a1[0] < 16; a1[0]++)
    //for (a1[1] = 0; a1[1] < 16; a1[1]++)
        for (a1[2] = 0; a1[2] < 16; a1[2]++)
        ///for (a1[3] = 0; a1[3] < 16; a1[3]++)
        ////////////////////////////
        for (b1[0] = 0; b1[0] < 16; b1[0]++)
        ///for (b1[1] = 0; b1[1] < 16; b1[1]++)
            for (b1[2] = 0; b1[2] < 16; b1[2]++)
            ///for (b1[3] = 0; b1[3] < 16; b1[3]++)
            ///////////////////////////////////////////////
            for (b2[0] = 0; b2[0] < 16; b2[0]++)
                for (b2[1] = 0; b2[1] < 16; b2[1]++)
                    //for (b2[2] = 0; b2[2] < 16; b2[2]++)
                    for (b2[3] = 0; b2[3] < 16; b2[3]++)
                        ///////////////////////////////////////////////////
                        //for (b3[0] = 0; b3[0] < 16; b3[0]++)
                            for (b3[1] = 0; b3[1] < 16; b3[1]++)
                                for (b3[2] = 0; b3[2] < 16; b3[2]++)
                                    //for (b3[3] = 0; b3[3] < 16; b3[3]++)
                                    {
                                        // printf("b1= (%x%x%x%x)\n", b1[0], b1[1], b1[2], b1[3]);
                                        if ((D_phi[a1[0] * 16 + b1[0]] == 0) || (D_phi[a1[1] * 16 + b1[1]] == 0) ||
                                            (D_phi[a1[2] * 16 + b1[2]] == 0) || (D_phi[a1[3] * 16 + b1[3]] == 0))
                                        {
                                            continue;
                                        }
                                        ////////////////
                                        assign(a2, b1);
                                        P(a2);
                                        if ((D_phi[a2[0] * 16 + b2[0]] == 0) || (D_phi[a2[1] * 16 + b2[1]] == 0) ||
                                            (D_phi[a2[2] * 16 + b2[2]] == 0) || (D_phi[a2[3] * 16 + b2[3]] == 0))
                                        {
                                            continue;
                                        }
                                        ////////////////
                                        assign(a3, b2);
                                        P(a3);
                                        if ((D_phi[a3[0] * 16 + b3[0]] == 0) || (D_phi[a3[1] * 16 + b3[1]] == 0) ||
                                            (D_phi[a3[2] * 16 + b3[2]] == 0) || (D_phi[a3[3] * 16 + b3[3]] == 0))
                                        {
                                            continue;
                                        }
                                        ///////////////
                                        assign(a4, b3);
                                        P(a4);
                                        float res = (float)(D_phi[a1[0] * 16 + b1[0]] * D_phi[a1[1] * 16 + b1[1]] * D_phi[a1[2] * 16 + b1[2]] * D_phi[a1[3] * 16 + b1[3]]); // / 16 / 16 / 16 / 16;
                                        // printf("1:  %f\n", res);
                                        res *= (float)(D_phi[a2[0] * 16 + b2[0]] * D_phi[a2[1] * 16 + b2[1]] * D_phi[a2[2] * 16 + b2[2]] * D_phi[a2[3] * 16 + b2[3]]) / 16 / 16 / 16 / 16;
                                        // printf("2:  %f\n", res);
                                        res *= (float)(D_phi[a3[0] * 16 + b3[0]] * D_phi[a3[1] * 16 + b3[1]] * D_phi[a3[2] * 16 + b3[2]] * D_phi[a3[3] * 16 + b3[3]]) / 16 / 16 / 16 / 16;
                                        if (res > 400)
                                        {
                                            printf("(%x%x%x%x, %x%x%x%x, %x%x%x%x, %x%x%x%x):   ", a1[0], a1[1], a1[2], a1[3], a2[0], a2[1], a2[2], a2[3], a3[0], a3[1], a3[2], a3[3], a4[0], a4[1], a4[2], a4[3]);
                                            printf("%f\n", res);
                                        }
                                    }
}