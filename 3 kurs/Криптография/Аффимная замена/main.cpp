#include <iostream>
#include <fstream>
using namespace std;

string GetText(string x)
{
    string str;
    fstream input;
    input.open(x);
    if (input.fail())
    {
        cout << "can't open" << endl;
    }
    char a;
    while (input.get(a))
    {
        str = str + a;
    }
    input.close();
    return str;
}

int main()
{
    string str;
    str = GetText("input.txt");
    cout << str << endl;
    int n = 3;

    for (int m = 0; m < 26; m++)
    {
        cout << "m= " << m << "  ";
        for (int i = 0; i < str.length(); i++)
        {
            int x = (int)str[i] - 65;
            cout << (char)(65 + ((x - m + 260) * n) % 26);
        }
        cout << endl
             << endl;
    }
}