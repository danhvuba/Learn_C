#include "matrix.h"

int main()
{
    // 19
    // A: 1000 0000 1000 0010 0000 0010 0000 0010
    // B: 1000 0000 0100 0000 0001 0000 0000 0000
    uint32_t first_a = 0x80820202; // 
    uint8_t a[n*n] = {0};
    for (int r = 0; r < n; r++)                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                       
    {
        for (int c = 0; c < n; c++)
        {
            a[r * n + c] = (first_a >> ((n + 11 + r - c) % n)) & 1;
        }
    }
    for (int r = 0; r < n; r++)
    {
        for (int c = 0; c < n; c++)
        {
            printf("%d ",  a[r * n + c]);
        }
        printf("\n");
    }
    printf("ro(A)= %x\n",  ro(a, 8));

    uint32_t first_b = 0x80401000; // 0xn1;
    uint8_t b[n*n] = {0};
    for (int r = 0; r < n; r++)
    {
        for (int c = 0; c < n; c++)
        {
            b[r * n + c] = (first_b >> ((n + 11 + r - c) % n)) & 1;
        }
    }
    printf("ro(B)= %x\n",  ro(b, 8));
}