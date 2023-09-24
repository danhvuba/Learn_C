#include <iostream>
#include <math.h>
#include <vector>
using namespace std;

const int p = 7;

int Inverse(int x); // x != 0

struct point // (x,y)
{
    int x, y;
    bool index;
    point();
    point(int, int);
    void Print();
};

class Ellipse // y^2 = x^3 + ax + b
{
    void Set_Point();

public:
    int a, b, size;
    struct Dot
    {
        point A;
        int ord;
    };
    vector<Dot> Dot_Ellipse;
    Ellipse(int, int);
    point Add(point, point);
    int Ord(point);
    void Print();
    void Print_Ord();
    // ~Ellipse();
};
