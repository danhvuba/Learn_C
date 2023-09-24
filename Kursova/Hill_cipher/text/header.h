#include <iostream>
#include <cstdlib>
#include <ctime>
#include <bitset>
#include <math.h>

using namespace std;

const int n = 20; // do dai khoang xet
const int m = 3;  // so bien
const int t = pow(2, m);

void Set_Bit(bitset<n> &X, float p);
float Probability_Bit(bitset<n> X);
bitset<n> Func_filter(bitset<n> X, bitset<t> fx);
bitset<t> Func_res(bitset<n> X, bitset<n> X2, bitset<n> X3, bitset<n> X4);
