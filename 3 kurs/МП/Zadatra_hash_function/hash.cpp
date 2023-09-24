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
    cout << setw(16) << "номер" << setw(10) << "код" << setw(20) << "на_склад" << setw(13) << "срок" << setw(11) << "кол" << setw(29) << "цена    товар" << endl;
    for (int i = 0; i < M; i++)
    {
        cout << "[" << setw(2) << i << "]";
        node *tmp = table[i];
        while (tmp != NULL)
        {
            cout << endl
                 << setw(8) << tmp->number << setw(10) << tmp->code << setw(14) << tmp->date << setw(7) << tmp->shelf_life << setw(9) << tmp->amount << setw(10) << tmp->price << "     " << tmp->name;
            tmp = tmp->next;
        }
        cout << endl;
    }
}

int Hash_Table::Insert(node *node_key)
{
    const int
    int step = 0;
    int val = Hash_Func(node_key->code);
    if (table[val] == NULL)
    {
        step++;
        table[val] = node_key;
        return step;
    }
    step++;
    node_key->next = table[val];
    table[val] = node_key;
    return step;
}

void Hash_Table::Get_data()
{
    int step = 0;
    int count = 0;
    fstream Input;
    Input.open("input.txt");
    while (!Input.eof())
    {
        count++;
        string tmp;
        node *new_node = new node;
        Input >> new_node->number;
        Input >> new_node->code;
        getline(Input, tmp); // убрать символ \n в конце строки
        getline(Input, new_node->name);
        getline(Input, new_node->date);
        Input >> new_node->shelf_life;
        Input >> new_node->amount;
        Input >> new_node->price;
        new_node->next = NULL;
        step = step + Insert(new_node);
    }
    cout << "Успех, средняя длина при добавлении " << (float)step / count << endl;
}

void Hash_Table::Find(int key)
{
    int step = 0;
    int val = Hash_Func(key);
    node *tmp = table[val];
    while (tmp != NULL)
    {
        step++;
        if (tmp->code == key)
        {
            cout << "Товар с кодом " << key << " - это " << tmp->name << " в table[" << val << "]" << endl;
            cout << "Количество шагов " << step << endl;
            return;
        }
        else
            tmp = tmp->next;
        step++;
    }
    cout << "Товар с кодом " << key << " нет в хэш-таблице" << endl;
    cout << "Количество шагов " << step << endl;
    return;
}

void Hash_Table::Delete(int key)
{
    int step = 0;
    int val = Hash_Func(key);
    node *tmp = table[val]; // искомый товар
    node *par = tmp;        // указатель на родитель
    while (tmp != NULL)
    {
        if (tmp->code == key)
        {
            step++;
            //            tmp
            // table[] =  *** -> ......
            if (tmp == table[val])
            {
                table[val] = tmp->next;
                delete tmp;
                cout << "Количество шагов " << step << endl;
                return;
            }
            //             par    tmp
            // table[]  = ____ -> *** -> .....
            if (par == table[val])
            {
                table[val]->next = tmp->next;
            }
            //         par    tmp
            // .... -> ___ -> *** -> ....
            else
                par->next = tmp->next;
            delete tmp;
            cout << "Количество шагов " << step << endl;
            return;
        }
        else
        {
            step++;
            par = tmp;
            tmp = tmp->next;
        }
    }
    cout << "Товар с кодом " << key << " не найден" << endl;
    cout << "Количество шагов " << step << endl;
    return;
}

Hash_Table::~Hash_Table()
{
    for (int i = 0; i < M; i++)
    {
        delete table[i];
    }
}