#include "RB_Tree.h"

int main()
{
    RB_Tree tree;
    for (int i = 0; i < 20; i++)
    {
        int a = rand() % 100;
        cout << "\nДобавить " << a << endl;
        tree.Get_node(a);
        cout << "Новое дерево:\n";
        tree.Display();
    }
    for (int i = 0; i < 10; i++)
    {
        int x;
        cout << "Удалим узел: ";
        cin >> x;
        tree.Delete(x);
        tree.Display();
    }
}