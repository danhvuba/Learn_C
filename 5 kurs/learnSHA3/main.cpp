#include <stdio.h>
#include <stdint.h>
#include <set>

void setPhi(uint8_t phi[256])
{
    int z;
    for (z = 0; z < 256; z++)
    {
        phi[z] = (z >> 1) ^ ((z & 1) << 1) ^ ((z & 1) << 2) ^ ((z & 1) << 3) ^ ((z & 1) << 7);
    }
}

void setPhi1(uint8_t phi[256])
{
    int x, y;
    for (x = 0; x < 5; x++)
        for (y = 0; y < 5; y++)
        {
            phi[y ^ (x << 4)] = (y << 4) ^ ((2 * x + 3 * y) % 5);
        }
}

void testPhi(uint8_t phi[256])
{
    int c[256] = {0};
    int z;
    for (z = 0; z < 256; z++)
    {
        c[phi[z]]++;
    }
    for (z = 0; z < 256; z++)
    {
        if (c[z] > 1)
        {
            printf("Phi isn't a bijection\n");
            return;
        }
    }
    printf("Phi is a bijection\n");
}

void graphPhi(uint8_t phi[256])
{
    std::set<uint8_t> Z;
    int z;
    for (z = 0; z < 256; z++)
    {
        Z.insert(z);
    }
    for (z = 0; z < 256; z++)
    {
        if (Z.find(z) != Z.end())
        {
            int tmp = z;
            printf("( %02x ", tmp);
            Z.erase(tmp);
            while (phi[tmp] != z)
            {
                tmp = phi[tmp];
                printf("%02x ", tmp);
                Z.erase(tmp);
            }
            printf(")\n");
        }
    }
}

int main()
{
    uint8_t phi[256];
    setPhi(phi);
    testPhi(phi);
    graphPhi(phi);

    {
        uint8_t phi1[256] = {0};
        std::set<uint8_t> Z;
        int x, y;
        for (x = 0; x < 5; x++)
            for (y = 0; y < 5; y++)
            {
                phi[y ^ (x << 4)] = (y << 4) ^ ((2 * x + 3 * y) % 5);
                // printf("%02x = %02x\n",(y ^ (x << 4)), phi[y ^ (x << 4)]);
                Z.insert(phi[y ^ (x << 4)]);
            };
        printf("\n----------------------\n");
        for (x = 0; x < 5; x++)
            for (y = 0; y < 5; y++)
                if (Z.find(y ^ (x << 4)) != Z.end())
                {
                    int tmp = y ^ (x << 4);
                    printf("( %02x ", tmp);
                    Z.erase(tmp);
                    while (phi[tmp] != (y ^ (x << 4)))
                    {
                        tmp = phi[tmp];
                        printf("%02x ", tmp);
                        Z.erase(tmp);
                    }
                    printf(")\n");
                }
    }

    {
        uint8_t phi1[256] = {0};
        std::set<uint8_t> Z;
        int x, y;
        for (x = 0; x < 5; x++)
            for (y = 0; y < 5; y++)
            {
                phi[y ^ (x << 4)] = (((x + 3 * y) % 5) << 4) ^ (x);
                //printf("%02x ", (((x + 3 * y) % 5) ^ (x)));
                Z.insert(phi[y ^ (x << 4)]);
            };
        printf("\n----------------------\n");
        for (x = 0; x < 5; x++)
            for (y = 0; y < 5; y++)
                if (Z.find(y ^ (x << 4)) != Z.end())
                {
                    int tmp = y ^ (x << 4);
                    printf("( %02x ", tmp);
                    Z.erase(tmp);
                    while (phi[tmp] != (y ^ (x << 4)))
                    {
                        tmp = phi[tmp];
                        printf("%02x ", tmp);
                        Z.erase(tmp);
                    }
                    printf(")\n");
                }
    }
    
}
