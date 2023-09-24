#include "function.h"
#include "degree.h"

uint8_t phi_x[16] = {3, 5, 4, 7, 0, 7, 4, 0, 5, 1, 2, 6, 2, 1, 3, 6};
uint8_t A1[16] = {0, 0, 1, 0,
                  0, 1, 0, 0,
                  0, 0, 0, 1,
                  1, 0, 0, 1};
uint8_t A2[9] = {1, 0, 1,
                 0, 0, 1,
                 1, 1, 0};
uint8_t A3[12] = {1, 0, 1,
                  1, 1, 1,
                  1, 1, 0,
                  1, 1, 0};
uint8_t a1 = 0b0001;
uint8_t a2 = 0b100;
uint8_t a3 = 0b101;

uint8_t phi1_x[16] = {0};
uint8_t phi2_x[16] = {0};
uint8_t phi3_x[16] = {0};

uint8_t mulA1(uint8_t x)
{
    uint8_t res = 0;
    for (int c = 0; c < 4; c++)
    {
        res = res << 1;
        for (int r = 0; r < 4; r++)
            res ^= A1[r * 4 + c] & ((x >> (3 - r)) & 1);
    }
    return res;
}

uint8_t mulA2(uint8_t x)
{
    uint8_t res = 0;
    for (int c = 0; c < 3; c++)
    {
        res = res << 1;
        for (int r = 0; r < 3; r++)
            res ^= A2[r * 3 + c] & ((x >> (2 - r)) & 1);
    }
    return res;
}

uint8_t mulA3(uint8_t x)
{
    uint8_t res = 0;
    for (int c = 0; c < 3; c++)
    {
        res = res << 1;
        for (int r = 0; r < 4; r++)
            res ^= A3[r * 3 + c] & ((x >> (3 - r)) & 1);
    }
    return res;
}

void setData()
{
    for (int x = 0; x < 16; x++)
    {
        phi1_x[x] = phi_x[mulA1(x) ^ a1];
        phi2_x[x] = mulA2(phi_x[x]) ^ a2;
        phi3_x[x] = phi_x[x] ^ mulA3(x) ^ a3;
    }
}

void printMatrix_16(float **x)
{
    for (int r = 0; r < 16; r++)
    {
        for (int c = 0; c < 8; c++)
        {
            printf("%3d ", (int)(16 * x[r][c]));
        }
        printf("\n");
    }
}

int main()
{
    setData();
    //////////////////////////////   1
    printf("phi 1: ");
    for (int x = 0; x < 16; x++)
    {
        printf("%x ", phi1_x[x]);
    }
    printf("\nphi 2: ");
    for (int x = 0; x < 16; x++)
    {
        printf("%x ", phi2_x[x]);
    }
    printf("\nphi 3: ");
    for (int x = 0; x < 16; x++)
    {
        printf("%x ", phi3_x[x]);
    }
    /////
    Function<uint8_t, uint8_t> phi(4, 3, phi_x);
    Function<uint8_t, uint8_t> phi1(4, 3, phi1_x);
    Function<uint8_t, uint8_t> phi2(4, 3, phi2_x);
    Function<uint8_t, uint8_t> phi3(4, 3, phi3_x);

    printf("\n16* p:     %d  %d  %d  %d", (int)(16 * phi.p_f), (int)(16 * phi1.p_f), (int)(16 * phi2.p_f), (int)(16 * phi3.p_f));
    printf("\n16* delta: %d  %d  %d  %d", (int)(16 * phi.delta_f), (int)(16 * phi1.delta_f), (int)(16 * phi2.delta_f), (int)(16 * phi3.delta_f));
    printf("\nlambda:    %2d  %2d  %2d  %2d", lambda(phi_x), lambda(phi1_x), lambda(phi2_x), lambda(phi3_x));

    printf("\nD_phi:\n");
    printMatrix_16(phi.p);
    printf("\nD_phi:\n");
    printMatrix_16(phi1.p);
    printf("\nD_phi:\n");
    printMatrix_16(phi2.p);
    printf("\nD_phi:\n");
    printMatrix_16(phi3.p);

    //uint8_t pi_x[16] = {0, 0xd, 1, 0xb, 6, 4, 8, 7, 9, 2, 5, 0xe, 0xc, 3, 0xf, 0xa};
    uint8_t pi_x[16] = {0x0, 0xd, 0x1, 0xb, 0x6, 0x4, 0x8, 0x7, 0x9, 0x2, 0x5, 0xe, 0xc, 0x3, 0xf, 0xa};
    //uint8_t pi_x[16] = {0xf, 6, 0xa, 8, 3, 7, 4, 2, 0xe, 0xc, 0xb, 0, 0xd, 1, 9, 5};

    uint8_t pi_1_x[16] = {0};
    for (int i = 0; i < 16; i++)
    {
        pi_1_x[pi_x[i]] = i;
    }
    Function<uint8_t, uint8_t> pi(4, 4, pi_x);
    Function<uint8_t, uint8_t> pi1(4, 4, pi_1_x);
    printf("\n16* p:     %d  %d", (int)(16 * pi.p_f), (int)(16 * pi1.p_f));
    printf("\n16* delta: %d  %d", (int)(16 * pi.delta_f), (int)(16 * pi1.delta_f));
    printf("\nlambda:    %2d  %2d", lambda(pi_x), lambda(pi_1_x));

}
