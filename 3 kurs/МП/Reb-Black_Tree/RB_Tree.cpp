#include "RB_Tree.h"

RB_Tree::RB_Tree()
{
    root = NULL;
};

//левое вращение
void RB_Tree::Left(node *node_key)
{
    //         key                   key'
    //        /   \                 /    \
    //       ?    tmp    ==>       ?     tmp'
    node *tmp = node_key->right_node;
    int val = tmp->number;
    tmp->number = node_key->number;
    node_key->number = val;

    //        key'                   key'
    //       /   \                  /   \
    //      1    tmp'    ==>      tmp'   3
    //          /   \            /  \
    //         2     3          1    2
    node_key->right_node = tmp->right_node;
    if (node_key->right_node != NULL)
    {
        node_key->right_node->parent = node_key;
    }

    tmp->right_node = tmp->left_node;
    if (tmp->right_node != NULL)
    {
        tmp->right_node->parent = tmp;
    }

    tmp->left_node = node_key->left_node;
    if (tmp->left_node != NULL)
    {
        tmp->left_node->parent = tmp;
    }
    node_key->left_node = tmp;
};

// правое вращение
void RB_Tree::Right(node *node_key)
{
    //         key                   key'
    //        /   \                 /    \
    //      tmp    ?      ==>     tmp'    ?
    node *tmp = node_key->left_node;
    int val = tmp->number;
    tmp->number = node_key->number;
    node_key->number = val;

    //         key'                  key'
    //        /   \                 /   \
    //      tmp'   1      ==>      2    tmp'
    //     /   \                        /  \
    //    2     3                      3    1
    node_key->left_node = tmp->left_node;
    if (node_key->left_node != NULL)
    {
        node_key->left_node->parent = node_key;
    }

    tmp->left_node = tmp->right_node;
    if (tmp->left_node != NULL)
    {
        tmp->left_node->parent = tmp;
    }

    tmp->right_node = node_key->right_node;
    if (tmp->right_node != NULL)
    {
        tmp->right_node->parent = tmp;
    }
    node_key->right_node = tmp;
};

node *RB_Tree::Brother(node *node_key)
{
    node *tmp = node_key->parent;
    if (tmp->right_node != node_key)
    {
        return tmp->right_node;
    }
    else
        return tmp->left_node;
};

node *RB_Tree::Find(node *node_key, int x)
{
    if (node_key == NULL)
    {
        return NULL;
    }
    if (node_key->number < x)
    {
        return Find(node_key->right_node, x);
    }
    else if (node_key->number > x)
    {
        return Find(node_key->left_node, x);
    }
    return node_key;
};

void RB_Tree::Fix_Insert(int x)
{
    //  найти узел = х
    node *node_key = Find(root, x);

    // если node_key - не root ||  parent - не black || node_key - не black (сначало это новый ~ red)
    while ((node_key != root) && (node_key->parent->color != 0) && (node_key->color != 0))
    {
        // parent- red
        node *uncl = Brother(node_key->parent);
        node *grand = node_key->parent->parent;
        // uncle -red
        //               grand                    <grand>
        //              /     \        ==>        /     \ 
        //       <parent>     <uncl>          parent     uncl
        //         /                           /
        //      <key>                       <key>
        if ((uncl != NULL) && (uncl->color == 1))
        {
            grand->color = 1;
            node_key->parent->color = 0;
            uncl->color = 0;
            node_key = node_key->parent->parent;
        }
        // ? := uncle - black/NULL -> вращение  ( uncl - black, когда уже вышел выше )
        else
        {
            //   |grand|
            //   /    \
            //  ?     <parent>
            if (grand->right_node == node_key->parent)
            {
                //     <parent>          <parent'>
                //      /          ==>        \
                //   <key>                    <key'>
                if (grand->right_node->left_node == node_key)
                {
                    Right(grand->right_node);
                }
                //       |grand|                      parent = grand'
                //       /    \                     /       \
                //      ?    <parent>   ==>     <grand>     <key>
                //                \               /
                //               <key>           ?
                Left(grand);
                grand->color = 0;
                grand->left_node->color = 1;
            }
            //       grand
            //       /    \
            //  <parent>   ?
            else
            {
                //   <parent>                   <parent'>
                //         \        ==>        /
                //        <key>             <key'>
                if (grand->left_node->right_node == node_key)
                {

                    Left(grand->left_node);
                }
                //         grand                 parent = grand'
                //        /    \                 /    \
                //    <parent>   ?    ==>     <key>   <grand>
                //      /                                \
                //   <key>                                ?
                Right(grand);
                grand->color = 0;
                grand->right_node->color = 1;
            }
        }
        // дальше расмотрим node_key = grand, делать пока: node_key - не root ||  parent - не black || node_key - не black
        node_key = grand;
    }
};

node *RB_Tree::Insert(node *node_key, int x)
{
    if (node_key == NULL)
    {
        //это произойдет если мы пришли в конец дерево, тогда создадим новый узел
        node *new_node = new node;
        new_node->number = x;
        new_node->left_node = NULL;
        new_node->right_node = NULL;
        new_node->parent = NULL;
        new_node->color = 1;
        node_key = new_node;
    }
    else if (node_key->number < x)
    {
        node_key->right_node = Insert(node_key->right_node, x);
        node_key->right_node->parent = node_key;
    }
    else if (node_key->number > x)
    {
        node_key->left_node = Insert(node_key->left_node, x);
        node_key->left_node->parent = node_key;
    }
    return node_key;
};

void RB_Tree::Draw(int level, node *node_key)
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
        if (node_key->color == 0)
        {
            cout << " " << node_key->number << " ";
        }
        else
            cout << "<" << node_key->number << ">";
        Draw(level + 1, node_key->left_node);
    }
};

void RB_Tree::Fix_Remove(int x)
{
    node *bro = Find(root, x);
    node *par = Find(root, bro->parent->number);
    // if (par->right_node == NULL)
    // {
    //     bro = par->left_node;
    // }
    // else
    //     bro = par->right_node;

    // ...............
    if (par->right_node == bro)
    {
        par->left_node = NULL;
    }
    else
        par->right_node = NULL;

    // брат красный
    if (bro->color == 1)
    {
        //           ?                        bro
        //         /    \                   /    \
        //      key     <bro>     ==>   ?-balck   b2
        //              /   \               \
        //             b1    b2            <b1>
        if (bro->parent->right_node == bro)
        {
            int c = par->color;
            Left(par);
            par->color = c;
            par->left_node->color = 0;
            par->left_node->right_node->color = 1;
            return;
        }
        else
        {
            //           ?                     bro
            //         /    \                /    \
            //      <bro>   key   ==>       b1    ?-balck
            //      /   \                          /
            //    b1    b2                       <b2>
            int c = par->color;
            Right(par);
            par->color = c;
            par->right_node->color = 0;
            par->right_node->left_node->color = 1;
            return;
        }
    }

    // брат черный
    // брат имеет 2 сына
    if ((bro->left_node != NULL) && (bro->right_node != NULL))
    {
        //       ?                   bro
        //     /   \    ==>        /      \
        //   key   bro        ? -balck     b2
        //        /   \            \
        //      <b1>  <b2>         <b1>
        if (par->right_node == bro)
        {
            int c = par->color;
            Left(par);
            par->color = c;
            par->left_node->color = 0;
            par->right_node->color = 0;
            return;
        }
        else
        {
            //        ?                   bro
            //      /   \    ==>        /      \
            //    bro   key            b1      ? -balck
            //   /   \                          /
            // <b1>  <b2>                     <b2>
            int c = par->color;
            Right(par);
            par->color = c;
            par->left_node->color = 0;
            par->left_node->color = 0;
            return;
        }
    }
    // брат не имеет сынов
    //       ?             ?
    //     /   \    ==>     \
    //   key   bro         <bro>
    else if ((bro->left_node == NULL) && (bro->right_node == NULL))
    {
        //     <par>           par
        //     /   \    ==>     \
        //   key   bro         <bro>
        if (par->color == 1)
        {
            par->color = 0;
            bro->color = 1;
            return;
        }
        else
        {
            //       b             b
            //     /   \    ==>     \
            //   key   bro         <bro>
            // ...........................
            bro->color = 1;
            Fix_Remove(Brother(par)->number);
            return;
        }
    }
    // брат имеет 1 сын
    else
    {
        if (par->right_node == bro)
        {
            //       ?                   ?
            //     /   \    ==>        /   \  
            //   key   bro          key    bro'
            //        /   \               /   \
            //       <b>  NULL          NULL  <b'>
            if (bro->right_node == NULL)
                Right(bro);
            //       ?                   bro
            //     /   \    ==>        /      \
            //   key   bro        ? -balck     b
            //        /   \
            //      NULL  <b>
            int c = par->color;
            Left(par);
            par->color = c;
            par->left_node->color = 0;
            par->right_node->color = 0;
            return;
        }
        else
        {
            //         ?                   ?
            //       /   \    ==>        /   \  
            //     bro   key          bro'    key
            //    /   \              /   \
            //  NULL  <b>          <b'>   NULL
            if (bro->left_node == NULL)
                Left(bro);
            //         ?                   bro
            //       /   \    ==>        /      \
            //     bro   key            b       ? -balck
            //    /   \
            //  <b>  NULL
            int c = par->color;
            Right(par);
            par->color = c;
            par->right_node->color = 0;
            par->left_node->color = 0;
            return;
        }
    }
    return;
};

node *RB_Tree::Remove(node *node_key, int x)
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
        if (node_key == root)
        {
            delete root;
            return NULL;
        }
        // всегда соверщает когда удалить узел не имеет 2 поддеревев
        // случай не имеет правое поддерево
        if (node_key->right_node == NULL)
        {
            // key - red
            //         <key>
            //         /  \
            //      NULL   NULL
            if (node_key->color == 1)
            {
                delete node_key;
                return NULL;
            }

            // key - black
            if ((node_key->left_node != NULL) && (node_key->left_node->color == 1))
            {
                //           key
                //         /     \
                //      <red>     NULL
                node *tmp = node_key->left_node;
                tmp->parent = node_key->parent;
                tmp->color = 0;
                delete node_key;
                return tmp;
            }
            //           key
            //         /     \
            //      NULL      NULL
            // node *tmp = Find(root, node_key->parent->number);
            // delete node_key;
            // if (tmp->right_node == NULL)
            // {
            //     Fix_Remove(tmp->left_node->number);
            //     return tmp->right_node;
            // }
            // else
            // {
            //     Fix_Remove(tmp->right_node->number);
            //     return tmp->left_node;
            // }
            return node_key;
        }
        else if (node_key->left_node == NULL)
        {
            // случай не имеет левое поддерево, есть правое

            // key - black
            //           key
            //         /     \
            //       NULL   <red>
            node *tmp = node_key->right_node;
            tmp->parent = node_key->parent;
            tmp->color = 0;
            delete node_key;
            return tmp;
        }

        // найдем самый правый узел из левого поддерева
        node *tmp = node_key->left_node;
        while (tmp->right_node != NULL)
        {
            tmp = tmp->right_node;
        }
        node_key->number = tmp->number;
        // удалим узел, который мы уже взял
        node_key->left_node = Remove(node_key->left_node, node_key->number);
    }
    return node_key;
};

void RB_Tree::Get_node(int x)
{
    root = Insert(root, x);
    Fix_Insert(x);
    root->color = 0;
};

void RB_Tree::Display()
{
    Draw(0, root);
    cout << endl;
};

void RB_Tree::Delete(int x)
{
    root = Remove(root, x);
};