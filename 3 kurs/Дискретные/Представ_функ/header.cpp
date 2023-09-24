#include "header.h"

int mul(bitset<n> a, bitset<n> b)
{
    int x = 0;
    for (int i = 0; i < n; i++)
    {
        x = x + a[i] * b[i];
    }
    return x;
}