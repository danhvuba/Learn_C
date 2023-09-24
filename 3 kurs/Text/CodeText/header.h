#include <iostream>
#include <math.h>
#include <fstream>
#include <string>
#include<ctime>
using namespace std;

int **NewMatrix(int);         // tao ma tran n.n
int *Xmatrix(int *, int **);  // nhan 1 hang voi ma tran
int Det(int **);              // dinh thuc
int DetAlg(int **, int, int); // algebraic complement
int **Imatrix(int **);        // ma tran nghich dao
bool Is(char);                // kiem tra ki tu
string GetText(string);       // lay text
int **CodeText(string);       // ma hoa text theo bo 3

void Nu(string);