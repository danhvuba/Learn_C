#include "matrixBit.h"

const uint64_t AStree[64] =
    {0x8e20faa72ba0b470, 0x47107ddd9b505a38, 0xad08b0e0c3282d1c, 0xd8045870ef14980e,
     0x6c022c38f90a4c07, 0x3601161cf205268d, 0x1b8e0b0e798c13c8, 0x83478b07b2468764,
     0xa011d380818e8f40, 0x5086e740ce47c920, 0x2843fd2067adea10, 0x14aff010bdd87508,
     0x0ad97808d06cb404, 0x05e23c0468365a02, 0x8c711e02341b2d01, 0x46b60f011a83988e,
     0x90dab52a387ae76f, 0x486dd4151c3dfdb9, 0x24b86a840e90f0d2, 0x125c354207487869,
     0x092e94218d243cba, 0x8a174a9ec8121e5d, 0x4585254f64090fa0, 0xaccc9ca9328a8950,
     0x9d4df05d5f661451, 0xc0a878a0a1330aa6, 0x60543c50de970553, 0x302a1e286fc58ca7,
     0x18150f14b9ec46dd, 0x0c84890ad27623e0, 0x0642ca05693b9f70, 0x0321658cba93c138,
     0x86275df09ce8aaa8, 0x439da0784e745554, 0xafc0503c273aa42a, 0xd960281e9d1d5215,
     0xe230140fc0802984, 0x71180a8960409a42, 0xb60c05ca30204d21, 0x5b068c651810a89e,
     0x456c34887a3805b9, 0xac361a443d1c8cd2, 0x561b0d22900e4669, 0x2b838811480723ba,
     0x9bcf4486248d9f5d, 0xc3e9224312c8c1a0, 0xeffa11af0964ee50, 0xf97d86d98a327728,
     0xe4fa2054a80b329c, 0x727d102a548b194e, 0x39b008152acb8227, 0x9258048415eb419d,
     0x492c024284fbaec0, 0xaa16012142f35760, 0x550b8e9e21f7a530, 0xa48b474f9ef5dc18,
     0x70a6a56e2440598e, 0x3853dc371220a247, 0x1ca76e95091051ad, 0x0edd37c48a08a6d8,
     0x07e095624504536c, 0x8d70c431ac02a736, 0xc83862965601dd1b, 0x641c314b2b8ee083};

uint64_t mul_table[8][256];

void set_mul_table()
{
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 256; j++)
        {
            uint64_t t = 0;
            // u8: a[0] <-> A[56 .. 63]
            for (int k = 0; k < 8; k++)
            {
                if (((j >> k) & 1))
                {
                    // 63 -8i -k =63 - (i<<3)|k
                    t ^= AStree[63 - (8 * i + k)];
                }
            }
            mul_table[i][j] = t;
        }
    }
}

int w64(uint64_t x)
{
    int res = 0;
    // 1
    res += (x & 0xff) == 0 ? 0 : 1;
    x >>= 8;
    // 2
    res += (x & 0xff) == 0 ? 0 : 1;
    x >>= 8;
    // 3
    res += (x & 0xff) == 0 ? 0 : 1;
    x >>= 8;
    // 4
    res += (x & 0xff) == 0 ? 0 : 1;
    x >>= 8;
    // 5
    res += (x & 0xff) == 0 ? 0 : 1;
    x >>= 8;
    // 6
    res += (x & 0xff) == 0 ? 0 : 1;
    x >>= 8;
    // 7
    res += (x & 0xff) == 0 ? 0 : 1;
    x >>= 8;
    // 8
    res += (x & 0xff) == 0 ? 0 : 1;
    x >>= 8;
    return res;
}

int main()
{
    // uint8_t *A = (uint8_t *)malloc(size * size * sizeof(uint8_t));
    // uint8_t *A_ = (uint8_t *)malloc(size * size * sizeof(uint8_t));
    // for (int i = 0; i < size; i++)
    // {
    //     for (int j = 0; j < size; j++)
    //     {
    //         A[i * size + j] = (AStree[i] >> (63 - j)) & 1;
    //     }
    // }
    // int n = rank(A, 64);
    // printf("rank A = %d\n", n);
    // InverseMatrix(A_, A);
    // MulMatrix(A_, A);
    // // PrintMatrix(A, 64);

    set_mul_table();
    int weight = 20;
    uint8_t x0, x1, x2, x3, x4 = 0, x5 = 0, x6 = 0, x7 = 0;
    for (x0 = 1; x0 < 256; x0++)
        for (x1 = 0; x1 < 256; x1++)
            for (x2 = 0; x2 < 256; x2++)
                for (x3 = 0; x3 < 256; x3++)
                // for (x4 = 0; x4 < 256; x4++)
                //     for (x5 = 0; x5 < 256; x5++)
                //         for (x6 = 0; x6 < 256; x6++)
                //             for (x7 = 0; x7 < 256; x7++)

                {
                    int w = 0;
                    w += (x0 == 0) ? 0 : 1;
                    w += (x1 == 0) ? 0 : 1;
                    w += (x2 == 0) ? 0 : 1;
                    w += (x3 == 0) ? 0 : 1;
                    w += (x4 == 0) ? 0 : 1;
                    w += (x5 == 0) ? 0 : 1;
                    w += (x6 == 0) ? 0 : 1;
                    w += (x7 == 0) ? 0 : 1;

                    uint64_t y = 0;
                    y ^= mul_table[0][x0];
                    y ^= mul_table[1][x1];
                    y ^= mul_table[2][x2];
                    y ^= mul_table[3][x3];
                    y ^= mul_table[4][x4];
                    y ^= mul_table[5][x5];
                    y ^= mul_table[6][x6];
                    y ^= mul_table[7][x7];
                    w += w64(y);
                    if (w < weight)
                    {
                        weight = w;
                        printf("w = %d\n", w);
                    }
                }
}