#include <stdio.h>
#include <stdint.h>

#define F1(x, y, z) (x & y | (~x) & z)
#define F2(x, y, z) (x & z | y & (~z))
#define F3(x, y, z) (x ^ y ^ z)
#define F4(x, y, z) (y ^ (x | (~z)))

int main()
{
    // F1
    {
        uint32_t y[256];
        for (int i = 0; i < 256; i++)
        {
            for (int j = 0; j < 256; j++)
            {
                for (int t = 0; t < 256; t++)
                {
                    y[F1(i, j, t)]++;
                }
            }
        }
        for (int i = 0; i < 256; i++)
        {
            if (y[i] < 65536)
            {
                printf("F1 not balance\n");
                return 0;
            }
        }
        printf("F1 balance\n");
    }

    // F2
    {
        uint32_t y[256];
        for (int i = 0; i < 256; i++)
        {
            for (int j = 0; j < 256; j++)
            {
                for (int t = 0; t < 256; t++)
                {
                    y[F1(i, j, t)]++;
                }
            }
        }
        for (int i = 0; i < 256; i++)
        {
            if (y[i] < 65536)
            {
                printf("F2 not balance\n");
                return 0;
            }
        }
        printf("F2 balance\n");
    }

    // F3
    {
        uint32_t y[256];
        for (int i = 0; i < 256; i++)
        {
            for (int j = 0; j < 256; j++)
            {
                for (int t = 0; t < 256; t++)
                {
                    y[F1(i, j, t)]++;
                }
            }
        }
        for (int i = 0; i < 256; i++)
        {
            if (y[i] < 65536)
            {
                printf("F3 not balance\n");
                return 0;
            }
        }
        printf("F3 balance\n");
    }
}