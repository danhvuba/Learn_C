#include "tree.h"

node *Find(node *node_key, int x)
{
    if (node_key == NULL)
    {
        return NULL;
    }

    if (*node_key->number < x)
    {
        return Find(node_key->right_node, x);
    }
    else if (*node_key->number > x)
    {
        return Find(node_key->left_node, x);
    }
    return node_key;
};

node *Insert(node *node_key, int x)
{
    if (node_key == NULL)
    {
        node *new_node = new node;
        new_node->number = new int;
        new_node->left_node = new node;
        new_node->right_node = new node;
        *new_node->number = x;
        new_node->left_node = NULL;
        new_node->right_node = NULL;
        node_key = new_node;
    }
    else if (*node_key->number < x)
    {
        node_key->right_node = Insert(node_key->right_node, x);
    }
    else if (*node_key->number > x)
    {
        node_key->left_node = Insert(node_key->left_node, x);
    }
    else
        cout << "number " << x << " already in the tree" << endl;

    return node_key;
};

node *Remove(node *node_key, int x)
{
    if (node_key == NULL)
    {
        cout << "number " << x << " isn't in the tree" << endl;
    }
    else if (*node_key->number < x)
    {
        node_key->right_node = Remove(node_key->right_node, x);
    }
    else if (*node_key->number > x)
    {
        node_key->left_node = Remove(node_key->left_node, x);
    }
    else if (*node_key->number == x)
    {
        if (node_key->right_node == NULL)
        {
            node *new_node = node_key->left_node;
            delete node_key;
            return new_node;
        }
        else if (node_key->left_node == NULL)
        {
            node *new_node = node_key->right_node;
            delete node_key;
            return new_node;
        }
        node *tmp = node_key->left_node;
        while (tmp->right_node != NULL)
        {
            tmp = tmp->right_node;
        }
        *node_key->number = *tmp->number;
        node_key->left_node = Remove(node_key->left_node, *tmp->number);
    }

    return node_key;
};

void Print(node *node_key)
{
    if (node_key)
    {
        cout << " " << *node_key->number;
        Print(node_key->right_node);
        Print(node_key->left_node);
    };
};

void Draw(int level, node *node_key)
{
    if (node_key != NULL)
    {
        Draw(level + 1, node_key->right_node);
        cout << endl;
        for (int i = 0; i < level; i++)
        {
            cout << setw(5) << " ";
        }
        cout << *node_key->number;
        Draw(level + 1, node_key->left_node);
    }
}

// vector<int> Matrix(node *node_key)
// {

// }
