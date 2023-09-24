#include "BM.h"

int *preBmBc(string frag, int &step)
{
    int m = frag.length();
    int *pre = new int[256];
    for (int i = 0; i < 256; i++)
    {
        pre[i] = m;
    }
    for (int i = 0; i < m - 1; i++)
    {
        step++;
        pre[(int)frag[i]] = m - 1 - i;
    }
    return pre;
}

int suffixLength(string frag, int p)
{
    int m = frag.length();
    int i = p, len = 0;
    while ((i >= 0) && (frag[i]) == frag[m - 1 - p + i])
    {
        len++;
        i--;
    }
    return len;
}

int *preBmGs(string frag, int &step)
{
    int m = frag.length();
    int *pre = new int[m + 1];
    for (int i = 0; i < m + 1; i++)
    {
        pre[i] = m + 1;
    }
    for (int i = 0; i < m - 1; i++)
    {
        step++;
        pre[m - 1 - (suffixLength(frag, i) - 1)] = m - 1 - i;
    }

    for (int i = 1; i < m; i++)
    {
        if (pre[i] == m + 1)
        {
            step++;
            for (int j = i; j >= 0; j--)
            {
                if ((j - suffixLength(frag, j)) == -1)
                {
                    step++;
                    pre[i] = m - 1 - i + (i - j);
                    break;
                }
            }
        }
    }
    pre[m] = 1;
    return pre;
}

void BM_Search(string text, string frag, int &step)
{
    int *bmBc = preBmBc(frag, step);
    int *bmGs = preBmGs(frag, step);
    int n = text.length();
    int m = frag.length();
    int i = m - 1;
    while (i < n)
    {
        int j = m - 1;
        while ((j >= 0) && (text[i] == frag[j]))
        {
            step++;
            if (j == 0)
            {
                cout << "   Допустимый сдвиг " << i - j << endl;
            }
            i--;
            j--;
        }
        step++;
        // if (text[i] != '\n')
        // {
        i = i + Max(bmGs[j + 1], bmBc[((int)text[i])]);
        // }
        // else
        //     i = i + Max(bmGs[j + 1], m);
    }
}

int Max(int a, int b)
{
    if (a <= b)
    {
        return b;
    }
    return a;
}