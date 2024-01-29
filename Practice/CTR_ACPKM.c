#include "kuznyechik.h"

#define CTR_SIZE 16
//////////////////////////////////

void getHex(char *Path, uint8_t *dst, int size)
{
    FILE *file = fopen(Path, "rb");
    fread(dst, 1, size, file);
    fclose(file);
}

// 128 bit = 16 byte
void add_128(uint8_t *dst)
{
    int i = 15;
    uint16_t n = 1;
    while ((n != 0) && (i >= 0))
    {
        n += dst[i];
        dst[i] = n & 0xff;
        n >>= 8;
        i--;
    }
}

// size <= N
void ctr_kuznyechik_crypt(uint8_t *key, uint8_t *CTR, uint8_t *out, const uint8_t *in, int size)
{
    struct kuznyechik_ctx ctx;
    kuznyechik_set_key(&ctx, key, KUZNYECHIK_KEY_SIZE);

    int i = 0;
    uint8_t buff[16];
    while (i < (size - CTR_SIZE))
    {
        kuznyechik_encrypt(&ctx, buff, CTR);
        add_128(CTR);
        xor_byte_cpy(out + i, buff, in + i, CTR_SIZE);
        i += CTR_SIZE;
    }
    kuznyechik_encrypt(&ctx, buff, CTR);
    add_128(CTR);
    xor_byte_cpy(out + i, buff, in + i, size - i);
}

uint8_t D1[16] = {0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8a, 0x8b, 0x8c, 0x8d, 0x8e, 0x8f};
uint8_t D2[16] = {0x90, 0x91, 0x92, 0x93, 0x94, 0x95, 0x96, 0x97, 0x98, 0x99, 0x9a, 0x9b, 0x9c, 0x9d, 0x9e, 0x9f};

void ACPKM(uint8_t *K)
{
    uint8_t buff[KUZNYECHIK_KEY_SIZE];
    memcpy(buff, K, KUZNYECHIK_KEY_SIZE);
    struct kuznyechik_ctx ctx;
    kuznyechik_set_key(&ctx, buff, KUZNYECHIK_KEY_SIZE);
    kuznyechik_encrypt(&ctx, K, D1);
    kuznyechik_encrypt(&ctx, K + 16, D2);
}

void CTR_ACPKM(uint8_t *key, uint8_t *IV, uint8_t *out, const uint8_t *in, int N, int size)
{
    uint8_t CTR[KUZNYECHIK_BLOCK_SIZE];
    memset(CTR, 0, KUZNYECHIK_BLOCK_SIZE);
    memcpy(CTR, IV, KUZNYECHIK_BLOCK_SIZE / 2);

    int i = 0;
    while (i < (size - N))
    {
        ctr_kuznyechik_crypt(key, CTR, out + i, in + i, N);
        ACPKM(key);
        i = i + N;
    }
    ctr_kuznyechik_crypt(key, CTR, out + i, in + i, size - i);
}

void printHex(uint8_t *val, int size)
{
    for (int i = 0; i < size; i++)
    {
        printf("%02X ", val[i]);
    }
    printf("\n");
}

int main()
{
    uint8_t key[32];
    uint8_t IV[8];
    uint8_t M[7 * 16];
    getHex("key", key, 32);
    getHex("IV", IV, 8);
    getHex("M", M, 7 * 16);

    printHex(key, 32);
    printf("------------\n");
    printHex(IV, 8);
    printf("------------\n");
    for (int i = 0; i < 7; i++)
    {
        printHex(M + i * 16, 16);
    }
    uint8_t res[7 * 16];
    CTR_ACPKM(key, IV, res, M, 32, 7 * 16);

    printf("------------\n");
    for (int i = 0; i < 7; i++)
    {
        printHex(res + i * 16, 16);
    }
}
