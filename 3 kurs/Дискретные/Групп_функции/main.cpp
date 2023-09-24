#include "header.h"

int main()
{
    vector<uint8_t> f;
    f.push_back(1);
    f.push_back(0);
    f.push_back(0);
    f.push_back(0);
    f.push_back(0);
    f.push_back(1);
    f.push_back(1);
    f.push_back(1);
    f.push_back(0);
    f.push_back(0);
    f.push_back(0);
    f.push_back(1);
    f.push_back(1);
    f.push_back(1);
    f.push_back(1);
    f.push_back(0);
    vector<vector<uint8_t>> res;
    vector<uint8_t> g;
    for (int i = 0; i < pow(2, n); i++)
    {
        g.push_back(0);
    }
    res.push_back(f);
    for (uint8_t a = 0; a < pow(2, n); a++)
    {
        f_eta(f, a, g);
        for (int i = 0; i < res.size(); i++)
        {
            if (res[i] == g)
            {
                break;
            }
            if (i == res.size() - 1)
            {
                res.push_back(g);
            }
        }
    }
    cout << "size: "<<res.size() << endl;
    for (int i = 0; i < res.size(); i++)
    {
        Print(res[i]);
    }
}