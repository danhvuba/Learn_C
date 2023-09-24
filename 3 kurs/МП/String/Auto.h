#include <iostream>
#include <string>
using namespace std;

// вычисление значения автомата
int AutoFunction(string frag, int val, char c, int &step);

// основная функция
void Search(string text, string frag, int &step);