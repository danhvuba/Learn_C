#include "RP.h"

int Hash(string str)
{
    int hs = 0, m = str.length();
    for (int i = 0; i < m; i++)
    {
        hs = hs + ((int)str[i] * (int)pow(x, m - 1 - i)) % q;
    }
    return (hs % q);
}

void RP_Search(string text, string frag, int &step)
{
    int n = text.length(), m = frag.length();
    int hs_frag = Hash(frag);
    int hs = Hash(text.substr(0, m));
    for (int i = 0; i < n - m + 1; i++)
    {
        step++;
        if (hs == hs_frag)
        {
            int j;
            for (j = 0; (j < m) && (text[j + i] == frag[j]); j++)
            {
                step++;
            }
            if (j == m)
                cout
                    << "   Допустимый сдвиг " << i << endl;
        }
        hs = (((hs - (int)text[i] * (int)pow(x, m - 1)) * x + (int)text[i + m]) % q + q) % q;
    }
}