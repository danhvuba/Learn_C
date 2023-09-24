#include "AVL_Tree.h"

int main()
{
    AVL_Tree Tree;
    fstream KeyFile;
    KeyFile.open("key_file.txt");
    int x;
    while (KeyFile >> x)
    {
        Tree.Get_node(x);
    }
    KeyFile.close();
    cout << "Дерево:" << endl;
    Tree.Display();

    fstream KeySearch;
    KeySearch.open("key_search.txt");
    int Y, y, N, n;
    float t1, t2;
    Y = y = N = n = 0;
    t1 = t2 = 0;
    while (KeySearch >> x)
    {
        Tree.Find(x, Y, y, t1, N, n, t2);
    }
    cout << "Среднее число сравнений при удачном поиске " << static_cast<float>(Y) / y << "\nСреднее время: " << t1 / y << " ms" << endl;
    cout << "Среднее число сравнений при не удачном поиске " << static_cast<float>(N) / n << "\nСреднее время: " << t2 / n << " ms" << endl;
}