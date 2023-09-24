#include "header.h"

int **NewMatrix(int n)
{
	int **X = new int *[n];
	for (int i = 0; i < n; i++)
	{
		X[i] = new int[n]{0};
	}
	return X;
}

int *Xmatrix(int *C, int **A)
{
	int *X = new int[3]{0};
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			X[i] = (X[i] + C[j] * A[j][i]) % 26;
		}
	}
	return X;
}

int Det(int **A)
{
	int x = A[0][0] * A[1][1] * A[2][2] + A[0][1] * A[1][2] * A[2][0] + A[0][2] * A[1][0] * A[2][1] - A[0][2] * A[1][1] * A[2][0] - A[0][0] * A[1][2] * A[2][1] - A[0][1] * A[1][0] * A[2][2] + 1000 * 26;
	return (x % 26);
}

int DetAlg(int **A, int m, int n)
{
	int **X = NewMatrix(2);
	int p = 0, q = 0;
	for (int i = 0; i < 3; i++)
	{
		if (i != n)
		{
			for (int j = 0; j < 3; j++)
			{
				if (j != m)
				{
					X[p][q] = A[i][j];
					q = (q + 1) % 2;
				}
			}
			p++;
		}
	}
	return ((X[0][0] * X[1][1] - X[1][0] * X[0][1]) * (int)pow(-1, m + n) + 2600) % 26;
}

int **Imatrix(int **A)
{
	int **B = NewMatrix(3);
	int x = Det(A);
	for (int i = 0; i < 26; i++)
	{
		if ((i * x) % 26 == 1)
		{
			x = i;
			break;
		}
	}

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			B[i][j] = (DetAlg(A, i, j) * x) % 26;
		}
	}
	return B;
}

bool Is(char x)
{
	if ((((int)x >= 65) && ((int)x <= 90)) || (((int)x >= 97) && ((int)x <= 122))) // || (x == ' '))
	{
		return true;
	}
	else
		return false;
}

string GetText(string path)
{
	string str;
	fstream input;
	input.open(path);
	if (input.fail())
	{
		cout << "can't open" << endl;
	}
	char a;
	while (input.get(a))
	{
		if (Is(a))
		{
			if (((int)a >= 65) && ((int)a <= 90))
			{
				str = str + (char)((int)a + 32);
			}
			else
				str = str + a;
		}
	}
	input.close();
	return str;
}

int **CodeText(string str)
{
	int lg = str.length() / 3;
	int **C = new int *[lg];
	for (int i = 0; i < lg; i++)
	{
		C[i] = new int[3];
	}
	int n = 0, m = 0;

	for (int i = 0; i < str.length(); i++)
	{
		int x = (int)str[i] - 97;
		C[n][m] = x;
		m++;
		if (m == 3)
		{
			m = 0;
			n++;
		}
	}
	return C;
}

void Nu(string str)
{
	string al;
	int lg = str.length();
	cout << "Nμ= [ ";
	for (int i = 97; i < 123; i++)
	{
		int count = 0;
		for (int j = 0; j < lg; j++)
		{
			if ((char)i == str[j])
			{
				count++;
			}
		}
		cout << count << " ";
	}
	cout << "];  N= " << lg << endl;
}