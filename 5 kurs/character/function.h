#include <stdio.h> 
#include <stdint.h> 
#include <stdlib.h> 

///////// NOTE free .....
// Function : V_n --> V_m
#define module(x) (x > 0 ? x : (-x))
// fx: V_n --> V_m
template <class TypeV_n, class TypeV_m>
class Function
{
private:
    // size of x, y
    int n, m;
    TypeV_n max_V_n = 0; // 0xffff
    TypeV_m max_V_m = 0;
    float **delta;
    float **p;
    void setDelta();
    void setp();
    void fastMt(uint8_t *f)
    {
        // h = M / 2
        int h, x, i;
        for (h = 1; h < (1 << n); h <<= 1)
        {
            for (x = 0; x < (1 << n); x = x + (h << 1))
                for (i = x; i < x + h; i++)
                    f[i + h] = f[i] ^ f[i + h];
        }
    }
    int sumBitVn(TypeV_n x)
    {
        int res = 0;
        for (int i = 0; i < n; i++)
        {
            if ((x & 1) != 0)
            {
                res++;
            }
            x >>= 1;
        }
        return res;
    }
    int XorBitVm(TypeV_m x)
    {
        int res = 0;
        for (int i = 0; i < m; i++)
        {
            res ^= (x & 1);
            x >>= 1;
        }
        return res;
    }
    int Degree(uint8_t *fx)
    {
        int res = 0;
        TypeV_n x;
        for (x = 0; x < max_V_n; x++)
        {
            if ((fx[x] != 0) && (sumBitVn(x) > res))
                res = sumBitVn(x);
        }
        if ((fx[x] != 0) && (sumBitVn(x) > res))
            res = sumBitVn(x);
        return res;
    }
    int lambda_(TypeV_m *fx)
    {
        int res = n;
        uint8_t f[1 << n] = {0};
        TypeV_m b;
        TypeV_n x;
        for (b = 1; b < max_V_m; b++)
        {
            // f ^ b
            for (x = 0; x < max_V_n; x++)
            {
                f[x] = XorBitVm(fx[x] & b);
            }
            // x = V_n
            f[x] = XorBitVm(fx[x] & b);

            fastMt(f);
            if (res > Degree(f))
            {
                res = Degree(f);
            }
        }
        // b = V_m
        for (x = 0; x < max_V_n; x++)
        {
            f[x] = XorBitVm(fx[x] & b);
        }
        // x = V_n
        f[x] = XorBitVm(fx[x] & b);

        fastMt(f);
        if (res > Degree(f))
        {
            res = Degree(f);
        }
        return res;
    }

public:
    TypeV_m *fx;
    float delta_f = 0;
    float p_f = 0;
    int lambda = 0;

    Function(int n, int m, TypeV_m *fx)
    {
        this->n = n;
        this->m = m;
        for (int i = 0; i < n; i++)
        {
            this->max_V_n ^= 1 << (i);
        }
        for (int i = 0; i < m; i++)
        {
            this->max_V_m ^= 1 << (i);
        }
        this->fx = fx;
    }

    void setData()
    {
        delta = (float **)malloc((max_V_n + 1) * sizeof(float *));
        p = (float **)malloc((max_V_n + 1) * sizeof(float *));
        int t;
        for (t = 0; t < max_V_n; t++)
        {
            delta[t] = (float *)malloc((max_V_m + 1) * sizeof(float));
            p[t] = (float *)malloc((max_V_m + 1) * sizeof(float));
        }
        // t= max_V_n
        delta[t] = (float *)malloc((max_V_m + 1) * sizeof(float));
        p[t] = (float *)malloc((max_V_m + 1) * sizeof(float));

        this->setDelta();
        this->setp();
        this->lambda = lambda_(fx);
    }

    ~Function()
    {
        free(delta);
        free(p);
    }
};

template <class TypeV_n, class TypeV_m>
void Function<TypeV_n, TypeV_m>::setDelta()
{
    TypeV_n a;
    for (a = 0; a < max_V_n; a++)
    {
        delta[a][0] = 0;
        // b!=0
        TypeV_m b;
        {
            for (b = 1; b < max_V_m; b++)
            {
                int count = 0;
                TypeV_n x;
                {
                    for (x = 0; x < max_V_n; x++)
                    {
                        uint8_t res = (x & a) ^ (fx[x] & b);
                        bool tmp = 0;
                        while (res != 0)
                        {
                            tmp ^= res & 1;
                            res = res >> 1;
                        }
                        if (tmp)
                        {
                            count++;
                        }
                    }
                    // x= max_V_n
                    {
                        uint8_t res = (x & a) ^ (fx[x] & b);
                        bool tmp = 0;
                        while (res != 0)
                        {
                            tmp ^= res & 1;
                            res = res >> 1;
                        }
                        if (tmp)
                        {
                            count++;
                        }
                    }
                }

                delta[a][b] = 2 * (static_cast<float>(count) / (max_V_n + 1)) - 1;
                if (module(delta[a][b]) > delta_f)
                {
                    delta_f = module(delta[a][b]);
                }
            }
            // b <= max_V_m
            {
                int count = 0;
                TypeV_n x;
                {
                    for (x = 0; x < max_V_n; x++)
                    {
                        uint8_t res = (x & a) ^ (fx[x] & b);
                        bool tmp = 0;
                        while (res != 0)
                        {
                            tmp ^= res & 1;
                            res = res >> 1;
                        }
                        if (tmp)
                        {
                            count++;
                        }
                    }
                    // x= max_V_n
                    {
                        uint8_t res = (x & a) ^ (fx[x] & b);
                        bool tmp = 0;
                        while (res != 0)
                        {
                            tmp ^= res & 1;
                            res = res >> 1;
                        }
                        if (tmp)
                        {
                            count++;
                        }
                    }
                }

                delta[a][b] = 2 * (static_cast<float>(count) / (max_V_n + 1)) - 1;
                if (module(delta[a][b]) > delta_f)
                {
                    delta_f = module(delta[a][b]);
                }
            }
        }
    }
    // a=max_V_n
    {
        delta[a][0] = 0;
        // b!=0
        TypeV_m b;
        {
            for (b = 1; b < max_V_m; b++)
            {
                int count = 0;
                TypeV_n x;
                {
                    for (x = 0; x < max_V_n; x++)
                    {
                        uint8_t res = (x & a) ^ (fx[x] & b);
                        bool tmp = 0;
                        while (res != 0)
                        {
                            tmp ^= res & 1;
                            res = res >> 1;
                        }
                        if (tmp)
                        {
                            count++;
                        }
                    }
                    // x= max_V_n
                    {
                        uint8_t res = (x & a) ^ (fx[x] & b);
                        bool tmp = 0;
                        while (res != 0)
                        {
                            tmp ^= res & 1;
                            res = res >> 1;
                        }
                        if (tmp)
                        {
                            count++;
                        }
                    }
                }

                delta[a][b] = 2 * (static_cast<float>(count) / (max_V_n + 1)) - 1;
                if (module(delta[a][b]) > delta_f)
                {
                    delta_f = module(delta[a][b]);
                }
            }
            // b <= max_V_m
            {
                int count = 0;
                TypeV_n x;
                {
                    for (x = 0; x < max_V_n; x++)
                    {
                        uint8_t res = (x & a) ^ (fx[x] & b);
                        bool tmp = 0;
                        while (res != 0)
                        {
                            tmp ^= res & 1;
                            res = res >> 1;
                        }
                        if (tmp)
                        {
                            count++;
                        }
                    }
                    // x= max_V_n
                    {
                        uint8_t res = (x & a) ^ (fx[x] & b);
                        bool tmp = 0;
                        while (res != 0)
                        {
                            tmp ^= res & 1;
                            res = res >> 1;
                        }
                        if (tmp)
                        {
                            count++;
                        }
                    }
                }

                delta[a][b] = 2 * (static_cast<float>(count) / (max_V_n + 1)) - 1;
                if (module(delta[a][b]) > delta_f)
                {
                    delta_f = module(delta[a][b]);
                }
            }
        }
    }

    delta[0][0] = 1;
}

template <class TypeV_n, class TypeV_m>
void Function<TypeV_n, TypeV_m>::setp()
{
    TypeV_m b;
    for (b = 0; b < max_V_m; b++)
    {
        p[0][b] = 0;
        TypeV_n a;
        for (a = 1; a < max_V_n; a++)
        {
            int count = 0;
            TypeV_n x;
            for (x = 0; x < max_V_n; x++)
            {
                if ((fx[x] ^ fx[x ^ a]) == b)
                {
                    count++;
                }
            }
            // x = max_V_n
            {
                if ((fx[x] ^ fx[x ^ a]) == b)
                {
                    count++;
                }
            }

            p[a][b] = static_cast<float>(count) / (max_V_n + 1);
            if (p[a][b] > p_f)
            {
                p_f = p[a][b];
            }
        }
        // a = max_V_n
        {
            int count = 0;
            TypeV_n x;
            for (x = 0; x < max_V_n; x++)
            {
                if ((fx[x] ^ fx[x ^ a]) == b)
                {
                    count++;
                }
            }
            // x = max_V_n
            {
                if ((fx[x] ^ fx[x ^ a]) == b)
                {
                    count++;
                }
            }

            p[a][b] = static_cast<float>(count) / (max_V_n + 1);
            if (p[a][b] > p_f)
            {
                p_f = p[a][b];
            }
        }
    }
    // b = max_V_m
    {
        p[0][b] = 0;
        TypeV_n a;
        for (a = 1; a < max_V_n; a++)
        {
            int count = 0;
            TypeV_n x;
            for (x = 0; x < max_V_n; x++)
            {
                if ((fx[x] ^ fx[x ^ a]) == b)
                {
                    count++;
                }
            }
            // x = max_V_n
            {
                if ((fx[x] ^ fx[x ^ a]) == b)
                {
                    count++;
                }
            }

            p[a][b] = static_cast<float>(count) / (max_V_n + 1);
            if (p[a][b] > p_f)
            {
                p_f = p[a][b];
            }
        }
        // a = max_V_n
        {
            int count = 0;
            TypeV_n x;
            for (x = 0; x < max_V_n; x++)
            {
                if ((fx[x] ^ fx[x ^ a]) == b)
                {
                    count++;
                }
            }
            // x = max_V_n
            {
                if ((fx[x] ^ fx[x ^ a]) == b)
                {
                    count++;
                }
            }

            p[a][b] = static_cast<float>(count) / (max_V_n + 1);
            if (p[a][b] > p_f)
            {
                p_f = p[a][b];
            }
        }
    }

    p[0][0] = 1;
}
