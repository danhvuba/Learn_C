#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <vector>
#include <algorithm>
using namespace std;

struct node
{
    int number;
    node *left_node;
    node *right_node;
};

node *Insert(node *, int); // функция вставки элемента
void Draw(int, node *);    // функция рисования дерево
void Matrix(node *, vector<int> &);
node *InTree(node *, vector<int>, int, int);
node *Bal(node *);
node *Balance(node *);
int Weight(node *);
