#include <cstdio>
#include <cstdint>
#include <ctime>
#include <thread>

using namespace std;

// number of round
#define r 3

// block 16-bit
// key : k0,..,kr = (r+1)*16

uint8_t pi[16] = {5, 2, 6, 8, 1, 0xd, 7, 0xe, 4, 0xf, 0xc, 0xa, 0xb, 3, 0, 9};
// const
uint8_t p[16] = {0, 4, 8, 12, 1, 5, 9, 13, 2, 6, 10, 14, 3, 7, 11, 15};

void X(uint16_t &x, uint16_t k)
{
    x ^= k;
}

void S(uint16_t &x)
{
    uint16_t res = 0;
    for (int i = 0; i < 4; i++)
    {
        res ^= ((pi[(x >> (4 * i)) & 0xf]) << (4 * i));
    }
    x = res;
}

#define bit(x, n) ((x >> n) & 1)
void P(uint16_t &x)
{
    uint8_t v[16], i;
    for (i = 0; i < 16; i++)
    {
        v[15 - i] = x & 1;
        x >>= 1;
    }
    x = 0;
    for (i = 0; i < 16; i++)
    {
        x <<= 1;
        x ^= v[p[i]];
    }
}
uint16_t S_[65536] = {0};
uint16_t P_[65536] = {0};
uint16_t K[676] = {0};
// k0 ... kr
void encryptTOYr(uint16_t &pt, uint16_t *key)
{
    // pt = S_[P_[S_[P_[S_[pt ^ *key0]] ^ *key1]] ^ *key2] ^ *key3;
    for (int i = 0; i < (r - 1); i++)
    {
        X(pt, key[i]);
        S(pt);
        P(pt);
    }
    X(pt, key[r - 1]);
    S(pt);
    X(pt, key[r]);
}

void findKey(int start, int end)
{
    uint16_t *k1, *k2, *k3, *k4, *max = K + 676;
    for (k1 = K; k1 < max; k1++)
        for (k2 = K; k2 < max; k2++)
            for (k3 = K; k3 < max; k3++)
                for (k4 = K + start; k4 < K + end; k4++)
                {
                    if ((S_[P_[S_[P_[S_[0x165C ^ *k1]] ^ *k2]] ^ *k3] ^ *k4) == 0xAD36)
                        if ((S_[P_[S_[P_[S_[0xA832 ^ *k1]] ^ *k2]] ^ *k3] ^ *k4) == 0x5B7D)
                            if ((S_[P_[S_[P_[S_[0x8336 ^ *k1]] ^ *k2]] ^ *k3] ^ *k4) == 0x8D6E)
                                if ((S_[P_[S_[P_[S_[0xA455 ^ *k1]] ^ *k2]] ^ *k3] ^ *k4) == 0x8734)
                                    if ((S_[P_[S_[P_[S_[0xA29D ^ *k1]] ^ *k2]] ^ *k3] ^ *k4) == 0x8F31)
                                        if ((S_[P_[S_[P_[S_[0x46B9 ^ *k1]] ^ *k2]] ^ *k3] ^ *k4) == 0x13B6)
                                            printf("\n%04X %04X %04X %04X", *k1, *k2, *k3, *k4);
                }
}

int main()
{
    for (uint16_t i = 0; i < 0xffff; i++)
    {
        uint16_t m = i;
        S(m);
        S_[i] = m;
        m = i;
        P(m);
        P_[i] = m;
    }

    // set bi alphabet
    uint8_t al[26] = {0};
    for (int i = 0; i < 26; i++)
    {
        al[i] = 0x61 + i;
    }
    for (int i = 0; i < 26; i++)
    {
        for (int j = 0; j < 26; j++)
        {
            K[26 * i + j] = al[i];
            K[26 * i + j] = (K[26 * i + j] << 8) ^ al[j];
        }
    }

    clock_t start, end;
    double time_use;
    start = clock();
    uint16_t *k1, *k2, *k3, *k4, *max = K + 676;
    for (k1 = K; k1 < max; k1++)
        for (k2 = K; k2 < max; k2++)
            for (k3 = K; k3 < K + 1; k3++)
                for (k4 = K; k4 < K + 1; k4++)
                {
                    if ((S_[P_[S_[P_[S_[0x165C ^ *k1]] ^ *k2]] ^ *k3] ^ *k4) == 0xAD36)
                        if ((S_[P_[S_[P_[S_[0xA832 ^ *k1]] ^ *k2]] ^ *k3] ^ *k4) == 0x5B7D)
                            if ((S_[P_[S_[P_[S_[0x8336 ^ *k1]] ^ *k2]] ^ *k3] ^ *k4) == 0x8D6E)
                                if ((S_[P_[S_[P_[S_[0xA455 ^ *k1]] ^ *k2]] ^ *k3] ^ *k4) == 0x8734)
                                    if ((S_[P_[S_[P_[S_[0xA29D ^ *k1]] ^ *k2]] ^ *k3] ^ *k4) == 0x8F31)
                                        if ((S_[P_[S_[P_[S_[0x46B9 ^ *k1]] ^ *k2]] ^ *k3] ^ *k4) == 0x13B6)
                                            printf("\n%04X %04X %04X %04X", *k1, *k2, *k3, *k4);
                }
    end = clock();
    time_use = (double)(end - start) / CLOCKS_PER_SEC;
    printf("\ntimes: = %f ", time_use);
    printf("\n%c%c%c%c%c%c%c%c\n", 0x70, 0x72, 0x6F, 0x70, 0x65, 0x72, 0x74, 0x79);

}