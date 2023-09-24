#include <iostream>
#include <vector>
#include <math.h>
#include <bitset>

using namespace std;

const int n = 4;
const int l = pow(2, n);

vector<float> BPF(vector<float> f, vector<vector<float>> B);
float P_of_f(vector<float> f, vector<float> p);
float P_real_f(vector<float> f, vector<float> p);
float Func_f_p(vector<float> f, float p);
