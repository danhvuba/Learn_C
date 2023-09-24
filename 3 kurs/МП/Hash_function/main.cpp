#include "hash.h"
int main()
{
    /////////////////////// Метод цепочек
    cout << "Метод цепочек" << endl;
    Hash_Table Table_1;
    for (int i = 0; i < 10; i++)
    {
        int x = rand() % 100;
        Table_1.Insert(x);
    }
    Table_1.Print();
    int x;
    cout << "\n\nfind element: ";
    cin >> x;
    Table_1.Find(x);
    cout << "delete element: ";
    cin >> x;
    Table_1.Delete(x);
    Table_1.Print();

    /////////////////////// Метод открытая адресация
    cout << "\n\nМетод открытая адресация" << endl;
    Hash_Table_Open_Addressing Table_2;
    for (int i = 0; i < 10; i++)
    {
        int x = rand() % 100;
        Table_2.Insert(x);
    }
    Table_2.Print();
    cout << "\n\nfind element: ";
    cin >> x;
    Table_2.Find(x);
    cout << "delete element: ";
    cin >> x;
    Table_2.Delete(x);
    Table_2.Print();

    /////////////////////// Метод aдресация с двойным хешированием
    Hash_Table_Double_Hash_Addressing Table_3;
    for (int i = 0; i < 10; i++)
    {
        int x = rand() % 100;
        Table_3.Insert(x);
    }
    Table_3.Print();
    cout << "\n\nfind element: ";
    cin >> x;
    Table_3.Find(x);
    cout << "delete element: ";
    cin >> x;
    Table_3.Delete(x);
    Table_3.Print();
}