#include "KMP.h"
#include "RP.h"
#include "Auto.h"
#include "BM.h"
#include <fstream>

void Simple_Search(string text, string frag, int &step)
{
    for (int r = 0; r < text.length() - frag.length(); r++)
    {
        int i = 0;
        while ((i < frag.length()) && (frag[i] == text[i + r]))
        {
            step++;
            i++;
        }
        step++;
        if (i == frag.length())
        {
            cout << "   Допустимый сдвиг " << r << endl;
        }
    }
};

int main()
{
    string text, frag;
    fstream input;
    input.open("text.txt");
    char a;
    while (input.get(a))
    {
        text = text + a;
    }
    input.close();

    cout << "Текст:\n"
         << text << "\n\nФрагмент:";
    getline(cin, frag);

    int step1 = 0, step2 = 0, step3 = 0, step4 = 0, step5 = 0;
    cout << "\nПростой поиск:" << endl;
    Simple_Search(text, frag, step1);

    cout << "КМП - поиск:" << endl;
    KMP_Search(text, frag, step2);

    cout << "RP - поиск:" << endl;
    RP_Search(text, frag, step3);

    cout << "Поиск с помощью конечного автомата:" << endl;
    Search(text, frag, step4);

    cout << "BM - поиск:" << endl;
    BM_Search(text, frag, step5);

    cout << "\nКоличество сравнений:\n";
    cout << "Простой поиск:                      " << step1 << endl;
    cout << "КМП - поиск:                        " << step2 << endl;
    cout << "RP - поиск:                         " << step3 << endl;
    cout << "Поиск с помощью конечного автомата: " << step4 << endl;
    cout << "BM - поиск:                         " << step5 << endl;
}
