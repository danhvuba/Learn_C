#include <iostream>
#include <string>
using namespace std;

// вычисление массива плохих символов
int *preBmBc(string frag, int &step);

// вычисление длинны суфикса
int suffixLength(string frag, int p);
// вычисление массива хороших символов
int *preBmGs(string frag, int &step);

// основная функция
void BM_Search(string text, string str, int &step);

int Max(int a, int b);
