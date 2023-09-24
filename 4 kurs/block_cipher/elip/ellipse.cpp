#include "ellipse.h"

int Inverse(int x)
{
    for (int i = 1; i < p; i++)
    {
        if ((i * x) % p == 1)
        {
            return i;
        }
    }
    return 0;
}

Ellipse::Ellipse(int x, int y)
{
    a = x % p;
    b = y % p;
    cout << "Ellipse: y^2 = x^3 + " << a << "x + " << b << endl;
    Dot D;
    D.ord = 0;
    Dot_Ellipse.push_back(D);
    Set_Point();
}

int Ellipse::Ord(point A)
{
    int ord = 1;
    point B = A;
    while (B.index != 0)
    {
        B = Add(B, A);
        ord++;
    }
    return ord;
}

// Ellipse::~Ellipse()
// {
//     cout << "Ellipse has destroyed" << endl;
// }

void Ellipse::Set_Point()
{
    for (int i = 0; i < p; i++)
    {
        int f_x = (i * i * i + a * i + b) % p;
        for (int j = 0; j < p; j++)
        {
            if (((j * j) % p) == f_x)
            {
                Dot D;
                D.A = point(i, j);
                D.ord = Ord(D.A);
                Dot_Ellipse.push_back(D);
            }
        }
    }

    size = Dot_Ellipse.size();
}

void Ellipse::Print()
{
    for (int i = 0; i < size; i++)
    {
        Dot_Ellipse.at(i).A.Print();
        //cout << "-" << Dot_Ellipse.at(i).ord << "   ";
    }
    cout << endl;
}

void Ellipse::Print_Ord()
{
    for (int i = 0; i < size; i++)
    {
        Dot_Ellipse.at(i).A.Print();
        cout << "-" << Dot_Ellipse.at(i).ord << "   ";
    }
    cout << endl;
}

point::point()
{
    index = 0;
}

point::point(int i, int j)
{
    x = i;
    y = j;
    index = 1;
}

point Ellipse::Add(point A, point B)
{
    if (A.index == 0)
    {
        return B;
    }
    if (B.index == 0)
    {
        return A;
    }

    if (A.x != B.x)
    {
        int lambda = (B.y - A.y + p) * Inverse((B.x - A.x + p) % p) % p;
        int i = (lambda * lambda - A.x - B.x + 2 * p) % p;
        int j = (lambda * (A.x - i + p) - A.y + p) % p;
        point C(i, j);
        return C;
    }

    // x1 = x2 ---> |y1| = |y2|
    if ((A.y + B.y) % p == 0) /// has y1=y2=0
    {
        point O(p, p);
        O.index = 0;
        return O;
    }

    // y1 = y2 != 0
    int lambda = (3 * A.x * A.x + a) * Inverse((2 * A.y % p)) % p;
    int i = (lambda * lambda - 2 * A.x + 2 * p) % p;
    int j = (lambda * (A.x - i + p) - A.y + p) % p;
    point C(i, j);
    return C;
}

void point::Print()
{
    if (index)
    {
        cout << "  (" << x << "," << y << ")";
    }
    else
        cout << "  _O_";
}