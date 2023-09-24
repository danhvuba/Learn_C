#pragma once
#include <iostream>
#include <fstream>
#include <iomanip>
#include <math.h>
using namespace std;

bool Is(char x);                  // kiem tra ki tu
string GetText(string str);       // lay text
int CountC(string str, string x); // dem lien nhau
int Count(string str, string x);  // dem theo bo
float Out(string str, string al);
float OutBigram(string str, string al);
float OutTrigram(string str, string al);