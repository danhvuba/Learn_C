#include "header.h"
void Set(int **&C, int n, int p)
{
    int i = 0, j = 0;
    while (true)
    {
        C[i][j]++;
        if (C[i][j] == p)
        {
            C[i][j] = 0;
            j++;
            if (j == n)
            {
                j = 0;
                i++;
            }
        }
        else
        {
            i = 0;
            j = 0;
            break;
        }
    }
}

int main()
{
    // ma tran chia khoa
    int **A = new int *[3];
    A[0] = new int[3]{3, 3, 5};
    A[1] = new int[3]{3, 2, 4};
    A[2] = new int[3]{7, 11, 2};

    //lay text
    string str = GetText("Text.txt");

    string text = str;

    cout << "открытый текст\n"
         << str << endl;

    //bo sung phan thieu bang "a"
    int x = str.length() % 3;
    if (x != 0)
    {
        for (int i = 0; i < (3 - x); i++)
        {
            str = str + 'a';
        }
    }
    // them trigram luu so chu thua
    str = str + (char)(3 - x + 97) + 'a' + 'a';

    //chuyen sang dang code bo 3
    int lg = str.length() / 3;
    int **C = CodeText(str);

    //ma hoa bang key A
    // cout << "\n\nпосле зашифрования\n";
    for (int i = 0; i < lg; i++)
    {
        C[i] = Xmatrix(C[i], A);
    }
    // for (int i = 0; i < lg; i++)
    // {
    //     for (int j = 0; j < 3; j++)
    //     {
    //         cout << C[i][j] << " ";
    //     }
    //     cout << "  ";
    // }

    // in text da ma hoa vao CodeText va in ra man hinh
    cout << "\n\nсоответствует текст\n";
    fstream Out;
    Out.open("CodeText.txt");
    for (int i = 0; i < lg; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            cout << (char)(C[i][j] + 97);
            Out << (char)(C[i][j] + 97);
        }
    }
    Out.close();

    //qua trinh nguoc lai
    cout << "\n\nОбратно\n";
    //lay code text
    string str_code = GetText("CodeText.txt");
    cout << str_code << endl;
    lg = str_code.length();

    //lay key
    int **B = new int *[3];

    // int **B = Imatrix(A);
    // for (int i = 0; i < 1; i++)
    // {
    //     for (int j = 0; j < 1; i++)
    //     {
    //         cout << B[i][j] << " "; ???????????????????????????
    //     }
    //     cout << endl;
    // }
    // cout << endl;

    //giai ma va in ra Out, man hinh
    C = CodeText(str_code);
    lg = lg / 3;
    string ot_text;
    // while (true)
    // {
    //     /* code */
    // }
    clock_t times = clock();
    B=Imatrix(A);
    for (int i = 0; i < lg; i++)
    {
        C[i] = Xmatrix(C[i], B);
    }
    for (int i = 0; i < lg - 1; i++)
    {
        if (i < (lg - 2))
        {
            for (int j = 0; j < 3; j++)
            {
                ot_text = ot_text + (char)(C[i][j] + 97);
            }
        }
        else
        {
            for (int j = 0; j < (3 - C[lg - 1][0]); j++)
            {
                ot_text = ot_text + (char)(C[i][j] + 97);
            }
        }
    }
    cout << 1000 * (float)(clock() - times) / CLOCKS_PER_SEC << endl;

    Out.open("Out.txt");
    cout << "\nтекст\n";
    for (int i = 0; i < lg - 1; i++)
    {
        if (i < (lg - 2))
        {
            for (int j = 0; j < 3; j++)
            {
                cout << (char)(C[i][j] + 97);
                Out << (char)(C[i][j] + 97);
            }
        }
        else
        {
            for (int j = 0; j < (3 - C[lg - 1][0]); j++)
            {
                cout << (char)(C[i][j] + 97);
                Out << (char)(C[i][j] + 97);
            }
        }
    }
    cout << endl;

    // cout << "\ntext: " << text << endl;
    // Nu(text);
    // cout << "\ncode: " << str_code << endl;
    // Nu(str_code);
}