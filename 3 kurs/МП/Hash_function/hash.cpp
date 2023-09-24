#include "hash.h"

int Hash_Func(int key)
{
    return (key % M);
}

/////////////////////// Метод цепочек
Hash_Table::Hash_Table()
{
    table = new node *[M];
}

void Hash_Table::Print()
{
    cout << "Hash Table:" << endl;
    for (int i = 0; i < M; i++)
    {
        cout << "table[" << setw(2) << i << "] ";
        node *tmp = table[i];
        while (tmp != NULL)
        {
            cout << " -> " << tmp->data;
            tmp = tmp->next;
        }
        cout << endl;
    }
}

void Hash_Table::Insert(int key)
{
    node *new_node = new node;
    new_node->data = key;
    new_node->next = NULL;
    int val = Hash_Func(key);
    if (table[val] == NULL)
    {
        table[val] = new_node;
    }
    else
    {
        new_node->next = table[val];
        table[val] = new_node;
    }
}

void Hash_Table::Find(int key)
{
    int val = Hash_Func(key);
    node *tmp = table[val];
    while (tmp != NULL)
    {
        if (tmp->data == key)
        {
            cout << "element " << key << " is on table[" << val << "]" << endl;
            return;
        }
        else
            tmp = tmp->next;
    }
    cout << "element " << key << " isn't on table" << endl;
}

void Hash_Table::Delete(int key)
{
    int val = Hash_Func(key);
    node *tmp = table[val];
    node *par = tmp;
    while (tmp != NULL)
    {
        if (tmp->data == key)
        {
            if (tmp == table[val])
            {
                table[val] = tmp->next;
                delete tmp;
                return;
            }

            if (par == table[val])
            {
                table[val]->next = tmp->next;
            }
            else
                par->next = tmp->next;
            delete tmp;
            return;
        }
        else
        {
            par = tmp;
            tmp = tmp->next;
        }
    }
    cout << "element " << key << " not found" << endl;
}

/////////////////////// Метод открытая адресация
Hash_Table_Open_Addressing::Hash_Table_Open_Addressing()
{
    table = new int *[M];
}

void Hash_Table_Open_Addressing::Print()
{
    cout << "Hash Table:" << endl;
    for (int i = 0; i < M; i++)
    {
        cout << "table[" << setw(2) << i << "] ";
        if ((table[i] != NULL) && (table[i] != &deleted))
        {
            cout << *table[i];
        }
        cout << endl;
    }
}

void Hash_Table_Open_Addressing::Insert(int key)
{
    int val = Hash_Func(key);
    while ((table[val] != NULL) && (table[val] != &deleted))
    {
        if (*table[val] == key)
        {
            cout << "element " << key << " was on table" << endl;
            return;
        }

        val++;
        if (val == M)
        {
            val = 0;
        }
        if (val == Hash_Func(key))
        {
            cout << "table is full" << endl;
            return;
        }
    }
    int *new_val = new int{key};
    table[val] = new_val;
}

void Hash_Table_Open_Addressing::Find(int key)
{
    int val = Hash_Func(key);
    while (table[val] != NULL)
    {
        if ((table[val] != &deleted) && (*table[val] == key))
        {
            cout << "element " << key << " is on table[" << val << "]" << endl;
            return;
        }

        val++;
        if (val == M)
        {
            val = 0;
        }
        if (val == Hash_Func(key))
        {
            break;
        }
    }
    cout << "element " << key << " not found" << endl;
}

void Hash_Table_Open_Addressing::Delete(int key)
{
    int val = Hash_Func(key);
    while (table[val] != NULL)
    {
        if ((table[val] != &deleted) && (*table[val] == key))
        {
            delete table[val];
            table[val] = &deleted;
            return;
        }

        val++;
        if (val == M)
        {
            val = 0;
        }
        if (val == Hash_Func(key))
        {
            break;
        }
    }
    cout << "element " << key << " not found" << endl;
}

/////////////////////// Метод aдресация с двойным хешированием
bool Is_Simple(int key)
{
    if (key < 2)
    {
        return false;
    }

    for (int i = 2; i < key; i++)
    {
        if ((key % i == 0) && (M % i == 0))
        {
            return false;
        }
    }
    return true;
}
int Hash_Func_2(int key)
{
    int val = Hash_Func(key);
    while (true)
    {
        if (Is_Simple(val))
        {
            return val;
        }
        val++;
        if (val == M)
        {
            val = 2;
        }
    }
}

Hash_Table_Double_Hash_Addressing::Hash_Table_Double_Hash_Addressing()
{
    table = new int *[M];
}

void Hash_Table_Double_Hash_Addressing::Print()
{
    cout << "Hash Table:" << endl;
    for (int i = 0; i < M; i++)
    {
        cout << "table[" << setw(2) << i << "] ";
        if ((table[i] != NULL) && (table[i] != &deleted))
        {
            cout << *table[i];
        }
        cout << endl;
    }
}

void Hash_Table_Double_Hash_Addressing::Insert(int key)
{
    int val = Hash_Func(key);
    while ((table[val] != NULL) && (table[val] != &deleted))
    {
        if (*table[val] == key)
        {
            cout << "element " << key << " was on table" << endl;
            return;
        }
        int c = Hash_Func_2(key);
        val = val - c;
        if (val < 0)
        {
            val = val + M;
        }
        if (val == Hash_Func(key))
        {
            cout << "table is full" << endl;
            return;
        }
    }
    int *new_val = new int{key};
    table[val] = new_val;
}

void Hash_Table_Double_Hash_Addressing::Find(int key)
{
    int val = Hash_Func(key);
    while (table[val] != NULL)
    {
        if ((table[val] != &deleted) && (*table[val] == key))
        {
            cout << "element " << key << " is on table[" << val << "]" << endl;
            return;
        }
        int c = Hash_Func_2(key);
        val = val - c;
        if (val < 0)
        {
            val = val + M;
        }
        if (val == Hash_Func(key))
        {
            break;
        }
    }
    cout << "element " << key << " not found" << endl;
}

void Hash_Table_Double_Hash_Addressing::Delete(int key)
{
    int val = Hash_Func(key);
    while (table[val] != NULL)
    {
        if ((table[val] != &deleted) && (*table[val] == key))
        {
            delete table[val];
            table[val] = &deleted;
            return;
        }

        int c = Hash_Func_2(key);
        val = val - c;
        if (val < 0)
        {
            val = val + M;
        }
        if (val == Hash_Func(key))
        {
            break;
        }
    }
    cout << "element " << key << " not found" << endl;
}