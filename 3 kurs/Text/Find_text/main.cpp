#include <iostream>
#include<fstream>
using namespace std;

int main()
{
    setlocale(LC_ALL, "Russian");
    fstream input;
	input.open("input.txt");                 // открыть входный файл : input.txt
	if (input.fail())                        // контролировать входный файл
	{
		cout << "cannot open file" << endl;
		return -1;
	}
	string x;                                // это string содержить все текст из входного файла
	char a;                                  // это просто char
	while (input.get(a))                     // взять все текст из входного файла по одному символу
	{
		x = x + a;
	}
	input.close();                           // закрыть входный файл
       //Взять текст из исходного файла, и копировать в string x

	fstream output;                          // открыть выходный файл : output.txt
	output.open("output.txt");
	if (output.fail())                       // контролировать выходный файл
	{
		cout << "cannot open file" << endl;
		return -2;
	}

	fstream pretext;
	pretext.open("pretext.txt");              // pretext.txt содержит все предлоги на русском языке
	if (output.fail())
	{
		cout << "cannot open file" << endl;
		return -3;
	}
	string str;
	while (pretext.get(a))
	{
		str = str + a;
	}
	pretext.close();                          // копировать все предлоги в string str



	int i = 1;                               // индекс показать положение указатели в string: str
	while (i < str.length())
	{
		int j;                               // индекс показать положение " " в string: str
		j = str.find(" ", i);
		string var;                          // это string содержить только один предлог
		int number=0;                        // индекс показать количество повторений предлога
		if (j != -1)
		{
			var.assign(str, i-1, j - i+1);       // взять один предлог из str
			int q;                           // индекс показать положение слова в x ( текст из входного файла)
			q = x.find(var, 0);
			if (q != -1)                     // если найдено предлог в x
			{
					number = number + 1;
					while (q != -1)              // дальше найти количество повторений
					{
						int p;                   // индекс показать положение, где найдено повторение
						p = x.find(var, q + 1);
						if (p != -1)             // если найдено
						{
							number = number + 1;
							q = p;
						}
						else break;              // если нет поовторении то выходить
					}
					output << number << var << endl;    // выводить количество и предлог в выходный файл
			}
		}
		else break;             // выходить когда уже проверял все предлог
		i = j + 1;                            // увиличить и проверять следующий предлог
	}


	output<<"ыыыы";
}
