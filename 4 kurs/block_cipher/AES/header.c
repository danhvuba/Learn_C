#include"header.h"

static u32 mul_by_x(u32 w)
{
	u32 x = w & 0x7f7f7f7f;
	u32 y = w & 0x80808080;

	/* multiply by polynomial 'x' (0b10) in GF(2^8) */
	return (x << 1) ^ (y >> 7) * 0x1b;
}

static u32 mul_by_x2(u32 w)
{
	u32 x = w & 0x3f3f3f3f;
	u32 y = w & 0x80808080;
	u32 z = w & 0x40404040;

	/* multiply by polynomial 'x^2' (0b100) in GF(2^8) */
	return (x << 2) ^ (y >> 7) * 0x36 ^ (z >> 6) * 0x1b;
}

static u32 mix_columns(u32 x)
{
	/*
	 * Perform the following matrix multiplication in GF(2^8)
	 *
	 * | 0x2 0x3 0x1 0x1 |   | x[0] |
	 * | 0x1 0x2 0x3 0x1 |   | x[1] |
	 * | 0x1 0x1 0x2 0x3 | x | x[2] |
	 * | 0x3 0x1 0x1 0x2 |   | x[3] |
	 */
	u32 y = mul_by_x(x) ^ ror32(x, 16);

	return y ^ ror32(x ^ y, 8);
}

static u32 inv_mix_columns(u32 x)
{
	/*
	 * Perform the following matrix multiplication in GF(2^8)
	 *
	 * | 0xe 0xb 0xd 0x9 |   | x[0] |
	 * | 0x9 0xe 0xb 0xd |   | x[1] |
	 * | 0xd 0x9 0xe 0xb | x | x[2] |
	 * | 0xb 0xd 0x9 0xe |   | x[3] |
	 *
	 * which can conveniently be reduced to
	 *
	 * | 0x2 0x3 0x1 0x1 |   | 0x5 0x0 0x4 0x0 |   | x[0] |
	 * | 0x1 0x2 0x3 0x1 |   | 0x0 0x5 0x0 0x4 |   | x[1] |
	 * | 0x1 0x1 0x2 0x3 | x | 0x4 0x0 0x5 0x0 | x | x[2] |
	 * | 0x3 0x1 0x1 0x2 |   | 0x0 0x4 0x0 0x5 |   | x[3] |
	 */
	u32 y = mul_by_x2(x);

	return mix_columns(x ^ y ^ ror32(y, 16));
}

static u32 subshift(u32 in[], int pos)
{
	return (aes_sbox[in[pos] & 0xff]) ^
	       (aes_sbox[(in[(pos + 1) % 4] >>  8) & 0xff] <<  8) ^
	       (aes_sbox[(in[(pos + 2) % 4] >> 16) & 0xff] << 16) ^
	       (aes_sbox[(in[(pos + 3) % 4] >> 24) & 0xff] << 24);
}

static u32 inv_subshift(u32 in[], int pos)
{
	return (aes_inv_sbox[in[pos] & 0xff]) ^
	       (aes_inv_sbox[(in[(pos + 3) % 4] >>  8) & 0xff] <<  8) ^
	       (aes_inv_sbox[(in[(pos + 2) % 4] >> 16) & 0xff] << 16) ^
	       (aes_inv_sbox[(in[(pos + 1) % 4] >> 24) & 0xff] << 24);
}

static u32 subw(u32 in)
{
	return (aes_sbox[in & 0xff]) ^
	       (aes_sbox[(in >>  8) & 0xff] <<  8) ^
	       (aes_sbox[(in >> 16) & 0xff] << 16) ^
	       (aes_sbox[(in >> 24) & 0xff] << 24);
}

/**
 * aes_expandkey - Expands the AES key as described in FIPS-197
 * @ctx:	The location where the computed key will be stored.
 * @in_key:	The supplied key.
 * @key_len:	The length of the supplied key.
 *
 * Returns 0 on success. The function fails only if an invalid key size (or
 * pointer) is supplied.
 * The expanded key size is 240 bytes (max of 14 rounds with a unique 16 bytes
 * key schedule plus a 16 bytes key which is used before the first round).
 * The decryption key is prepared for the "Equivalent Inverse Cipher" as
 * described in FIPS-197. The first slot (16 bytes) of each key (enc or dec) is
 * for the initial combination, the second slot for the first round and so on.
 */
int aes_expandkey(struct crypto_aes_ctx *ctx, const u8 *in_key,
		  unsigned int key_len)
{
	u32 kwords = key_len / sizeof(u32);
	u32 rc, i, j;
	int err;

	err = aes_check_keylen(key_len);
	if (err)
		return err;

	ctx->key_length = key_len;

	for (i = 0; i < kwords; i++)
		ctx->key_enc[i] = get_u32(in_key + i * sizeof(u32));

	for (i = 0, rc = 1; i < 10; i++, rc = mul_by_x(rc)) {
		u32 *rki = ctx->key_enc + (i * kwords);
		u32 *rko = rki + kwords;

		rko[0] = ror32(subw(rki[kwords - 1]), 8) ^ rc ^ rki[0];
		rko[1] = rko[0] ^ rki[1];
		rko[2] = rko[1] ^ rki[2];
		rko[3] = rko[2] ^ rki[3];

		if (key_len == AES_KEYSIZE_192) {
			if (i >= 7)
				break;
			rko[4] = rko[3] ^ rki[4];
			rko[5] = rko[4] ^ rki[5];
		} else if (key_len == AES_KEYSIZE_256) {
			if (i >= 6)
				break;
			rko[4] = subw(rko[3]) ^ rki[4];
			rko[5] = rko[4] ^ rki[5];
			rko[6] = rko[5] ^ rki[6];
			rko[7] = rko[6] ^ rki[7];
		}
	}

	/*
	 * Generate the decryption keys for the Equivalent Inverse Cipher.
	 * This involves reversing the order of the round keys, and applying
	 * the Inverse Mix Columns transformation to all but the first and
	 * the last one.
	 */
	ctx->key_dec[0] = ctx->key_enc[key_len + 24];
	ctx->key_dec[1] = ctx->key_enc[key_len + 25];
	ctx->key_dec[2] = ctx->key_enc[key_len + 26];
	ctx->key_dec[3] = ctx->key_enc[key_len + 27];

	for (i = 4, j = key_len + 20; j > 0; i += 4, j -= 4) {
		ctx->key_dec[i]     = inv_mix_columns(ctx->key_enc[j]);
		ctx->key_dec[i + 1] = inv_mix_columns(ctx->key_enc[j + 1]);
		ctx->key_dec[i + 2] = inv_mix_columns(ctx->key_enc[j + 2]);
		ctx->key_dec[i + 3] = inv_mix_columns(ctx->key_enc[j + 3]);
	}

	ctx->key_dec[i]     = ctx->key_enc[0];
	ctx->key_dec[i + 1] = ctx->key_enc[1];
	ctx->key_dec[i + 2] = ctx->key_enc[2];
	ctx->key_dec[i + 3] = ctx->key_enc[3];

	return 0;
}

/**
 * aes_encrypt - Encrypt a single AES block
 * @ctx:	Context struct containing the key schedule
 * @out:	Buffer to store the ciphertext
 * @in:		Buffer containing the plaintext
 */
void aes_encrypt(const struct crypto_aes_ctx *ctx, u8 *out, const u8 *in)
{
	const u32 *rkp = ctx->key_enc + 4;
	int rounds = 6 + ctx->key_length / 4;
	u32 st0[4], st1[4];
	int round;

	st0[0] = ctx->key_enc[0] ^ get_u32(in);
	st0[1] = ctx->key_enc[1] ^ get_u32(in + 4);
	st0[2] = ctx->key_enc[2] ^ get_u32(in + 8);
	st0[3] = ctx->key_enc[3] ^ get_u32(in + 12);

	/*
	 * Force the compiler to emit data independent Sbox references,
	 * by xoring the input with Sbox values that are known to add up
	 * to zero. This pulls the entire Sbox into the D-cache before any
	 * data dependent lookups are done.
	 */
	st0[0] ^= aes_sbox[ 0] ^ aes_sbox[ 64] ^ aes_sbox[134] ^ aes_sbox[195];
	st0[1] ^= aes_sbox[16] ^ aes_sbox[ 82] ^ aes_sbox[158] ^ aes_sbox[221];
	st0[2] ^= aes_sbox[32] ^ aes_sbox[ 96] ^ aes_sbox[160] ^ aes_sbox[234];
	st0[3] ^= aes_sbox[48] ^ aes_sbox[112] ^ aes_sbox[186] ^ aes_sbox[241];

	for (round = 0;; round += 2, rkp += 8) {
		st1[0] = mix_columns(subshift(st0, 0)) ^ rkp[0];
		st1[1] = mix_columns(subshift(st0, 1)) ^ rkp[1];
		st1[2] = mix_columns(subshift(st0, 2)) ^ rkp[2];
		st1[3] = mix_columns(subshift(st0, 3)) ^ rkp[3];

		if (round == rounds - 2)
			break;

		st0[0] = mix_columns(subshift(st1, 0)) ^ rkp[4];
		st0[1] = mix_columns(subshift(st1, 1)) ^ rkp[5];
		st0[2] = mix_columns(subshift(st1, 2)) ^ rkp[6];
		st0[3] = mix_columns(subshift(st1, 3)) ^ rkp[7];
	}

	put_u32(subshift(st1, 0) ^ rkp[4], out);
	put_u32(subshift(st1, 1) ^ rkp[5], out + 4);
	put_u32(subshift(st1, 2) ^ rkp[6], out + 8);
	put_u32(subshift(st1, 3) ^ rkp[7], out + 12);
}

/**
 * aes_decrypt - Decrypt a single AES block
 * @ctx:	Context struct containing the key schedule
 * @out:	Buffer to store the plaintext
 * @in:		Buffer containing the ciphertext
 */
void aes_decrypt(const struct crypto_aes_ctx *ctx, u8 *out, const u8 *in)
{
	const u32 *rkp = ctx->key_dec + 4;
	int rounds = 6 + ctx->key_length / 4;
	u32 st0[4], st1[4];
	int round;

	st0[0] = ctx->key_dec[0] ^ get_u32(in);
	st0[1] = ctx->key_dec[1] ^ get_u32(in + 4);
	st0[2] = ctx->key_dec[2] ^ get_u32(in + 8);
	st0[3] = ctx->key_dec[3] ^ get_u32(in + 12);

	/*
	 * Force the compiler to emit data independent Sbox references,
	 * by xoring the input with Sbox values that are known to add up
	 * to zero. This pulls the entire Sbox into the D-cache before any
	 * data dependent lookups are done.
	 */
	st0[0] ^= aes_inv_sbox[ 0] ^ aes_inv_sbox[ 64] ^ aes_inv_sbox[129] ^ aes_inv_sbox[200];
	st0[1] ^= aes_inv_sbox[16] ^ aes_inv_sbox[ 83] ^ aes_inv_sbox[150] ^ aes_inv_sbox[212];
	st0[2] ^= aes_inv_sbox[32] ^ aes_inv_sbox[ 96] ^ aes_inv_sbox[160] ^ aes_inv_sbox[236];
	st0[3] ^= aes_inv_sbox[48] ^ aes_inv_sbox[112] ^ aes_inv_sbox[187] ^ aes_inv_sbox[247];

	for (round = 0;; round += 2, rkp += 8) {
		st1[0] = inv_mix_columns(inv_subshift(st0, 0)) ^ rkp[0];
		st1[1] = inv_mix_columns(inv_subshift(st0, 1)) ^ rkp[1];
		st1[2] = inv_mix_columns(inv_subshift(st0, 2)) ^ rkp[2];
		st1[3] = inv_mix_columns(inv_subshift(st0, 3)) ^ rkp[3];

		if (round == rounds - 2)
			break;

		st0[0] = inv_mix_columns(inv_subshift(st1, 0)) ^ rkp[4];
		st0[1] = inv_mix_columns(inv_subshift(st1, 1)) ^ rkp[5];
		st0[2] = inv_mix_columns(inv_subshift(st1, 2)) ^ rkp[6];
		st0[3] = inv_mix_columns(inv_subshift(st1, 3)) ^ rkp[7];
	}

	put_u32(inv_subshift(st1, 0) ^ rkp[4], out);
	put_u32(inv_subshift(st1, 1) ^ rkp[5], out + 4);
	put_u32(inv_subshift(st1, 2) ^ rkp[6], out + 8);
	put_u32(inv_subshift(st1, 3) ^ rkp[7], out + 12);
}
