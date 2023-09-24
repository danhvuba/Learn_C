#include "field.h"
#include "degree.h"
int main()
{
    field f5(4, 0b1001);
    printf("5) field: 0 ");
    for (int i = 0; i < 15; i++)
    {
        printf("%x ", f5.Mul_n(0b10, i));
    }
    printf("\n  %x   %x   %x   %x", (4 ^ 1), f5.Mul(0x9, 0xc), f5.Mul_n(9, 14), f5.Mul_n(8, 42));

    field f6(8, 0b01001101);
    printf("\n6)  %x   %x", (0x7b ^ 0xdf), f6.Mul(0x97, 0x45));

    field f7(8, 0b10101001);
    printf("\n7)  %x   %x", f7.Mul_n(0x1d, 254), f7.Mul_n(0x21, 337));

    ///////////////////////////////////////////////////////////
    field f8(3, 0b101);
    uint8_t phi8[8] = {5, 7, 2, 2, 1, 5, 7, 1}; //{5, 0, 1, 2, 3, 3, 2, 0};
    uint8_t gx8[8] = {0};
    f8.getGx(phi8, gx8);
    printf("\n8) gx = ");
    for (int c = 0; c < (8); c++)
    {
        if (gx8[8 - 1 - c])
        {
            printf("%xx^%d ", gx8[8 - 1 - c], (8 - 1 - c));
        }
    }

    ////////////////////////////////////////////
    field f9(4, 0b1001);
    uint8_t phi9[16] = {0};
    uint8_t gx9[16] = {0xa, 1, 0, 0, 0, 0, 3, 0, 6, 0, 3, 0, 0, 2, 0, 0}; //{9, 3, 0, 0, 1, 0, 0, 0, 0xf, 0, 0, 0, 0xa, 0, 6, 7};
    f9.getPhi(phi9, gx9, 16);
    printf("\n9) phi: ");
    for (int c = 0; c < (16); c++)
    {
        printf("%x ", phi9[c]);
    }

    ////////////////////////////////////////////////??????????????????????????
    field f10(8, 0b01001101);
    uint8_t phi10_0[256] = {0};
    uint8_t gx10_0[8] = {0x7b, 0x7b, 0x93, 0x77, 0x47, 0xc0, 0x86, 0x55};
    printf("\n10) g0: ");
    f10.testGx(phi10_0, gx10_0, 8);
    printf("  %x", phi10_0[0xa8]);

    uint8_t phi10_1[256] = {0};
    uint8_t gx10_1[8] = {0xb6, 0x01, 0xa7, 0xed, 0x1f, 0x78, 0x79, 0x90};
    printf("\n    g1: ");
    f10.testGx(phi10_1, gx10_1, 8);
    printf("   %x", phi10_1[0x69]);

    uint8_t phi10_2[256] = {0};
    uint8_t gx10_2[8] = {0x80, 0x19, 0x93, 0x0f, 0xea, 0xcc, 0x54, 0x6d};
    printf("\n    g2: ");
    f10.testGx(phi10_2, gx10_2, 8);
    printf("   %x", phi10_2[0xa7]);

    /////////////////////////////////////////
    field f11(8, 0b01001101);
    uint8_t phi[256] = {0};
    uint8_t phi_1[256] = {0};
    for (int x = 0; x < 256; x++)
    {
        phi[x] = f11.Mul_n(x, 188);
        phi_1[phi[x]] = x;
    }
    printf("\n11) lambda: phi: %d\n          phi_1: %d", lambda(phi), lambda(phi_1));
}