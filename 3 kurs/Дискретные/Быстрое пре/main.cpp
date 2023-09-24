#include "header.h"

void PrintBit(int x)
{
    for (int i = 0; i < 5; i++)
    {
        cout<<((x>>(4-i))&1);
    }
    cout<<endl;
    
}

int main()
{
    srand(clock());
    uint32_t fx = 0x3a5c742e;
    ////////////////////////////////////// g
    vector<float> f;
    cout << "\nf= ";
    for (int i = 0; i < l; i++)
    {
        // int x = rand() % 2;
        int x = (fx >> (i)) & 1;
        if (x==0)
        {
            f.push_back(1);
        }
        else f.push_back(-1);
        
        // f.push_back(x);
        cout << x;
    }
    cout << endl;

    vector<float> B0 = {1, 1};
    vector<float> B1 = {1, -1};
    vector<vector<float>> B = {B0, B1};
    vector<float> ff = BPF(f, B);
    for (int i = 0; i < l; i++)
    {
        cout << (ff[i])<<"  ";
        PrintBit(i);
    }
}