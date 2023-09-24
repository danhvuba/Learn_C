#include "header.h"

void Print(vector<uint8_t> f)
{
    cout << "____";
    for (int i = 0; i < f.size(); i++)
    {
        cout << (int)f[i];
    }
    cout << endl;
}
void f_eta(vector<uint8_t> f, uint8_t a, vector<uint8_t> &g)
{
    for (int x = 0; x < pow(2, n); x++)
    {
        g[x] = f[x ^ a];
    }
    if (g==f)
    {
     cout<<"vector a: "<<(int)a<<endl;  
    }
        
};