#include <iostream>
#include <fstream>
#include <math.h>
#include <vector>
using namespace std;

bool Is(char c);                                                   // check letter
string GetText(string path);                                       // get text from file
int Count(string str, string n_gram);                              // count n_gram
void Forbidden_Gram(string str, string file_path);                 // find the forbidden n-gram
vector<float> Frequency_Bigram(string str);                        // find frequency bigram
void Out_Bigram(string str, string file_path);
float Function(string str, vector<float> bigram); // find delta by jacobsen method