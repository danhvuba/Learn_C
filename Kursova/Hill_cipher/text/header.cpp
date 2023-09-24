#include "header.h"

void Set_Bit(bitset<n> &X, float p)
{
    int tmp = p * n;
    if (tmp == 0)
    {
        X.reset();
        return;
    }
    if (tmp == n)
    {
        X.set();
        return;
    }
    for (int i = 0; i < tmp; i++)
    {
        int x = rand() % n;
        while (X[x] == 1)
        {
            x = rand() % n;
        }
        X.set(x, 1);
    }
}

float Probability_Bit(bitset<n> X)
{
    int tmp = X.count();
    return (float)tmp / n;
}

bitset<n> Func_filter(bitset<n> X, bitset<t> fx)
{
    bitset<n> Y;
    bitset<m> tmp;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            tmp[j] = X[(i + j) % n];
        }
        Y.set(i, fx[tmp.to_ulong()]);
    }
    return Y;
}

bitset<t> Func_res(bitset<n> X, bitset<n> X2, bitset<n> X3, bitset<n> X4)
{
    bitset<t> fx;
    bitset<n> Y;
    cout << endl;
    cout << "       fx     "
         << "         Y      "
         << "    p   " << endl;
    while (true)
    {
        Y = Func_filter(X, fx);
        if (Probability_Bit(Y) == 0.5)
        {
            bitset<n> Y2 = Func_filter(X2, fx);
            if (Probability_Bit(Y2) == 0.5)
            {
                bitset<n> Y3 = Func_filter(X3, fx);
                if (Probability_Bit(Y3) == 0.5)
                {

                        cout << fx << "    " << Y << "    " << Probability_Bit(Y) << endl;
                }
            }
        }

        if (fx.all())
        {
            break;
        }
        fx = fx.to_ulong() + 1;
    }
    return fx;
}
