#include "header.h"

int *BPF(int *f0, int **B)
{
    int *f = new int[l];
    for (int t = 0; t < l; t++)
    {
        f[t] = f0[t];
    }
    int step = log2(l);
    for (int n = 0; n < step; n++)
    {
        int *ff = new int[l];
        for (int t = 0; t < l; t++)
        {
            ff[t] = f[t];
        }
        int m = pow(2, n + 1);
        for (int i = 0; i < l; i++)
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

int *Waf(int *f)
{
    int *F = new int[l];
    for (int i = 0; i < l; i++)
    {
        F[i] = pow(-1, f[i]);
    }
    int **B = new int *[2];
    B[0] = new int[2];
    B[0][0] = 1;
    B[0][1] = 1;
    B[1] = new int[2];
    B[1][0] = 1;
    B[1][1] = -1;
    int *W = BPF(F, B);
    // for (int i = 0; i < l; i++)
    // {
    //     W[i] = W[i]; /// l; nhan voi 1/2^n
    // }
    return W;
}

int k_correc(int *W)
{
    bitset<n> a;
    int k;
    for (k = 1; k < n; k++)
    {
        for (int i = 1; i < l; i++)
        {
            a = i;
            if ((a.count() == k) && (W[i] != 0))
            {
                return k - 1;
            }
        }
    }
    return k;
}

int *res(int *f)
{
    int *W = Waf(f);
    int *res = new int[2];
    res[0] = k_correc(W);

    if (W[0] != 0)
    {
        res[1] = 0;
    }
    else
        res[1] = res[0];

    return res;
}

bool Is_bent(int *f)
{
    int *W = new int[l];
    W = Waf(f);
    for (int i = 0; i < l; i++)
    {
        int x = W[i] / m;
        if ((x * x) != 1)
        {
            return false;
        }
    }
    return true;
}