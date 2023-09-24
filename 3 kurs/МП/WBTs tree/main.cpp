#include "header.h"

int main()
{
    vector<int> C;
    node *tree = NULL;
    int n;
    cout << "Ввeдитe количество элементов: ";
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        int a = rand() % (10 * n);
        cout<<"insert "<<a<<endl;
        tree = Insert(tree, a);
        Draw(0, tree);
        cout << "\n-------------------\n";
        tree = Balance(tree);
        Draw(0, tree);
        cout << "\n-------------------\n";
    }
}