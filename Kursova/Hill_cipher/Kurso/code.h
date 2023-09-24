#include <iostream>
#include <math.h>
#include <fstream>
#include <string>
#include <vector>
#include "matrix.h"
using namespace std;

int **CodeText(string str);                      // encrypt text in sets of 3
string Encryption(string str, Matrix &Key);      // encryption of text                 // o day thi khong can vi khong co return, va ben trong can thao tac tiep
string Decryption(string str_code, Matrix &Key); // decryption of code
bool Is_Text(string str);