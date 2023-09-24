#include "matrix.h"

int main()
{
    // 1 A = 00000111 = 07
    uint8_t first_a1 = 0x07;
    uint8_t a1[64] = {0};
    for (int r = 0; r < 8; r++)
    {
        for (int c = 0; c < 8; c++)
        {
            a1[r * 8 + c] = (first_a1 >> ((8 + 7 + r - c) % 8)) & 1;
        }
    }
    Matrix A1(a1, 8);
    uint8_t a1_1[64] = {0};
    printf("1) first row A^-1:  ");
    A1.InverseMatrix(a1_1);
    for (int i = 0; i < 8; i++)
    {
        printf("%d", a1_1[1 * 8 + i]);
    }
    printf("\n");

    ///////////////
    // 1 A 2= 000100100001= 121
    uint16_t first_a2 = 0b000100100001;//0x121;
    uint8_t a2[144] = {0};
    for (int r = 0; r < 12; r++)
    {
        for (int c = 0; c < 12; c++)
        {
            a2[r * 12 + c] = (first_a2 >> ((12 + 11 + r - c) % 12)) & 1;
        }
    }
    Matrix A2(a2, 12);
    uint8_t a2_1[144] = {0};
    printf("2) first row A^-1:  ");
    A2.InverseMatrix(a2_1);
    for (int i = 0; i < 12; i++)
    {
        printf("%d", a2_1[0 * 12 + i]);
    }
    printf("\n");
    ro(1, a2, 12);
    ro(2, a2, 12);
    ro(3, a2, 12);
    ro(4, a2, 12);
    // printMatrix(a2,12);
    // printf("\n////////////////////\n");
    // printMatrix(a2_1,12);


    ///////////////
    // 1 A 3= 0101000000100000 = 520
    uint16_t first_a3 =0b0101000000100000;// 0x520;
    uint8_t a3[256] = {0};
    for (int r = 0; r < 16; r++)
    {
        for (int c = 0; c < 16; c++)
        {
            a3[r * 16 + c] = (first_a3 >> ((16 + 15 + r - c) % 16)) & 1;
        }
    }
    Matrix A3(a3, 16);
    uint8_t a3_1[144] = {0};
    printf("3) first row A^-1:  ");
    A3.InverseMatrix(a3_1);
    for (int i = 0; i < 16; i++)
    {
        printf("%d", a3_1[0 * 16 + i]);
    }
    printf("\n");
    ro(1, a3, 16);
    ro(2, a3, 16);
    ro(4, a3, 16);
    ro(8, a3, 16);
    // printMatrix(a3,16);
    // printf("\n////////////////////\n");
    // printMatrix(a3_1,16);


    ///////////////
    // 1 A 4= 1001101001000000 = 9a40
    uint16_t first_a4 = 0b1001101001000000;
    uint8_t a4[256] = {0};
    for (int r = 0; r < 16; r++)
    {
        for (int c = 0; c < 16; c++)
        {
            a4[r * 16 + c] = (first_a4 >> ((16 + 15 + r - c) % 16)) & 1;
        }
    }
    Matrix A4(a4, 16);
    uint8_t a4_1[144] = {0};
    printf("4) first row A^-1:  ");
    A4.InverseMatrix(a4_1);
    for (int i = 0; i < 16; i++)
    {
        printf("%d", a4_1[0 * 16 + i]);
    }
    printf("\n");
    ro(1, a4, 16);

}