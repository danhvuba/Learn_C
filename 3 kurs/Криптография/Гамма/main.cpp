#include "header.h"

int main()
{
    vector<string> tx;
    // bo Ё Й Ъ

    tx.push_back("А"); // 0
    tx.push_back("Б"); // 1
    tx.push_back("В"); // 2
    tx.push_back("Г"); // 3
    tx.push_back("Д"); // 4
    tx.push_back("Е"); // 5
    // tx.push_back("Ё"); // 6 --------------------------1
    tx.push_back("Ж"); // 7
    tx.push_back("З"); // 8
    tx.push_back("И"); // 9
    tx.push_back("Й"); // 10
    tx.push_back("К"); // 11
    tx.push_back("Л"); // 12
    tx.push_back("М"); // 13
    tx.push_back("Н"); // 14
    tx.push_back("О"); // 15
    tx.push_back("П"); // 16
    tx.push_back("Р"); // 17
    tx.push_back("С"); // 18
    tx.push_back("Т"); // 19
    tx.push_back("У"); // 20
    tx.push_back("Ф"); // 21
    tx.push_back("Х"); // 22
    tx.push_back("Ц"); // 23
    tx.push_back("Ч"); // 24
    tx.push_back("Ш"); // 25
    tx.push_back("Щ"); // 26
    tx.push_back("Ъ"); // 27
    tx.push_back("Ы"); // 28
    tx.push_back("Ь"); // 29
    tx.push_back("Э"); // 30
    tx.push_back("Ю"); // 31
    tx.push_back("Я"); // 32
    tx.push_back(" "); // 33

    for (int i = 0; i < tx.size(); i++)
    {
        cout << tx[i];
    }
    cout << endl
         << endl;

    string str;
    str = Get("text.txt");
    vector<vector<string>> text = Get_text(str);
    for (int i = 0; i < 5; i++)
    {
        Print(text[i]);
    }
    cout << endl;

    vector<vector<int>> text_num = To_Int(text, tx);
    for (int i = 0; i < text_num.size(); i++)
    {
        for (int j = 0; j < text_num[i].size(); j++)
        {
            cout << setw(3) << text_num[i][j];
        }
        cout << endl
             << endl;
    }

    vector<vector<int>> num_sub;
    for (int i = 0; i < 4; i++)
    {
        vector<int> sub;
        for (int j = 0; j < text_num[i].size(); j++)
        {
            sub.push_back(text_num[i][j] - text_num[i + 1][j]);
        }
        num_sub.push_back(sub);
    }

    vector<int> key = {10, 0, 10, 14, 5};

    for (int i = 0; i < num_sub[0].size() - 5; i++)
    {
        cout << "i= " << i << "  ";
        for (int j = 0; j < 5; j++)
        {
            cout << tx[(-num_sub[1][i + j] + key[j] + 330) % 33];
        }
        cout << endl;
        for (int j = 0; j < 5; j++)
        {

            cout << num_sub[1][i + j] << "  ";
        }
        cout << endl;
    }

    // key = {32,10, 0, 10, 14, 5,32,29,18,14,32,12,14,6,5,18};
    key = {13, 14, 32, 4, 0, 6, 5, 32, 5, 17, 11, 8, 32, 14, 13, 8, 32, 8, 32, 15, 14, 4, 18, 2, 5, 16, 4, 31, 18, 17, 31, 7, 15, 18, 32, 10, 0, 10, 14, 5, 32, 29, 18, 14, 32, 12, 14, 6, 5, 18};
    int i = 0;
    cout << "----------------------------------------\n\n2-line: i= " << i << endl;
    cout << "\n1-line:  ";
    for (int j = 0; j < key.size(); j++)
    {
        cout << tx[(num_sub[0][i + j] + key[j] + 330) % 33];
    }
    cout << endl;
    // for (int j = 0; j < key.size(); j++)
    // {

    //     cout << num_sub[0][i + j] << "  ";
    // }
    cout << endl;

    cout << "2-line:  ";
    for (int j = 0; j < key.size(); j++)
    {
        cout << tx[(key[j] + 330) % 33];
    }
    cout << endl;
    // for (int j = 0; j < key.size(); j++)
    // {

    //     cout << num_sub[0][i + j] << "  ";
    // }
    cout << endl;

    cout << "3-line:  ";
    for (int j = 0; j < key.size(); j++)
    {
        cout << tx[(-num_sub[1][i + j] + key[j] + 330) % 33];
    }
    cout << endl;
    // for (int j = 0; j < key.size(); j++)
    // {

    //     cout << num_sub[1][i + j] << "  ";
    // }
    cout << endl;

    /// new key
    for (int j = 0; j < key.size(); j++)
    {
        key[j] = (-num_sub[1][i + j] + key[j] + 330) % 33;
    }
    cout << "4-line:  ";
    for (int j = 0; j < key.size(); j++)
    {
        cout << tx[(-num_sub[2][i + j] + key[j] + 330) % 33];
    }
    cout << endl
         << endl;
    // for (int j = 0; j < key.size(); j++)
    // {

    //     cout << num_sub[2][i + j] << "  ";
    // }
    // cout << endl;

    /// new key
    for (int j = 0; j < key.size(); j++)
    {
        key[j] = (-num_sub[2][i + j] + key[j] + 330) % 33;
    }
    cout << "5-line:  ";
    for (int j = 0; j < key.size(); j++)
    {
        cout << tx[(-num_sub[3][i + j] + key[j] + 330) % 33];
    }
    cout << endl;
    // for (int j = 0; j < key.size(); j++)
    // {

    //     cout << num_sub[3][i + j] << "  ";
    // }
    // cout << endl;

    for (int t = 0; t < 50; t++)
    {
        cout << tx[(text_num[2][t] - key[t]+33)%33] << "  ";
    }
    cout << endl;
}