#include <iostream>
#include <cstdlib>
#include <iomanip>
using namespace std;

const int M = 13;

int Hash_Func(int);

// Метод цепочек
struct node
{
    int data;
    node *next;
};

class Hash_Table
{
private:
    node **table;

public:
    Hash_Table();
    void Print();
    void Insert(int);
    void Find(int);
    void Delete(int);
};

// Метод открытая адресация
class Hash_Table_Open_Addressing
{
private:
    int **table;
    int deleted = 0;

public:
    Hash_Table_Open_Addressing();
    void Print();
    void Insert(int);
    void Find(int);
    void Delete(int);
};

// Метод aдресация с двойным хешированием
bool Is_Simple(int);
int Hash_Func_2(int);

class Hash_Table_Double_Hash_Addressing
{
private:
    int **table;
    int deleted = 0;

public:
    Hash_Table_Double_Hash_Addressing();
    void Print();
    void Insert(int);
    void Find(int);
    void Delete(int);
};
