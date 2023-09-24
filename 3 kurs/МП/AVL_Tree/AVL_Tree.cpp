#include "AVL_Tree.h"

AVL_Tree::AVL_Tree()
{
    root = NULL;
}

node *AVL_Tree::Insert(node *node_key, int x)
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
    node_key = Balance(node_key);
    return node_key;
};

void AVL_Tree::Draw(int level, node *node_key)
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

//левое вращение
node *AVL_Tree::Left(node *node_key)
{
    if (Hight(node_key->right_node->left_node) > Hight(node_key->right_node->right_node))
    {
        // двойное вращение
        node_key->right_node = Right(node_key->right_node);
    }
    node *tmp = node_key->right_node;
    node_key->right_node = tmp->left_node;
    tmp->left_node = node_key;
    return tmp;
}

// правое вращение
node *AVL_Tree::Right(node *node_key)
{
    if (Hight(node_key->left_node->left_node) < Hight(node_key->left_node->right_node))
    {
        // двойное вращение
        node_key->left_node = Left(node_key->left_node);
    }
    node *tmp = node_key->left_node;
    node_key->left_node = tmp->right_node;
    tmp->right_node = node_key;
    return tmp;
}

int AVL_Tree::Hight(node *node_key)
{
    int r = 0, l = 0;
    // r- высота правого поддерева; l- высота левого поддерева
    if (node_key == NULL)
    {
        return -1;
    }
    if (node_key->right_node != NULL)
    {
        r = r + 1 + Hight(node_key->right_node);
    }
    if (node_key->left_node != NULL)
    {
        l = l + 1 + Hight(node_key->left_node);
    }
    if (r >= l)
    {
        return r;
    }
    return l;
}

node *AVL_Tree::Balance(node *node_key)
{
    if ((Hight(node_key->left_node) - Hight(node_key->right_node)) < -1)
    {
        // правое поддерево выше
        node_key = Left(node_key);
    }
    else if ((Hight(node_key->left_node) - Hight(node_key->right_node)) > 1)
    {
        // левое поддерево выше
        node_key = Right(node_key);
    }
    return node_key;
}

node *AVL_Tree::Remove(node *node_key, int x)
{
    if (node_key == NULL)
    {
        return node_key;
    }
    else if (node_key->number < x)
    {
        node_key->right_node = Remove(node_key->right_node, x);
    }
    else if (node_key->number > x)
    {
        node_key->left_node = Remove(node_key->left_node, x);
    }
    else if (node_key->number == x) // уже нашли элемент
    {
        if (node_key->right_node == NULL)
        {
            // случай не имеет правое поддерево
            node *new_node = node_key->left_node;
            delete node_key;
            return new_node;
        }
        else if (node_key->left_node == NULL)
        {
            // случай не имеет левое поддерево
            node *new_node = node_key->right_node;
            delete node_key;
            return new_node;
        }

        // найдем самый правый узел из левого поддерева
        node *tmp = node_key->left_node;
        while (tmp->right_node != NULL)
        {
            tmp = tmp->right_node;
        }
        node_key->number = tmp->number;
        // удалим узел, который мы уже взял
        node_key->left_node = Remove(node_key->left_node, tmp->number);
    }
    // балансировать дерево
    node_key = Balance(node_key);
    return node_key;
};

void AVL_Tree::Get_node(int x)
{
    root = Insert(root, x);
};

void AVL_Tree::Display()
{
    Draw(0, root);
    cout << endl;
};

void AVL_Tree::Delete(int x)
{
    root = Remove(root, x);
};

void AVL_Tree::Find(int x, int &Y, int &y, float &t1, int &N, int &n, float &t2)
{
    clock_t time_start = clock();
    node *tmp = root;
    int step = 0;
    while (tmp != NULL)
    {
        if (tmp->number == x)
        {
            step++;
            cout << "Ключ " << setw(3) << x << "    найден, Число сравнений " << step << endl;
            t1=t1+1000*(float)(clock()-time_start)/CLOCKS_PER_SEC;
            Y = Y + step;
            y++;
            return;
        }
        else if (tmp->number < x)
        {
            step++;
            tmp = tmp->right_node;
        }
        else
        {
            step++;
            tmp = tmp->left_node;
        }
    }
    if (tmp == NULL)
    {
        step++;
        cout << "Ключ " << setw(3) << x << " не найден, Число сравнений " << step << endl;
        t2=t2+1000*(float)(clock()-time_start)/CLOCKS_PER_SEC;
        N = N + step;
        n++;
        return;
    }
};