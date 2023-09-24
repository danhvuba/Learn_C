#include "tree.h"

int main()
{
    node *tree = NULL;
    srand(time(NULL));
    int n;
    cout << "enter number of element: ";
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        int a = rand()%100;
        tree = Insert(tree, a);
    }
    cout << "elements of the tree: ";
    Print(tree);
    cout << endl;
    Draw(0, tree);
    cout << endl;

    int val;
    cout << "search number: ";
    cin >> val;
    node *x = Find(tree, val);
    if (x != NULL)
    {
        cout << "&node " << *x->number << "= " << x << endl;
    }
    else
        cout << "number " << val << " isn't in the tree" << endl;

    cout << "delete number: ";
    cin >> val;
    tree = Remove(tree, val);

    cout << "new tree: ";
    Print(tree);
    Draw(0, tree);
    cout << endl;
}