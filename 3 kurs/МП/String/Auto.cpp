#include "Auto.h"
#include "KMP.h"

int AutoFunction(string frag, int val, char c, int &step)
{
    if (val == 0)
    {
        step++;
        if (frag[0] == c)
        {
            return 1;
        }
        else
            return 0;
    }
    if ((val < frag.length()) && (frag[val] == c))
    {
        step++;
        return val + 1;
    }

    int x = 0;
    int *pre = Prefix_Function(frag, x);
    int k = val;
    while (true)
    {
        k = pre[k - 1];
        val = k;
        step++;
        if (frag[k] == c)
        {
            return val + 1;
        }
        if (k == 0)
        {
            step++;
            if (frag[0] == c)
            {
                return 1;
            }
            return 0;
        }
    }
    return 0;
}

void Search(string text, string frag, int &step)
{
    int val = 0;
    for (int i = 0; i < text.length(); i++)
    {
        val = AutoFunction(frag, val, text[i],step);
        if (val == frag.length())
        {
            cout << "   Допустимый сдвиг " << i - frag.length() + 1 << endl;
        }
    }
}
