#include <cstdio>  // c std input, output: printf ...
#include <cstdint> // uint8_t ...
#include <cstdlib> // realloc, calloc ...

///////// NOTE free .....
// Function : V_n --> V_m
#define module(x) (x > 0 ? x : (-x))
// fx: V_n --> V_m
template <class TypeV_n, class TypeV_m>
class Function
{
private:
    // size of x, y
    TypeV_n max_V_n = 0; // 0xffff
    TypeV_m max_V_m = 0;
    float **delta;
    float **p;
    void setDelta();
    void setp();

public:
    TypeV_n *fx;
    float delta_f = 0;
    float p_f = 0;

    Function(int n, int m, TypeV_n *fx)
    {
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
