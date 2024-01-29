#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "kuztable.h"

#define KUZNYECHIK_KEY_SIZE 32
#define KUZNYECHIK_BLOCK_SIZE 16
#define KUZNYECHIK_SUBKEYS_SIZE (16 * 10)

struct kuznyechik_ctx
{
    uint8_t key[KUZNYECHIK_SUBKEYS_SIZE];
    uint8_t dekey[KUZNYECHIK_SUBKEYS_SIZE];
};

static void S(uint8_t *a, const uint8_t *b);

static void Sinv(uint8_t *a, const uint8_t *b);

static void Linv(uint8_t *a, const uint8_t *b);

static void LSX(uint8_t *a, const uint8_t *b, const uint8_t *c);

static void XLiSi(uint8_t *a, const uint8_t *b, const uint8_t *c);

static void subkey(uint8_t *out, const uint8_t *key, unsigned int i);

static int kuznyechik_set_key(struct kuznyechik_ctx *ctx, const uint8_t *in_key, unsigned int key_len);

static void kuznyechik_encrypt(const struct kuznyechik_ctx *ctx, uint8_t *out, const uint8_t *in);

/// @brief 
/// @param ctx 
/// @param out 
/// @param in 
static void kuznyechik_decrypt(const struct kuznyechik_ctx *ctx, uint8_t *out, const uint8_t *in);



void xor_byte(uint8_t *dst, const uint8_t *src, unsigned int size)
{
    int i = 0;
    for (; i < size; i++)
    {
        dst[i] ^= src[i];
    }
}

void xor_byte_cpy(uint8_t *dst, const uint8_t *src1, const uint8_t *src2, unsigned int size)
{
    int i = 0;
    for (; i < size; i++)
    {
        dst[i] = src1[i] ^ src2[i];
    }
}

/////////////////////////////
void S(uint8_t *a, const uint8_t *b)
{
    a[0] = pi[b[0]];
    a[1] = pi[b[1]];
    a[2] = pi[b[2]];
    a[3] = pi[b[3]];
    a[4] = pi[b[4]];
    a[5] = pi[b[5]];
    a[6] = pi[b[6]];
    a[7] = pi[b[7]];
    a[8] = pi[b[8]];
    a[9] = pi[b[9]];
    a[10] = pi[b[10]];
    a[11] = pi[b[11]];
    a[12] = pi[b[12]];
    a[13] = pi[b[13]];
    a[14] = pi[b[14]];
    a[15] = pi[b[15]];
}

void Sinv(uint8_t *a, const uint8_t *b)
{
    a[0] = pi_inv[b[0]];
    a[1] = pi_inv[b[1]];
    a[2] = pi_inv[b[2]];
    a[3] = pi_inv[b[3]];
    a[4] = pi_inv[b[4]];
    a[5] = pi_inv[b[5]];
    a[6] = pi_inv[b[6]];
    a[7] = pi_inv[b[7]];
    a[8] = pi_inv[b[8]];
    a[9] = pi_inv[b[9]];
    a[10] = pi_inv[b[10]];
    a[11] = pi_inv[b[11]];
    a[12] = pi_inv[b[12]];
    a[13] = pi_inv[b[13]];
    a[14] = pi_inv[b[14]];
    a[15] = pi_inv[b[15]];
}

void Linv(uint8_t *a, const uint8_t *b)
{
    memcpy(a, &kuz_table_inv[0][b[0] * 16], KUZNYECHIK_BLOCK_SIZE);
    xor_byte(a, &kuz_table_inv[1][b[1] * 16], KUZNYECHIK_BLOCK_SIZE);
    xor_byte(a, &kuz_table_inv[2][b[2] * 16], KUZNYECHIK_BLOCK_SIZE);
    xor_byte(a, &kuz_table_inv[3][b[3] * 16], KUZNYECHIK_BLOCK_SIZE);
    xor_byte(a, &kuz_table_inv[4][b[4] * 16], KUZNYECHIK_BLOCK_SIZE);
    xor_byte(a, &kuz_table_inv[5][b[5] * 16], KUZNYECHIK_BLOCK_SIZE);
    xor_byte(a, &kuz_table_inv[6][b[6] * 16], KUZNYECHIK_BLOCK_SIZE);
    xor_byte(a, &kuz_table_inv[7][b[7] * 16], KUZNYECHIK_BLOCK_SIZE);
    xor_byte(a, &kuz_table_inv[8][b[8] * 16], KUZNYECHIK_BLOCK_SIZE);
    xor_byte(a, &kuz_table_inv[9][b[9] * 16], KUZNYECHIK_BLOCK_SIZE);
    xor_byte(a, &kuz_table_inv[10][b[10] * 16], KUZNYECHIK_BLOCK_SIZE);
    xor_byte(a, &kuz_table_inv[11][b[11] * 16], KUZNYECHIK_BLOCK_SIZE);
    xor_byte(a, &kuz_table_inv[12][b[12] * 16], KUZNYECHIK_BLOCK_SIZE);
    xor_byte(a, &kuz_table_inv[13][b[13] * 16], KUZNYECHIK_BLOCK_SIZE);
    xor_byte(a, &kuz_table_inv[14][b[14] * 16], KUZNYECHIK_BLOCK_SIZE);
    xor_byte(a, &kuz_table_inv[15][b[15] * 16], KUZNYECHIK_BLOCK_SIZE);
}

void LSX(uint8_t *a, const uint8_t *b, const uint8_t *c)
{
    uint8_t t[16];

    memcpy(t, &kuz_table[0][(b[0] ^ c[0]) * 16], KUZNYECHIK_BLOCK_SIZE);
    xor_byte(t, &kuz_table[1][(b[1] ^ c[1]) * 16], KUZNYECHIK_BLOCK_SIZE);
    xor_byte(t, &kuz_table[2][(b[2] ^ c[2]) * 16], KUZNYECHIK_BLOCK_SIZE);
    xor_byte(t, &kuz_table[3][(b[3] ^ c[3]) * 16], KUZNYECHIK_BLOCK_SIZE);
    xor_byte(t, &kuz_table[4][(b[4] ^ c[4]) * 16], KUZNYECHIK_BLOCK_SIZE);
    xor_byte(t, &kuz_table[5][(b[5] ^ c[5]) * 16], KUZNYECHIK_BLOCK_SIZE);
    xor_byte(t, &kuz_table[6][(b[6] ^ c[6]) * 16], KUZNYECHIK_BLOCK_SIZE);
    xor_byte(t, &kuz_table[7][(b[7] ^ c[7]) * 16], KUZNYECHIK_BLOCK_SIZE);
    xor_byte(t, &kuz_table[8][(b[8] ^ c[8]) * 16], KUZNYECHIK_BLOCK_SIZE);
    xor_byte(t, &kuz_table[9][(b[9] ^ c[9]) * 16], KUZNYECHIK_BLOCK_SIZE);
    xor_byte(t, &kuz_table[10][(b[10] ^ c[10]) * 16], KUZNYECHIK_BLOCK_SIZE);
    xor_byte(t, &kuz_table[11][(b[11] ^ c[11]) * 16], KUZNYECHIK_BLOCK_SIZE);
    xor_byte(t, &kuz_table[12][(b[12] ^ c[12]) * 16], KUZNYECHIK_BLOCK_SIZE);
    xor_byte(t, &kuz_table[13][(b[13] ^ c[13]) * 16], KUZNYECHIK_BLOCK_SIZE);
    xor_byte(t, &kuz_table[14][(b[14] ^ c[14]) * 16], KUZNYECHIK_BLOCK_SIZE);
    xor_byte_cpy(a, t, &kuz_table[15][(b[15] ^ c[15]) * 16], KUZNYECHIK_BLOCK_SIZE);
}

void XLiSi(uint8_t *a, const uint8_t *b, const uint8_t *c)
{
    uint8_t t[16];

    memcpy(t, &kuz_table_inv_LS[0][b[0] * 16], KUZNYECHIK_BLOCK_SIZE);
    xor_byte(t, &kuz_table_inv_LS[1][b[1] * 16], KUZNYECHIK_BLOCK_SIZE);
    xor_byte(t, &kuz_table_inv_LS[2][b[2] * 16], KUZNYECHIK_BLOCK_SIZE);
    xor_byte(t, &kuz_table_inv_LS[3][b[3] * 16], KUZNYECHIK_BLOCK_SIZE);
    xor_byte(t, &kuz_table_inv_LS[4][b[4] * 16], KUZNYECHIK_BLOCK_SIZE);
    xor_byte(t, &kuz_table_inv_LS[5][b[5] * 16], KUZNYECHIK_BLOCK_SIZE);
    xor_byte(t, &kuz_table_inv_LS[6][b[6] * 16], KUZNYECHIK_BLOCK_SIZE);
    xor_byte(t, &kuz_table_inv_LS[7][b[7] * 16], KUZNYECHIK_BLOCK_SIZE);
    xor_byte(t, &kuz_table_inv_LS[8][b[8] * 16], KUZNYECHIK_BLOCK_SIZE);
    xor_byte(t, &kuz_table_inv_LS[9][b[9] * 16], KUZNYECHIK_BLOCK_SIZE);
    xor_byte(t, &kuz_table_inv_LS[10][b[10] * 16], KUZNYECHIK_BLOCK_SIZE);
    xor_byte(t, &kuz_table_inv_LS[11][b[11] * 16], KUZNYECHIK_BLOCK_SIZE);
    xor_byte(t, &kuz_table_inv_LS[12][b[12] * 16], KUZNYECHIK_BLOCK_SIZE);
    xor_byte(t, &kuz_table_inv_LS[13][b[13] * 16], KUZNYECHIK_BLOCK_SIZE);
    xor_byte(t, &kuz_table_inv_LS[14][b[14] * 16], KUZNYECHIK_BLOCK_SIZE);
    xor_byte(t, &kuz_table_inv_LS[15][b[15] * 16], KUZNYECHIK_BLOCK_SIZE);
    xor_byte_cpy(a, t, c, 16);
}

void subkey(uint8_t *out, const uint8_t *key, unsigned int i)
{
    uint8_t test[16];

    LSX(test, key + 0, kuz_key_table[i + 0]);
    xor_byte_cpy(out + 16, test, key + 16, 16);
    LSX(test, out + 16, kuz_key_table[i + 1]);
    xor_byte_cpy(out + 0, test, key + 0, 16);
    LSX(test, out + 0, kuz_key_table[i + 2]);
    xor_byte(out + 16, test, 16);
    LSX(test, out + 16, kuz_key_table[i + 3]);
    xor_byte(out + 0, test, 16);
    LSX(test, out + 0, kuz_key_table[i + 4]);
    xor_byte(out + 16, test, 16);
    LSX(test, out + 16, kuz_key_table[i + 5]);
    xor_byte(out + 0, test, 16);
    LSX(test, out + 0, kuz_key_table[i + 6]);
    xor_byte(out + 16, test, 16);
    LSX(test, out + 16, kuz_key_table[i + 7]);
    xor_byte(out + 0, test, 16);
}

/////////////////////////
int kuznyechik_set_key(struct kuznyechik_ctx *ctx, const uint8_t *in_key, unsigned int key_len)
{
    unsigned int i;

    memcpy(ctx->key, in_key, 32);
    subkey(ctx->key + 32, ctx->key, 0);
    subkey(ctx->key + 64, ctx->key + 32, 8);
    subkey(ctx->key + 96, ctx->key + 64, 16);
    subkey(ctx->key + 128, ctx->key + 96, 24);
    for (i = 0; i < 10; i++)
        Linv(ctx->dekey + 16 * i, ctx->key + 16 * i);

    return 0;
}

void kuznyechik_encrypt(const struct kuznyechik_ctx *ctx, uint8_t *out, const uint8_t *in)
{
    uint8_t temp[KUZNYECHIK_BLOCK_SIZE];

    LSX(temp, ctx->key + 16 * 0, in);
    LSX(temp, ctx->key + 16 * 1, temp);
    LSX(temp, ctx->key + 16 * 2, temp);
    LSX(temp, ctx->key + 16 * 3, temp);
    LSX(temp, ctx->key + 16 * 4, temp);
    LSX(temp, ctx->key + 16 * 5, temp);
    LSX(temp, ctx->key + 16 * 6, temp);
    LSX(temp, ctx->key + 16 * 7, temp);
    LSX(temp, ctx->key + 16 * 8, temp);
    xor_byte_cpy(out, ctx->key + 16 * 9, temp, 16);
}

void kuznyechik_decrypt(const struct kuznyechik_ctx *ctx, uint8_t *out, const uint8_t *in)
{
    uint8_t temp[KUZNYECHIK_BLOCK_SIZE];

    S(temp, in);
    XLiSi(temp, temp, ctx->dekey + 16 * 9);
    XLiSi(temp, temp, ctx->dekey + 16 * 8);
    XLiSi(temp, temp, ctx->dekey + 16 * 7);
    XLiSi(temp, temp, ctx->dekey + 16 * 6);
    XLiSi(temp, temp, ctx->dekey + 16 * 5);
    XLiSi(temp, temp, ctx->dekey + 16 * 4);
    XLiSi(temp, temp, ctx->dekey + 16 * 3);
    XLiSi(temp, temp, ctx->dekey + 16 * 2);
    XLiSi(temp, temp, ctx->dekey + 16 * 1);
    Sinv(out, temp);
    xor_byte(out, ctx->key + 16 * 0, 16);
}