#include "ellipse.h"

int main()
{
    // int a, b, size = 0;

    // for (int i = 0; i < p; i++)
    // {
    //     for (int j = 0; j < p; j++)
    //     {
    //         Ellipse E(i, j);
    //         cout << E.size << endl;
    //         if (E.size > size)
    //         {
    //             size = E.size;
    //             a = i;
    //             b = j;
    //         }
    //     }
    // }
    // cout << "/////////////////////" << endl;
    // Ellipse E(a, b);

    Ellipse E(0, 3);
    cout << "size: " << E.size << endl;
    E.Print_Ord();
    // for (int j = 0; j < E.size; j++)
    // {
    //     point A = E.Dot_Ellipse.at(j).A;
    //     for (int i = 0; i < E.size; i++)
    //     {
    //         A = E.Add(A, E.Dot_Ellipse.at(j).A);
    //         A.Print();
    //     }
    //     cout << endl;
    // }
}