template<class T>
void BSTree::Display(int level, BSTNode<T> *node)
{
    if (node != NULL)
    {
        Display(level + 1, node->right);
        cout << endl;
        for (int i = 0; i < level; i++)
            cout << setw(5) << " ";
        cout << *node->key;
        Display(level+1, node->left);
    }
}
template<class T>
void BSTree::Display()
{
    Display(0, root);
}
