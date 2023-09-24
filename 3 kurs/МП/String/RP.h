#include <iostream>
#include <string>
#include <math.h>
using namespace std;

const int q = 101;
const int x = 2;

// хэш-функция
int Hash(string str);

// основная функция
void RP_Search(string text, string frag, int &step);