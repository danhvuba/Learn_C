#include "frequency.h"

bool Is(char x)
{
    if ((((int)x >= 65) && ((int)x <= 90)) || (((int)x >= 97) && ((int)x <= 122)))
    {
        return true;
    }
    else
        return false;
}

string GetText(string path)
{
    string str;
    fstream input;
    input.open(path);
    if (input.fail())
    {
        cout << "can't open" << endl;
    }
    char a;
    while (input.get(a))
    {
        if (Is(a))
        {
            if (((int)a >= 97) && ((int)a <= 122))
            {
                str = str + (char)((int)a - 32);
            }
            else
                str = str + a;
        }
    }
    input.close();
    return str;
}

int Count(string str, string x)
{
    int c = 0, i = 0;
    while (str.find(x, i) != -1)
    {
        i = str.find(x, i) + x.length();
        if (i % x.length() == 0)
        {
            c++;
        }
    }
    return c;
}

void Forbidden_Gram(string str, string path)
{
    // alphabet A-Z
    string al;
    for (int i = 65; i <= 90; i++)
    {
        al.push_back((char)i);
    }
    fstream Out;
    Out.open(path);
    int x;
    // bigram
    for (int i = 0; i < al.length(); i++)
    {
        string s;
        s.push_back(al[i]);
        for (int j = 0; j < al.length(); j++)
        {
            x = Count(str, s + al[j]);
            if (x == 0)
            {
                Out << s + al[j] << endl;
            }
        }
    }

    // trigram
    for (int i = 0; i < al.length(); i++)
    {
        string s;
        s.push_back(al[i]);
        for (int j = 0; j < al.length(); j++)
        {
            for (int k = 0; k < al.length(); k++)
            {
                x = Count(str, s + al[j] + al[k]);
                if (x == 0)
                {
                    Out << s + al[j] + al[k] << endl;
                }
            }
        }
    }
    Out.close();
}

vector<float> Frequency_Bigram(string str)
{
    // alphabet A-Z
    string al;
    for (int i = 65; i <= 90; i++)
    {
        al.push_back((char)i);
    }

    vector<float> fre;
    float x;
    // bigram
    for (int i = 0; i < al.length(); i++)
    {
        string s;
        s.push_back(al[i]);
        for (int j = 0; j < al.length(); j++)
        {
            x = static_cast<float>(2 * Count(str, s + al[j])) / str.length();
            fre.push_back(roundf(1000 * x) / 1000);
        }
    }
    return fre;
}

void Out_Bigram(string str, string path)
{
    fstream Out;
    Out.open(path);
    vector<float> fre = Frequency_Bigram(str);
    for (int i = 0; i < fre.size(); i++)
    {
        Out << fre[i] << endl;
    }
    Out.close();
}

float Function(string str, vector<float> bigram)
{
    vector<float> f = Frequency_Bigram(str);
    float s = 0;

    for (int i = 0; i < (26*26); i++)
    {
        float x = f[i] - bigram[i];
        if (x > 0)
        {
            s = s + x;
        }
        else
            s = s - x;
    }
    return s;
}
