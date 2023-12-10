#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

int main()
{
    uint8_t b[1250];
    for (int x = 0; x < 256; x++)
    {
        for (int i = 0; i < 8; i++)
        {
            b[i] = (x >> (7 - i)) & 1;
        }
        for (int i = 8; i < 1250; i++)
        {
            b[i] = b[i - 1] ^ b[i - 8];
        }
        uint8_t res = 0;
        for (int i = 0; i < 8; i++)
        {
            res = (res << 1) ^ ((b[1201 + i] & b[1201 + 2 + i] ^ b[1201 + 7 + i]) & 1);
        }
        if (res == 0x21)
        {
            printf("%02x\n", x);
        }
    }
}