#include <stdio.h>
#include <stdint.h>

class field
{
public:
    int n;
    uint8_t fx;
    uint8_t max = 0;
    field(int n, uint8_t fx)
    {
        this->n = n;
        this->fx = fx;
        for (int i = 0; i < (n); i++)
        {
            max = (max << 1) ^ 1;
        }
    }
    uint8_t Mul(uint8_t ax, uint8_t bx)
    {
        uint8_t result = 0;
        while (ax != 0 && bx != 0)
        {
            if (bx & 1 != 0)
                result ^= ax;
            ax = (((ax >> (n - 1)) == 0) ? (ax << 1) : ((ax << 1) ^ fx)) & max;
            bx = bx >> 1;
        }
        return result;
    }

    uint8_t Mul_n(uint8_t ax, int tmp)
    {
        if (tmp == 0)
        {
            return 1;
        }

        if (ax == 0)
        {
            return 0;
        }

        // ax!=0
        uint8_t result = 1;
        while (tmp != 0)
        {
            if ((tmp & 1) != 0)
                result = Mul(result, ax);
            tmp = tmp >> 1;
            ax = Mul(ax, ax);
        }
        return result;
    }

    void getGx(uint8_t *phi, uint8_t *gx)
    {
        for (int c = 0; c < (1 << n); c++)
        {
            gx[0] ^= Mul(phi[c], (1 ^ Mul_n(c, (1 << n) - 1)));
            for (int i = 1; i < ((1 << n)); i++)
            {
                gx[i] ^= Mul(phi[c], Mul_n(c, ((1 << n) - 1 - i)));
            }
        }
    }

    void getPhi(uint8_t *phi, uint8_t *gx, int deg)
    {
        for (int x = 0; x < (1 << n); x++)
        {
            for (int i = 0; i < deg; i++)
            {
                phi[x] ^= Mul(gx[i], Mul_n(x, i));
            }
        }
    }

    void testGx(uint8_t *phi, uint8_t *gx, int deg)
    {
        uint8_t count[256] = {0};
        for (int x = 0; x < (1 << n); x++)
        {
            for (int i = 0; i < deg; i++)
            {
                phi[x] ^= Mul(gx[i], Mul_n(x, i));
            }
            count[phi[x]]++;
        }
        for (int x = 0; x < (1 << n); x++)
        {
            if (count[x] != 1)
            {
                printf("NO");
                return;
            }
        }
        printf("YES");
    }
};
