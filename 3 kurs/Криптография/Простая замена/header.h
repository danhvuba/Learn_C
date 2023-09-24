//#pragma once
#include <iostream>
#include <fstream>
#include <iomanip>
#include <math.h>
#include <string>
using namespace std;

void SortArray(string *A, int a, int b);
string Rus(string n, string *id);
bool Yes(string *S, string k);

string GetText(string str);
int Cout(string str, string x);
void Out(string str, string *al, int n);
void OutBigram(string str, string *al, int n);
void OutTrigram(string str, string *al, int n);