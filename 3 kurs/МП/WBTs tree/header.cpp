#include "header.h"

node *Insert(node *node_key, int x)
{
    if (node_key == NULL)
    {
        //это произойдет если мы пришли в конец дерево, тогда создадим новый узел
        node *new_node = new node;
        new_node->number = x;
        new_node->left_node = NULL;
        new_node->right_node = NULL;
        node_key = new_node;
    }
    else if (node_key->number < x)
    {
        node_key->right_node = Insert(node_key->right_node, x);
    }
    else if (node_key->number > x)
    {
        node_key->left_node = Insert(node_key->left_node, x);
    }
    return node_key;
};

void Draw(int level, node *node_key)
{
    if (node_key != NULL)
    {
        Draw(level + 1, node_key->right_node);
        cout << endl;
        // выводим на экран "  " по степени узла
        for (int i = 0; i < level; i++)
        {
            cout << setw(5) << " ";
        }
        cout << node_key->number;
        Draw(level + 1, node_key->left_node);
    }
}

void Matrix(node *node_key, vector<int> &C)
{
    if (node_key != NULL)
    {
        C.push_back(node_key->number);
        Matrix(node_key->left_node, C);
        Matrix(node_key->right_node, C);
    }
}

node *InTree(node *node_key, vector<int> C, int l, int r)
{

    if (l == r)
    {
        node_key = Insert(node_key, C[l]);
        return node_key;
    }
    int tmp = (r + l) / 2;

    node_key = Insert(node_key, C[tmp]);
    if (l < tmp)
    {
        InTree(node_key, C, l, tmp - 1);
    }
    if (tmp < r)
    {
        InTree(node_key, C, tmp + 1, r);
    }
    return node_key;
}

node *Bal(node *node_key)
{
    vector<int> C;
    Matrix(node_key, C);
    sort(C.begin(), C.end());
    int l = 0, r = C.size() - 1;
    node *tree = NULL;
    tree = InTree(tree, C, l, r);
    return tree;
}

int Weight(node *node_key)
{
    int x = 0;
    if (node_key == NULL)
    {
        return 0;
    }
    x = x + Weight(node_key->left_node);
    x = x + Weight(node_key->right_node);
    return x + 1;
}
node *Balance(node *node_key)
{
    if (node_key == NULL)
    {
        return node_key;
    }
    if ((node_key->left_node == NULL) && (Weight(node_key) >= 3))
    {
        node_key = Bal(node_key);
    }
    if ((node_key->right_node == NULL) && (Weight(node_key) >= 3))
    {
        node_key = Bal(node_key);
    }

    if ((Weight(node_key) * 0.25 >= Weight(node_key->left_node)) || (Weight(node_key) * 0.25 <= Weight(node_key->right_node)))
    {
        node_key = Bal(node_key);
    }
    node_key->right_node = Balance(node_key->right_node);
    node_key->left_node = Balance(node_key->left_node);
    return node_key;
}
