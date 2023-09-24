#include <iostream>

using namespace std;

// tham chieu den dia chi cua x
// calloc, realloc, malloc
// khi cap phat bo nho bang realloc thi se sua vao dia chi moi
void calloc_realloc(int *&x, int &lg)
{
    x[lg] = 1;
    lg++;
    for (int i = 0; i < 2; i++)
    {
        lg++;
        x = (int *)realloc(x, lg * sizeof(int));
        x[lg - 1] = i;
    }
}