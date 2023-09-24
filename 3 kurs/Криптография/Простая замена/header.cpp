#include "header.h"

string GetText(string x)
{
	ifstream inp(x);
	char a;
	string str;
	while (inp.get(a))
	{
		str = str + a;
	}
	inp.close();
	return str;
}

int Cout(string str, string x)
{
	int c = 0, i = 0;
	while (str.find(x, i) != -1)
	{
		i = str.find(x, i) + 1;
		c++;
	}
	return c;
}

void Out(string str, string *al, int n)
{
	float x;
	cout << setw(5) << "ALPHABET" << setw(50) << "FREQUENCY %" << endl;
	cout << "----------------------------------------------------------" << endl;
	for (int i = 0; i < n; i++)
	{
		x = Cout(str, al[i]);
		cout << setw(5) << al[i] << setw(50) << x << endl;
	}
	cout << "----------------------------------------------------------" << endl;
}

void OutBigram(string str, string *al, int n)
{
	float x;
	cout << setw(5) << "BIGRAM" << setw(50) << "FREQUENCY %" << endl;
	cout << "----------------------------------------------------------" << endl;
	for (int i = 0; i < n; i++)
	{

		for (int j = 0; j < n; j++)
		{
			x = Cout(str, al[i] + " " + al[j]);
			if (x > 5)
			{
				cout << setw(5) << al[i] + " " + al[j] << setw(50) << x << endl;
			}
		}
	}
	cout << "----------------------------------------------------------" << endl;
}

void OutTrigram(string str, string *al, int n)
{
	float x;
	cout << setw(5) << "TRIGRAM" << setw(50) << "FREQUENCY %" << endl;
	cout << "----------------------------------------------------------" << endl;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			for (int k = 0; k < n; k++)
			{
				x = Cout(str, al[i] + " " + al[j] + " " + al[k]);
				if (x > 2)
				{
					cout << setw(5) << al[i] + " " + al[j] + " " + al[k] << setw(50) << x << endl;
				}
			}
		}
	}
	cout << "----------------------------------------------------------" << endl;
}

void SortArray(string *A, int a, int b)
{
	string tmp;
	int j;
	for (int i = a; i < b; i++)
	{
		tmp = A[i];
		for (int j = i - 1; (j > a - 1) && (A[j] > tmp); j--)
		{
			A[j + 1] = A[j];
			A[j] = tmp;
		}
	}
}

bool Yes(string *S, string k)
{
	for (int i = 0; i < 30; i++)
	{
		if (S[i] == k)
		{
			return false;
		}
	}
	return true;
}

string Rus(string n, string *id)
{
	if (n == id[0])
	{
		return "а";
	}
	if (n == id[1])
	{
		return "б";
	}
	if (n == id[2])
	{
		return "в";
	}
	if (n == id[3])
	{
		return "г";
	}
	if (n == id[4])
	{
		return "д";
	}
	if (n == id[5])
	{
		return "е";
	}
	if (n == id[6])
	{
		return "ж";
	}
	if (n == id[7])
	{
		return "з";
	}
	if (n == id[8])
	{
		return "и";
	}
	if (n == id[9])
	{
		return "й";
	}
	if (n == id[10])
	{
		return "к";
	}
	if (n == id[11])
	{
		return "л";
	}
	if (n == id[12])
	{
		return "м";
	}
	if (n == id[13])
	{
		return "н";
	}
	if (n == id[14])
	{
		return "о";
	}
	if (n == id[15])
	{
		return "п";
	}
	if (n == id[16])
	{
		return "р";
	}
	if (n == id[17])
	{
		return "с";
	}
	if (n == id[18])
	{
		return "т";
	}
	if (n == id[19])
	{
		return "у";
	}
	if (n == id[20])
	{
		return "ф";
	}
	if (n == id[21])
	{
		return "х";
	}
	if (n == id[22])
	{
		return "ц";
	}
	if (n == id[23])
	{
		return "ч";
	}
	if (n == id[24])
	{
		return "ш";
	}
	if (n == id[25])
	{
		return "щ";
	}
	if (n == id[26])
	{
		return "ъ";
	}
	if (n == id[27])
	{
		return "ы";
	}
	if (n == id[28])
	{
		return "ь";
	}
	if (n == id[29])
	{
		return "э";
	}
	if (n == id[30])
	{
		return "ю";
	}
	if (n == id[31])
	{
		return "я";
	}
	if (n == id[32])
	{
		return " ";
	}
	return n;
}