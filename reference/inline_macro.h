#include <iostream>

using namespace std;

// inline & macro
// A macro that returns the absolute value of i
#define unsafe(i) \
    ((i) >= 0 ? (i) : -(i))
// An inline function that returns the absolute value of i
inline int safe(int i)
{
    return i >= 0 ? i : -i;
}
int f()
{
    return 0;
}

void userCode(int x)
{
    int ans;
    ans = unsafe(x++); // Error! x is incremented twice
    ans = unsafe(f()); // Danger! f() is called twice
    ans = safe(x++);   // Correct! x is incremented once
    ans = safe(f());   // Correct! f() is called once
}