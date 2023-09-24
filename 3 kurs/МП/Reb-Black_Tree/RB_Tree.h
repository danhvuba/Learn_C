#include <iostream>
#include <iomanip>
#include <cstdlib>
using namespace std;

struct node
{
    int number;
    node *parent;
    node *left_node;
    node *right_node;
    // 0 - black , 1 - red <...>
    int color;
};

class RB_Tree
{
private:
    node *root;

    void Left(node *);         // левое вращение
    void Right(node *);        // правое вращение
    node *Brother(node *);     // брат этого узла
    void Fix_Insert(int);      // балансирование начиная с узла = int (после вставки)
    node *Insert(node *, int); // функция вставки элемента
    void Draw(int, node *);    // функция рисования дерево
    node *Remove(node *, int); // функция удаления
    void Fix_Remove(int);

public:
    RB_Tree();
    void Display();          // выводить на экран
    void Get_node(int);      // добавить элемент в дерево
    void Delete(int);        // удалить элемент
    node *Find(node *, int); // поиск узла
};