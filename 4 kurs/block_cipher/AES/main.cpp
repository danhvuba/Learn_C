#include "field.h"

#define Nr 10
#define Nk 4

// F_1[0] = 0;
uint8_t F_2_8_1[256] = {0};
// ord 0 = 0
uint8_t ord_2_8[256] = {0};

void setF_2_8()
{
    // not count '0'
    for (uint8_t i = 0xff; i > 0; i--)
    {
        F_2_8_1[i] = InverseF_2_8(i);
        ord_2_8[i] = OrdF_2_8(i);
    }
}

//////////////////////
uint8_t pi[256] = {0x63, 0x7c, 0x77, 0x7b, 0xf2, 0x6b, 0x6f, 0xc5, 0x30, 0x01, 0x67, 0x2b, 0xfe, 0xd7, 0xab, 0x76,
                   0xca, 0x82, 0xc9, 0x7d, 0xfa, 0x59, 0x47, 0xf0, 0xad, 0xd4, 0xa2, 0xaf, 0x9c, 0xa4, 0x72, 0xc0,
                   0xb7, 0xfd, 0x93, 0x26, 0x36, 0x3f, 0xf7, 0xcc, 0x34, 0xa5, 0xe5, 0xf1, 0x71, 0xd8, 0x31, 0x15,
                   0x04, 0xc7, 0x23, 0xc3, 0x18, 0x96, 0x05, 0x9a, 0x07, 0x12, 0x80, 0xe2, 0xeb, 0x27, 0xb2, 0x75,
                   0x09, 0x83, 0x2c, 0x1a, 0x1b, 0x6e, 0x5a, 0xa0, 0x52, 0x3b, 0xd6, 0xb3, 0x29, 0xe3, 0x2f, 0x84,
                   0x53, 0xd1, 0x00, 0xed, 0x20, 0xfc, 0xb1, 0x5b, 0x6a, 0xcb, 0xbe, 0x39, 0x4a, 0x4c, 0x58, 0xcf,
                   0xd0, 0xef, 0xaa, 0xfb, 0x43, 0x4d, 0x33, 0x85, 0x45, 0xf9, 0x02, 0x7f, 0x50, 0x3c, 0x9f, 0xa8,
                   0x51, 0xa3, 0x40, 0x8f, 0x92, 0x9d, 0x38, 0xf5, 0xbc, 0xb6, 0xda, 0x21, 0x10, 0xff, 0xf3, 0xd2,
                   0xcd, 0x0c, 0x13, 0xec, 0x5f, 0x97, 0x44, 0x17, 0xc4, 0xa7, 0x7e, 0x3d, 0x64, 0x5d, 0x19, 0x73,
                   0x60, 0x81, 0x4f, 0xdc, 0x22, 0x2a, 0x90, 0x88, 0x46, 0xee, 0xb8, 0x14, 0xde, 0x5e, 0x0b, 0xdb,
                   0xe0, 0x32, 0x3a, 0x0a, 0x49, 0x06, 0x24, 0x5c, 0xc2, 0xd3, 0xac, 0x62, 0x91, 0x95, 0xe4, 0x79,
                   0xe7, 0xc8, 0x37, 0x6d, 0x8d, 0xd5, 0x4e, 0xa9, 0x6c, 0x56, 0xf4, 0xea, 0x65, 0x7a, 0xae, 0x08,
                   0xba, 0x78, 0x25, 0x2e, 0x1c, 0xa6, 0xb4, 0xc6, 0xe8, 0xdd, 0x74, 0x1f, 0x4b, 0xbd, 0x8b, 0x8a,
                   0x70, 0x3e, 0xb5, 0x66, 0x48, 0x03, 0xf6, 0x0e, 0x61, 0x35, 0x57, 0xb9, 0x86, 0xc1, 0x1d, 0x9e,
                   0xe1, 0xf8, 0x98, 0x11, 0x69, 0xd9, 0x8e, 0x94, 0x9b, 0x1e, 0x87, 0xe9, 0xce, 0x55, 0x28, 0xdf,
                   0x8c, 0xa1, 0x89, 0x0d, 0xbf, 0xe6, 0x42, 0x68, 0x41, 0x99, 0x2d, 0x0f, 0xb0, 0x54, 0xbb, 0x16};

uint8_t A[64] = {1, 1, 1, 1, 0, 0, 0, 1,
                 1, 1, 1, 0, 0, 0, 1, 1,
                 1, 1, 0, 0, 0, 1, 1, 1,
                 1, 0, 0, 0, 1, 1, 1, 1,
                 0, 0, 0, 1, 1, 1, 1, 1,
                 0, 0, 1, 1, 1, 1, 1, 0,
                 0, 1, 1, 1, 1, 1, 0, 0,
                 1, 1, 1, 1, 1, 0, 0, 0};
uint8_t a = 0b01100011;
void setPi()
{
    for (int x = 0; x < 256; x++)
    {
        // alpha
        uint8_t tmp = (x == 0) ? 0 : F_2_8_1[x];
        // phi
        for (int j = 0; j < 8; j++)
        {
            pi[x] <<= 1;
            for (int i = 0; i < 8; i++)
            {
                pi[x] ^= (tmp >> (7 - i)) & A[i * 8 + j];
            }
        }
        pi[x] ^= a;
    }
}

// AddRoundKey
void X(uint8_t *state, uint32_t *w)
{
    for (int c = 0; c < 4; c++)
    {
        for (int r = 0; r < 4; r++)
        {
            ///////////////////////////////////////// right or left wi ???. Try ...3210 wi
            state[4 * r + c] ^= ((w[c] >> (8 * (3 - r))) & 0xff);
        }
    }
}

// SubByte
void S(uint8_t *state)
{
    for (int r = 0; r < 4; r++)
    {
        for (int c = 0; c < 4; c++)
        {
            state[4 * r + c] = pi[state[4 * r + c]];
        }
    }
}

// ShiftRow
void P(uint8_t *state)
{
    uint8_t tmp = state[4 * 1 + 0];
    // row 1
    state[4 * 1 + 0] = state[4 * 1 + 1];
    state[4 * 1 + 1] = state[4 * 1 + 2];
    state[4 * 1 + 2] = state[4 * 1 + 3];
    state[4 * 1 + 3] = tmp;

    // row 2
    tmp = state[4 * 2 + 0];
    state[4 * 2 + 0] = state[4 * 2 + 2];
    state[4 * 2 + 2] = tmp;
    tmp = state[4 * 2 + 1];
    state[4 * 2 + 1] = state[4 * 2 + 3];
    state[4 * 2 + 3] = tmp;

    // row 3
    tmp = state[4 * 3 + 3];
    state[4 * 3 + 3] = state[4 * 3 + 2];
    state[4 * 3 + 2] = state[4 * 3 + 1];
    state[4 * 3 + 1] = state[4 * 3 + 0];
    state[4 * 3 + 0] = tmp;
}

uint8_t aState[4] = {0x02, 0x01, 0x01, 0x03};
// MixColumns
void L(uint8_t *state)
{
    for (int c = 0; c < 4; c++)
    {
        uint8_t tmp[4] = {state[4 * 0 + c], state[4 * 1 + c], state[4 * 2 + c], state[4 * 3 + c]};
        mulF(tmp, aState);
        state[4 * 0 + c] = tmp[0];
        state[4 * 1 + c] = tmp[1];
        state[4 * 2 + c] = tmp[2];
        state[4 * 3 + c] = tmp[3];
    }
}

/// DeploymentKey
uint32_t SubWord(uint32_t x)
{
    uint32_t tmp = pi[(x >> 24) & 0xff];
    tmp = (tmp << 8) ^ pi[(x >> 16) & 0xff];
    tmp = (tmp << 8) ^ pi[(x >> 8) & 0xff];
    tmp = (tmp << 8) ^ pi[(x >> 0) & 0xff];
    return tmp;
}

uint32_t RotWord(uint32_t x)
{
    return (((x << 8) & 0xffffffff) ^ ((x >> 24) & 0xff));
}

// key = Nk * 32-bit
// ki = 4(Nr+1) * 32-bit
void DeploymentKey(uint32_t *w, uint32_t *key)
{
    for (int j = 0; j < Nk; j++)
    {
        w[j] = key[j];
    }

    if (Nk != 8)
    {
        for (int j = Nk; j < (4 * (Nr + 1)); j++)
        {
            if ((j % Nk) != 0)
            {
                w[j] = w[j - Nk] ^ w[j - 1];
            }
            else
            {
                // Rcon
                w[j] = MulF_2_8_n(0x02, ((j / Nk) - 1));
                w[j] = w[j - Nk] ^ SubWord(RotWord(w[j - 1])) ^ (w[j] << 24);
            }
        }
    }
    else // Nk =8
    {
        for (int j = Nk; j < (4 * (Nr + 1)); j++)
        {
            if ((j % Nk) == 4)
            {
                w[j] = w[j - Nk] ^ SubWord(w[j - 1]);
            }
            else if ((j % Nk) != 0)
            {
                w[j] = w[j - Nk] ^ w[j - 1];
            }
            else if ((j % Nk) == 0)
            {
                // Rcon
                w[j] = MulF_2_8_n(0x02, ((j / Nk) - 1));
                w[j] = w[j - Nk] ^ SubWord(RotWord(w[j - 1])) ^ (w[j] << 24);
            }
        }
    }
}

// input 16 * byte
// w = 4(Nr+1) * 32-bit
void AESEncrypt(uint8_t *input, uint32_t *w)
{
    // deployment key
    // encrypt
    // 0  4   8 12
    // 1  5   9 13       state
    // 2  6  10 14
    // 3  7  11 15
    // w0 w1 w2 w3
    uint8_t state[16];
    for (int c = 0; c < 4; c++)
    {
        for (int r = 0; r < 4; r++)
        {
            state[4 * r + c] = input[4 * c + r];
        }
    }

    // ki= (w4i,.. ,w4i+3) w-uint32_t

    for (int i = 0; i < (Nr - 1); i++)
    {
        X(state, &w[4 * i]);
        S(state);
        P(state);
        L(state);
    }
    X(state, &w[4 * (Nr - 1)]);
    S(state);
    P(state);
    X(state, &w[4 * (Nr)]);

    for (int c = 0; c < 4; c++)
    {
        for (int r = 0; r < 4; r++)
        {
            input[4 * c + r] = state[4 * r + c];
        }
    }
}

int main()
{
    setF_2_8();
    // setPi();

    // exercise 24-29
    // 24
    printf("EX 24:\n ord [x] = %d\n", ord_2_8[0x02]);
    printf(" [x]^51 = 0x%02x\n", MulF_2_8_n(0x02, 51));
    for (int i = 0; i < 256; i++)
    {
        if (ord_2_8[i] == 255)
        {
            printf(" 0x%02x", i);
        }
    }
    printf("\n------------------------------------------------------------------------------\n");

    // 25
    uint8_t x[4] = {0x02, 0x01, 0x01, 0x03};
    printf("EX 25:\n inverse");
    for (int i = 0; i < 4; i++)
    {
        printf(" %02x", x[3 - i]);
    }
    inverseF(x);
    printf(":\n        ");
    for (int i = 0; i < 4; i++)
    {
        printf(" %02x", x[3 - i]);
    }
    printf("\n------------------------------------------------------------------------------\n");

    // 26
    // 27
    // 30
    uint8_t input[16] = {0};
    uint32_t key[4] = {0x55555555, 0x55555555, 0x55555555, 0x55555555};
    uint32_t w[44];
    DeploymentKey(w,key);
    AESEncrypt(input,w);
    for (int i = 0; i < 16; i++)
    {
        printf("%x",input[i]);
    }
    
}