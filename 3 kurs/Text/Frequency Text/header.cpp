#include "header.h"
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

// int CountC(string str, string x)
// {
// 	int c = 0, i = 0;
// 	while (str.find(x, i) != -1)
// 	{
// 		i = str.find(x, i) + 1;
// 		c++;
// 	}
// 	return c;
// }
int Count(string str, string x)
{
	int c = 0, i = 0;
	while (str.find(x, i) != -1)
	{
		i = str.find(x, i) + x.length();
		if (i % x.length() == 0)
		{
			c++;
		}
	}
	return c;
}

float Out(string str, string al)
{
	float x, H = 1;
	cout << setw(5) << "Алфабит" << setw(20) << "Frequency " << endl;
	cout << "----------------------------------------------------------" << endl;
	for (int i = 0; i < al.length(); i++)
	{
		string s;
		s.push_back(al[i]);
		x = static_cast<float>(Count(str, s)) / str.length();
		H = H * pow(x, -x);
		cout << setw(5) << al[i] << setw(20) << roundf(10000 * x) / 100 << endl;
	}
	cout << "\nH(ξ)= " << log(H) / log(2) << endl;
	cout << "----------------------------------------------------------" << endl;
	return log(H) / log(2);
}

float OutBigram(string str, string al)
{
	fstream III;
	III.open("out.txt");
	float x, H1 = 1;
	cout << setw(5) << "Биграм" << setw(20) << "Frequency " << endl;
	cout << "----------------------------------------------------------" << endl;
	for (int i = 0; i < al.length(); i++)
	{
		string s;
		s.push_back(al[i]);
		for (int j = 0; j < al.length(); j++)
		{
			x = static_cast<float>(2 * Count(str, s + al[j])) / str.length();
			H1 = H1 * pow(x, -x);
			if ((x * str.length()) >=0)
			{
				III << roundf(1000000 * x) / 1000000 << endl; // setw(5) << s + al[j] << setw(20) <<endl			}
			}
		}
		cout << "\nH(η)= " << log(H1) / log(2) << endl; //<<"\nH(η)/2=  "<<log(H1)/log(2)/2<<endl;
		cout << "----------------------------------------------------------" << endl;
		
	}
	return log(H1) / log(2);
}
float OutTrigram(string str, string al)
{
	fstream II;
	II.open("out2.txt");
	float x, H1 = 1;
	cout << setw(5) << "Триграм" << setw(20) << "Frequency " << endl;
	cout << "----------------------------------------------------------" << endl;
	for (int i = 0; i < al.length(); i++)
	{
		string s;
		s.push_back(al[i]);
		for (int j = 0; j < al.length(); j++)
		{
			for (int k = 0; k < al.length(); k++)
			{
				x = static_cast<float>(3 * Count(str, s + al[j] + al[k])) / str.length();
				H1 = H1 * pow(x, -x);
				if ((x * str.length()) >=0)
				{
					II <<roundf(1000000 * x) / 1000000 << endl; //setw(5) << s + al[j] + al[k] << setw(20) <<endl;
				}
			}
		}
	}
	cout << "\nH(ζ)= " << log(H1) / log(2) << endl; //<<"\nH(ζ/3= "<<log(H1)/log(2)/3<<endl;
	cout << "----------------------------------------------------------" << endl;
	return log(H1) / log(2);
}