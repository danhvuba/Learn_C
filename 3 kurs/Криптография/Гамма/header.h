#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <iomanip>

using namespace std;

string Get(string str);
string Rus(string n, string *id);
void Print(vector<string> line);

vector<vector<string>> Get_text(string str);

vector<vector<int>> To_Int(vector<vector<string>> text, vector<string> tx);

string To_text(int val, vector<string> tx);