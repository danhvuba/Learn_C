#include "header.h"

int main()
{
    vector<int> y = GetText("text.txt");
    cout << "size= " << y.size() << endl;
    for (int i = 0; i < y.size(); i++)
    {
        cout << y[i] << " ";
    }

    ////////////////////////////////////////////////   find 'u'
    cout << "\n//////////////////////////" << endl;
    for (int u = 1; u < 10; u++)
    {
        cout << "u= " << u << ", I_c= " << Average_I(y, u) << endl;
    }
    cout << endl;

    ///////////////////////////////////// сдвиг относительный 1
    int u;
    cout << "u= ";
    cin >> u;
    int n = y.size() / u;
    vector<vector<int>> Y;
    for (int i = 0; i < u; i++)
    {
        vector<int> y_i;
        for (int j = 0; j < n; j++)
        {
            y_i.push_back(y[i + j * u]);
        }
        Y.push_back(y_i);
    }

    ///////////////////////////////////////// key
    vector<int> s;
    for (int i = 1; i < u; i++)
    {
        s.push_back(Func_s(Y[0], Y[i]));
    }

    for (int i = 0; i < 26; i++)
    {
        cout << "i=  " << i << "   key= " << (char)((-1 + 26 - i) % 26 + 65); ////////////////// tru di 1
        for (int j = 0; j < s.size(); j++)
        {
            cout << (char)((-1 + 26 + -i + 26 - s[j]) % 26 + 65);
        }
        cout << endl;
    }

    int i;
    cout << "\ni= ";
    cin >> i;
    Des_y(Y, s, i);
}