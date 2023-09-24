//#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

float module(float x);

vector<int> GetText(string str);    // lay text va chuyen ve dang 0-26
vector<int> Count_f(vector<int> y); // dem so lan xuat hien cac so 0-26

float Icx(vector<int> y);
float Average_I(vector<int> y, int u);

float MIcxy(vector<int> x, vector<int> y);
vector<int> Y_s(vector<int> y, int s); // сдвиг s
int Func_s(vector<int> y_1, vector<int> y_2);

void Des_y(vector<vector<int>> Y, vector<int> s, int s0);