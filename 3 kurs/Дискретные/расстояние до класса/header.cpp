#include "header.h"

vector<float> BPF(vector<float> f, vector<vector<float>> B)
{
    int step = log2(f.size());
    for (int n = 0; n < step; n++)
    {
        vector<float> ff;
        for (int t = 0; t < f.size(); t++)
        {
            ff.push_back(f[t]);
        }
        int m = pow(2, n + 1);
        for (int i = 0; i < f.size(); i++)
        {
            if ((i % m) < (m / 2))
            {
                f[i] = ff[i] * B[0][0] + ff[i + m / 2] * B[0][1];
            }
            else
            {
                f[i] = ff[i - m / 2] * B[1][0] + ff[i] * B[1][1];
            }
        }
    }
    return f;
}

float P_real_f(vector<float> f, vector<float> p)
{
    vector<float> B0 = {1, 0};
    vector<float> B1 = {-1, 1};
    vector<vector<float>> B = {B0, B1};
    vector<float> ff = BPF(f, B);
    // for (int i = 0; i < ff.size(); i++)
    // {
    //     cout << ff[i] << endl;
    // }
    bitset<n> x;
    float res = 0;
    for (int i = 0; i < ff.size(); i++)
    {
        if (ff[i] != 0)
        {
            x = i;
            float tmp = 1;
            for (int j = 0; j < n; j++)
            {
                tmp = tmp * pow(p[j], x[j]);
            }
            res = res + tmp*ff[i];
        }
    }
    return res;
}

float P_of_f(vector<float> f, vector<float> p)
{
    bitset<n> x;
    float res = 0;
    for (int i = 0; i < f.size(); i++)
    {
        if (f[i] != 0)
        {
            x = i;
            float tmp = 1;
            for (int j = 0; j < n; j++)
            {
                if (x[j] == 0)
                {
                    tmp = tmp * (1 - p[j]);
                }
                else
                    tmp = tmp * p[j];
            }
            res = res + tmp;
        }
    }
    return res;
}

float Func_f_p(vector<float> f, float p)
{
    bitset<n> x;
    float res = 0;
    for (int i = 0; i < f.size(); i++)
    {
        if (f[i] != 0)
        {
            x = i;
            float tmp = 1;
            
            res = res + tmp;
        }
    }
    return res;

}