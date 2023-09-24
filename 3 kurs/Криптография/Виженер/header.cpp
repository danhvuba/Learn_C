#include "header.h"

float module(float x)
{
	if (x > 0)
	{
		return x;
	}
	return -x;
}

vector<int> GetText(string str)
{
	ifstream inp(str);
	char a;
	vector<int> res;
	while (inp.get(a))
	{
		if (((int)a >= 65) && ((int)a <= 90))
		{
			res.push_back((int)a - 65);
		}
	}
	inp.close();
	return res;
}

vector<int> Count_f(vector<int> y)
{
	vector<int> res;
	for (int i = 0; i < 26; i++)
	{
		res.push_back(0);
	}
	for (int i = 0; i < y.size(); i++)
	{
		res[y[i]]++;
	}

	return res;
}

float Icx(vector<int> y)
{
	vector<int> f = Count_f(y);
	float res = 0;
	for (int i = 0; i < f.size(); i++)
	{
		res = res + f[i] * (f[i] - 1);
	}
	return res / (y.size() * (y.size() - 1));
}

float Average_I(vector<int> y, int u)
{
	int n = y.size() / u;
	float res = 0;
	for (int i = 0; i < u; i++)
	{
		vector<int> y_i;
		for (int j = 0; j < n; j++)
		{
			y_i.push_back(y[i + j * u]);
		}
		res = res + Icx(y_i);
	}
	return res / u;
}

float MIcxy(vector<int> x, vector<int> y)
{
	vector<int> f1 = Count_f(x);
	vector<int> f2 = Count_f(y);
	float res = 0;
	for (int i = 0; i < 26; i++)
	{
		res = res + f1[i] * f2[i];
	}
	return res / (x.size() * y.size());
}

vector<int> Y_s(vector<int> y, int s)
{
	vector<int> res;
	for (int i = 0; i < y.size(); i++)
	{
		res.push_back((y[i] + s) % 26);
	}
	return res;
}

int Func_s(vector<int> y_1, vector<int> y_2)
{
	int x = 0;
	vector<int> tmp = Y_s(y_2, x);
	float delta = module(MIcxy(y_1, tmp) - 0.066);
	for (int i = 0; i < 26; i++)
	{
		tmp = Y_s(y_2, i);
		if (module(MIcxy(y_1, tmp) - 0.066) < delta)
		{
			x = i;
			delta = module(MIcxy(y_1, tmp) - 0.066);
		}
	}
	return x;
}

void Des_y(vector<vector<int>> Y, vector<int> s, int s0)
{
	cout << "\nkey= " << (char)((-1+26 - s0) % 26 + 65);////////////////// tru di 1
	for (int j = 0; j < s.size(); j++)
	{
		cout << (char)((-1 + 26 + -s0 + 26 - s[j]) % 26 + 65);
	}
	cout << endl;

	for (int i = 0; i < Y[0].size(); i++)
	{
		cout << (char)((Y[0][i] + s0) % 26 + 65);
		for (int j = 0; j < s.size(); j++)
		{
			cout << (char)((Y[j + 1][i] + s0 + 26 + s[j]) % 26 + 65);
		}
	}
	cout << endl;
}