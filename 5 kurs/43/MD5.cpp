#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <string>
#include <string.h>

// little endian computer
#define LITTLE_ENDIAN

#ifdef LITTLE_ENDIAN
// length: number of 32bit word
#define byteReverse32(buffer, length) // Nothing
#else
// length: number of 32bit word
static void byteReverse32(unsigned char *buffer, int length);

// Note: this code is harmless on little-endian machines.
static void byteReverse32(unsigned char *buffer, int length)
{
    uint32_t t;
    do
    {
        t = __builtin_bswap32(*(uint32_t *)buffer);
        *(uint32_t *)buffer = t;
        buffer += 4;
    } while (--length);
}
#endif

// byte -> little endian (only on 32 bit word)
// all in byte
// 64 bit - 16 byte of size(number of bit): s15 ... s8 s7 ...s0
// messenger    a  b ....
//"abc..." ->   m0 m1 ... after padding:

// m0 m1 ... PADDING[0] PADDING[1].... s0 .. s7 s8 ...s15
// trans to little endian (32bit words)
// | m7 .. m0 |... | s7 .. s0 | |s15 ..s8|
// MD5Transform -> state[0] .. state[3]
// trans state to big endian => [0] [1] [2] [3] = (in byte) =
// res = digest[0]..digest[16] in byte

#define F1(x, y, z) (x & y | (~x) & z)
#define F2(x, y, z) (x & z | y & (~z))
#define F3(x, y, z) (x ^ y ^ z)
#define F4(x, y, z) (y ^ (x | (~z)))

#define MD5Step(f, a, b, c, d, x, k, s) \
    {                                   \
        a += f(b, c, d) + x + k;        \
        a = (a << s) ^ (a >> (32 - s)); \
        a += b;                         \
    }
// 1n0 0000 .. 512 bit
static uint8_t PADDING[] = {0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

struct MD5Context
{
    // state of h
    uint32_t state[4];
    // 512 bit of input
    uint8_t input[64];
    // number of input-bit
    uint64_t size;
};

void MD5Initialize(struct MD5Context &ctx)
{
    ctx.state[0] = 0x67452301;
    ctx.state[1] = 0xefcdab89;
    ctx.state[2] = 0x98badcfe;
    ctx.state[3] = 0x10325476;
}

// state-4, X-16
void MD5Transform(uint32_t state[4], uint32_t X[16])
{
    uint32_t a, b, c, d;
    a = state[0];
    b = state[1];
    c = state[2];
    d = state[3];
    // round 1
    MD5Step(F1, a, b, c, d, X[0], 0xd76aa478, 7);
    MD5Step(F1, d, a, b, c, X[1], 0xe8c7b756, 12);
    MD5Step(F1, c, d, a, b, X[2], 0x242070db, 17);
    MD5Step(F1, b, c, d, a, X[3], 0xc1bdceee, 22);
    MD5Step(F1, a, b, c, d, X[4], 0xf57c0faf, 7);
    MD5Step(F1, d, a, b, c, X[5], 0x4787c62a, 12);
    MD5Step(F1, c, d, a, b, X[6], 0xa8304613, 17);
    MD5Step(F1, b, c, d, a, X[7], 0xfd469501, 22);
    MD5Step(F1, a, b, c, d, X[8], 0x698098d8, 7);
    MD5Step(F1, d, a, b, c, X[9], 0x8b44f7af, 12);
    MD5Step(F1, c, d, a, b, X[10], 0xffff5bb1, 17);
    MD5Step(F1, b, c, d, a, X[11], 0x895cd7be, 22);
    MD5Step(F1, a, b, c, d, X[12], 0x6b901122, 7);
    MD5Step(F1, d, a, b, c, X[13], 0xfd987193, 12);
    MD5Step(F1, c, d, a, b, X[14], 0xa679438e, 17);
    MD5Step(F1, b, c, d, a, X[15], 0x49b40821, 22);

    // round 2
    MD5Step(F2, a, b, c, d, X[1], 0xf61e2562, 5);
    MD5Step(F2, d, a, b, c, X[6], 0xc040b340, 9);
    MD5Step(F2, c, d, a, b, X[11], 0x265e5a51, 14);
    MD5Step(F2, b, c, d, a, X[0], 0xe9b6c7aa, 20);
    MD5Step(F2, a, b, c, d, X[5], 0xd62f105d, 5);
    MD5Step(F2, d, a, b, c, X[10], 0x02441453, 9);
    MD5Step(F2, c, d, a, b, X[15], 0xd8a1e681, 14);
    MD5Step(F2, b, c, d, a, X[4], 0xe7d3fbc8, 20);
    MD5Step(F2, a, b, c, d, X[9], 0x21e1cde6, 5);
    MD5Step(F2, d, a, b, c, X[14], 0xc33707d6, 9);
    MD5Step(F2, c, d, a, b, X[3], 0xf4d50d87, 14);
    MD5Step(F2, b, c, d, a, X[8], 0x455a14ed, 20);
    MD5Step(F2, a, b, c, d, X[13], 0xa9e3e905, 5);
    MD5Step(F2, d, a, b, c, X[2], 0xfcefa3f8, 9);
    MD5Step(F2, c, d, a, b, X[7], 0x676f02d9, 14);
    MD5Step(F2, b, c, d, a, X[12], 0x8d2a4c8a, 20);

    // round 3
    MD5Step(F3, a, b, c, d, X[5], 0xfffa3942, 4);
    MD5Step(F3, d, a, b, c, X[8], 0x8771f681, 11);
    MD5Step(F3, c, d, a, b, X[11], 0x6d9d6122, 16);
    MD5Step(F3, b, c, d, a, X[14], 0xfde5380c, 23);
    MD5Step(F3, a, b, c, d, X[1], 0xa4beea44, 4);
    MD5Step(F3, d, a, b, c, X[4], 0x4bdecfa9, 11);
    MD5Step(F3, c, d, a, b, X[7], 0xf6bb4b60, 16);
    MD5Step(F3, b, c, d, a, X[10], 0xbebfbc70, 23);
    MD5Step(F3, a, b, c, d, X[13], 0x289b7ec6, 4);
    MD5Step(F3, d, a, b, c, X[0], 0xeaa127fa, 11);
    MD5Step(F3, c, d, a, b, X[3], 0xd4ef3085, 16);
    MD5Step(F3, b, c, d, a, X[6], 0x04881d05, 23);
    MD5Step(F3, a, b, c, d, X[9], 0xd9d4d039, 4);
    MD5Step(F3, d, a, b, c, X[12], 0xe6db99e5, 11);
    MD5Step(F3, c, d, a, b, X[15], 0x1fa27cf8, 16);
    MD5Step(F3, b, c, d, a, X[2], 0xc4ac5665, 23);

    // round 4
    MD5Step(F4, a, b, c, d, X[0], 0xf4292244, 6);
    MD5Step(F4, d, a, b, c, X[7], 0x432aff97, 10);
    MD5Step(F4, c, d, a, b, X[14], 0xab9423a7, 15);
    MD5Step(F4, b, c, d, a, X[5], 0xfc93a039, 21);
    MD5Step(F4, a, b, c, d, X[12], 0x655b59c3, 6);
    MD5Step(F4, d, a, b, c, X[3], 0x8f0ccc92, 10);
    MD5Step(F4, c, d, a, b, X[10], 0xffeff47d, 15);
    MD5Step(F4, b, c, d, a, X[1], 0x85845dd1, 21);
    MD5Step(F4, a, b, c, d, X[8], 0x6fa87e4f, 6);
    MD5Step(F4, d, a, b, c, X[15], 0xfe2ce6e0, 10);
    MD5Step(F4, c, d, a, b, X[6], 0xa3014314, 15);
    MD5Step(F4, b, c, d, a, X[13], 0x4e0811a1, 21);
    MD5Step(F4, a, b, c, d, X[4], 0xf7537e82, 6);
    MD5Step(F4, d, a, b, c, X[11], 0xbd3af235, 10);
    MD5Step(F4, c, d, a, b, X[2], 0x2ad7d2bb, 15);
    MD5Step(F4, b, c, d, a, X[9], 0xeb86d391, 21);

    state[0] += a;
    state[1] += b;
    state[2] += c;
    state[3] += d;
}

// 0 1 2 3 .....
// length in byte
void MD5(uint8_t digest[16], uint8_t *messenger, uint64_t length)
{
    MD5Context ctx;
    MD5Initialize(ctx);
    ctx.size = (uint64_t)length * 8;

    while (length >= 64)
    {
        memcpy(ctx.input, messenger, 64);
        byteReverse32(ctx.input, 16);
        MD5Transform(ctx.state, (uint32_t *)ctx.input);
        // next input 64*8 =512
        messenger += 64;
        length -= 64;
    }
    // length of input (byte) < 64
    memcpy(ctx.input, messenger, length);

    // pad to 448/512 (56/64)
    if (length >= 56)
    {
        // padding to 64byte -512 bit
        memcpy(ctx.input + length, PADDING, 64 - length);
        byteReverse32(ctx.input, 16);
        MD5Transform(ctx.state, (uint32_t *)ctx.input);
        memset(ctx.input, 0, 56);
    }
    else // length < 56
    {
        memcpy(ctx.input + length, PADDING, 56 - length);
    }

    // add 64 bit (8 byte) of size
    for (int i = 0; i < 4; i++)
    {
        ctx.input[56 + i] = (ctx.size >> (8 * i)) & 0xff;
        ctx.input[60 + i] = (ctx.size >> (32 + 8 * i)) & 0xff;
    }

    byteReverse32(ctx.input, 16);
    MD5Transform(ctx.state, (uint32_t *)ctx.input);
    memcpy(digest, ctx.state, 16);
}

uint32_t MD5New(uint8_t *messenger, uint64_t length)
{
    uint32_t res = 0;
    uint8_t digest[16];
    MD5(digest, messenger, length);
    res = (digest[0] ^ digest[4] ^ digest[8] ^ digest[12]) << 24;
    res ^= (digest[1] ^ digest[5] ^ digest[9] ^ digest[13]) << 16;
    res ^= (digest[2] ^ digest[6] ^ digest[10] ^ digest[14]) << 8;
    res ^= (digest[3] ^ digest[7] ^ digest[11] ^ digest[15]);
    return res;
}

int main()
{
    // space = 0x20
    std::string mess = "Ву Ба Зань, к зачету необходимо готовится";
    std::string mess_ = "Ву Ба Зань, вам зачет автомат";
    int l = mess.size();
    int l_ = mess_.size();

    int n = 100000;
    uint8_t m[l + n - 1];
    uint8_t m_[l_ + n - 1];

    uint32_t h[n];
    uint32_t h_[n];

    memcpy(m, mess.c_str(), l);
    memset(m + l, 0x20, n - 1);

    memcpy(m_, mess_.c_str(), l_);
    memset(m_ + l_, 0x20, n - 1);

    for (int i = 0; i < n; i++)
    {
        h[i] = MD5New(m, l + i);
        h_[i] = MD5New(m_, l_ + i);
    }
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (h[i] == h_[j])
            {
                printf("i = %d, j = %d", i, j);
            }
        }
    }

    return 0;
}