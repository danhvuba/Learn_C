#include <iostream>
#include <cstdlib>
#include <iomanip>
#include <string>
#include <fstream>
using namespace std;

const int M = 11;

int Hash_Func(int);

// Метод цепочек
struct node
{
    int number;     // номер склада
    int code;       // код товара - key
    string name;    // наименование товара
    string date;    // дата поступления на склад
    int shelf_life; // срок хранения в дня
    int amount;     // количество единиц товара
    int price;      // цена за единицу товара
    node *next;
};

class Hash_Table
{
private:
    node **table;
    int Insert(node *);
public:
    Hash_Table();
    void Print();
    void Get_data();
    void Find(int);
    void Delete(int);
    ~Hash_Table();
};
