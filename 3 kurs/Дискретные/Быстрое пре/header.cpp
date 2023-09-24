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

