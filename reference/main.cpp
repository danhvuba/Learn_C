// #pragma once
#include <iostream>
#include <vector>
#include "calloc_realloc.h"

/// so sanh luon luon te
// biet duoc so vong lap thif dung luon
using namespace std;

// what Is
#define whatIs(x) cerr << "Line " << __LINE__ << ": " << #x << " = " << (x) << endl
// #define whatIs(n) printf("Line %d: %s = %04x\n",__LINE__, #n, n)

// size_t be careful
// nen dung size_t khi tra ve, so sanh kich thuoc
// hoac kich thuoc lon
void size_t_loop()
{
    vector<int> a = {2, 3};

    // infinity loop
    for (size_t i = a.size(); i >= 0; i--)
    {
        printf("hello\n");
    }
    // If you're worried that v.size() could go above 2,147,483,647, use size_t.
    // If you're using i inside your loop for ____more____ than just looking inside the vector,
    // and you're concerned about subtle signed/unsigned related bugs, use int.
}

int main()
{
    // calloc and malloc
    int *x = (int *)malloc(1 * sizeof(int));
    int lg = 0;
    calloc_realloc(x, lg);

    // what is
    for (int i = 0; i < 2; i++)
    {
        whatIs(x[i]);
    }

    // fast
    cout << sizeof(int_fast8_t) << endl;

    // printf
    printf("%02X\n", 0xa);
    printf("%02x\n", 0xa);

    // 1 max 32 bit - int
    printf("%d", (1 << 32));

    // // define
    // // #define n 32 faster
    // // int n = 32;
    ////////////////////////////////////
    // // uint8_t v[32]={0} creat array-> faster
    // for (int i = 0; i < n; i++)
    // {
    //     for (int j = 0; j < n; j++)
    //     {
    //         v[i]^=....
    //         res^=...
    //     }
    //     res<<1;
    // }
    ///////////////////////

    // value <<< 0x4334 ...
    // x = 0x165C;
    // pt = S_[0x165C ^ K]; // faster
    // pt = S_[x ^ K];  

    // Array  
    // for (int* arr=Arr ; arr < Arr+n; arr++) *arr .... faster
    // for (int i = 0; i < n; i++) Arr[i]
    
      
}
