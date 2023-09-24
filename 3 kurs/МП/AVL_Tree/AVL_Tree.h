#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <fstream>
#include <ctime>
using namespace std;

struct node
{
    int number;
    node *left_node;
    node *right_node;
};

class AVL_Tree
{
private:
    node *root;

    node *Insert(node *, int); // функция вставки элемента
    void Draw(int, node *);    // функция рисования дерево
    int Hight(node *);         // функция вычисления высоты
    node *Left(node *);        // левое вращение
    node *Right(node *);       // правое вращение
    node *Balance(node *);     // функция балансирования
    node *Remove(node *, int); // функция удаления
public:
    AVL_Tree();
    void Display();                                               // выводить на экран
    void Get_node(int);                                           // добавить элемент в дерево
    void Delete(int);                                             // удалить элемент
    void Find(int, int &, int &, float &, int &, int &, float &); // поиск узла
};
