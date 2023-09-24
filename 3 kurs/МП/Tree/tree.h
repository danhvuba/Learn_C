#include <iostream>
#include<iomanip>
//#include<cstdlib>
using namespace std;

struct node
{
    int *number;
    node *left_node;
    node *right_node;
};

node *Find(node *, int);
node *Insert(node *, int);
node* Remove(node *, int);
void Print(node *);
void Draw(int, node*);
