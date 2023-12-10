#include "header.h"

static inline u8 byte(const u32 x, const unsigned n)
{
	return x >> (n << 3);
}

/**
 * crypto_aes_set_key - Set the AES key.
 * @tfm:	The %crypto_tfm that is used in the context.
 * @in_key:	The input key.
 * @key_len:	The size of the key.
 *
 * This function uses aes_expand_key() to expand the key.  &crypto_aes_ctx
 * _must_ be the private data embedded in @tfm which is retrieved with
 * crypto_tfm_ctx().
 *
 * Return: 0 on success; -EINVAL on failure (only happens for bad key lengths)
 */

// int crypto_aes_set_key(const u8 *in_key,
// 		unsigned int key_len)
// {
// 	struct crypto_aes_ctx *ctx;

// 	return aes_expandkey(ctx, in_key, key_len);
// }

/* encrypt a block of text */

#define f_rn(bo, bi, n, k)                                             \
	do                                                                 \
	{                                                                  \
		bo[n] = crypto_ft_tab[0][byte(bi[n], 0)] ^                     \
				crypto_ft_tab[1][byte(bi[(n + 1) & 3], 1)] ^           \
				crypto_ft_tab[2][byte(bi[(n + 2) & 3], 2)] ^           \
				crypto_ft_tab[3][byte(bi[(n + 3) & 3], 3)] ^ *(k + n); \
	} while (0)

#define f_nround(bo, bi, k) \
	do                      \
	{                       \
		f_rn(bo, bi, 0, k); \
		f_rn(bo, bi, 1, k); \
		f_rn(bo, bi, 2, k); \
		f_rn(bo, bi, 3, k); \
		k += 4;             \
	} while (0)

#define f_rl(bo, bi, n, k)                                             \
	do                                                                 \
	{                                                                  \
		bo[n] = crypto_fl_tab[0][byte(bi[n], 0)] ^                     \
				crypto_fl_tab[1][byte(bi[(n + 1) & 3], 1)] ^           \
				crypto_fl_tab[2][byte(bi[(n + 2) & 3], 2)] ^           \
				crypto_fl_tab[3][byte(bi[(n + 3) & 3], 3)] ^ *(k + n); \
	} while (0)

#define f_lround(bo, bi, k) \
	do                      \
	{                       \
		f_rl(bo, bi, 0, k); \
		f_rl(bo, bi, 1, k); \
		f_rl(bo, bi, 2, k); \
		f_rl(bo, bi, 3, k); \
	} while (0)



static void crypto_aes_encrypt(const struct crypto_aes_ctx *ctx, u8 *out, const u8 *in)
{
	u32 b0[4], b1[4];
	const u32 *kp = ctx->key_enc + 4;
	const int key_len = ctx->key_length;

	b0[0] = ctx->key_enc[0] ^ get_u32(in);
	b0[1] = ctx->key_enc[1] ^ get_u32(in + 4);
	b0[2] = ctx->key_enc[2] ^ get_u32(in + 8);
	b0[3] = ctx->key_enc[3] ^ get_u32(in + 12);

	if (key_len > 24)
	{
		f_nround(b1, b0, kp);
		f_nround(b0, b1, kp);
	}

	if (key_len > 16)
	{
		f_nround(b1, b0, kp);
		f_nround(b0, b1, kp);
	}

	f_nround(b1, b0, kp);
	f_nround(b0, b1, kp);
	f_nround(b1, b0, kp);
	f_nround(b0, b1, kp);
	f_nround(b1, b0, kp);
	f_nround(b0, b1, kp);
	f_nround(b1, b0, kp);
	f_nround(b0, b1, kp);
	f_nround(b1, b0, kp);
	f_lround(b0, b1, kp);

	put_u32(b0[0], out);
	put_u32(b0[1], out + 4);
	put_u32(b0[2], out + 8);
	put_u32(b0[3], out + 12);
}

/* decrypt a block of text */

#define i_rn(bo, bi, n, k)                                             \
	do                                                                 \
	{                                                                  \
		bo[n] = crypto_it_tab[0][byte(bi[n], 0)] ^                     \
				crypto_it_tab[1][byte(bi[(n + 3) & 3], 1)] ^           \
				crypto_it_tab[2][byte(bi[(n + 2) & 3], 2)] ^           \
				crypto_it_tab[3][byte(bi[(n + 1) & 3], 3)] ^ *(k + n); \
	} while (0)

#define i_nround(bo, bi, k) \
	do                      \
	{                       \
		i_rn(bo, bi, 0, k); \
		i_rn(bo, bi, 1, k); \
		i_rn(bo, bi, 2, k); \
		i_rn(bo, bi, 3, k); \
		k += 4;             \
	} while (0)

#define i_rl(bo, bi, n, k)                                             \
	do                                                                 \
	{                                                                  \
		bo[n] = crypto_il_tab[0][byte(bi[n], 0)] ^                     \
				crypto_il_tab[1][byte(bi[(n + 3) & 3], 1)] ^           \
				crypto_il_tab[2][byte(bi[(n + 2) & 3], 2)] ^           \
				crypto_il_tab[3][byte(bi[(n + 1) & 3], 3)] ^ *(k + n); \
	} while (0)

#define i_lround(bo, bi, k) \
	do                      \
	{                       \
		i_rl(bo, bi, 0, k); \
		i_rl(bo, bi, 1, k); \
		i_rl(bo, bi, 2, k); \
		i_rl(bo, bi, 3, k); \
	} while (0)

static void crypto_aes_decrypt(const struct crypto_aes_ctx *ctx, u8 *out, const u8 *in)
{
	u32 b0[4], b1[4];
	const int key_len = ctx->key_length;
	const u32 *kp = ctx->key_dec + 4;

	b0[0] = ctx->key_dec[0] ^ get_u32(in);
	b0[1] = ctx->key_dec[1] ^ get_u32(in + 4);
	b0[2] = ctx->key_dec[2] ^ get_u32(in + 8);
	b0[3] = ctx->key_dec[3] ^ get_u32(in + 12);

	if (key_len > 24)
	{
		i_nround(b1, b0, kp);
		i_nround(b0, b1, kp);
	}

	if (key_len > 16)
	{
		i_nround(b1, b0, kp);
		i_nround(b0, b1, kp);
	}

	i_nround(b1, b0, kp);
	i_nround(b0, b1, kp);
	i_nround(b1, b0, kp);
	i_nround(b0, b1, kp);
	i_nround(b1, b0, kp);
	i_nround(b0, b1, kp);
	i_nround(b1, b0, kp);
	i_nround(b0, b1, kp);
	i_nround(b1, b0, kp);
	i_lround(b0, b1, kp);

	put_u32(b0[0], out);
	put_u32(b0[1], out + 4);
	put_u32(b0[2], out + 8);
	put_u32(b0[3], out + 12);
}

int main()
{
	printf("hello\n");
	struct crypto_aes_ctx *ctx = malloc(sizeof(struct crypto_aes_ctx));
	unsigned int key_len = 128 / 8;
	u8 in_key[16] = {0x2b, 0x7e, 0x15, 0x16, 0x28, 0xae, 0xd2, 0xa6, 0xab, 0xf7, 0x15, 0x88, 0x09, 0xcf, 0x4f, 0x3c};
	u8 plain[16] = {0x6b, 0xc1, 0xbe, 0xe2, 0x2e, 0x40, 0x9f, 0x96, 0xe9, 0x3d, 0x7e, 0x11, 0x73, 0x93, 0x17, 0x2a};
	aes_expandkey(ctx, in_key, key_len);
}
