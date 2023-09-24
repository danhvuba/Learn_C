#include "KMP.h"

int *Prefix_Function(string str, int &step)
{
    int *pre = new int[str.length()];
    pre[0] = 0;
    int k = 0;
    for (int id = 1; id < str.length(); id++)
    {
        while (true)
        {
            step++;
            if ((str[k] == str[id]))
            {
                pre[id] = k + 1;
                break;
            }
            if (k == 0)
            {
                pre[id] = 0;
                break;
            }
            // 0 1 ......         k-1
            // <--------k---------->
            // *********************_
            // ******_________******
            //                <----> pre[k-1]
            k = pre[k - 1];
        }
    }
    return pre;
}

void KMP_Search(string text, string frag, int &step)
{
    int *pre = Prefix_Function(frag, step);
    int k = 0;
    for (int r = 0; r < text.length(); r++)
    {
        while (true)
        {
            step++;
            if (frag[k] == text[r])
            {
                k++;
                break;
            }
            if (k == 0)
            {
                break;
            }
            k = pre[k - 1];
        }
        if (k == frag.length())
        {
            cout << "   Допустимый сдвиг " << r - frag.length() + 1 << endl;
            k--;
        }
    }
}