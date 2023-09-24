//#pragma once
#include "code.h"
#include "frequency.h"

int main()
{
    clock_t times = clock();
    // // text
    // string str;
    // str = GetText("novel1.txt");
    // // str = GetText("tex_text.txt");
    // Forbidden_Gram(str, "forbidden.txt");
    // Out_Bigram(str, "bigram.txt");
    // vector<float> fre1 = Frequency_Bigram(str);

    vector<float> fre;
    fstream In;
    In.open("bigram.txt");
    float f;
    while (In >> f)
    {
        fre.push_back(f);
    }
    In.close();
    // vector<string> f_gram;
    // In.open("forbidden.txt");
    // string s;
    // while (getline(In, s))
    // {
    //     f_gram.push_back(s);
    // }
    // In.close();

    // key
    Matrix A(3, 26);
    A.Mtr[0] = new int[3]{2, 3, 1};
    A.Mtr[1] = new int[3]{3, 1, 0};
    A.Mtr[2] = new int[3]{1, 0, 0};

    // cryption
    string text = GetText("Text.txt");
    cout << "enter:     " << text << "\n   length= " << text.size() << endl;
    string code = Encryption(text, A);
    cout << "code text: " << code << "\n   length= " << code.size() << endl;
    cout << "done, times: " << 1000 * (float)(clock() - times) / CLOCKS_PER_SEC << " ms" << endl;

    // find key
    times = clock();
    Matrix K(3, 26);
    K.Mtr[0] = new int[3]{0, 0, 1};
    K.Mtr[1] = new int[3]{0, 1, 0};
    K.Mtr[2] = new int[3]{1, 0, 0};

    cout << "start with: " << endl;
    K.Print_matrix();

    Matrix Key;
    float delta = 2;
    string text_code;
    // for (int i = 1; i < 26; i++)
    // {
    // for (int i = 1; i < 3; i++)
    // {
    while (true)
    {
        if (K.IS())
        {
            text_code = Decryption(code, K);
            if (Is_Text(text_code))//(true)//
            {
                float del = Function(text_code, fre);
                if (del < delta)
                {
                    K.Print_matrix();
                    Key = K;
                    cout << "text: " << text_code << endl;
                    cout << "del = " << del << endl;
                    delta = del;
                }
            }
        }

        K.SetUp();
        // K.Print_matrix();
        if (K.Mtr[1][1] == 2)
        {
            break;
        }
    }
    cout << "end\n";

    cout << 1000 * (float)(clock() - times) / CLOCKS_PER_SEC << " ms" << text.size() << endl;

    if (Is_Text(Decryption(code, A)))
    {
        cout << "ok" << endl;
    }
}