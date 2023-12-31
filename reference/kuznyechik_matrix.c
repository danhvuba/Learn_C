#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>

#define BlockSize 128
#define Nr 10

#define u8 unsigned char
#define u64 unsigned long long

static u8 Pi[256] = {0xfc, 0xee, 0xdd, 0x11, 0xcf, 0x6e, 0x31, 0x16, 0xfb, 0xc4, 0xfa, 0xda, 0x23, 0xc5, 0x04, 0x4d,
                     0xe9, 0x77, 0xf0, 0xdb, 0x93, 0x2e, 0x99, 0xba, 0x17, 0x36, 0xf1, 0xbb, 0x14, 0xcd, 0x5f, 0xc1,
                     0xf9, 0x18, 0x65, 0x5a, 0xe2, 0x5c, 0xef, 0x21, 0x81, 0x1c, 0x3c, 0x42, 0x8b, 0x01, 0x8e, 0x4f,
                     0x05, 0x84, 0x02, 0xae, 0xe3, 0x6a, 0x8f, 0xa0, 0x06, 0x0b, 0xed, 0x98, 0x7f, 0xd4, 0xd3, 0x1f,
                     0xeb, 0x34, 0x2c, 0x51, 0xea, 0xc8, 0x48, 0xab, 0xf2, 0x2a, 0x68, 0xa2, 0xfd, 0x3a, 0xce, 0xcc,
                     0xb5, 0x70, 0x0e, 0x56, 0x08, 0x0c, 0x76, 0x12, 0xbf, 0x72, 0x13, 0x47, 0x9c, 0xb7, 0x5d, 0x87,
                     0x15, 0xa1, 0x96, 0x29, 0x10, 0x7b, 0x9a, 0xc7, 0xf3, 0x91, 0x78, 0x6f, 0x9d, 0x9e, 0xb2, 0xb1,
                     0x32, 0x75, 0x19, 0x3d, 0xff, 0x35, 0x8a, 0x7e, 0x6d, 0x54, 0xc6, 0x80, 0xc3, 0xbd, 0x0d, 0x57,
                     0xdf, 0xf5, 0x24, 0xa9, 0x3e, 0xa8, 0x43, 0xc9, 0xd7, 0x79, 0xd6, 0xf6, 0x7c, 0x22, 0xb9, 0x03,
                     0xe0, 0x0f, 0xec, 0xde, 0x7a, 0x94, 0xb0, 0xbc, 0xdc, 0xe8, 0x28, 0x50, 0x4e, 0x33, 0x0a, 0x4a,
                     0xa7, 0x97, 0x60, 0x73, 0x1e, 0x00, 0x62, 0x44, 0x1a, 0xb8, 0x38, 0x82, 0x64, 0x9f, 0x26, 0x41,
                     0xad, 0x45, 0x46, 0x92, 0x27, 0x5e, 0x55, 0x2f, 0x8c, 0xa3, 0xa5, 0x7d, 0x69, 0xd5, 0x95, 0x3b,
                     0x07, 0x58, 0xb3, 0x40, 0x86, 0xac, 0x1d, 0xf7, 0x30, 0x37, 0x6b, 0xe4, 0x88, 0xd9, 0xe7, 0x89,
                     0xe1, 0x1b, 0x83, 0x49, 0x4c, 0x3f, 0xf8, 0xfe, 0x8d, 0x53, 0xaa, 0x90, 0xca, 0xd8, 0x85, 0x61,
                     0x20, 0x71, 0x67, 0xa4, 0x2d, 0x2b, 0x09, 0x5b, 0xcb, 0x9b, 0x25, 0xd0, 0xbe, 0xe5, 0x6c, 0x52,
                     0x59, 0xa6, 0x74, 0xd2, 0xe6, 0xf4, 0xb4, 0xc0, 0xd1, 0x66, 0xaf, 0xc2, 0x39, 0x4b, 0x63, 0xb6};

static u8 rPi[256] = {0xa5, 0x2d, 0x32, 0x8f, 0x0e, 0x30, 0x38, 0xc0, 0x54, 0xe6, 0x9e, 0x39, 0x55, 0x7e, 0x52, 0x91,
                      0x64, 0x03, 0x57, 0x5a, 0x1c, 0x60, 0x07, 0x18, 0x21, 0x72, 0xa8, 0xd1, 0x29, 0xc6, 0xa4, 0x3f,
                      0xe0, 0x27, 0x8d, 0x0c, 0x82, 0xea, 0xae, 0xb4, 0x9a, 0x63, 0x49, 0xe5, 0x42, 0xe4, 0x15, 0xb7,
                      0xc8, 0x06, 0x70, 0x9d, 0x41, 0x75, 0x19, 0xc9, 0xaa, 0xfc, 0x4d, 0xbf, 0x2a, 0x73, 0x84, 0xd5,
                      0xc3, 0xaf, 0x2b, 0x86, 0xa7, 0xb1, 0xb2, 0x5b, 0x46, 0xd3, 0x9f, 0xfd, 0xd4, 0x0f, 0x9c, 0x2f,
                      0x9b, 0x43, 0xef, 0xd9, 0x79, 0xb6, 0x53, 0x7f, 0xc1, 0xf0, 0x23, 0xe7, 0x25, 0x5e, 0xb5, 0x1e,
                      0xa2, 0xdf, 0xa6, 0xfe, 0xac, 0x22, 0xf9, 0xe2, 0x4a, 0xbc, 0x35, 0xca, 0xee, 0x78, 0x05, 0x6b,
                      0x51, 0xe1, 0x59, 0xa3, 0xf2, 0x71, 0x56, 0x11, 0x6a, 0x89, 0x94, 0x65, 0x8c, 0xbb, 0x77, 0x3c,
                      0x7b, 0x28, 0xab, 0xd2, 0x31, 0xde, 0xc4, 0x5f, 0xcc, 0xcf, 0x76, 0x2c, 0xb8, 0xd8, 0x2e, 0x36,
                      0xdb, 0x69, 0xb3, 0x14, 0x95, 0xbe, 0x62, 0xa1, 0x3b, 0x16, 0x66, 0xe9, 0x5c, 0x6c, 0x6d, 0xad,
                      0x37, 0x61, 0x4b, 0xb9, 0xe3, 0xba, 0xf1, 0xa0, 0x85, 0x83, 0xda, 0x47, 0xc5, 0xb0, 0x33, 0xfa,
                      0x96, 0x6f, 0x6e, 0xc2, 0xf6, 0x50, 0xff, 0x5d, 0xa9, 0x8e, 0x17, 0x1b, 0x97, 0x7d, 0xec, 0x58,
                      0xf7, 0x1f, 0xfb, 0x7c, 0x09, 0x0d, 0x7a, 0x67, 0x45, 0x87, 0xdc, 0xe8, 0x4f, 0x1d, 0x4e, 0x04,
                      0xeb, 0xf8, 0xf3, 0x3e, 0x3d, 0xbd, 0x8a, 0x88, 0xdd, 0xcd, 0x0b, 0x13, 0x98, 0x02, 0x93, 0x80,
                      0x90, 0xd0, 0x24, 0x34, 0xcb, 0xed, 0xf4, 0xce, 0x99, 0x10, 0x44, 0x40, 0x92, 0x3a, 0x01, 0x26,
                      0x12, 0x1a, 0x48, 0x68, 0xf5, 0x81, 0x8b, 0xc7, 0xd6, 0x20, 0x0a, 0x08, 0x00, 0x4c, 0xd7, 0x74};

static u8 M[256] = {0xcf, 0x6e, 0xa2, 0x76, 0x72, 0x6c, 0x48, 0x7a, 0xb8, 0x5d, 0x27, 0xbd, 0x10, 0xdd, 0x84, 0x94,
                    0x98, 0x20, 0xc8, 0x33, 0xf2, 0x76, 0xd5, 0xe6, 0x49, 0xd4, 0x9f, 0x95, 0xe9, 0x99, 0x2d, 0x20,
                    0x74, 0xc6, 0x87, 0x10, 0x6b, 0xec, 0x62, 0x4e, 0x87, 0xb8, 0xbe, 0x5e, 0xd0, 0x75, 0x74, 0x85,
                    0xbf, 0xda, 0x70, 0x0c, 0xca, 0x0c, 0x17, 0x1a, 0x14, 0x2f, 0x68, 0x30, 0xd9, 0xca, 0x96, 0x10,
                    0x93, 0x90, 0x68, 0x1c, 0x20, 0xc5, 0x06, 0xbb, 0xcb, 0x8d, 0x1a, 0xe9, 0xf3, 0x97, 0x5d, 0xc2,
                    0x8e, 0x48, 0x43, 0x11, 0xeb, 0xbc, 0x2d, 0x2e, 0x8d, 0x12, 0x7c, 0x60, 0x94, 0x44, 0x77, 0xc0,
                    0xf2, 0x89, 0x1c, 0xd6, 0x02, 0xaf, 0xc4, 0xf1, 0xab, 0xee, 0xad, 0xbf, 0x3d, 0x5a, 0x6f, 0x01,
                    0xf3, 0x9c, 0x2b, 0x6a, 0xa4, 0x6e, 0xe7, 0xbe, 0x49, 0xf6, 0xc9, 0x10, 0xaf, 0xe0, 0xde, 0xfb,
                    0x0a, 0xc1, 0xa1, 0xa6, 0x8d, 0xa3, 0xd5, 0xd4, 0x09, 0x08, 0x84, 0xef, 0x7b, 0x30, 0x54, 0x01,
                    0xbf, 0x64, 0x63, 0xd7, 0xd4, 0xe1, 0xeb, 0xaf, 0x6c, 0x54, 0x2f, 0x39, 0xff, 0xa6, 0xb4, 0xc0,
                    0xf6, 0xb8, 0x30, 0xf6, 0xc4, 0x90, 0x99, 0x37, 0x2a, 0x0f, 0xeb, 0xec, 0x64, 0x31, 0x8d, 0xc2,
                    0xa9, 0x2d, 0x6b, 0x49, 0x01, 0x58, 0x78, 0xb1, 0x01, 0xf3, 0xfe, 0x91, 0x91, 0xd3, 0xd1, 0x10,
                    0xea, 0x86, 0x9f, 0x07, 0x65, 0x0e, 0x52, 0xd4, 0x60, 0x98, 0xc6, 0x7f, 0x52, 0xdf, 0x44, 0x85,
                    0x8e, 0x44, 0x30, 0x14, 0xdd, 0x02, 0xf5, 0x2a, 0x8e, 0xc8, 0x48, 0x48, 0xf8, 0x48, 0x3c, 0x20,
                    0x4d, 0xd0, 0xe3, 0xe8, 0x4c, 0xc3, 0x16, 0x6e, 0x4b, 0x7f, 0xa2, 0x89, 0x0d, 0x64, 0xa5, 0x94,
                    0x6e, 0xa2, 0x76, 0x72, 0x6c, 0x48, 0x7a, 0xb8, 0x5d, 0x27, 0xbd, 0x10, 0xdd, 0x84, 0x94, 0x01};

static u8 FI[256][256];

static u64 *Tl[16];

// Multiplication in GF(2^8) with P(x)=x^8+x^7+x^6+x+1 --> 111000011
u8 gmul(u8 a, u8 b)
{
    u8 p = 0;
    while (a != 0 && b != 0)
    {
        if (b & 1)
            p ^= a;

        if (a & 0x80)
            a = (a << 1) ^ 0x1c3;
        else
            a <<= 1;
        b >>= 1;
    }
    return p;
}

void Field_Init()
{
    unsigned int i, j;
    for (i = 0; i < 256; ++i)
        for (j = 0; j < 256; ++j)
            FI[i][j] = gmul(i, j);
}

#define GETU64(pt) (((u64)(pt)[0] << 56) ^ ((u64)(pt)[1] << 48) ^ ((u64)(pt)[2] << 40) ^ ((u64)(pt)[3] << 32) ^ ((u64)(pt)[4] << 24) ^ ((u64)(pt)[5] << 16) ^ ((u64)(pt)[6] << 8) ^ ((u64)(pt)[7]))
#define PUTU64(ct, st)              \
    {                               \
        (ct)[0] = (u8)((st) >> 56); \
        (ct)[1] = (u8)((st) >> 48); \
        (ct)[2] = (u8)((st) >> 40); \
        (ct)[3] = (u8)((st) >> 32); \
        (ct)[4] = (u8)((st) >> 24); \
        (ct)[5] = (u8)((st) >> 16); \
        (ct)[6] = (u8)((st) >> 8);  \
        (ct)[7] = (u8)(st);         \
    }
#define GETBYTE64(n, i) ((u8)((n >> (8 * i)) & 0xff))

#define XOR(pt64, st64)             \
    {                               \ 
        (pt64)[0] ^= (st64)[0];     \
        (pt64)[1] ^= (st64)[1];     \
    }

#define S(pt64)                                     \
    {                                               \
        u8 pt8[16] = {0};                           \
        PUTU64(pt8    , pt64[0]);                   \
        PUTU64(pt8 + 8, pt64[1]);                   \
        pt64[0] = ((u64)Pi[pt8[0]] << 56) ^ ((u64)Pi[pt8[1]] << 48) ^ ((u64)Pi[pt8[ 2]] << 40) ^ ((u64)Pi[pt8[ 3]] << 32) ^ ((u64)Pi[pt8[ 4]] << 24) ^ ((u64)Pi[pt8[ 5]] << 16) ^ ((u64)Pi[pt8[ 6]] << 8) ^ ((u64)Pi[pt8[ 7]]);\
        pt64[1] = ((u64)Pi[pt8[8]] << 56) ^ ((u64)Pi[pt8[9]] << 48) ^ ((u64)Pi[pt8[10]] << 40) ^ ((u64)Pi[pt8[11]] << 32) ^ ((u64)Pi[pt8[12]] << 24) ^ ((u64)Pi[pt8[13]] << 16) ^ ((u64)Pi[pt8[14]] << 8) ^ ((u64)Pi[pt8[15]]);\
    }

void L(u64 *pt64)
{
    u64 buffer[2] = {0}, t0, t1;
    u8 pt8[16] = {0};
    memcpy(buffer, pt8, 2 * sizeof(64));
    PUTU64(pt8    , pt64[0]);
    PUTU64(pt8 + 8, pt64[1]);

    t0 = Tl[ 0][pt8[ 0] << 1] ^ Tl[ 1][pt8[ 1] << 1] ^ Tl[ 2][pt8[ 2] << 1] ^ Tl[ 3][pt8[ 3] << 1] ^ \
         Tl[ 4][pt8[ 4] << 1] ^ Tl[ 5][pt8[ 5] << 1] ^ Tl[ 6][pt8[ 6] << 1] ^ Tl[ 7][pt8[ 7] << 1] ^ \
         Tl[ 8][pt8[ 8] << 1] ^ Tl[ 9][pt8[ 9] << 1] ^ Tl[10][pt8[10] << 1] ^ Tl[11][pt8[11] << 1] ^ \
         Tl[12][pt8[12] << 1] ^ Tl[13][pt8[13] << 1] ^ Tl[14][pt8[14] << 1] ^ Tl[15][pt8[15] << 1] ;
    t1 = Tl[ 0][pt8[ 0] << 1 ^ 1] ^ Tl[ 1][pt8[ 1] << 1 ^ 1] ^ Tl[ 2][pt8[ 2] << 1 ^ 1] ^ Tl[ 3][pt8[ 3] << 1 ^ 1] ^ \
         Tl[ 4][pt8[ 4] << 1 ^ 1] ^ Tl[ 5][pt8[ 5] << 1 ^ 1] ^ Tl[ 6][pt8[ 6] << 1 ^ 1] ^ Tl[ 7][pt8[ 7] << 1 ^ 1] ^ \
         Tl[ 8][pt8[ 8] << 1 ^ 1] ^ Tl[ 9][pt8[ 9] << 1 ^ 1] ^ Tl[10][pt8[10] << 1 ^ 1] ^ Tl[11][pt8[11] << 1 ^ 1] ^ \
         Tl[12][pt8[12] << 1 ^ 1] ^ Tl[13][pt8[13] << 1 ^ 1] ^ Tl[14][pt8[14] << 1 ^ 1] ^ Tl[15][pt8[15] << 1 ^ 1] ;
        
    pt64[0] = t0;
    pt64[1] = t1;
}

void F(u64 *rk, u64 *pt1, u64 *pt0)
{
    u64 buffer[2] = {0};
    memcpy(buffer, pt1, 2 * sizeof(u64));

    XOR(pt1, rk);
    S(pt1);
    L(pt1);
    XOR(pt1, pt0);

    memcpy(pt0, buffer, 2 * sizeof(u64));
}

void key_expand(u64 *rk, u64 *cipherKey)
{
    assert(rk != NULL && cipherKey != NULL);

    u8 i, j;
    u64 *buffer = (u64 *)calloc(4, sizeof(u64));
    u64 *rC     = (u64 *)calloc(2, sizeof(u64));

    memcpy(rk, cipherKey, 4 * sizeof(u64));
    memcpy(buffer, rk, 4 * sizeof(u64));

    for (i = 1; i < 5; ++i)
    {
        for (j = 1; j < 9; ++j)
        {
            memset(rC, 0ULL, 2 * sizeof(u64));
            rC[1] = j + (i - 1) * 8;
            L(rC);
            F(rC, buffer, buffer + 2);
        }
        memcpy(rk + 4 * i, buffer, 4 * sizeof(u64));
    }

    printf("\n--------------- BEGIN KEY GENERATING ---------------\n");

    for (i = 0; i < 10; ++i)
    {
        printf("K[%02d] = %016llx%016llx \n", i + 1, rk[2 * i], rk[2 * i + 1]);
    }

    printf("---------------  END KEY GENERATING  ---------------\n");

    free(rC);
    free(buffer);
}

void encrypt(u64 *ct64, u64 *pt64, u64 *rk)
{
    assert(ct64 != NULL && pt64 != NULL && rk != NULL);

    // printf("\n--------------- BEGIN ENCRYPTING ---------------\n");

    // u64 P0, P1, S0, S1;

    // P0 = pt64[0];
    // P1 = pt64[1];


    u64 buffer[2] = { 0 };
    memcpy(buffer, pt64, 2 * sizeof(u64));

    
    // printf("plaintext =       %016llx%016llx\n", P0, P1);

    u8 i = 0;
    for (; i < Nr - 1; ++i)
    {
        XOR(buffer, rk + 2 * i);
        S(buffer);
        L(buffer);
    }
    XOR(buffer, rk + 2 * i);
    memcpy(ct64, buffer, 2 * sizeof(u64));

    // printf("ciphertext =      %016llx%016llx\n", ct64[0], ct64[1]);

    // printf("---------------  END ENCRYPTING  ---------------\n");
}

void vec_mul(u64 *v, u8 *u, u8 k)
{
    u8 v8[16] = {0}, i;
    
    for (i = 0; i < 16; ++i)
        v8[i] = gmul(k, u[i]);
    
    v[0] = GETU64(v8);
    v[1] = GETU64(v8 + 8);
}

void LUT_gen()
{
    int i, j;
    for (i = 0; i < 16; ++i)
        Tl[i] = (u64 *)calloc(2 * 256, sizeof(u64));
    
    for (i = 0; i < 16; ++i)
    {
        for (j = 0; j < 256; ++j)
        {
            vec_mul(Tl[i] + 2 * j, M + 16 * i, j);
        }
    }

    // for (j = 0; j < 256; ++j)
    // {
    //     printf("%016llx%016llx ", Tl[0][2 * j], Tl[0][2 * j + 1]);
    // }
}


int main()
{
    Field_Init();

    LUT_gen();

    u64 pt64[2] = {0x1122334455667700, 0xffeeddccbbaa9988};
    u64 cipherKey[4] = {0x8899aabbccddeeffULL, 0x0011223344556677ULL, 0xfedcba9876543210ULL, 0x0123456789abcdefULL};
    u64 rk[20], ct64[2];

    key_expand(rk, cipherKey);

    // encrypt(ct64, pt64, rk);

    printf("MEASURING RUNNING TIME...\n");
    size_t i, num_test = 1000000;
    clock_t begin = clock();

    for (i = 0; i < num_test; ++i)
        encrypt(ct64, pt64, rk);

    clock_t end = clock();
    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("RUNNING TIME = %lf\n", time_spent);
    printf("SPEED        = %lf Mbits/s \n", (num_test * 128) / (time_spent * 1024 * 1024));

    for (int i = 0; i < 16; ++i)
        free(Tl[i]);

    return 0;
}