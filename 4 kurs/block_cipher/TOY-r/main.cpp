#include <cstdlib>
#include <cstdio>
#include <cstdint>
#include <ctime>

// number of round
#define r 3

// block 16-bit
// key : k0,..,kr = (r+1)*16

// uint8_t pi[16] = {0x8, 0x5, 0x6, 0xe, 0x7, 0x0, 0xf, 0x2, 0xa, 0x9, 0x3, 0xc, 0xb, 0xd, 0x1, 0x4};
uint8_t pi[16] = {5, 2, 6, 8, 1, 0xd, 7, 0xe, 4, 0xf, 0xc, 0xa, 0xb, 3, 0, 9};
uint8_t pi_1[16] = {0};
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

void S_1(uint16_t &x)
{
    uint16_t res = 0;
    for (int i = 0; i < 4; i++)
    {
        res ^= ((pi_1[(x >> (4 * i)) & 0xf]) << (4 * i));
    }
    x = res;
}

#define bit(x, n) ((x >> n) & 1)
void P(uint16_t &x)
{
    uint16_t res = 0;
    for (int i = 0; i < 16; i++)
    {
        res ^= ((bit(x, (15 - p[15 - i]))) << i);
    }
    x = res;
}

// k0 ... kr
void encryptTOYr(uint16_t &pt, uint16_t *key)
{
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

void decryptTOYr(uint16_t &pt, uint16_t *key)
{
    X(pt, key[r]);
    S_1(pt);
    X(pt, key[r - 1]);
    for (int i = 0; i < (r - 1); i++)
    {
        P(pt);
        S_1(pt);
        X(pt, key[r - 2 - i]);
    }
}

int main()
{
    // /// pi_13
    // FILE *data = fopen("pi_13", "rb");
    // for (int i = 0; i < 16; i++)
    // {
    //     int x = fscanf(data, "%1hhx", &pi[i]);
    // }
    for (int i = 0; i < 16; i++)
    {
        printf("%x ", pi[i]);
        pi_1[pi[i]] = i;
    }

    uint16_t key0[4] = {0x3D21, 0x9A6D, 0x8070, 0xABA6};
    uint16_t pt0[5] = {0xD16B, 0xF9F1, 0x1750, 0xE054, 0x717A};
    uint16_t ct0[5] = {0x7DE2, 0xA9E0, 0xFEBF, 0xB22B, 0x0A43};
    for (int i = 0; i < 5; i++)
    {
        encryptTOYr(pt0[i], key0);
        printf("\n%04X ", pt0[i]);
    }
    uint16_t key[4] = {0};
    uint16_t pt[6] = {0x165C, 0xA832, 0x8336, 0xA455, 0xA29D, 0x46B9};
    uint16_t ct[6] = {0xAD36, 0x5B7D, 0x8D6E, 0x8734, 0x8F31, 0x13B6};

    uint8_t al[26] = {0};
    for (int i = 0; i < 26; i++)
    {
        al[26] = 61 + i;
    }
    clock_t start, end;
    double time_use;
    start = clock();
    int i1, i2, i3, i4, i5, i6, i7, i8;
    for (i1 = 0; i1 < 26; i1++)
        for (i2 = 0; i2 < 26; i2++)
            for (i3 = 0; i3 < 26; i3++)
                for (i4 = 0; i4 < 26; i4++)
                    for (i5 = 0; i5 < 26; i5++)
                        for (i6 = 0; i6 < 1; i6++)
                            for (i7 = 0; i7 < 1; i7++)
                                for (i8 = 0; i8 < 1; i8++)
                                {
                                    key[0] = al[i1];
                                    key[0] = (key[0] << 8) ^ al[i2];
                                    key[1] = al[i3];
                                    key[1] = (key[0] << 8) ^ al[i4];
                                    key[2] = al[i5];
                                    key[2] = (key[0] << 8) ^ al[i6];
                                    key[3] = al[i7];
                                    key[3] = (key[0] << 8) ^ al[i8];
                                    encryptTOYr(pt[0], key);
                                    if (pt[0] == ct[0])
                                    {
                                        encryptTOYr(pt[1], key);
                                        if (pt[1] == ct[1])
                                        {
                                            encryptTOYr(pt[2], key);
                                            if (pt[2] == ct[2])
                                            {
                                                printf("\n%04X %04X %04X %04X", key[0], key[1], key[2], key[3]);
                                            }
                                        }
                                    }
                                }
    end = clock();
    time_use = (double)(end - start) / CLOCKS_PER_SEC;
    printf("\ntimes:  %f ", time_use);

}