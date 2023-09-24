#include <iostream>
#include <math.h>
#include <bitset>

using namespace std;

const int n = 8;
const int k = n / 2;
const int l = pow(2, n);
const int m = pow(2, k);

int *BPF(int *f, int **B);
int *Waf(int *f);
int k_correc(int *W);
int *res(int *f);

bool Is_bent(int *f);
