#include "header.h"

string Rus(string n, string *id)
{
    if (n == id[0])
    {
        return "а";
    }
    if (n == id[1])
    {
        return "б";
    }
    if (n == id[2])
    {
        return "в";
    }
    if (n == id[3])
    {
        return "г";
    }
    if (n == id[4])
    {
        return "д";
    }
    if (n == id[5])
    {
        return "е";
    }
    if (n == id[6])
    {
        return "ж";
    }
    if (n == id[7])
    {
        return "з";
    }
    if (n == id[8])
    {
        return "и";
    }
    if (n == id[9])
    {
        return "й";
    }
    if (n == id[10])
    {
        return "к";
    }
    if (n == id[11])
    {
        return "л";
    }
    if (n == id[12])
    {
        return "м";
    }
    if (n == id[13])
    {
        return "н";
    }
    if (n == id[14])
    {
        return "о";
    }
    if (n == id[15])
    {
        return "п";
    }
    if (n == id[16])
    {
        return "р";
    }
    if (n == id[17])
    {
        return "с";
    }
    if (n == id[18])
    {
        return "т";
    }
    if (n == id[19])
    {
        return "у";
    }
    if (n == id[20])
    {
        return "ф";
    }
    if (n == id[21])
    {
        return "х";
    }
    if (n == id[22])
    {
        return "ц";
    }
    if (n == id[23])
    {
        return "ч";
    }
    if (n == id[24])
    {
        return "ш";
    }
    if (n == id[25])
    {
        return "щ";
    }
    if (n == id[26])
    {
        return "ъ";
    }
    if (n == id[27])
    {
        return "ы";
    }
    if (n == id[28])
    {
        return "ь";
    }
    if (n == id[29])
    {
        return "э";
    }
    if (n == id[30])
    {
        return "ю";
    }
    if (n == id[31])
    {
        return "я";
    }
    if (n == id[32])
    {
        return " ";
    }
    return n;
}

string      Get(string x)
{
    ifstream inp(x);
    char a;
    string str;
    while (inp.get(a))
    {
        str = str + a;
    }
    inp.close();
    return str;
}

void Print(vector<string> line)
{
    for (int i = 0; i < line.size(); i++)
    {
        cout << line[i];
    }
    cout << "-----" << endl;
}

vector<vector<string>> Get_text(string str)
{
    vector<vector<string>> text;
    int id = 0;
    for (int i = 0; i < 5; i++)
    {
        vector<string> line;
        for (int j = 0; j < 50; j++)
        {
            string tmp;
            if (str[id] != ' ')
            {
                tmp = tmp + str[id] + str[id + 1];
                id = id + 2;
            }
            else
            {
                tmp = ' ';
                id++;
            }
            line.push_back(tmp);
        }
        text.push_back(line);
        id = id + 1;
    }
    return text;
}

vector<vector<int>> To_Int(vector<vector<string>> text, vector<string> tx)
{
    vector<vector<int>> res;
    for (int i = 0; i < 5; i++)
    {
        vector<int> res_1;
        for (int j = 0; j < text[i].size(); j++)
        {
            for (int x = 0; x < tx.size(); x++)
            {
                if (tx[x] == text[i][j])
                {
                    res_1.push_back(x);
                }
            }
        }
        res.push_back(res_1);
    }
    return res;
}

// string To_text(int val, vector<string> tx)
// {
//     for (int i = 0; i < tx.size(); i++)
//     {
//         if (tx[i]==tx[val])
//         {
//             return tx[val];
//         }
        
//     }
    
// }