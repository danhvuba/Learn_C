#include "code.h"

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
		int x = (int)str[i] - 65;
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

string Encryption(string str, Matrix &Key)
{
	// bo sung phan thieu bang "A"
	int x = str.length() % 3;
	if (x != 0)
	{
		for (int i = 0; i < (3 - x); i++)
		{
			str = str + 'A';
		}
	}
	// them trigram luu so chu thua
	str = str + (char)(3 - x + 65) + 'A' + 'A';
	int lg = str.length() / 3;

	// chuyen sang dang code bo 3
	int **C = CodeText(str);
	// ma hoa bang key
	for (int i = 0; i < lg; i++)
	{
		C[i] = Key.Xmatrix(C[i]);
	}

	// chuyen va text
	string code;
	for (int i = 0; i < lg; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			code.push_back((char)(C[i][j] + 65));
		}
	}
	return code;
}

string Decryption(string str_code, Matrix &Key)
{
	int lg = str_code.length() / 3;
	// giai ma
	int **C = CodeText(str_code);
	Matrix A(Key.Inverse_matrix());
	for (int i = 0; i < lg; i++)
	{
		C[i] = A.Xmatrix(C[i]);
	}

	// chuyen ve text theo quy tac
	string text;
	for (int i = 0; i < lg - 1; i++)
	{
		if (i < (lg - 2))
		{
			for (int j = 0; j < 3; j++)
			{
				text.push_back((char)(C[i][j] + 65));
			}
		}
		else
		{
			for (int j = 0; j < (3 - C[lg - 1][0]); j++)
			{
				text.push_back((char)(C[i][j] + 65));
			}
		}
	}
	return text;
}

bool Is_Text(string str)
{
	fstream Input;
	Input.open("forbidden.txt");
	string x;
	getline(Input, x);
	while (x != "")
	{
		int val = str.find(x);
		if ((val < str.size()) && (val % x.size() == 0))
		{
			return false;
		}
		getline(Input, x);
	}
	return true;
}
