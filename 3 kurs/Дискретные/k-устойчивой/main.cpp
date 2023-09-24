#include "header.h"

int main()
{

    ////////////////////////////////////// g
    int count = 0;
    int *f = new int[l];
    bitset<m> g;
    bitset<k> x;
    bitset<k> y;
    for (int i = 0; i < pow(2, m); i++)
    {
        g = i;
        for (int yy = 0; yy < m; yy++)
        {
            y = yy;
            for (int xx = 0; xx < m; xx++)
            {
                x = xx;
                int tmp = 0;
                for (int i = 0; i < n / 2; i++)
                {
                    tmp = tmp + x[i] * y[i];
                }

                f[y.to_ulong() * m + x.to_ulong()] = (tmp + g[x.to_ulong()]) % 2;
            }
        }
        if (Is_bent(f))
        {
            count++;
        }
    }
    cout << "number:  " << count << endl;

    // cout << "к-устойчивой: " << endl;
    // int *f = new int[l];
    // bitset<l> ff;
    // for (int i = 0; i < pow(2, l); i++)
    // {
    //     ff =int j = 0; j < l; j++)
    //     { i;
    //     for (
    //         f[j] = ff[j];
    //     }
    //     int *k = res(f);
    //     if ((k[1] == 2))
    //     {
    //         cout << "f: " << ff << endl;
    //     }
    // }
}