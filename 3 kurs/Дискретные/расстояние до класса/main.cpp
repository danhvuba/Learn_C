#include "header.h"

int main()
{
    srand(clock());

    ////////////////////////////////////// g
    vector<float> f;
    cout << "\nf= ";
    for (int i = 0; i < l; i++)
    {
        int x = rand() % 2;
        f.push_back(x);
        cout << x;
    }

    /////////////////////////////////////  p(x1,x2....)
    vector<float> p;
    cout << "\np1,p2,...,pn= ";
    for (int i = 0; i < n; i++)
    {
        float x = (float)(rand() % 100) / 100;
        p.push_back(x);
        cout << x << "  ";
    }
    cout << "\nF_f(p1,...,pn)= " << P_of_f(f, p) << endl;
    cout << "D_f(p1,...,pn)= " << P_real_f(f, p) << endl;

    ////////////////////////////////////////
    float p1 = 0.498347;
    vector<float> pp;
    for (int i = 0; i < n; i++)
    {
        pp.push_back(p1);
    }
    cout << "\nF_f(p,...p,)= " << P_of_f(f, pp) << endl;

    int weight = 0;
    for (int i = 0; i < f.size(); i++)
    {
        weight = weight + f[i];
    }
    cout << "||f||/2^n= " << (float)weight / pow(2, n) << endl;

    // расстояние f до класса L
    vector<float> ff = {1, 0, 1, 0, 0, 1, 1, 1, 0, 0, 0, 1, 1, 0, 1, 0};
    vector<float> F;
    for (int i = 0; i < ff.size(); i++)
    {
        float x = pow(-1, ff[i]);
        F.push_back(x);
    }

    vector<float> B0 = {1, 1};
    vector<float> B1 = {1, -1};
    vector<vector<float>> B = {B0, B1};
    vector<float> Waf = BPF(F, B);
    for (int i = 0; i < Waf.size(); i++)
    {
        cout << Waf[i] << endl;
    }

    bitset<l> g;
    bitset<l> FF = 22757;
    bitset<n + 1> a;
    for (int i = 0; i < pow(2, n + 1); i++)
    {
        a = i;
        bitset<n> x;
        for (int j = 0; j < l; j++)
        {
            x = j;
            g[j] = (a[0] * x[0] + a[1] * x[1] + a[2] * x[2] + a[3] * x[3] + a[4]) % 2;
        }
        bitset<l> res;
        for (int t = 0; t < l; t++)
        {
            res[t] = (g[t] + FF[t]) % 2;
        }
        cout << "g:  " << g << endl
             << "  res: " << res << endl;
        cout << "             res=       " << res.count() << "   a=  " << a << endl;
    }
}